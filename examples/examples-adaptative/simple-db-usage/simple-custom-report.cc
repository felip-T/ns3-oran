#include <ns3/oran-module.h>
#include <ns3/lte-module.h>
#include <ns3/mobility-module.h>
#include <ns3/internet-module.h>
#include <ns3/network-module.h>
#include <iostream>

#include "oran-reporter-ue-ipv4.h"

using namespace ns3;


//Exemple on gathering data from "SQL global" database.
//This example creates a custom reporter for

void
QueryRcSink(std::string query, std::string args, int rc)
{
    std::cout << Simulator::Now().GetSeconds() << " Query "
              << ((rc == SQLITE_OK || rc == SQLITE_DONE) ? "OK" : "ERROR") << "(" << rc << "): \""
              << query << "\"";

    if (!args.empty())
    {
        std::cout << " (" << args << ")";
    }
    std::cout << std::endl;
}


int main(){
	Time simTime = Seconds(10);
	u_int16_t numberEnbs = 1;
	u_int16_t numberUes = 1;
	//CommandLine cmd;

	NodeContainer enbNodes;
	NodeContainer ueNodes;


	enbNodes.Create(numberEnbs);
	ueNodes.Create(numberUes);

	MobilityHelper mobilityEnb;
	mobilityEnb.SetMobilityModel("ns3::ConstantPositionMobilityModel");
	mobilityEnb.Install(enbNodes);
	enbNodes.Get(0)->GetObject<ConstantPositionMobilityModel>()->SetPosition(Vector(0, 0, 10));

	MobilityHelper mobilityUe;
	mobilityUe.SetMobilityModel("ns3::ConstantVelocityMobilityModel");
	mobilityUe.Install(ueNodes);
	for (u_int16_t i=0; i<numberUes; i++){
		ueNodes.Get(i)->GetObject<ConstantVelocityMobilityModel>()->SetPosition(Vector(5*(i+1), 0, 1.5));
		ueNodes.Get(i)->GetObject<ConstantVelocityMobilityModel>()->SetVelocity(Vector(5, 0, 0));
	}

	Ptr<LteHelper> lteHelper = CreateObject<LteHelper>();
	Ptr<PointToPointEpcHelper> epcHelper = CreateObject<PointToPointEpcHelper>();
	lteHelper->SetEpcHelper(epcHelper);
	InternetStackHelper internet;

	NetDeviceContainer enbLteDevs = lteHelper->InstallEnbDevice(enbNodes);
	NetDeviceContainer ueLteDevs = lteHelper->InstallUeDevice(ueNodes);
	
	//Ipv4AddressHelper ipv4h;
	//ipv4h.SetBase("1.0.0.0", "255.0.0.0");
	//Ipv4InterfaceContainer internetIpIfaces = ipv4h.Assign(ueLteDevs);


    	internet.Install(ueNodes);
    	Ipv4InterfaceContainer ueIpIface;
    	ueIpIface = epcHelper->AssignUeIpv4Address(NetDeviceContainer(ueLteDevs));


	lteHelper->AttachToClosestEnb(ueLteDevs, enbLteDevs);
	
	//Oran configuration
	Ptr<OranDataRepository> dataRep = CreateObject<OranAdaptativeSqlite>();
	Ptr<OranCmm> cmm = CreateObject<OranCmmNoop>();
	Ptr<OranNearRtRic> nearRtRic = CreateObject<OranNearRtRic>();
	Ptr<OranNearRtRicE2Terminator> nearRtRicE2Terminator = CreateObject<OranNearRtRicE2Terminator>();

	TypeId defaultLmTid = TypeId::LookupByName("ns3::OranLmNoop");
	ObjectFactory defaultLmFactory;
	defaultLmFactory.SetTypeId(defaultLmTid);
	Ptr<OranLm> defaultLm = defaultLmFactory.Create<OranLm>();
	defaultLm->SetAttribute("NearRtRic", PointerValue(nearRtRic));

	cmm->SetAttribute("NearRtRic", PointerValue(nearRtRic));

	nearRtRicE2Terminator->SetAttribute("NearRtRic", PointerValue(nearRtRic));
	nearRtRicE2Terminator->SetAttribute("DataRepository", PointerValue(dataRep));

	nearRtRic->SetAttribute("DefaultLogicModule", PointerValue(defaultLm));
	nearRtRic->SetAttribute("E2Terminator", PointerValue(nearRtRicE2Terminator));
	nearRtRic->SetAttribute("DataRepository", PointerValue(dataRep));
	nearRtRic->SetAttribute("ConflictMitigationModule", PointerValue(cmm));

	Simulator::Schedule(Seconds(0.5), &OranNearRtRic::Start, nearRtRic);

	for (uint32_t idx=0; idx < ueNodes.GetN(); idx++){
		Ptr<OranE2NodeTerminatorLteUe> lteUeTerminator = CreateObject<OranE2NodeTerminatorLteUe>();

		Ptr<OranReporterLocation> locationReporter = CreateObject<OranReporterLocation>();
		locationReporter->SetAttribute("Terminator", PointerValue(lteUeTerminator));

		Ptr<OranReporterUeIpv4> ipv4Reporter = CreateObject<OranReporterUeIpv4>();
		ipv4Reporter->SetAttribute("Terminator", PointerValue(lteUeTerminator));

		lteUeTerminator->AddReporter(locationreporter);
		lteUeTerminator->AddReporter(ipv4Reporter);

		lteUeTerminator->SetAttribute("NearRtRic", PointerValue(nearRtRic));
        	lteUeTerminator->SetAttribute("RegistrationIntervalRv",
                                      StringValue("ns3::ConstantRandomVariable[Constant=10]"));
        	lteUeTerminator->SetAttribute("SendIntervalRv",
                                      StringValue("ns3::ConstantRandomVariable[Constant=1]"));
		lteUeTerminator->Attach(ueNodes.Get(idx));

		Simulator::Schedule(Seconds(1), &OranE2NodeTerminatorLteUe::Activate, lteUeTerminator);
	}

	nearRtRic->Data()->TraceConnectWithoutContext("QueryRc", MakeCallback(&QueryRcSink));

	Simulator::Stop(simTime);
	Simulator::Run();
	Simulator::Destroy();
	return 0;
}
