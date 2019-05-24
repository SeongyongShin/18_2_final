#pragma once
#include "IComponent.h"
#include "DirectHeader.h"
#include "RectangleComponent.h"

class C2DSpriteComponent;
class CTileComponent :
	public IComponent
{
private:
	const int m_iTileType=0;
	bool m_bBlocked=false;
private:
	static int m_iMaxX;
	static int m_iMaxY;

public:
	static void SetMaxTile(int x, int y);


private:
	const int m_iIndexX;
	const int m_iIndexY;

	const float m_fX;
	const float m_fY;

public:
	D3DXVECTOR3 GetPos() { return D3DXVECTOR3(m_fX, m_fY,0); }


	static int GetMaxX();
	static int GetMaxY();
	int GetIndexX();
	int GetIndexY();
private:




private:
	C2DSpriteComponent* m_pSpriteComponent = nullptr;

public:
	CTileComponent(int indexX, int indexY, int tileType);
	virtual ~CTileComponent();

	virtual void Update(float deltaTime) override;


	virtual void Render() override;

	
	bool isSetComplete();
	bool isBlocked();
};
