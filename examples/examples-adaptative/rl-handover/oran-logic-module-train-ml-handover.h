#ifndef ORAN_TRAIN_LM_HANDOVER_H
#define ORAN_TRAIN_LM_HANDOVER_H

#include "open-gym.h"

#include <ns3/ai-module.h>
#include <ns3/oran-data-repository.h>
#include <ns3/oran-lm.h>
#include <ns3/oran-module.h>
#include <ns3/vector.h>
#include <ns3/net-device-container.h>

namespace ns3
{

class OranLmCustomHandover : public OranLm
{
  protected:
    struct UeInfo
    {
        uint64_t nodeId;
        uint16_t cellId;
        uint16_t rnti;
        double apploss;
        double sinr;
        Vector position;
    };

    struct EnbInfo
    {
        uint64_t nodeId;
        uint16_t cellId;
        Vector position;
    };

  public:
    static TypeId GetTypeId();
    OranLmCustomHandover();
    ~OranLmCustomHandover() override;

    std::vector<Ptr<OranCommand>> Run(void) override;
    void EndSimulation();
    void SetEnbDevs(std::vector<Ptr<LteEnbNetDevice>> enbDevs);

  private:
    std::vector<OranLmCustomHandover::UeInfo> GetUeInfos(
        Ptr<OranDataRepository> data, uint64_t) const;
    std::vector<OranLmCustomHandover::EnbInfo> GetEnbInfos(
        Ptr<OranDataRepository> data) const;
    std::vector<Ptr<OranCommand>> GetHandoverCommands(
        Ptr<OranDataRepository> data,
        std::vector<OranLmCustomHandover::UeInfo> ueInfos,
        std::vector<OranLmCustomHandover::EnbInfo> enbInfos,
	OranLmCustomHandover::UeInfo ueInfo) const;

    std::vector<OranLmCustomHandover::UeInfo> GetAllUeInfos(Ptr<OranDataRepository>) const;

    std::vector<Ptr<LteEnbNetDevice>> m_enbDevs;
    uint64_t m_nEnb;

    Ptr<EnvOran> m_model;
};

} // namespace ns3

#endif
