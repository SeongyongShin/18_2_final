#include "Camera.h"
#include "Direct.h"

IMPLEMENT_SINGLETON(CCamera)

void CCamera::SetPos(D3DXVECTOR3 vecPos)
{
	m_vecPos = vecPos;
	D3DXMatrixTranslation(&m_matTransform, -m_vecPos.x, -m_vecPos.y, -m_vecPos.z);
}


D3DXVECTOR3 CCamera::GetPos()
{
	return m_vecPos;
}

D3DXMATRIX CCamera::GetTransform()
{
	return m_matTransform;
}

CCamera::CCamera()
{
}


CCamera::~CCamera()
{
}
