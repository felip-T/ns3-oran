#ifndef ORAN_REPORT_SINR_UE_SQL_H
#define ORAN_REPORT_SINR_UE_SQL_H

#include <ns3/oran-report-sqlite.h>

#include <ns3/object.h>
#include <ns3/vector.h>

#include <string>

namespace ns3
{
class OranReportSinrUeSql : public OranReportSqlite
{
  public:
    static TypeId GetTypeId();
    OranReportSinrUeSql();
    ~OranReportSinrUeSql() override;
    std::string ToString() const override;
    std::vector<std::tuple<std::string, std::string>> GetTableInfo() override;
    std::string GetTableName() override;

  private:
    uint64_t m_ueId;
    uint64_t m_cellId;
    double m_sinr;
    double m_rsrp;
    uint64_t m_rnti;

  public:
    double GetSinr() const;
    double GetRsrp() const;
};

} // namespace ns3

#endif
