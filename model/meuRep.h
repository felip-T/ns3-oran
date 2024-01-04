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

#ifndef ORAN_DATA_REPOSITORY_H
#define ORAN_DATA_REPOSITORY_H

#include "oran-command.h"
#include "oran-near-rt-ric.h"
#include "oran-report.h"

#include <ns3/nstime.h>
#include <ns3/object.h>
#include <ns3/vector.h>

#include <map>
#include <tuple>

namespace ns3
{
class OranDataRepository : public Object
{
  public:
    static TypeId GetTypeId(void);

    OranDataRepository(void);

    ~OranDataRepository(void) override;

    virtual void Activate(void);

    virtual void Deactivate(void);

    virtual bool IsActive(void) const;

    virtual bool IsNodeRegistered(uint64_t e2NodeId) = 0;

    virtual uint64_t RegisterNode(OranNearRtRic::NodeType type, uint64_t id) = 0;

    virtual uint64_t DeregisterNode(uint64_t e2NodeId) = 0;

    virtual void Save(Ptr<OranReport> report) = 0;

    virtual std::vector<std::tuple<uint64_t, Time>> GetLastRegistrationRequests(void) = 0;

    virtual void LogCommandE2Terminator(Ptr<OranCommand> cmd) = 0;

    virtual void LogCommandLm(std::string lm, Ptr<OranCommand> cmd) = 0;

    virtual void LogActionLm(std::string lm, std::string logstr) = 0;

    virtual void LogActionCmm(std::string cmm, std::string logstr) = 0;

  protected:
    void DoDispose(void) override;

    bool m_active;
}; // class OranDataRepository

} // namespace ns3

#endif /* ORAN_DATA_REPOSITORY_H */
