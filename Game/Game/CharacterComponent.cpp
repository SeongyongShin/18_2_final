#include "CharacterComponent.h"

#include "GameObject.h"
#include "MainGame.h"
#include "CharacterRenderComponent.h"
#include "BulletComponent.h"
#include <windows.h>
#include "2DSpriteComponent.h"
#include "CircleComponent.h"
#include "RectangleComponent.h"


#define GetFriend(X) m_pOwner->getComponent<X>();

CCharacterComponent::CCharacterComponent()
{
	
	m_Status = STOP_IDLE;
	m_CurrentWay = WAY_DOWN;
	m_fAngle = 0;
	m_SyncState = COMPONENT_TO_OWNER;
}

CCharacterComponent::~CCharacterComponent()
{
}





void CCharacterComponent::Update(float deltaTime)
{
	
	
	if (m_pRenderComponent)
	{
		UpdateStatus();

	}
	else
	{
		m_pRenderComponent = GetFriend(CCharacterRenderComponent);
		
	}


	if (m_pRectangleComponent)
	{
		
		m_pRectangleComponent->SetHeight(16);
		m_pRectangleComponent->SetWidth(16);

	}
	else
	{
		m_pRectangleComponent = GetFriend(CRectangleComponent);
		m_pRectangleComponent->SetHeight(16);
		m_pRectangleComponent->SetWidth(16);

	}
	
	IComponent::Update(deltaTime);
}

void CCharacterComponent::Render()
{	
}

void CCharacterComponent::CreateBullet(bool isEnemy)
{
	CGameObject* pGameObject = new CGameObject;
	
	pGameObject->AddComponent<CBulletComponent>();
	pGameObject->getComponent<CBulletComponent>()->SetPos(m_vecPos);
	pGameObject->AddComponent<CRectangleComponent>();
	pGameObject->AddComponent<C2DSpriteComponent>();


	pGameObject->getComponent<CBulletComponent>()->SetBulletInfo(m_fAngle,10, isEnemy,1000);

	//~~~~~ CBullet 추가정보~~//

	CMainGame::GetInstance()->CreateObject(pGameObject);
}








void CCharacterComponent::ResetPos()
{
	m_vecPos = m_vecPrevPos;
}

void CCharacterComponent::ResetX()
{
	m_vecPos.x = m_vecPrevPos.x;

}

void CCharacterComponent::ResetY()
{
	m_vecPos.y = m_vecPrevPos.y;
}

D3DXVECTOR3 CCharacterComponent::GetMapTileIndex(int iMapSizeX, int iMapSizeY)	//오른쪽위: X 오른쪽아래 : Y
{
	

	return D3DXVECTOR3(m_vecPos.x / iMapSizeX, m_vecPos.y / iMapSizeY,0 );
}

D3DXVECTOR3 CCharacterComponent::GetPrevMapTileIndex(int iMapSizeX, int iMapSizeY)	//오른쪽위: X 오른쪽아래 : Y
{
	
	return D3DXVECTOR3(m_vecPrevPos.x / iMapSizeX, m_vecPrevPos.y / iMapSizeY, 0);
}

D3DXVECTOR3 CCharacterComponent::GetPos()
{
	return m_vecPos;
}


void CCharacterComponent::SetAngle(float fAdjust)
{
	m_fAngle = fAdjust;
}

void CCharacterComponent::UpdateStatus()
{

	m_pRenderComponent->m_CurrentWay = m_CurrentWay;
	m_pRenderComponent->m_CurrentStatus = m_Status;

}

void CCharacterComponent::Move(eWay way, float fDistance)
{
	m_vecPrevPos = m_vecPos;

	

	if (m_Status != WALK && m_Status != WALK_AIM && m_Status == WALK_FIRE)
		m_pRenderComponent->ResetFrame();
	
	


	m_Status = WALK;


	switch (way)
	{
	case WAY_LEFT:
		m_vecPos.x -= fDistance;
		break;
	case WAY_RIGHT:
		m_vecPos.x += fDistance;
		break;
	case WAY_RIGHT_DOWN:
		m_vecPos.x += fDistance * pow(0.5, 0.5);
		m_vecPos.y += fDistance * pow(0.5, 0.5);
		break;
	case WAY_DOWN:
		m_vecPos.y += fDistance;
		break;
	case WAY_LEFT_DOWN:
		m_vecPos.x -= fDistance * pow(0.5, 0.5);
		m_vecPos.y += fDistance * pow(0.5, 0.5);
		break;
	case WAY_LEFT_UP:
		m_vecPos.x -= fDistance * pow(0.5, 0.5);
		m_vecPos.y -= fDistance * pow(0.5, 0.5);
		break;
	case WAY_UP:
		m_vecPos.y -= fDistance;
		break;
	case WAY_RIGHT_UP:
		m_vecPos.x += fDistance * pow(0.5, 0.5);
		m_vecPos.y -= fDistance * pow(0.5, 0.5);
		break;
	case WAY_END:
		break;
	default:
		m_Status = eStatus::STOP_IDLE;
		break;
	}


}

void CCharacterComponent::SetWay(eWay way)
{
	if (way != m_CurrentWay)
	{
		m_pRenderComponent->ResetFrame();
	}

	m_CurrentWay = way;
}