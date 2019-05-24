
#include "GameObject.h"
#include "direct.h"
#include "MainGame.h"

#include "IComponent.h"


CGameObject* CGameObject::CreateObject()
{
	return new CGameObject;
}

void CGameObject::Update(float deltaTime)
{
	for (auto iter = componentMap.begin(); iter != componentMap.end(); iter++)
	{
		iter->second->Update(deltaTime);
	}
}

void CGameObject::Render()
{
	for (auto iter = componentMap.begin(); iter != componentMap.end(); iter++)
	{
		iter->second->Render();
	}
	
}



bool CGameObject::isDead()
{
	return m_isDead;
}

void CGameObject::SetDead()
{
	m_isDead = true;
}

void CGameObject::SetPos(D3DXVECTOR3 vec)
{
	m_vecPos = vec;
}

CGameObject::CGameObject()
{
	
}

CGameObject::~CGameObject()
{
	for (auto iter = componentMap.begin(); iter != componentMap.end();iter++ )
	{
		
		delete iter->second;

		
	}
	 
	componentMap.clear();
}
