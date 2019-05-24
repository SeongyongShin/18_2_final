#pragma once


#include <string>
using namespace std;


#include <bitset>
#include <array>

class IComponent;

#define ComponentID int


inline int getNewComponentID()
{
	static int lastID = 0u;
	return lastID++;
}

template <typename T> int getComponentID()
{
	static_assert(std::is_base_of<IComponent, T>::value, "");
	static int typeID = getNewComponentID();
	return typeID;
}





#include "GameObject.h"


enum eSyncState
{
	OWNER_TO_COMPONENT,
	COMPONENT_TO_OWNER,
	NONE,
};

class CGameObject;
class IComponent
{
public:
	IComponent* getThis()
	{
		return this;
	}

protected:
	CGameObject* m_pOwner;
	D3DXVECTOR3 m_vecPos;
	

	eSyncState m_SyncState;

	void Synchronize();
	

public:
	virtual void Update(float deltaTime);
	virtual void Render();
	void SetPos(D3DXVECTOR3 vecPos);

	void SetOwner(CGameObject* const pGameObject);
	void SetSynchronizeState(eSyncState SyncState);



	const CGameObject* GetOwner();





public:
	IComponent();
	virtual ~IComponent()=0;
};

