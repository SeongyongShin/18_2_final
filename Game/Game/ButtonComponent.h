#pragma once
#include "IComponent.h"
class C2DSpriteComponent;
class CRectangleComponent;
class CButtonComponent :
	public IComponent
{
	int iWidth;
	int iHeight;


public:
	virtual void Update(float deltaTime);


private:
	bool bMouseDown = false;
	bool bClicked = false;
	CRectangleComponent* pRectangleComponent=nullptr;
	C2DSpriteComponent* pSpriteComponent = nullptr;

public:
	CButtonComponent();
	virtual ~CButtonComponent();
	bool Clicked();
};

