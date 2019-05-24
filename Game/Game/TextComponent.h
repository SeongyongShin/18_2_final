#pragma once
#include "IComponent.h"


class CText;
class CTextComponent :
	public IComponent
{
private:
	CText* pText;

	wstring m_strText;
	
	
	
	bool m_isAutoSize;

public:

	

	void SetText(wstring);
	void AddText(wstring);
	void SetFormat(DWORD Format);	//중앙,좌측,우측,위,아래 등 설정
	void SetColor(D3DCOLOR color);
	void SetFontSize(int iSize);
	void SetTextBoxSize(int iWidth,int iHeight);


	void SetAutoSize();
	virtual void Update(float deltaTime) override;


	virtual void Render() override;

public:
	CTextComponent();
	virtual ~CTextComponent();
};

