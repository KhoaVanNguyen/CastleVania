#ifndef _CTEXT_H_
#define _CTEXT_H_
#include <d3dx9.h>
class CText
{
	LPDIRECT3DDEVICE9 m_device;
	LPD3DXFONT m_font;
	int m_fontSize;
	CHAR m_fontType;
public:
	CText();
	CText(int _fontSize,CHAR _fontFace);
	virtual ~CText(void);
	void Draw(LPCSTR,RECT,UINT,D3DCOLOR);
	void Init();
	
	void SetFontSize(int _fontsize){m_fontSize = _fontsize;}
};
#endif
