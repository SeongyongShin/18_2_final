

#include "Scene.h"
#include "GameObject.h"
#include "PlayerComponent.h"
#include "BulletComponent.h"
#include "EnemyComponent.h"





void CScene::Update(float fDeltaTime)
{	
	

	//Check Dead
	for (auto iter = m_pGameObjectList.begin(); iter != m_pGameObjectList.end();)
	{
		
		if ((*iter)->isDead())
		{
			delete(*iter);
			m_pGameObjectList.erase(iter++);
			continue;
		}


		(*iter)->Update(fDeltaTime);

		if ((*iter)->getComponent<CPlayerComponent>())
		{
			bulletCheck.addPlayer(*iter);
		}

		if ((*iter)->getComponent<CBulletComponent>())
		{
			if((*iter)->getComponent<CBulletComponent>()->isEnemy())
				bulletCheck.addEnemyBullet(*iter);

			else
				bulletCheck.addPlayerBullet(*iter);
		}

		if ((*iter)->getComponent<CEnemyComponent>())
		{
			bulletCheck.addEnemy(*iter);
		}




		iter++;

		
		
		

		
	}

	bulletCheck.Update(fDeltaTime);
}

void CScene::Render()
{
	
	for (auto iter = m_pGameObjectList.begin(); iter != m_pGameObjectList.end(); iter++)
	{
		(*iter)->Render();
	}
	
}

CScene::CScene()
{
}


CScene::~CScene()
{
}

void CScene::CreateObject(CGameObject* pGameObject)
{
	m_pGameObjectList.push_back(pGameObject);
}
