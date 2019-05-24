#pragma once
#include "Scene.h"
#include "List"
#include "Camera.h"
using namespace std;
class CStage :
	public CScene
{
private:
	CGameObject* m_pPlayer;

	vector<vector<CGameObject*>> vecTile;
	bool updateTile = true;
	

public:
	virtual void Update(float fDeltaTime);


	virtual void Render();


private:
	void LoadTile();

public:
	CStage();
	virtual ~CStage();
};

