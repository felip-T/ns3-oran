#ifndef ORAN_MOD_SQLITE_H
#define ORAN_MOD_SQLITE_H

#include "oran-data-repository-sqlite.h"
#include "oran-report-sql.h"

namespace ns3 {

class OranModSqlite : public OranDataRepositorySqlite
{
public:
    static TypeId GetTypeId (void);
    OranModSqlite ();
    ~OranModSqlite () override;
    void CreateReportTable(Ptr<OranReportSql>);
    void CreateReportSave(Ptr<OranReportSql>);
    std::unordered_map<std::string, std::string> GetLastReport(const std::string&);
    std::unordered_map<std::string, std::string> GetLastReport(const std::string&, uint64_t nodeId);
    std::unordered_map<std::string, std::string> GetSecondLastReport(const std::string&, uint64_t nodeId);
    std::unordered_map<std::string, std::string> GetCustomQuery(const std::string&);

protected:
    static std::string ParseReportTableInfo(Ptr<OranReportSql>);
    static std::string CreateReportSaveQuery(Ptr<OranReportSql>);
    static std::vector<std::tuple<std::string, std::string>> ParseReport(Ptr<OranReportSql>);

    std::unordered_map<std::string, bool> m_reportTableCreated;
};
}

#endif // ORAN_MOD_SQLITE_H
