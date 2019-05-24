#pragma once
#include <list>
#include <vector>
#include <array>
#include "IComponent.h"
#include "BulletCheckSystem.h"
using namespace std;

class CGameObject;
class CMouse;
class CScene
{

protected:
	CBulletCheckSystem bulletCheck;


	list <CGameObject*> m_pGameObjectList;

	
	

	int m_iStageChange = -1;

public:




public:
	

public:
	virtual void Update(float fDeltaTime);
	virtual void Render();
	CScene();
	virtual ~CScene();
	void CreateObject(CGameObject* pGameObject);
};