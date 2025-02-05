#include <ns3/oran-module.h>
#include <ns3/object.h>

namespace ns3{

class OranReportTriggerApplossThreshold : public OranReportTrigger{
	public:
		static TypeId GetTypeId();
		OranReportTriggerApplossThreshold();
		~OranReportTriggerApplossThreshold() override;
		void Activate(Ptr<OranReporter> reporter) override;
		void Deactivate() override;
	
	private:
		void CheckTriggeredTrace(double, double);
		Time m_lastReport;
};
}
