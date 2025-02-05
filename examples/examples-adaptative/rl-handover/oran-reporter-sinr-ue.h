#ifndef UEREPORTERSINR_H
#define UEREPORTERSINR_H
#include <ns3/oran-module.h>
#include <ns3/log.h>
#include <ns3/double.h>

#include "oran-report-sinr-ue.h"

namespace ns3 {
class OranReporterSinrUe : public OranReporter
{
    public:
    static TypeId GetTypeId();

    OranReporterSinrUe();
    ~OranReporterSinrUe() override;

    void UpdateData(uint16_t cellId, double sinr, double rsrp, uint64_t rnti);
    std::vector<Ptr<OranReport>> GenerateReports() override;

    private:
    double m_sinr;
    double m_rsrp;
		uint64_t m_rnti;
		uint16_t m_cellId;

};
}
#endif
