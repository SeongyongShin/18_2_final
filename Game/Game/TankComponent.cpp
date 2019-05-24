#include "TankComponent.h"
#include "2DSpriteComponent.h"


CTankComponent::CTankComponent()
{
	m_SyncState = COMPONENT_TO_OWNER;
	m_pCanon = new CGameObject;
	m_pCanon->AddComponent<C2DSpriteComponent>();
	m_pCanon->getComponent<C2DSpriteComponent>()->SetTexture(L"Tank");
	m_pCanon->getComponent<C2DSpriteComponent>()->SetSprite(L"Cannon");
	m_pCanon->getComponent<C2DSpriteComponent>()->SetDrawFrame();
	m_pCanon->getComponent<C2DSpriteComponent>()->SetSynchronizeState(OWNER_TO_COMPONENT);

	m_pBody = new CGameObject;
	m_pBody->AddComponent<C2DSpriteComponent>();
	m_pBody->getComponent<C2DSpriteComponent>()->SetTexture(L"Tank");
	m_pBody->getComponent<C2DSpriteComponent>()->SetSprite(L"Tank_Body");
	m_pBody->getComponent<C2DSpriteComponent>()->SetDrawFrame();
	m_pBody->getComponent<C2DSpriteComponent>()->SetSynchronizeState(OWNER_TO_COMPONENT);
	
}


CTankComponent::~CTankComponent()
{
}

void CTankComponent::Update(float deltaTime)
{
	
	m_pCanon->SetPos(m_vecPos);
	m_pBody->SetPos(m_vecPos);

	IComponent::Update(deltaTime);

}

void CTankComponent::Render()
{
	m_pBody->Render();
	m_pCanon->Render();
}
