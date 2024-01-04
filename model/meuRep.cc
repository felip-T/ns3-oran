#include "oran-data-repository.h"

#include <ns3/log.h>

namespace ns3
{

NS_LOG_COMPONENT_DEFINE("OranDataRepository");

NS_OBJECT_ENSURE_REGISTERED(OranDataRepository);

TypeId
OranDataRepository::GetTypeId(void)
{
    static TypeId tid = TypeId("ns3::OranDataRepository").SetParent<Object>();

    return tid;
}

OranDataRepository::OranDataRepository(void)
    : Object(),
      m_active(false)
{
    NS_LOG_FUNCTION(this);
}

OranDataRepository::~OranDataRepository(void)
{
    NS_LOG_FUNCTION(this);
}

void
OranDataRepository::Activate(void)
{
    NS_LOG_FUNCTION(this);

    m_active = true;
}

void
OranDataRepository::Deactivate(void)
{
    NS_LOG_FUNCTION(this);

    m_active = false;
}

bool
OranDataRepository::IsActive(void) const
{
    NS_LOG_FUNCTION(this);

    return m_active;
}

void
OranDataRepository::DoDispose(void)
{
    NS_LOG_FUNCTION(this);

    Object::DoDispose();
}

} // namespace ns3
