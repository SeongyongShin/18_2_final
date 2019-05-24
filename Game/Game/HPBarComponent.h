#pragma once
#include "IComponent.h"
class CHPBarComponent :
	public IComponent
{
private:
	float m_fCurrentHP;
	float m_fMaxHP;

public:
	CHPBarComponent();
	virtual ~CHPBarComponent();
};

