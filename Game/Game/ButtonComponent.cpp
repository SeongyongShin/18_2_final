#include "ButtonComponent.h"
#include "RectangleComponent.h"
#include "Defines.h"
#include "2DSpriteComponent.h"
void CButtonComponent::Update(float deltaTime)
{
	POINT MousePos;
	GetCursorPos(&MousePos);
	ScreenToClient(g_hWnd, &MousePos);



	IComponent::Update(deltaTime);

	if (pSpriteComponent)
	{
		iWidth =pSpriteComponent->GetTextureSize().x;
		iHeight = pSpriteComponent->GetTextureSize().y;
	}
	else
	{
		pSpriteComponent = m_pOwner->getComponent<C2DSpriteComponent>();
	}

	if (pRectangleComponent)
	{
		pRectangleComponent->SetHeight(iWidth);
		pRectangleComponent->SetWidth(iHeight);
	}
	else
	{
		pRectangleComponent = m_pOwner->getComponent<CRectangleComponent>();
	}




	if (pRectangleComponent!=nullptr && pRectangleComponent->CheckCollision(MousePos.x, MousePos.y) )
	{
		if (GetAsyncKeyState(VK_LBUTTON))
		{
			bMouseDown = true;
		}
		else
		{
			if (bMouseDown)
			{
				bClicked = true;
			}
			else
			{
				bClicked = false;
			}

			bMouseDown = false;
		}
	}
	else
	{
		bMouseDown = false;
		bClicked = false;
	}
}

CButtonComponent::CButtonComponent()
{
	m_SyncState = COMPONENT_TO_OWNER;
}


CButtonComponent::~CButtonComponent()
{
}

bool CButtonComponent::Clicked()
{
	return bClicked;
}
