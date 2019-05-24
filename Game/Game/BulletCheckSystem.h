#pragma once
#include <list>
class CGameObject;
class CRectangleComponent;
class CBulletCheckSystem
{
private:
	std::list<CGameObject*> m_pPlayerList;
	std::list<CGameObject*> m_pEnemyBulletList;

	std::list<CGameObject*> m_pEnemyList;
	std::list<CGameObject*> m_pPlayrBulletList;

private:
	void CheckPlayerHit();
	void CheckEnemyHit();

public:
	void Update(float deltaTime);

public:
	void addPlayer(CGameObject* pPlayer);
	void addEnemyBullet(CGameObject* pEnemyBullet);
	void addEnemy(CGameObject* pEnemy);
	void addPlayerBullet(CGameObject* pPlayerBullet);

public:
	CBulletCheckSystem();
	virtual ~CBulletCheckSystem();
	
};

