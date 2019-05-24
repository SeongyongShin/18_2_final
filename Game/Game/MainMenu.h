#pragma once
#include "Scene.h"

class CGameObject;
class CMainMenu :
	public CScene
{
private:
	CGameObject* pButton[3];


public:



	virtual void Update(float fDeltaTime) override;


	virtual void Render() override;

public:
	CMainMenu();
	virtual ~CMainMenu();
};

