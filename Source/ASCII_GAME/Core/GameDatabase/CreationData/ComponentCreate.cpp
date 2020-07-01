#include "ComponentCreate.h"
#include "../../Components/ComponentManager.h"
#include "../GameDataHelpers.h"

ComponentCreate::ComponentCreate()
:m_ComponentId(-1)
{
}

void ComponentCreate::InitialiseFromBinary(char*& buffer)
{
	GDb::InitialiseFromBinary(&m_ComponentId, buffer);

	//ComponentManager::Instance()->RegisterComponentCreationData(m_ComponentId, this);
}
