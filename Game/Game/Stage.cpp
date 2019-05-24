#include "Stage.h"
#include <algorithm>
#include "GameObject.h"
#include "CharacterComponent.h"
#include "2DSpriteComponent.h"
#include "RectangleComponent.h"
#include "CharacterRenderComponent.h"
#include "PlayerComponent.h"
#include "TileComponent.h"
#include "TextComponent.h"
#include "EnemyComponent.h"
#include "CTexture.h"

#include <iostream>
#include "direct.h"
#include <fstream>
#include "TankComponent.h"
void CStage::Update(float fDeltaTime)
{
	CScene::Update(fDeltaTime);



	if (updateTile)
	{
		updateTile = false;
		for (int i = 0; i < vecTile.size(); i++)	//(타일 업데이트)
		{
			for (int j = 0; j < vecTile[i].size(); j++)
			{
				vecTile[i][j]->getComponent<CTileComponent>()->Update(fDeltaTime);

				if (!vecTile[i][j]->getComponent<CTileComponent>()->isSetComplete())
				{
					updateTile = true;
				}
			}
		}
	}

	CEnemyComponent::GetPlayerPos(m_pPlayer->GetPos());



	for (auto iter = m_pGameObjectList.begin(); iter != m_pGameObjectList.end(); iter++)
	{
		if((*iter)->getComponent<CCharacterComponent>())
		{
			float indexX = (*iter)->getComponent<CCharacterComponent>()->GetMapTileIndex(32, 32).x;
			float indexY = (*iter)->getComponent<CCharacterComponent>()->GetMapTileIndex(32, 32).y;
			float prevIndexX = (*iter)->getComponent<CCharacterComponent>()->GetPrevMapTileIndex(32, 32).x;
			float prevIndexY = (*iter)->getComponent<CCharacterComponent>()->GetPrevMapTileIndex(32, 32).y;

			if (indexX >= vecTile.size() || indexX <= 0)
			{
				(*iter)->getComponent<CCharacterComponent>()->ResetX();
			}

			if (indexY >= vecTile.size() || indexY <= 0)
			{
				(*iter)->getComponent<CCharacterComponent>()->ResetY();
			}

			indexX = (*iter)->getComponent<CCharacterComponent>()->GetMapTileIndex(32, 32).x;
			indexY = (*iter)->getComponent<CCharacterComponent>()->GetMapTileIndex(32, 32).y;
			prevIndexX = (*iter)->getComponent<CCharacterComponent>()->GetPrevMapTileIndex(32, 32).x;
			prevIndexY = (*iter)->getComponent<CCharacterComponent>()->GetPrevMapTileIndex(32, 32).y;


			if (vecTile[indexX][indexY]->getComponent<CTileComponent>()->isBlocked())
			{
				if (vecTile[indexX][prevIndexY]->getComponent<CTileComponent>()->isBlocked())
				{
					(*iter)->getComponent<CCharacterComponent>()->ResetX();
				}
				if (vecTile[prevIndexX][indexY]->getComponent<CTileComponent>()->isBlocked())
				{
					(*iter)->getComponent<CCharacterComponent>()->ResetY();
				}
			}
		}
	}
}


void CStage::Render()
{
	CCamera::GetInstance()->SetPos(m_pPlayer->GetPos() -D3DXVECTOR3(CLIENT_WIDTH/2, CLIENT_HEIGHT/2,0)  );
	CTexture::UpdateCamera(CCamera::GetInstance()->GetTransform());

	int cameraX = CCamera::GetInstance()->GetPos().x / 32;
	int cameraY = CCamera::GetInstance()->GetPos().y / 32;

	for (int x = 0; x < CTileComponent::GetMaxX(); x++)
	{

		for (int y = 0; y < CTileComponent::GetMaxY(); y++)
		{

			if(x > cameraX-1  &&
				x < cameraX + 40 &&
				y > cameraY -2 &&
				y < cameraY + 30 )
				vecTile[y][x]->Render();
		}

	}
	
	
	

	CScene::Render();
}

void CStage::LoadTile()
{

	
	
	std::ifstream infile("..\\Script\\TileMap.csv");

	if (infile.is_open())
	{

		int line = 0;
		int width;
		int height;
		char record[1024 * 4];
		
		while (!infile.eof())
		{

			infile.getline(record, 1024 * 4);
			char* token = strtok(record, ",");

			switch (line)
			{
			case 0:
				if (NULL != token)
				{
					token = strtok(NULL, ",");
					width = atoi(token);
					token = strtok(NULL, ",");
					height = atoi(token);

					CTileComponent::SetMaxTile(width, height);

				}
				break;
			default:
				if (NULL != token)
				{
					vector<CGameObject*> tileRow;
					for (int x = 0; x < width; x++)
					{
						int tileType = atoi(token);
						token = strtok(NULL, ",");
						CGameObject* pTile = new CGameObject();
						pTile->AddComponent<CTileComponent>(x, line, tileType);
						pTile->AddComponent<C2DSpriteComponent>();
						tileRow.push_back(pTile);


					}
					vecTile.push_back(tileRow);

				}
				break;
			}
			line++;
		}
		infile.close();
	}

	
	

	else
	{
		for (int i = 0; i < 10; i++)
		{
			vector<CGameObject*> tileRow;
			for (int j = 0; j < 10; j++)
			{
				CGameObject* pTile = new CGameObject();
				if (rand() % 2)
					pTile->AddComponent<CTileComponent>(i, j, 17);
				else
					pTile->AddComponent<CTileComponent>(i, j, 139);

				pTile->AddComponent<C2DSpriteComponent>();
				tileRow.push_back(pTile);
			}

			vecTile.push_back(tileRow);
		}

	}
}

//#include "TextComponent.h"




CStage::CStage()
{
	LoadTile();

	CGameObject* pPlayer = new CGameObject();
	pPlayer->AddComponent<CCharacterRenderComponent>();
	pPlayer->AddComponent<CCharacterComponent>();
	pPlayer->AddComponent<CPlayerComponent>();
	pPlayer->AddComponent<CRectangleComponent>(200, 200, 50, 50);
	pPlayer->getComponent<CCharacterComponent>()->SetPos(D3DXVECTOR3(200, 200, 0));
	pPlayer->AddComponent<CTextComponent>();
	pPlayer->getComponent<CTextComponent>()->SetText(L"플레이어");

	m_pGameObjectList.push_back(pPlayer);
	m_pPlayer = pPlayer;



	for (int i = 0; i < 10; i++)
	{
	
		CGameObject* pEnemy = new CGameObject();
		pEnemy->AddComponent<CCharacterRenderComponent>();
		pEnemy->AddComponent<CCharacterComponent>();
		pEnemy->AddComponent<CEnemyComponent>();
		pEnemy->AddComponent<CRectangleComponent>(200*(rand()%10), 200*(rand() % 10), 50, 50);
		pEnemy->getComponent<CCharacterComponent>()->SetPos(D3DXVECTOR3(200, 200, 0));
		m_pGameObjectList.push_back(pEnemy);

	}
	//--------------반복--------------->파싱으로 변경//

	CGameObject* pTank = new CGameObject();
	pTank->AddComponent<CTankComponent>();
	pTank->AddComponent<CRectangleComponent>(200, 200, 124, 96);
	pTank->getComponent<CTankComponent>()->SetPos(D3DXVECTOR3(200, 200, 0));
	m_pGameObjectList.push_back(pTank);

	//-------------------------------//
}


CStage::~CStage()
{
}
