#include "IComponent.h"




void IComponent::Synchronize()
{
	if (m_SyncState == OWNER_TO_COMPONENT)
	{
		m_vecPos = m_pOwner->GetPos();
	}
	else if (m_SyncState == COMPONENT_TO_OWNER)
	{
		m_pOwner->SetPos(m_vecPos);
	}
}

void IComponent::Update(float deltaTime)
{
	Synchronize();
}

void IComponent::Render()
{

}

void IComponent::SetPos(D3DXVECTOR3 vecPos)
{
	m_vecPos = vecPos;
}

void IComponent::SetOwner( CGameObject* const pGameObject)
{
	m_pOwner = pGameObject;
}

void IComponent::SetSynchronizeState(eSyncState SyncState)
{
	m_SyncState = SyncState;
}

const CGameObject* IComponent::GetOwner()
{
	return m_pOwner;
}





IComponent::IComponent()
{
	m_SyncState = OWNER_TO_COMPONENT;	//DEFAULT
}

IComponent::~IComponent()
{
}
