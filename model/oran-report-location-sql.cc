#include "oran-report-location-sql.h"


#include <ns3/log.h>
#include <ns3/uinteger.h>
#include <ns3/vector.h>
#include <ns3/string.h>

namespace ns3
{

NS_LOG_COMPONENT_DEFINE("OranReportLocationSql");

NS_OBJECT_ENSURE_REGISTERED(OranReportLocationSql);

TypeId
OranReportLocationSql::GetTypeId(void)
{
    static TypeId tid = TypeId("ns3::OranReportLocationSql")
                            .SetParent<OranReportSqlite>()
                            .AddConstructor<OranReportLocationSql>()
                            .AddAttribute("Location",
                                          "The location of the node.",
                                          VectorValue(),
                                          MakeVectorAccessor(&OranReportLocationSql::m_location),
                                          MakeVectorChecker());

    return tid;
}

OranReportLocationSql::OranReportLocationSql(void)
    : OranReportSqlite()
{
    m_tableInfo.emplace_back("x", "REAL");
    m_tableInfo.emplace_back("y", "REAL");
    m_tableInfo.emplace_back("z", "REAL");
    NS_LOG_FUNCTION(this);
}

OranReportLocationSql::~OranReportLocationSql(void)
{
    NS_LOG_FUNCTION(this);
}

std::string
OranReportLocationSql::ToString(void) const
{
    NS_LOG_FUNCTION(this);

    std::stringstream ss;
    Time time = GetTime();

    ss << "OranReportLocation("
       << "nodeid=" << GetReporterE2NodeId() << ";time=" << time.GetTimeStep()
       << ";x=" << m_location.x << ";y=" << m_location.y << ";z=" << m_location.z << ")";

    return ss.str();
}

Vector
OranReportLocationSql::GetLocation(void) const
{
    NS_LOG_FUNCTION(this);

    return m_location;
}

std::vector<std::tuple<std::string, std::string>>
OranReportLocationSql::GetTableInfo()
{
    NS_LOG_FUNCTION(this);
    return m_tableInfo;
}
std::string
OranReportLocationSql::GetTableName()
{
    NS_LOG_FUNCTION(this);
    return "location";
}
} // namespace ns3
