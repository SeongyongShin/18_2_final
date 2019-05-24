#include "CircleComponent.h"



void CCircleComponent::SetCircle(float fX, float fY, float fRadius)
{
	m_fX = fX;
	m_fY = fY;
	m_fRadius = fRadius;
}

CCircleComponent::CCircleComponent()
{
	m_SyncState = OWNER_TO_COMPONENT;
}


CCircleComponent::~CCircleComponent()
{
}

void CCircleComponent::SetPos(float x, float y)
{
	m_fX = x;
	m_fY = y;
}
