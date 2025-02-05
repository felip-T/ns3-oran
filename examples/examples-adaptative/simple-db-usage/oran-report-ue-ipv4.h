#ifndef ORAN_REPORT_UE_IPV4_H
#define ORAN_REPORT_UE_IPV4_H

#include <ns3/oran-report-sqlite.h>

#include <ns3/object.h>
#include <ns3/vector.h>

#include <string>

namespace ns3
{
class OranReportUeIpv4 : public OranReportSqlite
{
  public:
    static TypeId GetTypeId();
    OranReportUeIpv4();
    ~OranReportUeIpv4() override;
    std::string ToString() const override;
    std::vector<std::tuple<std::string, std::string>> GetTableInfo() override;
    std::string GetTableName() override;
    std::string GetIpv4();

  private:
    std::string m_ipv4;

  public:
    std::string GetIpv4() const;
};

} // namespace ns3

#endif
