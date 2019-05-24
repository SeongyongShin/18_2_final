#pragma once
#include "IComponent.h"
#include "DirectHeader.h"
class CRectangleComponent;
class C2DSpriteComponent;
class CBulletComponent :
	public IComponent
{
private:
	CRectangleComponent*  m_pRectangleComponent = nullptr;
	C2DSpriteComponent*  m_pSpriteComonent=nullptr;
	
private:
	float m_fAngle;
	float m_fVelocity;
	bool m_isEnemy;

	float m_fMaxDistance=300;
	float m_fCurrentDistance=0;

public:
	virtual void Update(float deltaTime) override;
	void SetBulletInfo(float fAngle, float fVelocity, bool isEnemy,float fMaxDistance);

	CBulletComponent();
	virtual ~CBulletComponent();

	


	virtual void Render() override;

	bool isEnemy();
};

