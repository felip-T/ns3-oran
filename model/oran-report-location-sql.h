#ifndef ORAN_REPORT_LOCATION_SQL_H
#define ORAN_REPORT_LOCATION_SQL_H

#include "oran-report-sql.h"

#include <ns3/object.h>
#include <ns3/vector.h>

#include <string>

namespace ns3
{
class OranReportLocationSql : public OranReportSql
{
  public:
    static TypeId GetTypeId(void);
    OranReportLocationSql(void);
    ~OranReportLocationSql(void) override;
    std::string ToString(void) const override;
    std::vector<std::tuple<std::string, std::string>> GetTableInfo() override;
    std::string GetTableName() override;

  private:
    Vector m_location;

  public:
    Vector GetLocation(void) const;
}; // class OranReportLocation

} // namespace ns3

#endif /* ORAN_REPORT_LOCATION_H */
