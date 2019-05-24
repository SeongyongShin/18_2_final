#pragma once
#include "IComponent.h"
#include "DirectHeader.h"
class CMachineGun :
	public IComponent
{
private:
	D3DXVECTOR3 m_vecPos;
	float m_fDirection;

	float m_fFireRate;
	float m_fPassedTime;

public:
	CMachineGun();
	virtual ~CMachineGun();

	virtual void Update(float deltaTime) override;


	virtual void Render() override;




	void Fire();

	
};

