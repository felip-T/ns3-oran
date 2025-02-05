#include "oran-report-trigger-apploss.h"

namespace ns3{

NS_LOG_COMPONENT_DEFINE("OranReportTriggerApplossThreshold");
NS_OBJECT_ENSURE_REGISTERED(OranReportTriggerApplossThreshold);

TypeId OranReportTriggerApplossThreshold::GetTypeId(){
	static TypeId tid = TypeId("ns3::OranReportTriggerApplossThreshold")
		.SetParent<OranReportTrigger>()
		.AddConstructor<OranReportTriggerApplossThreshold>();
	return tid;
}

OranReportTriggerApplossThreshold::OranReportTriggerApplossThreshold() : OranReportTrigger(){
	NS_LOG_FUNCTION(this);
}

OranReportTriggerApplossThreshold::~OranReportTriggerApplossThreshold(){
	NS_LOG_FUNCTION(this);
}

void
OranReportTriggerApplossThreshold::Activate(Ptr<OranReporter> reporter){
	NS_LOG_FUNCTION(this);
	if (!m_active){
			reporter->TraceConnectWithoutContext("AppLoss",
					MakeCallback(&OranReportTriggerApplossThreshold::CheckTriggeredTrace, this));
	}
	m_lastReport = Seconds(0.0);
	OranReportTrigger::Activate(reporter);
}

void
OranReportTriggerApplossThreshold::Deactivate()
{
	NS_LOG_FUNCTION(this);
	OranReportTrigger::Deactivate();
}


void
OranReportTriggerApplossThreshold::CheckTriggeredTrace(double oldValue, double newValue)
{
	if (newValue > 0.05){
		if (Simulator::Now().GetSeconds() - m_lastReport.GetSeconds() > 0.2){
			// std::cout << "HERE:  asd" << m_lastReport << " " << Simulator::Now() << " " << newValue <<  std::endl;
			TriggerReport();
			m_lastReport = Simulator::Now();
		}
	}
}
}
