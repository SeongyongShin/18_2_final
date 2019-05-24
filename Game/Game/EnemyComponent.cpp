#include "EnemyComponent.h"
#include "CharacterComponent.h"


D3DXVECTOR3 CEnemyComponent::m_vecPlayerPos;

std::list<D3DXVECTOR3> CEnemyComponent::m_bulletPosList;
//D3DXVECTOR3 CEnemyComponent::m_bulletPosList;

CEnemyComponent::CEnemyComponent()
{

}


CEnemyComponent::~CEnemyComponent()
{
}

void CEnemyComponent::Update(float deltaTime)
{
	if (m_pCharacterComponent)
	{
		m_fCurrentMoveRate += deltaTime;
		//cout << "플레이어 좌표 : " << m_vecPlayerPos.x << "," << m_vecPlayerPos.y << "적 좌표 : " << m_vecPos.x << "," << m_vecPos.y << endl;
		//cout << 1 / deltaTime<<endl;
		m_pCharacterComponent->Move((eWay)m_currentWay, speed * deltaTime); // 움직이는 방향, 속도
		m_pCharacterComponent->SetWay((eWay)m_currentWay); // 현재 바라보는 방향
		m_pCharacterComponent->SetAngle(m_currentWay * 45); // 총쏘는 방향(45를 곱하면 각도가 나옴)
		//if (ck) {
		//   m_pCharacterComponent->SetPos(m_pCharacterComponent->GetPos() + D3DXVECTOR3(1 , 1, 0));//움직이고싶은 xyz 좌표);
		//   ck = false;
		//}
		//else {
		//   ck = true;
		//   m_pCharacterComponent->SetPos(m_pCharacterComponent->GetPos() + D3DXVECTOR3(-1, -1, 0));//움직이고싶은 xyz 좌표);
		//}

		//D3DXVECTOR3 A;

		dx = m_vecPlayerPos.x - m_vecPos.x;
		dy = m_vecPlayerPos.y - m_vecPos.y;
		absxy = abs(abs(dx) - abs(dy));
		dxy = (dx * dx) + (dy * dy);
		if ((dx > 0) && (dy > 0)) { // 오른쪽 아래에 플레이어가 있을 때
			if ((abs(dx) > abs(dy)) && abs(dx) > (abs(dy) * 2)) {
				if (m_fCurrentMoveRate >= m_fMoveRate) {// 다가가는 방향 정의, 시간차를 두고
					rand1 = rand() % 3;
					m_currentWay = 1;
					m_fCurrentMoveRate = 0;
					m_pCharacterComponent->SetWay((eWay)m_currentWay);
					m_pCharacterComponent->SetAngle(sin((dy) / sqrt((double)dxy)) * 45);
					m_pCharacterComponent->CreateBullet(true);

				}
				else {
					switch (rand1) {
					case 1: m_currentWay = 1;
						break;
					case 2: m_currentWay = 3;
						break;
					default: m_currentWay = 2;
						break;
					}
				}
			}
			else if ((abs(dx) < abs(dy)) && abs(dy) > (abs(dx) * 2)) {
				if (m_fCurrentMoveRate >= m_fMoveRate) {// 다가가는 방향 정의, 시간차를 두고
					rand1 = rand() % 3;
					m_currentWay = 2;
					m_pCharacterComponent->SetWay((eWay)m_currentWay);
					m_pCharacterComponent->SetAngle(sin((dy) / sqrt((double)dxy)) * 90);
					m_pCharacterComponent->CreateBullet(true);
					m_fCurrentMoveRate = 0;
				}
				else {
					switch (rand1) {
					case 1: m_currentWay = 1;
						break;
					case 2: m_currentWay = 3;
						break;
					default: m_currentWay = 2;
						break;
					}
				}
			}
			else { // 오른쪽 아래 사선에있을때
				cout << sqrt(dxy) << endl;
				rand1 = rand() % 3;
				if (sqrt(dxy) < 1000) {
					if (m_fCurrentMoveRate >= m_fMoveRate) {
						if (rand() % 3 != 1) {
							m_currentWay = 1;
							m_pCharacterComponent->SetWay((eWay)m_currentWay);
							m_pCharacterComponent->SetAngle(sin((dy) / sqrt((double)dxy)) * 90);
							m_pCharacterComponent->CreateBullet(true);
						}
						rand1 = rand() % 8;
						m_currentWay = rand1;
						m_fCurrentMoveRate = 0;
					}
				}
				else {
					if (m_fCurrentMoveRate >= m_fMoveRate) {
						switch (rand1) {
						case 0: m_currentWay = 1;
							break;
						case 1: m_currentWay = 0;
							break;
						default: m_currentWay = 2;
							break;
						}
						m_fCurrentMoveRate = 0;
					}
				}
				if (absxy < 0.5) {
					if (m_fCurrentMoveRate >= m_fMoveRate) {
						m_currentWay = 1;
						m_pCharacterComponent->SetWay((eWay)m_currentWay);
						m_pCharacterComponent->SetAngle(sin((dy) / sqrt((double)dxy)) * 90);
						m_pCharacterComponent->CreateBullet(true);
						m_fCurrentMoveRate = 0;
					}
				}

			}
			if (m_fCurrentMoveRate >= m_fMoveRate) {
				if (abs(dy) < 0.5) {
					m_currentWay = 0;
					m_pCharacterComponent->SetWay((eWay)m_currentWay);
					m_pCharacterComponent->SetAngle(0);
					m_pCharacterComponent->CreateBullet(true);
				}
				else if (abs(dx) < 0.5) {
					m_currentWay = 2;
					m_pCharacterComponent->SetWay((eWay)m_currentWay);
					m_pCharacterComponent->SetAngle(2);
					m_pCharacterComponent->CreateBullet(true);
				}
				m_fCurrentMoveRate = 0;
			}
		}
		else if ((dx < 0) && (dy > 0)) { // 왼쪽 아래에 플레이어가 있을 때
			m_currentWay = rand() % 8;
		}
		else if ((dx < 0) && (dy < 0)) { // 왼쪽 위에 플레이어가 있을 때
			m_currentWay = rand() % 8;
		}
		else {//오른쪽 위에 있을 때
			m_currentWay = rand() % 8;
		}
	}
	//if (!m_bulletPosList.empty())
	//{
	//   cout << m_bulletPosList.back().x << "," << m_bulletPosList.back().y << endl;
	//}
	else
	{
		m_pCharacterComponent = m_pOwner->getComponent<CCharacterComponent>();
	}


	IComponent::Update(deltaTime);
}

void CEnemyComponent::Render()
{

}

void CEnemyComponent::GetPlayerPos(D3DXVECTOR3 vecPlayerPos)
{
	m_vecPlayerPos = vecPlayerPos;
}

void CEnemyComponent::GetPlayerBulletPosList(std::list<D3DXVECTOR3> bulletPosList)
//void CEnemyComponent::GetPlayerBulletPosList(D3DXVECTOR3 bulletPosList)
{
	m_bulletPosList = bulletPosList;
}