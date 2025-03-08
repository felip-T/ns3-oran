#include "oran-logic-module-train-ml-handover.h"

#include "open-gym.h"

#include <ns3/abort.h>
#include <ns3/log.h>
#include <ns3/lte-module.h>
#include <ns3/pointer.h>
#include <ns3/simulator.h>
#include <ns3/uinteger.h>
#include <typeinfo>

#include <cfloat>

	namespace ns3 {

	NS_LOG_COMPONENT_DEFINE("OranLmCustomHandover");

	NS_OBJECT_ENSURE_REGISTERED(OranLmCustomHandover);

	TypeId OranLmCustomHandover::GetTypeId(void) {
	  static TypeId tid =
	      TypeId("ns3::OranLmCustomHandover")
		  .SetParent<OranLm>()
		  .AddConstructor<OranLmCustomHandover>()
		  .AddAttribute("nEnb", "Number of eNBs", UintegerValue(2),
				MakeUintegerAccessor(&OranLmCustomHandover::m_nEnb),
				MakeUintegerChecker<uint64_t>());

	  return tid;
	}

	OranLmCustomHandover::OranLmCustomHandover(void) : OranLm() {
	  NS_LOG_FUNCTION(this);

	  m_model = CreateObject<EnvOran>(2);
	  m_name = "OranLmCustomHandover";
	}

	OranLmCustomHandover::~OranLmCustomHandover(void) { NS_LOG_FUNCTION(this); }

	std::vector<Ptr<OranCommand>> OranLmCustomHandover::Run(void) {
	  NS_LOG_FUNCTION(this);

	  std::vector<Ptr<OranCommand>> commands;

	  if (m_active) {
	    NS_ABORT_MSG_IF(m_nearRtRic == nullptr, "Attempting to run LM (" + m_name +
							") with NULL Near-RT RIC");

	    Ptr<OranDataRepository> data = m_nearRtRic->Data();
	    Ptr<OranAdaptativeSqlite> db = data->GetObject<OranAdaptativeSqlite>();
	    auto reportt = db->GetLastReport("nodeapploss");
	    // for (auto rep : reportt) {
	    //   std::cout << rep.first << " " << rep.second << std::endl;
	    // }
	    std::string id = reportt["nodeid"];
	    if (id.size() != 0) {
	      try {
		UeInfo ueInfo = GetUeInfos(data, std::stoul(id, nullptr, 0)).at(0);
		std::vector<UeInfo> ueInfos = GetAllUeInfos(data);
		// std::cout << "INFOS" << std::endl;
		// for (auto ue : ueInfos) {
		//   std::cout << ue.nodeId << std::endl;
		// }
		std::vector<EnbInfo> enbInfos = GetEnbInfos(data);
		commands = GetHandoverCommands(data, ueInfos, enbInfos, ueInfo);
	      } catch (...) {
					// std::cout << "ERROR: " << id << std::endl;
	      }
	    }
	  }

	  // Return the commands.
	  return commands;
	}

	std::vector<OranLmCustomHandover::UeInfo>
	OranLmCustomHandover::GetUeInfos(Ptr<OranDataRepository> data,
					 uint64_t ueId) const {
	  NS_LOG_FUNCTION(this << data);

	  Ptr<OranAdaptativeSqlite> db = DynamicCast<OranAdaptativeSqlite>(data);

	  std::vector<UeInfo> ueInfos;

	  UeInfo ueInfo;
	  ueInfo.nodeId = ueId;
	  // Get the current cell ID and RNTI of the UE and record it.
	  bool found;
	  std::tie(found, ueInfo.cellId, ueInfo.rnti) =
	      db->GetLteUeCellInfo(ueInfo.nodeId);
	  if (found) {
	    // Get the latest location of the UE.
	    std::map<Time, Vector> nodePositions =
		db->GetNodePositions(ueInfo.nodeId, Seconds(0), Simulator::Now());

	    if (!nodePositions.empty()) {
	      // We found both the cell and location informtaion for this UE
	      // so record it for a later analysis.
	      double apploss;
	      double sinr = -1000;

	      try {
		apploss = db->GetAppLoss(ueInfo.nodeId);
		std::string query =
		    "SELECT sinr FROM sinr WHERE ueid = " + std::to_string(ueId) +
		    " ORDER BY time DESC LIMIT 1";
		sinr = std::stod(db->GetCustomQuery(query)["SINR"]);
	      } catch (...) {
		apploss = -1;
	      }

	      if (apploss != -1) {
		ueInfo.apploss = apploss;
		ueInfo.sinr = sinr;
		ueInfo.position = nodePositions.rbegin()->second;
		ueInfos.push_back(ueInfo);
	      }
	    } else {
	      NS_LOG_INFO(
		  "Could not find LTE UE location for E2 Node ID = " << ueInfo.nodeId);
	    }
	  } else {
	    NS_LOG_INFO(
		"Could not find LTE UE cell info for E2 Node ID = " << ueInfo.nodeId);
	  }
	  return ueInfos;
	}

	std::vector<OranLmCustomHandover::EnbInfo>
	OranLmCustomHandover::GetEnbInfos(Ptr<OranDataRepository> data) const {
	  NS_LOG_FUNCTION(this << data);

	  std::vector<EnbInfo> enbInfos;
	  for (auto enbId : data->GetLteEnbE2NodeIds()) {
	    EnbInfo enbInfo;
	    enbInfo.nodeId = enbId;
	    // Get the cell ID of this eNB and record it.
	    bool found;
	    std::tie(found, enbInfo.cellId) = data->GetLteEnbCellInfo(enbInfo.nodeId);
	    if (found) {
	      // Get all known locations of the eNB.
	      std::map<Time, Vector> nodePositions =
		  data->GetNodePositions(enbInfo.nodeId, Seconds(0), Simulator::Now());

	      if (!nodePositions.empty()) {
		// We found both the cell and location information for this
		// eNB so record it for a later analysis.
		enbInfo.position = nodePositions.rbegin()->second;
		enbInfos.push_back(enbInfo);
	      } else {
		NS_LOG_INFO("Could not find LTE eNB location for E2 Node ID = "
			    << enbInfo.nodeId);
	      }
	    } else {
	      NS_LOG_INFO("Could not find LTE eNB cell info for E2 Node ID = "
			  << enbInfo.nodeId);
	    }
	  }
	  return enbInfos;
	}

	std::vector<Ptr<OranCommand>> OranLmCustomHandover::GetHandoverCommands(
	    Ptr<OranDataRepository> data,
	    std::vector<OranLmCustomHandover::UeInfo> ueInfos,
	    std::vector<OranLmCustomHandover::EnbInfo> enbInfos,
	    OranLmCustomHandover::UeInfo ueInfo) const {
	  NS_LOG_FUNCTION(this << data);

	  std::vector<Ptr<OranCommand>> commands;

	  double allApploss = 0;
	  for (size_t i = 0; i < ueInfos.size(); i++) {
	    allApploss += ueInfos[i].apploss;
	    // std::cout << "allApploss: " << allApploss << std::endl;
	    // std::ofstream logger("logs.txt", std::ios::app);
	    // if (logger.is_open()) {
	    //   logger << allApploss << '\n';
	    // }
	    // logger.close();
	  }
	  allApploss /= ueInfos.size();
	  // std::cout << "allApploss total: " << allApploss << std::endl;

	  // double min = DBL_MAX;               // The minimum distance recorded.
	  uint64_t oldCellNodeId;
	  uint16_t newCellId = -1;
	  std::vector<double> dists;
	  for (const auto &enbInfo : enbInfos) {
	    double dist =
		std::sqrt(std::pow(ueInfo.position.x - enbInfo.position.x, 2) +
			  std::pow(ueInfo.position.y - enbInfo.position.y, 2) +
			  std::pow(ueInfo.position.z - enbInfo.position.z, 2));

	    dists.push_back(dist);

	    if (ueInfo.cellId == enbInfo.cellId) {
	      oldCellNodeId = enbInfo.nodeId;
	    }
	  }

	  bool hand = false;

	  for (auto a : m_enbDevs) {
	    auto cell = a->GetCellId();
	    if (ueInfo.cellId == cell) {
	      hand = DynamicCast<LteEnbRrc>(a->GetRrc())->HasUeManager(ueInfo.rnti);
	    }
	  }

	  if (hand) {
	    Ptr<OpenGymBoxContainer<double>> observation =
		CreateObject<OpenGymBoxContainer<double>>();
	    // observation->AddValue(ueInfo.cellId);
	    observation->AddValue(ueInfo.apploss);
	    observation->AddValue(log10(ueInfo.sinr)/5);
    for (auto dist : dists) {
      observation->AddValue(dist / (sqrt(2) * 100));
    }

    std::cout << "Model observation: (apploss | log10(SINR)/5 | dist eNB 1 | dist eNB 2):" <<std::endl << observation << std::endl;
    m_model->SetObservation(observation);
    m_model->m_reward = 1 - allApploss;
    m_model->Notify();

    newCellId = m_model->m_action+1;
  }

  if (newCellId != ueInfo.cellId) {
    if (hand) {
      Ptr<OranCommandLte2LteHandover> handoverCommand =
          CreateObject<OranCommandLte2LteHandover>();
      handoverCommand->SetAttribute("TargetE2NodeId",
                                    UintegerValue(oldCellNodeId));
      handoverCommand->SetAttribute("TargetRnti", UintegerValue(ueInfo.rnti));
      handoverCommand->SetAttribute("TargetCellId", UintegerValue(newCellId));
      data->LogCommandLm(m_name, handoverCommand);
      commands.push_back(handoverCommand);
    }
    // else
    // {
    //     std::cout << "FAIL nodeID: " << ueInfo.nodeId << std::endl;
    // }
  }
  return commands;
}

void OranLmCustomHandover::EndSimulation() {
  std::cout << "simulation end" << std::endl;
  Ptr<OpenGymBoxContainer<double>> observation =
        CreateObject<OpenGymBoxContainer<double>>();
  observation->AddValue(0);
  observation->AddValue(0);
  observation->AddValue(0);
  observation->AddValue(0);
  m_model->SetObservation(observation);
  m_model->m_reward=1;
  m_model->Notify();
  m_model->NotifySimulationEnd();
}

void OranLmCustomHandover::SetEnbDevs(
    std::vector<Ptr<LteEnbNetDevice>> enbDevs) {
  m_enbDevs = enbDevs;
}

std::vector<OranLmCustomHandover::UeInfo>
OranLmCustomHandover::GetAllUeInfos(Ptr<OranDataRepository> data) const {
  NS_LOG_FUNCTION(this << data);

  Ptr<OranAdaptativeSqlite> db = DynamicCast<OranAdaptativeSqlite>(data);

  std::vector<UeInfo> ueInfos;
  for (auto ueId : db->GetLteUeE2NodeIds()) {
    UeInfo ueInfo;
    ueInfo.nodeId = ueId;
    // Get the current cell ID and RNTI of the UE and record it.
    bool found;
    std::tie(found, ueInfo.cellId, ueInfo.rnti) =
        db->GetLteUeCellInfo(ueInfo.nodeId);
    if (found) {
      // Get the latest location of the UE.
      std::map<Time, Vector> nodePositions =
          db->GetNodePositions(ueInfo.nodeId, Seconds(0), Simulator::Now());

      if (!nodePositions.empty()) {
        // We found both the cell and location informtaion for this UE
        // so record it for a later analysis.
        double apploss;
        double sinr = -1000;

        try {
          apploss = db->GetAppLoss(ueInfo.nodeId);
          std::string query =
              "SELECT sinr FROM sinr WHERE ueid = " + std::to_string(ueId) +
              " ORDER BY time DESC LIMIT 1";
          sinr = std::stod(db->GetCustomQuery(query)["SINR"]);
        } catch (...) {
          apploss = -1;
        }

        if (apploss != -1) {
          ueInfo.apploss = apploss;
          ueInfo.sinr = sinr;
          ueInfo.position = nodePositions.rbegin()->second;
          ueInfos.push_back(ueInfo);
        }
      } else {
        NS_LOG_INFO("Could not find LTE UE location for E2 Node ID = "
                    << ueInfo.nodeId);
      }
    } else {
      NS_LOG_INFO(
          "Could not find LTE UE cell info for E2 Node ID = " << ueInfo.nodeId);
    }
  }
  return ueInfos;
}

} // namespace ns3
