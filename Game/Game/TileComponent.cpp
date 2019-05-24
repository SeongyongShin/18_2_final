#include "TileComponent.h"
#include "2DSpriteComponent.h"

#include "GameObject.h"
#include "direct.h"

int CTileComponent::m_iMaxX;

int CTileComponent::m_iMaxY;

void CTileComponent::SetMaxTile(int x, int y)
{
	m_iMaxX = x;
	m_iMaxY = y;
}

int CTileComponent::GetMaxX()
{
	return m_iMaxX;
}

int CTileComponent::GetMaxY()
{
	return m_iMaxY;
}

int CTileComponent::GetIndexX()
{
	return m_iIndexX;
}

int CTileComponent::GetIndexY()
{
	return m_iIndexY;
}



CTileComponent::CTileComponent(int indexX, int indexY, int tileType) :
	m_iIndexX(indexX), m_iIndexY(indexY), m_iTileType(tileType),
	m_fX(16 + indexX * 32), m_fY(16 + indexY * 32)
{
	if(m_iTileType ==17 )
		m_bBlocked = false;
	else if (m_iTileType == 139)
		m_bBlocked = true;
}

CTileComponent::~CTileComponent()
{ 
}

void CTileComponent::Update(float deltaTime)
{
	if(!m_pSpriteComponent)
	{
		m_pSpriteComponent = GetOwner()->getComponent<C2DSpriteComponent>();  
		if (m_pSpriteComponent)
		{


			m_pSpriteComponent->SetTexture(L"Tile");
			m_pSpriteComponent->SetSprite(L"Tile");

			
			m_pSpriteComponent->SetFrame(m_iTileType);
			m_pSpriteComponent->SetPos(m_fX, m_fY);

			m_pSpriteComponent->SetDrawFrame();
		}
		
	}

	
}


void CTileComponent::Render()
{
	
}

bool CTileComponent::isSetComplete()
{
	if (m_pSpriteComponent)
		return true;
	else
		return false;
}

bool CTileComponent::isBlocked()
{
	return m_bBlocked;
}