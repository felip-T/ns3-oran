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

#ifndef ORAN_CMM_HANDOVER_H
#define ORAN_CMM_HANDOVER_H

#include "oran-cmm.h"
#include "oran-command-lte-2-lte-handover.h"

namespace ns3 {

class OranCommand;

/**
 * \ingroup oran
 *
 * An ORAN conflict mitigation module
 */
class OranCmmHandover : public OranCmm
{
public:
  /**
   * Gets the TypeId of the OranCmmHandover class.
   *
   * \return The TypeId
   */
  static TypeId GetTypeId (void);
  /**
   * Creates an instance of the OranCmmHandover class.
   */
  OranCmmHandover (void);
  /**
   * The destructor of the OranCmmHandover class.
   */
  ~OranCmmHandover (void) override;
  /**
   * Prompts this conflict mitigation module to execute its logic
   * and filter the input commands. This is a No Operation module,
   * so the input set of commands will be returned without filtering
   *
   * \param inputCommands A map with the input commands generated by all the LMs
   * \return A vector with the commands filtered by this module
   */
  std::vector<Ptr<OranCommand> > Filter (
      std::map<std::tuple<std::string, bool>, std::vector<Ptr<OranCommand> > > inputCommands) override;

protected:
  /**
   * Disposes of the object.
   */
  void DoDispose (void) override;

private:
  /**
   * Keep track of pending handover commands.
   */
  std::vector<Ptr<OranCommandLte2LteHandover> > m_pendingCmds;

}; // class OranCmmHandover

} // namespace ns3

#endif // ORAN_CMM_HANDOVER_H

