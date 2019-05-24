#pragma once
#include "Scene.h"
#include <queue>

class CText;
class CIntro :
	public CScene
{
private:
	CText* pMainText=nullptr;
	CText* pBlinkingText;




	std::queue<wstring> m_IntroTextQueue;
	wstring m_strCurrentText;
	

	float fFadeColor = 0;
	float fFadeTime = 0.1;
	float fCurrentFadeTime=0;

	bool bFadeIn=true;
	bool bFadeOut=false;

	bool bNextTextAvailable=false;

	bool bButtonBlink=false;
	float fButtonBlinkTime=0.1;
	float fCurrentBlinkTime=0;


	void UpdateText(float deltaTime);	//텍스트 출력 페이드효과
	void UpdateNext(float deltaTime);	//다음텍스트 출력 여부
	void UpdateBlink(float deltaTime);	//모두 출력완료시 깜빡거림

public:
	CIntro();
	virtual ~CIntro();

	virtual void Update(float fDeltaTime);


	virtual void Render() override;

};

