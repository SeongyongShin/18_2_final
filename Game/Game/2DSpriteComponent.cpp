#include "2DSpriteComponent.h"

#include "MainGame.h"
#include "SpriteResource.h"

void C2DSpriteComponent::SetSizeAsFrame()
{
	m_RenderInfo.vecSize = CMainGame::GetInstance()->
		GetSpriteResource()->
		GetSpriteSize(m_strTextureName, m_strSpriteName);
}

D3DXVECTOR3 C2DSpriteComponent::GetTextureSize()
{
	
	return CMainGame::GetInstance()->
		GetSpriteResource()->
		GetTextureSize(m_strTextureName);
}

void C2DSpriteComponent::SetTexture(wstring texture)
{
	m_strTextureName = texture;

	m_pTexture = CMainGame::GetInstance()->GetSpriteResource()->GetTexture(m_strTextureName);
}

void C2DSpriteComponent::SetSprite(wstring sprite)
{
	m_strSpriteName = sprite;

	m_pSprite = m_pTexture->GetSprite(sprite);

}

void C2DSpriteComponent::SetFrame(int frame)
{
	m_iFrame = frame;
}

void C2DSpriteComponent::SetAngle(float fAngle)
{
	m_RenderInfo.fRenderDirection = fAngle;

}

void C2DSpriteComponent::SetPos(D3DXVECTOR3 vecPos)
{
	m_RenderInfo.vecPos = vecPos;
}

void C2DSpriteComponent::SetPos(float x, float y, float z /*= 0*/)
{
	m_RenderInfo.vecPos = D3DXVECTOR3(x, y, z);
}

void C2DSpriteComponent::SetRatio(float XRatio, float YRatio)
{
	m_RenderInfo.vecRenderRatio = D3DXVECTOR3(XRatio, YRatio, 1);
}

void C2DSpriteComponent::SetSize(float width, float height)
{
	m_RenderInfo.vecSize = D3DXVECTOR3(width, height, 0);
}

void C2DSpriteComponent::DrawFrame()
{
	
	m_pTexture->Draw( m_pSprite,m_iFrame, &m_RenderInfo);

	

}

void C2DSpriteComponent::DrawSprite()
{
	m_pTexture->DrawWholeSprite(m_strSpriteName, &m_RenderInfo);

}

void C2DSpriteComponent::DrawTexture()
{
	m_pTexture->DrawWholeTexture(&m_RenderInfo);
}


void C2DSpriteComponent::Update(float deltaTime)
{
	m_RenderInfo.vecPos = m_vecPos;

	IComponent::Update(deltaTime);
}

void C2DSpriteComponent::Render()
{
	switch (m_iDrawState)
	{
	case 1:
		DrawFrame();
		break;
	case 2:
		DrawSprite();
		break;
	case 3:
		DrawTexture();
		break;
	}
}

C2DSpriteComponent::C2DSpriteComponent()
{
	SetSizeAsFrame();
	m_SyncState = OWNER_TO_COMPONENT;
}


C2DSpriteComponent::~C2DSpriteComponent()
{
}
