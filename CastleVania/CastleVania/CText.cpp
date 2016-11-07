#include "CText.h"
#include "Global.h"


CText::CText()
{
	m_device = GL_graphic->GetDevice();
	m_fontType = (CHAR)"Arial";
	m_fontSize = 24;
	Init();
}
CText::CText(int _fontSize,CHAR _fontFace)
{
	m_device =	GL_graphic->GetDevice();
	m_fontType = _fontFace;
	m_fontSize = _fontSize;
	Init();
}
void CText::Init()
{
	D3DXFONT_DESC FontDesc = {m_fontSize,
		0,
		400,
		0,
		false,
		DEFAULT_CHARSET,
		OUT_TT_PRECIS,
		CLIP_DEFAULT_PRECIS,
		DEFAULT_PITCH,
		m_fontType};

	D3DXCreateFontIndirect(m_device,&FontDesc,&m_font);
}
void CText::Draw(LPCSTR _text,RECT _position,UINT _alignment,D3DCOLOR _color)
{
	m_font->DrawText(NULL,
		_text,
		-1,
		&_position,
		_alignment,
		_color);
}

CText::~CText(void)
{
	if(m_font != NULL)
	{
		m_font->Release(); //release font
		m_font = NULL;
	}
}
