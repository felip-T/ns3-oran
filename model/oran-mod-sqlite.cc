#include "oran-mod-sqlite.h"

#include <ns3/log.h>

namespace ns3
{

NS_LOG_COMPONENT_DEFINE("OranModSqlite");

NS_OBJECT_ENSURE_REGISTERED(OranModSqlite);

TypeId
OranModSqlite::GetTypeId(void)
{
    static TypeId tid = TypeId("ns3::OranModSqlite")
                            .SetParent<OranDataRepositorySqlite>()
                            .AddConstructor<OranModSqlite>();
    return tid;
}

OranModSqlite::OranModSqlite()
    : OranDataRepositorySqlite()
{
    NS_LOG_FUNCTION(this);
}

OranModSqlite::~OranModSqlite()
{
    NS_LOG_FUNCTION(this);
}

void
OranModSqlite::CreateReportTable(Ptr<OranReportSql> report)
{
    NS_LOG_FUNCTION(this << report);
    if (!m_reportTableCreated[report->GetTableName()]){
        std::string stmt = ParseReportTableInfo(report);
        RunCreateStatement(stmt);
        m_reportTableCreated[report->GetTableName()] = true;
    }
}

std::string
OranModSqlite::ParseReportTableInfo(Ptr<OranReportSql> report)
{
    NS_LOG_FUNCTION(report);
    std::string stmt = "CREATE TABLE IF NOT EXISTS " + report->GetTableName() + " (";
    stmt += "entryid        INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL, ";

    for (auto& col : report->GetTableInfo())
    {
        stmt += std::get<0>(col) + "\t" + std::get<1>(col) + "\t NOT NULL, ";
    }
    stmt += "FOREIGN KEY(nodeid) REFERENCES node(nodeid)              );";

    return stmt;
}

void
OranModSqlite::CreateReportSave(Ptr<OranReportSql> report)
{
    NS_LOG_FUNCTION(this << report);
    if (m_active)
    {
        int rc;
        sqlite3_stmt* stmt = nullptr;
        sqlite3_prepare_v2(m_db, CreateReportSaveQuery(report).c_str(), -1, &stmt, 0);
        rc = sqlite3_step(stmt);
        CheckQueryReturnCode(stmt, rc);
        sqlite3_finalize(stmt);
    }
}

std::string
OranModSqlite::CreateReportSaveQuery(Ptr<OranReportSql> report)
{
    NS_LOG_FUNCTION(report);
    std::string stmt = "INSERT INTO " + report->GetTableName() + " (";
    std::string values = "VALUES (";
    std::vector<std::tuple<std::string, std::string>> repData = ParseReport(report);
    for (size_t i = 0; i < repData.size() - 1; i++)
    {
        stmt += std::get<0>(repData[i]) + ", ";
        values += std::get<1>(repData[i]) + ", ";
    }
    stmt += std::get<0>(repData[repData.size() - 1]) + ") ";
    values += std::get<1>(repData[repData.size() - 1]) + ");";
    stmt += values;
    return stmt;
}

std::vector<std::tuple<std::string, std::string>>
OranModSqlite::ParseReport(Ptr<OranReportSql> report)
{
    NS_LOG_FUNCTION(report);
    std::vector<std::tuple<std::string, std::string>> repData;
    std::string repDataStr = report->ToString();
    size_t p = repDataStr.find('(');
    repDataStr = repDataStr.substr(p + 1, repDataStr.find(')') - p - 1);
    repDataStr += ";";
    std::string token;
    size_t pos = 0;
    while ((pos = repDataStr.find(';')) != std::string::npos)
    {
        token = repDataStr.substr(0, pos);
        size_t pos2 = token.find('=');
        std::string colName = token.substr(0, pos2);
        std::string colVal = token.substr(pos2 + 1, token.length() - pos2 - 1);
        repData.emplace_back(colName, colVal);
        repDataStr.erase(0, pos + 1);
    }
    return repData;
}

std::unordered_map<std::string, std::string>
OranModSqlite::GetLastReport(const std::string& table)
{
    NS_LOG_FUNCTION(this);
    std::unordered_map<std::string, std::string> repData;
    if (m_active)
    {
        int rc;
        sqlite3_stmt* stmt = nullptr;
        std::string query = "SELECT * FROM " + table + " ORDER BY entryid DESC LIMIT 1;";
        sqlite3_prepare_v2(m_db,
                           query.c_str(),
                           -1,
                           &stmt,
                           0);
        while ((rc = sqlite3_step(stmt)) == SQLITE_ROW)
        {
            for (int i = 0; i < sqlite3_column_count(stmt); i++)
            {
                std::string colName = sqlite3_column_name(stmt, i);
                std::string colVal = (const char*)sqlite3_column_text(stmt, i);
                repData[colName] = colVal;
            }
        }
        CheckQueryReturnCode(stmt, rc);
        sqlite3_finalize(stmt);
    }
    return repData;
}

std::unordered_map<std::string, std::string>
OranModSqlite::GetLastReport(const std::string& table, uint64_t nodeId)
{
    NS_LOG_FUNCTION(this);
    std::unordered_map<std::string, std::string> repData;
    if (m_active)
    {
        int rc;
        sqlite3_stmt* stmt = nullptr;
        std::string query = "SELECT * FROM " + table + " WHERE nodeid = " + std::to_string(nodeId) + " ORDER BY time DESC LIMIT 1;";
        sqlite3_prepare_v2(m_db,
                           query.c_str(),
                           -1,
                           &stmt,
                           0);
        while ((rc = sqlite3_step(stmt)) == SQLITE_ROW)
        {
            for (int i = 0; i < sqlite3_column_count(stmt); i++)
            {
                std::string colName = sqlite3_column_name(stmt, i);
                std::string colVal = (const char*)sqlite3_column_text(stmt, i);
                repData[colName] = colVal;
            }
        }
        CheckQueryReturnCode(stmt, rc);
        sqlite3_finalize(stmt);
    }
    return repData;
}

std::unordered_map<std::string, std::string>
OranModSqlite::GetCustomQuery(const std::string& query)
{
    NS_LOG_FUNCTION(this);
    std::unordered_map<std::string, std::string> repData;
    if (m_active)
    {
        int rc;
        sqlite3_stmt* stmt = nullptr;
        sqlite3_prepare_v2(m_db,
                           query.c_str(),
                           -1,
                           &stmt,
                           0);
        while ((rc = sqlite3_step(stmt)) == SQLITE_ROW)
        {
            for (int i = 0; i < sqlite3_column_count(stmt); i++)
            {
                std::string colName = sqlite3_column_name(stmt, i);
                std::string colVal = (const char*)sqlite3_column_text(stmt, i);
                repData[colName] = colVal;
            }
        }
        CheckQueryReturnCode(stmt, rc);
        sqlite3_finalize(stmt);
    }
    return repData;
}
} // namespace ns3
