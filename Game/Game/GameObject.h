#pragma once

#include <map>

#include "DirectHeader.h"
#include "IComponent.h"



class CGameObject
{
private:
	D3DXVECTOR3 m_vecPos;

	
private:  
	std::map<int, IComponent*> componentMap;

public:
	CGameObject* CreateObject();

	void Update(float deltaTime);
	void Render();
	D3DXVECTOR3 GetPos() { return m_vecPos; }
	void SetPos(D3DXVECTOR3 vec);
	void AddPos(D3DXVECTOR3 vec) { m_vecPos += vec; }
	
	
	template <typename T,typename ...args>
	T& AddComponent(args...additional)
	{
		T* newComponent = new T(additional...);
		newComponent->SetOwner(this);
		componentMap.insert(make_pair(getComponentID<T>(),newComponent));
		return *newComponent;
	}

	template <typename T> void removeComponent()
	{
		if (componentMap[getComponentID <T>()])
		{
			delete componentMap[getComponentID <T>()];
			componentMap[getComponentID <T>()] = NULL;
			componentMap.erase(getComponentID <T>());
		}
	}
	

	template<typename T> T* getComponent() const //has기능도 가능
	{
		ComponentID ID = getComponentID<T>();
		IComponent* p = nullptr;
		if(componentMap.find(ID) != componentMap.end())
			p = componentMap.find(ID)->second;
		return (T*)p;
	}


private:
	bool m_isDead = false;
public:
	bool isDead();
	void SetDead();



public:
	CGameObject();
	~CGameObject();
};



