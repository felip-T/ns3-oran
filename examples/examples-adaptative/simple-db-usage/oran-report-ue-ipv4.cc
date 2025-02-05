#include "oran-report-ue-ipv4.h"

#include <ns3/double.h>
#include <ns3/log.h>
#include <ns3/string.h>
#include <ns3/uinteger.h>

namespace ns3
{

NS_LOG_COMPONENT_DEFINE("OranReportUeIpv4");

NS_OBJECT_ENSURE_REGISTERED(OranReportUeIpv4);

TypeId
OranReportUeIpv4::GetTypeId()
{
    static TypeId tid = TypeId("ns3::OranReportUeIpv4")
                            .SetParent<OranReportSqlite>()
                            .AddConstructor<OranReportUeIpv4>()
                            .AddAttribute("ipv4",
                                          "Actual ue upv4",
                                          StringValue(),
                                          MakeStringAccessor(&OranReportUeIpv4::m_ipv4),
                                          MakeStringChecker());

    return tid;
}

OranReportUeIpv4::OranReportUeIpv4()
    : OranReportSqlite()
{
    m_tableInfo.emplace_back("ipv4", "TEXT");
    NS_LOG_FUNCTION(this);
}

OranReportUeIpv4::~OranReportUeIpv4()
{
    NS_LOG_FUNCTION(this);
}

std::string
OranReportUeIpv4::ToString() const
{
    NS_LOG_FUNCTION(this);

    std::stringstream ss;
    Time time = GetTime();

    ss << "OranReportIpv4("
       << "nodeid=" << GetReporterE2NodeId() << ";time=" << time.GetTimeStep() 
       << ";ipv4=" << "\"" << m_ipv4 << "\"" << ")";

    return ss.str();
}

std::string
OranReportUeIpv4::GetIpv4() const
{
    NS_LOG_FUNCTION(this);

    return m_ipv4;
}

std::vector<std::tuple<std::string, std::string>>
OranReportUeIpv4::GetTableInfo()
{
    NS_LOG_FUNCTION(this);
    return m_tableInfo;
}

std::string
OranReportUeIpv4::GetTableName()
{
    NS_LOG_FUNCTION(this);
    return "UeIpv4";
}
} // namespace ns3
