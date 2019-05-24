#pragma once
#include "IComponent.h"
#include "CharacterEnum.h"
#include "DirectHeader.h"


class CRectangleComponent;
class CCharacterRenderComponent;

class CCharacterComponent :public IComponent
{
private:
	CCharacterRenderComponent* m_pRenderComponent=nullptr;
	IComponent* m_pTextComponent=nullptr;
	CRectangleComponent* m_pRectangleComponent=nullptr;



	D3DXVECTOR3 m_vecPrevPos;

private:

	


	eStatus m_Status;
	eWay m_CurrentWay;
	float m_fAngle;

	bool b_isRendering;

public:
	CCharacterComponent();
	virtual ~CCharacterComponent();

	
	

	virtual void Update(float deltaTime) override;
	virtual void Render() override;
	void UpdateStatus();


	void Move(eWay way, float fDistance);
	void SetWay(eWay way);
	void SetStatus(eStatus status) { m_Status = status; }

	void CreateBullet(bool isEnemy);

	void ResetPos();
	void ResetX();
	void ResetY();

	D3DXVECTOR3 GetMapTileIndex(int iMapSizeX, int iMapSizeY); //중앙 인덱스 반환

	D3DXVECTOR3 GetPrevMapTileIndex(int iMapSizeX, int iMapSizeY); //오른쪽위;
	D3DXVECTOR3 GetPos();

	void SetAngle(float fAdjust);
};
