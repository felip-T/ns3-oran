#include "oran-report-sql.h"
#include "ns3/log.h"

namespace ns3
{

NS_LOG_COMPONENT_DEFINE("OranReportSql");

NS_OBJECT_ENSURE_REGISTERED(OranReportSql);

TypeId OranReportSql::GetTypeId(void)
{
    static TypeId tid = TypeId("ns3::OranReportSql")
                            .SetParent<OranReport>()
                            .AddConstructor<OranReportSql>();
    return tid;
}

OranReportSql::OranReportSql() : OranReport()
{
    m_tableInfo.emplace_back("nodeid", "INTEGER");
    m_tableInfo.emplace_back("time", "INTEGER");
    NS_LOG_FUNCTION(this);
}

OranReportSql::~OranReportSql()
{
    NS_LOG_FUNCTION(this);
}

std::vector<std::tuple<std::string, std::string>>
OranReportSql::GetTableInfo()
{
    NS_LOG_FUNCTION(this);
    return m_tableInfo;
}

} // namespace ns3
