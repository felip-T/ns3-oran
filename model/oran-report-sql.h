#ifndef ORAN_REPORT_SQL_H
#define ORAN_REPORT_SQL_H

#include "oran-report.h"

namespace ns3 {
class OranReportSql : public OranReport
{
public:
    OranReportSql();
    ~OranReportSql() override;

    static TypeId GetTypeId();

    virtual std::vector<std::tuple<std::string, std::string>> GetTableInfo();
    virtual std::string GetTableName(){return "";}

protected:
    std::vector<std::tuple<std::string, std::string>> m_tableInfo;
};
} // namespace ns3
#endif /* ORAN_REPORT_SQL_H */
