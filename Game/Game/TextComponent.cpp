#include "TextComponent.h"
#include "Text.h"






void CTextComponent::SetText(wstring text)
{
	m_strText = text;
	
}

void CTextComponent::AddText(wstring text)
{
	m_strText += text;
}

void CTextComponent::SetFormat(DWORD Format)
{
	pText->SetFormat(Format);
}

void CTextComponent::SetColor(D3DCOLOR color)
{
	pText->SetColor(color);
}

void CTextComponent::SetFontSize(int iSize)
{
	pText->SetFontSize(iSize);
}

void CTextComponent::SetTextBoxSize(int iWidth, int iHeight)
{
	
	pText->SetTextRange(m_vecPos.x - iWidth / 2, m_vecPos.y - iHeight / 2,
		m_vecPos.x + iWidth / 2, m_vecPos.y + iHeight / 2);
	
	m_isAutoSize = false;
}

void  CTextComponent::SetAutoSize()
{
	m_isAutoSize = true;
}

void CTextComponent::Update(float deltaTime)
{
	pText->SetText(m_strText);

	
	
	if (m_isAutoSize)
	{
		if (m_strText.find(L"\n") == wstring::npos)
		{
			int Width = pText->GetFontSize() * m_strText.length()*2;
			int Height = pText->GetFontSize() * 2;

			pText->SetTextRange(m_vecPos.x - Width / 2, m_vecPos.y - Height / 2,
				m_vecPos.x + Width / 2, m_vecPos.y + Height / 2);
		}
		else
		{
			int currentIndex = 0;
			int	NextIndex = 0;
			int maxX=0;
			int iCount = 0;
			while (  m_strText.find(L"\n", currentIndex,1) !=(-1))
			{
				NextIndex = m_strText.find(L"\n", currentIndex, 1);
				NextIndex += currentIndex;
				iCount++;
				if (maxX < NextIndex - currentIndex)
					maxX = NextIndex - currentIndex;
				currentIndex = NextIndex;

			}

			int Width = pText->GetFontSize() * maxX;
			int Height = pText->GetFontSize() * 2 * iCount;


			pText->SetTextRange(m_vecPos.x - Width / 2, m_vecPos.y - Height / 2,
				m_vecPos.x + Width / 2, m_vecPos.y + Height / 2);
		}

	}

	IComponent::Update(deltaTime);
}

void CTextComponent::Render()
{
	pText->Render();
}

CTextComponent::CTextComponent()
{
	pText = new CText();
	pText->Init();
	pText->SetFormat( DT_VCENTER | DT_CENTER);

	pText->SetColor(D3DCOLOR_ARGB(255, 0, 0, 0));
	


	m_SyncState = OWNER_TO_COMPONENT;
	SetAutoSize();
}


CTextComponent::~CTextComponent()
{
	pText->Release();
	delete pText;
}
