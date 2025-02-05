/**
 * @file oran-report-sqlite.h
 * @brief Implementation of the OranReportSqlite class
 */

#ifndef ORAN_REPORT_SQLITE_H
#define ORAN_REPORT_SQLITE_H

#include "oran-report.h"
#include <string>

namespace ns3 {
/**
 * @ingroup oran
 * @class OranReportSqlite
 * @brief The OranReportSqlite class is a base class for all custom reports to
 * be used with the OranAdaptativeSqlite database.
 *
 * It is expected that the user's custom report inherits from this class and
 * implements the GetTableInfo and GetTableName virtual methods, as well as the
 * ToString method, inherited from OranReport base class.
 */
class OranReportSqlite : public OranReport
{
public:
    OranReportSqlite(); //!< Default constructor
    ~OranReportSqlite() override; //!< Destructor

		/**
 		 *  Register this type.
 		 *  @return The object TypeId.
 		 */
    static TypeId GetTypeId();

    /**
     * @brief Get the table information, used by OranAdaptativeSqlite to parse
     * the report data.
     *
     * This function should return a vector of tuples, where each tuple contains
     * the SQlite column name followed by the column data type.
     *
     * As an example, the following code snippet shows how to implement this
     * method for a custom report that has a table with two columns, a "TEXT"
     * containing the node IPV4 address and an "INTEGER" containing the current
     * connected cellId:
		 *
		 *
		 * @code
		 * std::vector<std::tuple<std::string, std::string>> GetTableInfo(){
		 * 	std::vector<std::tuple<std::string, std::string>> tableInfo;
		 * 	tableInfo.emplace_back(std::make_tuple("ipv4", "TEXT"));
		 * 	tableInfo.emplace_back(std::make_tuple("cellId", "INTEGER"));
		 * 	return tableInfo;
		 * }
     * @endcode
		 *
     * @return Vector of tuples with the table information.
     */
    virtual std::vector<std::tuple<std::string, std::string>> GetTableInfo();
    /**
     * @brief Returns the table name used by OranAdaptativeSqlite.
     *
     * This method should return the name of the table that will be created by
     * OranAdaptativeSqlite to store reports of this kind.
     *
     * @return The table name.
     */
    virtual std::string GetTableName(){return "";}

protected:
  /**
   * @brief The table information that can be initialized in constructor and
   * returned by \ref GetTableInfo.
   */
  std::vector<std::tuple<std::string, std::string>> m_tableInfo;
};
} // namespace ns3
#endif /* ORAN_REPORT_SQL_H */
