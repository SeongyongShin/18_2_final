#include "MainMenu.h"
#include "Defines.h"
#include "Scene.h"
#include "2DSpriteComponent.h"
#include "ButtonComponent.h"
#include "MainGame.h"
#include "Intro.h"
#include "TextComponent.h"
#include "RectangleComponent.h"

void CMainMenu::Update(float fDeltaTime)
{
	for (int i = 0; i < 3; i++)
	{
		pButton[i]->Update(fDeltaTime);
		
	}

	if (pButton[0]->getComponent<CButtonComponent>()->Clicked())
	{
		CMainGame::GetInstance()->ChangeScene<CIntro>();
		
	}


}

void CMainMenu::Render()
{
	for (int i = 0; i < 3; i++)
	{
		pButton[i]->Render();
	}

}

CMainMenu::CMainMenu()
{
	for (int i = 0; i < 3; i++)
	{
		pButton[i] = new CGameObject;
		pButton[i]->AddComponent<CButtonComponent>();
		pButton[i]->AddComponent<C2DSpriteComponent>();
		pButton[i]->AddComponent<CRectangleComponent>();
		pButton[i]->AddComponent<CTextComponent>();
		
		pButton[i]->getComponent<CButtonComponent>()->SetPos(D3DXVECTOR3(800,200+ 200*i,0));
		
		auto p = pButton[i]->getComponent<C2DSpriteComponent>();
		pButton[i]->getComponent<C2DSpriteComponent>()->SetTexture(L"Button");
		

		pButton[i]->getComponent<C2DSpriteComponent>()->SetDrawTexture();
		
	}
	pButton[0]->getComponent<CTextComponent>()->SetText(L"시작");
	pButton[1]->getComponent<CTextComponent>()->SetText(L"옵션");
	pButton[2]->getComponent<CTextComponent>()->SetText(L"종료");

}


CMainMenu::~CMainMenu()
{
	for (auto iter = m_pGameObjectList.begin(); iter != m_pGameObjectList.end(); iter++)
	{
		delete (*iter);
	}
	m_pGameObjectList.clear();

}
