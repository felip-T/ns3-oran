#include "oran-reporter-ue-ipv4.h"

namespace ns3
{

NS_LOG_COMPONENT_DEFINE("OranReporterUeIpv4");
NS_OBJECT_ENSURE_REGISTERED(OranReporterUeIpv4);

TypeId
OranReporterUeIpv4::GetTypeId()
{
    static TypeId tid = TypeId("ns3::OranReporterUeIpv4")
                            .SetParent<OranReporter>()
                            .AddConstructor<OranReporterUeIpv4>();

    return tid;
}

OranReporterUeIpv4::OranReporterUeIpv4()
    : OranReporter()
{
	NS_LOG_FUNCTION(this);
}

OranReporterUeIpv4::~OranReporterUeIpv4()
{
	NS_LOG_FUNCTION(this);
}

std::vector<Ptr<OranReport>>
OranReporterUeIpv4::GenerateReports()
{
    std::vector<Ptr<OranReport>> reports;
    if (m_active)
    {
        NS_ABORT_MSG_IF(m_terminator == nullptr,
                       "Attempting to generate reports in reporter with NULL E2 Terminator");

	std::stringstream ipv4String;
	ipv4String << m_terminator->GetNode()->GetObject<Ipv4>()->GetAddress(1,0).GetLocal();

        Ptr<OranReportUeIpv4> ipv4UeReport = CreateObject<OranReportUeIpv4>();
        ipv4UeReport->SetAttribute("ReporterE2NodeId",
                                   UintegerValue(m_terminator->GetE2NodeId()));
        ipv4UeReport->SetAttribute("ipv4", StringValue(ipv4String.str()));
        ipv4UeReport->SetAttribute("Time", TimeValue(Simulator::Now()));

        reports.emplace_back(ipv4UeReport);
        }
    return reports;
}
} // namespace ns3
