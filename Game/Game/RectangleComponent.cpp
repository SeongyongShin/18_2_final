#include "RectangleComponent.h"



CRectangleComponent::CRectangleComponent()
{
	m_SyncState = OWNER_TO_COMPONENT;
}


CRectangleComponent::CRectangleComponent(float x, float y, float width, float height)
{
	Set(x, y, width, height);
}

CRectangleComponent::CRectangleComponent(RECT rc)
{
	Set(rc);
}

CRectangleComponent::~CRectangleComponent()
{
}

void CRectangleComponent::Set(RECT rc)
{
	m_rc = rc;
	UpdateFromRECT();
}

void CRectangleComponent::Set(float x, float y, float width, float height)
{
	m_vecPos.x = x;
	m_vecPos.y = y;
	m_fWidth = width;
	m_fHeight = height;
	UpdateToRECT();

}

void CRectangleComponent::SetPos(float x, float y)
{
	m_vecPos.x = x;
	m_vecPos.y = y;
	
	UpdateToRECT();
}

void CRectangleComponent::SetWidth(float width)
{

	m_fWidth = width;

	UpdateToRECT();
}

void CRectangleComponent::SetHeight(float height)
{

	m_fHeight = height;
	UpdateToRECT();
}

void CRectangleComponent::Update(float deltaTime)
{
	IComponent::Update(deltaTime);
}

const std::wstring CRectangleComponent::GetComponentID()
{
	return L"Rectangle";
}

POINT CRectangleComponent::GetMapTileIndex(int iPoint, int iMapSizeX, int iMapSizeY)
{
	float IndexX = m_vecPos.x / (float)64 - m_vecPos.y / (float)32 + iMapSizeX / 2;
	float IndexY = m_vecPos.x / (float)64 + m_vecPos.y / (float)32 - iMapSizeY / 2;

	POINT result = { IndexX, IndexY };
	return result;
}


bool CRectangleComponent::CheckCollision(CRectangleComponent* rc)
{
	RECT temp;

	return IntersectRect(&temp,&m_rc, & (rc->GetRect()));
}

bool CRectangleComponent::CheckCollision(CGameObject* pGameObject)
{
	if (pGameObject->getComponent<CRectangleComponent>())
	{
		RECT temp;
		return IntersectRect(&temp, &m_rc, &(pGameObject->getComponent<CRectangleComponent>()->GetRect()));
	}

	else
		return false;
}

bool CRectangleComponent::CheckCollision(int x, int y)
{
	if (x >= m_rc.left && x <= m_rc.right && y >= m_rc.top && y <= m_rc.bottom)
		return true;
	else
		return false;
}

bool CRectangleComponent::CheckCollisionCircle(float fRadius, float fX, float fY)
{
	return false;
}

void CRectangleComponent::UpdateFromRECT()
{
	m_vecPos.x = m_rc.right - m_rc.left;
	m_vecPos.y = m_rc.bottom - m_rc.top;
}

void CRectangleComponent::UpdateToRECT()
{
	m_rc.left = m_vecPos.x - m_fWidth / 2;
	m_rc.top = m_vecPos.y - m_fHeight / 2;
	m_rc.right = m_vecPos.x + m_fWidth / 2;
	m_rc.bottom = m_vecPos.y + m_fHeight / 2;
}
