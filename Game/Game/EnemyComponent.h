#pragma once
#include "IComponent.h"
#include <list>
#include<iostream>
#include<math.h>
#include<random>
#include<time.h>
using namespace std;
class CCharacterComponent;
class CEnemyComponent :
	public IComponent
{
private:
	CCharacterComponent* m_pCharacterComponent;


	int      m_currentWay = 0;
	float   m_fBulletCycle = 0.1;
	float   m_fFireRate = 5;
	bool ck = false;
	float   m_fMoveRate = 1;
	float   m_fCurrentMoveRate = 0;
	float dx = 0, dy = 0, absxy = 0;
	int rand1 = 0;
	float dxy = 0;
	float speed = 30;

	//AI�� ���� �÷��̾� ����

	static D3DXVECTOR3 m_vecPlayerPos; //�÷��̾� ��ǥ.
	static std::list<D3DXVECTOR3> m_bulletPosList; //�Ѿ� ��ǥ.
	//static D3DXVECTOR3 m_bulletPosList; //�Ѿ� ��ǥ.
public:
	CEnemyComponent();
	virtual ~CEnemyComponent();

	virtual void Update(float deltaTime) override;


	virtual void Render() override;



	static void GetPlayerPos(D3DXVECTOR3 vecPlayerPos);
	static void GetPlayerBulletPosList(std::list<D3DXVECTOR3> bulletPosList);
	//static void GetPlayerBulletPosList(D3DXVECTOR3 bulletPosList);
};

