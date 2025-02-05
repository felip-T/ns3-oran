#ifndef ORANREPORTERUECURRENTENB_H
#define ORANREPORTERUECURRENTENB_H
#include <ns3/oran-module.h>
#include "oran-report-ue-ipv4.h"
#include <ns3/log.h>
#include <ns3/string.h>
#include <ns3/internet-module.h>
#include <sstream>

namespace ns3 {
class OranReporterUeIpv4 : public OranReporter
{
    public:
    static TypeId GetTypeId();

    OranReporterUeIpv4();
    ~OranReporterUeIpv4() override;

    std::vector<Ptr<OranReport>> GenerateReports() override;
};
}
#endif
