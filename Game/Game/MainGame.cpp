#include "MainGame.h"
#include "Scene.h"
#include "MainMenu.h"
#include "Defines.h"
#include "Stage.h"
#include <windows.h>

#include "Text.h"
#include "SoundResource.h"
#include "SpriteResource.h"
#include "Intro.h"
#include <stdio.h>


IMPLEMENT_SINGLETON(CMainGame)








void CMainGame::UpdateChangeScene()
{
	if (m_pNewScene)
	{
		if (m_pCurrentScene)
			delete m_pCurrentScene;
		m_pCurrentScene = m_pNewScene;
		m_pNewScene = nullptr;
	}
}



void CMainGame::Init()
{
	pSoundResource = new CSoundResource;
	pSoundResource->Init();
	pSpriteResource = new CSpriteResource;
	m_pCurrentScene = new CMainMenu;

	
}

void CMainGame::Update(float deltaTime)
{
	
	UpdateChangeScene();
	m_pCurrentScene->Update(deltaTime);
	
	pSoundResource->PlayMusic(L"233");
	
}

void CMainGame::Render()
{
	m_pCurrentScene->Render();
}

void CMainGame::ResetSprite()
{
	SAFE_DELETE(pSpriteResource);
	pSpriteResource = new CSpriteResource;
}


void CMainGame::CreateObject(CGameObject* pGameObject)
{
	m_pCurrentScene->CreateObject(pGameObject);
}

CMainGame::CMainGame()
{
	
	AllocConsole();                 

	FILE* pFile;

	freopen_s(&pFile,"CONOUT$", "a", stderr); 
	freopen_s(&pFile, "CONOUT$", "a", stdout);
	freopen_s(&pFile, "CONIN$", "r", stdin);
	SetConsoleTitleA("Test v.1.0");


}


CMainGame::~CMainGame()
{
	
	
	delete pSoundResource;
	delete pSpriteResource;
	delete m_pCurrentScene;
}
