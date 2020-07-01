#include "GameObject.h"
#include "../GameDatabase/CreationData/GameObjectCreate.h"
#include "../Components/ComponentManager.h"
#include "../Components/Component.h"
#include "../Renderer/ASCIIRenderer.h"
#include "../Utils/Utils.h"

GameObject::GameObject(const GameObjectCreate* pCreationData)
{
	if (pCreationData)
	{
		m_Position = Vector2(pCreationData->m_Position.x, pCreationData->m_Position.y);
		//components in database
		for (GDb::C_Pointer<ComponentCreate> pComponentCreate : pCreationData->m_ComponentIds)
		{
			Component* pComponent = ComponentManager::Instance()->GetComponent(pComponentCreate.GetItem(), this);
			if (pComponent)
			{
				pComponent->Initialise();
				m_Components.push_back(pComponent);
			}
		}

		//programatic components
		for (int i = 0; i < pCreationData->m_Components.size(); i++)
		{			
			Component* pComponent = ComponentManager::Instance()->GetComponent(pCreationData->m_Components[i], this);
			if (pComponent)
			{
				m_Components.push_back(pComponent);
			}
		}
	}
}

GameObject::~GameObject()
{
	for (std::vector<Component*>::iterator it = m_Components.begin(); it != m_Components.end(); ++it)
	{
		SAFE_DELETE_PTR(*it);
	}
}

void GameObject::OnMessage(Message* pMessage)
{
	//TODO - subscribe to messages so dont need to send message to all components
	for (int i = 0; i < m_Components.size(); i++)
	{
		m_Components[i]->OnMessage(pMessage);
	}
}

void GameObject::BroadcastMessage(Message* pMessage)
{

}

void GameObject::Update(float delta)
{
	for (std::vector<Component*>::iterator it = m_Components.begin(); it != m_Components.end(); ++it)
	{
		(*it)->Update(delta);
	}
}

void GameObject::Render(ASCIIRenderer* pRenderer)
{
	pRenderer->PushMatrix();

	pRenderer->Translate(m_Position);

	for (std::vector<Component*>::iterator it = m_Components.begin(); it != m_Components.end(); ++it)
	{
		(*it)->Render(pRenderer);
	}

	pRenderer->PopMatrix();

}
