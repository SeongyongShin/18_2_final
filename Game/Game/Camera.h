#pragma once
#include "DirectHeader.h"
#include "Defines.h"
class CCamera
{
	DECLARE_SINGLETON(CCamera)

private:
	D3DXVECTOR3 m_vecPos;
	D3DXMATRIX m_matTransform;
	int m_iWidth = CLIENT_WIDTH;
	int m_iHeight = CLIENT_HEIGHT;

public:
	void SetPos(D3DXVECTOR3);
	D3DXVECTOR3 GetPos();
public:
	D3DXMATRIX GetTransform();


};

