#pragma once
#include "SubstantialComponent.h"
#include <windows.h>

class CGameObject;
class CRectangleComponent :
	public CSubstantialComponent
{
private:
	float m_fWidth;
	float m_fHeight;

	RECT m_rc;

	void UpdateFromRECT();// RECT로부터 XYWH로 업데이트
	void UpdateToRECT();	//XYWH로부터 RECT로 업데이트

public:
	CRectangleComponent();
	CRectangleComponent(float x, float y, float width, float height);
	CRectangleComponent(RECT rc);

	virtual ~CRectangleComponent();


	void Set(RECT rc);
	void Set(float x, float y, float width, float height);
	void SetPos(float x, float y);
	void SetWidth(float width);
	void SetHeight(float height);

	float GetWidth() { return m_fWidth; }
	float GetHeight() { return m_fHeight; }
	RECT GetRect() { return m_rc; }




	virtual void Update(float deltaTime) override;
	virtual const wstring GetComponentID() override;


	POINT GetMapTileIndex(int iPoint,int iMapSizeX,int iMapSizeY); //인자값에 따라 사각형 꼭지점 결정, 1.좌상, 2. 좌하, 3.우하, 4.우상


	bool CheckCollision(CRectangleComponent* rc);
	bool CheckCollision(CGameObject* pGameObject);
	bool CheckCollision(int x, int y);
	bool CheckCollisionCircle(float fRadius, float fX, float fY);
	
};

