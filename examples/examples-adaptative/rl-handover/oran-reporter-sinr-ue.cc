#include "oran-reporter-sinr-ue.h"

namespace ns3
{

NS_LOG_COMPONENT_DEFINE("OranReporterSinrUe");
NS_OBJECT_ENSURE_REGISTERED(OranReporterSinrUe);

TypeId
OranReporterSinrUe::GetTypeId()
{
    static TypeId tid = TypeId("ns3::OranReporterSinrUe")
                            .SetParent<OranReporter>()
                            .AddConstructor<OranReporterSinrUe>();

    return tid;
}

OranReporterSinrUe::OranReporterSinrUe()
    : OranReporter()
{
}

OranReporterSinrUe::~OranReporterSinrUe()
{
}

void
OranReporterSinrUe::UpdateData(uint16_t cellId, double sinr, double rsrp, uint64_t rnti){
	m_sinr = sinr;
	m_rsrp = rsrp;
	m_rnti = rnti;
	m_cellId = cellId;
}

std::vector<Ptr<OranReport>>
OranReporterSinrUe::GenerateReports()
{
	std::vector<Ptr<OranReport>> reports;	

  uint64_t ueNodeId = m_terminator->GetNearRtRic()->Data()->GetLteUeE2NodeIdFromCellInfo(m_cellId, m_rnti);

  Ptr<OranReportSinrUeSql> sinrUeReport = CreateObject<OranReportSinrUeSql>();
  sinrUeReport->SetAttribute("ReporterE2NodeId",
                             UintegerValue(m_terminator->GetE2NodeId()));
  sinrUeReport->SetAttribute("ueid", UintegerValue(ueNodeId));
  sinrUeReport->SetAttribute("cellid", UintegerValue(m_cellId));
  sinrUeReport->SetAttribute("RNTI", UintegerValue(m_rnti));
  sinrUeReport->SetAttribute("SINR", DoubleValue(m_sinr));
  sinrUeReport->SetAttribute("RSRP", DoubleValue(m_rsrp));
  sinrUeReport->SetAttribute("Time", TimeValue(Simulator::Now()));

  reports.emplace_back(sinrUeReport);
  
	return reports;
}

// std::vector<std::tuple<uint64_t, uint64_t>>
// OranReporterSinrUe::GetAllRegisteredUeIds(uint64_t cellId, Ptr<OranAdaptativeSqlite> db)
// {
//     uint64_t cellIdUe;
//     uint64_t rnti;
//     std::vector<std::tuple<uint64_t, uint64_t>> ids;
//     for (auto ueId : db->GetLteUeE2NodeIds())
//     {
//         bool found;
//         std::tie(found, cellIdUe, rnti) = db->GetLteUeCellInfo(ueId);
//         if (found && cellIdUe == cellId)
//         {
//             ids.emplace_back(ueId, rnti);
//         }
//     }
//
//     return ids;
// }
} // namespace ns3
