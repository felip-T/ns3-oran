/**
 * @file oran-report-location-sql.h
 * @brief Implementation of the OranReportLocationSql class
 */

#ifndef ORAN_REPORT_LOCATION_SQL_H
#define ORAN_REPORT_LOCATION_SQL_H

#include "oran-report-sqlite.h"

#include <ns3/object.h>
#include <ns3/vector.h>

#include <string>

namespace ns3
{
/**
 * @ingroup oran
 * @class OranReportLocationSql
 * @brief A custom report to be used with the OranReportSqlite class.
 */
class OranReportLocationSql : public OranReportSqlite
{
  public:
		/**
 		 *  Register this type.
 		 *  @return The object TypeId.
 		 */
    static TypeId GetTypeId(void);

    OranReportLocationSql(void); //!< Default constructor
    ~OranReportLocationSql(void) override; //!< Destructor

    /**
     * @brief Returns a structured string representation of the
     * OranReportLocationSql report, used by  OranAdaptativeSqlite database to
     * fetch the report information.
     *
     * @return A string with the report information.
     */
    std::string ToString(void) const override;

    /**
     * @brief Get the table information about the OranReportLocationSql report, used by OranAdaptativeSqlite to parse the report data.
		 * @return A Vector of tuples with the table information for \ref OranReportLocationSql.
     */
    std::vector<std::tuple<std::string, std::string>> GetTableInfo() override;

		/**
		 * @brief Returns the table name used by OranAdaptativeSqlite for the
		 * OranReportLocationSql report.
		 * @return A string with the table name for OranReportLocationSql.
		 */
    std::string GetTableName() override;

		/**
		 * @brief Returns the location of the node, stored in \ref m_location.
		 *
		 * @return Vector with the node location.
		 */
    Vector GetLocation(void) const;

  private:
 	 	/**
 	 	 * @brief Stores the node location.
 	 	 */
    Vector m_location;
}; // class OranReportLocation

} // namespace ns3

#endif /* ORAN_REPORT_LOCATION_H */
