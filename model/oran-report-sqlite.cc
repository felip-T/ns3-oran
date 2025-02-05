#include "oran-report-sqlite.h"
#include "ns3/log.h"

namespace ns3
{

NS_LOG_COMPONENT_DEFINE("OranReportSqlite");

NS_OBJECT_ENSURE_REGISTERED(OranReportSqlite);

TypeId OranReportSqlite::GetTypeId(void)
{
    static TypeId tid = TypeId("ns3::OranReportSqlite")
                            .SetParent<OranReport>()
                            .AddConstructor<OranReportSqlite>();
    return tid;
}

OranReportSqlite::OranReportSqlite() : OranReport()
{
    m_tableInfo.emplace_back("nodeid", "INTEGER");
    m_tableInfo.emplace_back("time", "INTEGER");
    NS_LOG_FUNCTION(this);
}

OranReportSqlite::~OranReportSqlite()
{
    NS_LOG_FUNCTION(this);
}

std::vector<std::tuple<std::string, std::string>>
OranReportSqlite::GetTableInfo()
{
    NS_LOG_FUNCTION(this);
    return m_tableInfo;
}

} // namespace ns3
