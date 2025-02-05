/**
 * @file oran-adaptative-sqlite.h
 * @brief Implementation of the OranAdaptativeSqlite class
 */

#ifndef ORAN_ADAPTATIVE_SQLITE_H
#define ORAN_ADAPTATIVE_SQLITE_H

#include "oran-data-repository-sqlite.h"
#include "oran-report-sqlite.h"

namespace ns3 {

/**
 * @ingroup oran
 * @class OranAdaptativeSqlite
 * @brief The OranAdaptativeSqlite class is a new implementation of the database
 * for the Near-Rt RIC. 
 *
 * This database is accepts custom reports that inherit
 * from OranReportSqlite. The tables of this database are created dinamically
 * based on the report information. Therefore, the user can define reports with
 * arbitrary information.
 */
class OranAdaptativeSqlite : public OranDataRepositorySqlite
{
public:
		/**
 		 *  Register this type.
 		 *  @return The object TypeId.
 		 */
    static TypeId GetTypeId (void);

    OranAdaptativeSqlite (); //!< Default constructor
    ~OranAdaptativeSqlite () override; //!< Destructor
		/**
		 * @brief Returns the last report of a given type.
		 *
		 * @param table A string with a table name.
		 * @return A map with keys as column names and values as column values.
		 */
    std::unordered_map<std::string, std::string> GetLastReport(const std::string& table);
				/**
				 * @brief Returns the last report of a given type for a given node ID.
				 *
				 * @param table A string with a table name.
				 * @param nodeId The node ID.
				 * @return A map with keys as column names and values as column values.
				 */
    std::unordered_map<std::string, std::string> GetLastReport(const std::string& table, uint64_t nodeId);
				/**
				 * @brief Returns the second last report of a gicen type for a given node ID.
				 *
				 * @param table A string with a table name.
				 * @param nodeId The node ID.
				 * @return A map with keys as column names and values as column values.
				 */
    std::unordered_map<std::string, std::string> GetSecondLastReport(const std::string& table, uint64_t nodeId);
				/**
				 * @brief Returns the custom query result.
				 *
				 * @param query A string with a SQL query.
				 * @return A map with keys as column names and values as column values.
				 */
    std::unordered_map<std::string, std::string> GetCustomQuery(const std::string& query);

    friend class OranNearRtRicE2Terminator;
protected:
    static std::string ParseReportTableInfo(Ptr<OranReportSqlite>);
    static std::string CreateReportSaveQuery(Ptr<OranReportSqlite>);
    static std::vector<std::tuple<std::string, std::string>> ParseReport(Ptr<OranReportSqlite>);
    void CreateReportTable(Ptr<OranReportSqlite>);
    void CreateReportSave(Ptr<OranReportSqlite>);

    std::unordered_map<std::string, bool> m_reportTableCreated;
};
}

#endif // ORAN_ADAPTATIVE_SQLITE_H
