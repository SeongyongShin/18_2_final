#pragma once
#include "IComponent.h"

class C2DSpriteComponent;

class CTankComponent :
	public IComponent
{
private:
	float m_fCurrentHP=100  ;
	float m_fMaxHP=300;

	float m_fCanonAngle=0;
	float m_fBodyAngle=0;


private:
	CGameObject* m_pCanon;
	CGameObject* m_pBody;
	

public:
	CTankComponent();
	virtual ~CTankComponent();

	virtual void Update(float deltaTime) override;
	virtual void Render() override;

};

