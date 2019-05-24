#include "Intro.h"
#include "MainGame.h"
#include "Text.h"
#include "Stage.h"


CIntro::CIntro()
{
	pMainText = new CText();
	pMainText->SetColor(D3DCOLOR_ARGB(0,255,255,255));
	pMainText->SetTextRange(0,0, 1200, 900);
	pMainText->SetFontSize(10);

	m_IntroTextQueue.push(L"1940년 5월 10일, 독일군의 전면적 침공으로 서부전선이 마침내 포화에 휩싸였다.");
	m_IntroTextQueue.push(L"베네룩스 3국은 물론, 영프 연합군도 각지에서 참패와 후퇴만을 거듭했으며,");
	m_IntroTextQueue.push(L"독일군이 아르덴 산림지대를 돌파하고 뫼즈 강을 넘으며  ");
	m_IntroTextQueue.push(L"연합국이 예측치 못한 대규모 우회포위기동으로 주력부대가 모조리 포위섬멸될 위기에 빠졌다.");
	m_IntroTextQueue.push(L"연합국은 아라스에서 반격을 개시했으나 실패했고, 결국 독일군에 완전히 포위되고 만다.");
	m_IntroTextQueue.push(L"하인츠 구데리안의 기갑부대가 퇴로가 없는 연합군을 짓밟기 위해 빠른 속도로 진격하고 있었다.");
	
	pBlinkingText = new CText();
	pBlinkingText->SetColor(D3DCOLOR_ARGB(255, 255, 255, 255));
	pBlinkingText->SetTextRange(1000, 800, 1200, 900);
	pBlinkingText->SetFontSize(20);
	pBlinkingText->SetText(L"▶");


	m_strCurrentText = m_IntroTextQueue.front();
	m_IntroTextQueue.pop();




}


CIntro::~CIntro()
{
	if (pMainText)
	{
		pMainText->Release();
		delete pMainText;
		pMainText = nullptr;
	}
}

void CIntro::Update(float fDeltaTime)
{
	UpdateText(fDeltaTime);
	UpdateNext(fDeltaTime);
	UpdateBlink(fDeltaTime);
	

}

void CIntro::Render()
{
	pMainText->Render();

	if (bNextTextAvailable == true)
	{
		if (bButtonBlink)
			pBlinkingText->Render();
	}
}

void CIntro::UpdateText(float fDeltaTime)
{
	if (bFadeIn)
	{
		fCurrentFadeTime += fDeltaTime;

		fFadeColor = 255 * fCurrentFadeTime / fFadeTime;

		if (fFadeColor > 255)
		{
			bFadeIn = false;
			bNextTextAvailable = true;
			fFadeColor = 255;
			fCurrentFadeTime = 0;
		}

	}
	if (bFadeOut)
	{
		fCurrentFadeTime += fDeltaTime;
		fFadeColor = 255 - (255 * fCurrentFadeTime / fFadeTime);
		if (fFadeColor < 0)
		{
			fCurrentFadeTime = 0;
			bFadeOut = false;
			fFadeColor = 0;

			if (!m_IntroTextQueue.empty())
			{
				bFadeIn = true;
				m_strCurrentText = m_IntroTextQueue.front();
				m_IntroTextQueue.pop();
			}

			else
			{
				CMainGame::GetInstance()->ChangeScene<CStage>();
			}
		}
	}
	pMainText->SetText(m_strCurrentText);
	pMainText->SetColor(D3DCOLOR_ARGB((int)fFadeColor, 255, 255, 255));
}

void CIntro::UpdateNext(float deltaTime)
{
	if (bNextTextAvailable == true)
	{
		if (GetAsyncKeyState(VK_LBUTTON))
		{
			bFadeOut = true;
			bNextTextAvailable = false;
		}
		
	}


}

void CIntro::UpdateBlink(float deltaTime)
{
	fCurrentBlinkTime += deltaTime;

	if (fCurrentBlinkTime >= fButtonBlinkTime)
	{
		bButtonBlink = !bButtonBlink;
		fCurrentBlinkTime = 0;
	}
}