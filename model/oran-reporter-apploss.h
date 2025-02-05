/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/**
 * NIST-developed software is provided by NIST as a public service. You may
 * use, copy and distribute copies of the software in any medium, provided that
 * you keep intact this entire notice. You may improve, modify and create
 * derivative works of the software or any portion of the software, and you may
 * copy and distribute such modifications or works. Modified works should carry
 * a notice stating that you changed the software and should note the date and
 * nature of any such change. Please explicitly acknowledge the National
 * Institute of Standards and Technology as the source of the software.
 *
 * NIST-developed software is expressly provided "AS IS." NIST MAKES NO
 * WARRANTY OF ANY KIND, EXPRESS, IMPLIED, IN FACT OR ARISING BY OPERATION OF
 * LAW, INCLUDING, WITHOUT LIMITATION, THE IMPLIED WARRANTY OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE, NON-INFRINGEMENT AND DATA ACCURACY. NIST
 * NEITHER REPRESENTS NOR WARRANTS THAT THE OPERATION OF THE SOFTWARE WILL BE
 * UNINTERRUPTED OR ERROR-FREE, OR THAT ANY DEFECTS WILL BE CORRECTED. NIST
 * DOES NOT WARRANT OR MAKE ANY REPRESENTATIONS REGARDING THE USE OF THE
 * SOFTWARE OR THE RESULTS THEREOF, INCLUDING BUT NOT LIMITED TO THE
 * CORRECTNESS, ACCURACY, RELIABILITY, OR USEFULNESS OF THE SOFTWARE.
 *
 * You are solely responsible for determining the appropriateness of using and
 * distributing the software and you assume all risks associated with its use,
 * including but not limited to the risks and costs of program errors,
 * compliance with applicable laws, damage to or loss of data, programs or
 * equipment, and the unavailability or interruption of operation. This
 * software is not intended to be used in any situation where a failure could
 * cause risk of injury or damage to property. The software developed by NIST
 * employees is not subject to copyright protection within the United States.
 */

#ifndef ORAN_REPORTER_APPLOSS
#define ORAN_REPORTER_APPLOSS

#include "oran-report.h"
#include "oran-reporter.h"
#include "ns3/traced-value.h"
#include "ns3/trace-source-accessor.h"

#include <ns3/ptr.h>

#include <vector>

namespace ns3
{

class Packet;
class Address;

/**
 * \ingroup oran
 *
 * A Reporter that captures the application packet loss of the node.
 */
class OranReporterAppLoss : public OranReporter
{
  public:
    /**
     * Get the TypeId of the OranReporterAppLoss class.
     *
     * \return The TypeId.
     */
    static TypeId GetTypeId(void);
    /**
     * Constructor of the OranReporterAppLoss class.
     */
    OranReporterAppLoss(void);
    /**
     * Destructor of the OranReporterAppLoss class.
     */
    ~OranReporterAppLoss(void) override;
    /**
     * Records the transmission of a packet.
     *
     * \param p The packet.
     */
    void AddTx(Ptr<const Packet> p);
    /**
     * Records the reception of a packet from a given address.
     *
     * \param p The packet.
     * \param from The address that the packet is from.
     */
    void AddRx(Ptr<const Packet> p, const Address& from);

  protected:
    /**
     * Capture the application packet loss and instantiate an OranReportAppLoss.
     *
     * \return The generated Report.
     */
    std::vector<Ptr<OranReport>> GenerateReports(void) override;

  private:
    /**
     * The number of transmitted packets.
     */
    uint64_t m_tx;
    /**
     * The number of recived packets.
     */
    uint64_t m_rx;
    TracedValue<double> m_appLoss;
};

} // namespace ns3

#endif // ORAN_REPORTER_APPLOSS
