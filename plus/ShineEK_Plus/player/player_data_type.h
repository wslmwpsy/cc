#ifndef _PLAYER_DATA_TYPE_H_
#define _PLAYER_DATA_TYPE_H_


enum OSD_PLAY_MODE // 滚动字幕方式
{
	OSD_RIGHT_IN_UP_OUT		= 0,	// 右进上出
	OSD_UP_IN_UP_OUT		= 1,	// 上进上出
	OSD_STRAIGHT_IN_UP_OUT		= 2,	// 直进上出
	OSD_STRAIGHT_IN_STRAIGHT_OUT	= 3,	// 直进直出
	OSD_RIGHT_IN_STRAIGHT_OUT	= 4,	// 右进直出
	OSD_STATIC			= 5,	// 静态显示
	OSD_RIGHT_TO_LEFT		= 6,	// 右进左出
	OSD_LEFT_TO_RIGHT		= 7,	// 左进右出
	OSD_UP_TO_DOWN			= 8,	// 上进下出
	OSD_DOWN_TO_UP			= 9,	// 下进上出
};


class text_osd_info
{
public:
	// 构造函数（用于初始将数据置空）
	text_osd_info() : fgcl(RGB(255,0,0)), shcl(RGB(0,255,0))
	{
		memset(&lf, 0, sizeof(lf));
		lf.lfWidth = 20;
		lf.lfHeight = 40;
		lf.lfWeight = 400;
		lf.lfQuality = 3;
		lf.lfCharSet = 134;
		_tcscpy(lf.lfFaceName, L"黑体");
	}

	TCHAR* Text() const { return (TCHAR*)m_text; }
	void Text(TCHAR* text) 
	{
		if (NULL==text)
		{
			return;
		}
		if (_tcslen(text)>(sizeof(m_text)/2))
		{
			return;
		}
		memset(m_text,0x0,sizeof(m_text));
		_tcscpy(m_text , text); 
	}

	COLORREF TextColor() const { return fgcl; }
	COLORREF TextColor() { return fgcl; }
	void TextColor(COLORREF c) { fgcl = c; }

	COLORREF ShadeColor() const { return shcl; }
	COLORREF ShadeColor() { return shcl; }
	void ShadeColor(COLORREF c) { shcl = c; }


	const LOGFONTW& Font() const { return lf; }
	const LOGFONTW& Font() { return lf; }
	void Font(LOGFONTW font) { lf = font; }

	const TCHAR* TextFont() const { return lf.lfFaceName; }
	TCHAR* TextFont() { return lf.lfFaceName; }
	void TextFont(const TCHAR* s) { _tcscpy(lf.lfFaceName, s); }


	void TextSize(int size)
	{
		if (size >= 5)
		{
			lf.lfWidth = size / 2;
			lf.lfHeight = size;
		}
	}

public:
	TCHAR m_text[2048]; // 消息内容
	long fgcl;	       // 前景颜色（文字颜色）
	long shcl;	       // 阴影颜色（背景颜色）
	LOGFONT lf;	       // 文字字体信息
};

class play_variable
{
public:
	enum OSD_PLAY_MODE play_mode;	// 显示
	long nRepeat;	// 重复次数
	long iHSpeed;	// 横向速度
	long iVSpeed;	// 纵向速度
	long nDelayTime; // 停留时间
	long sx;	// 起始横坐标
	long sy;	// 起始纵坐标
	long ex;	// 终止横坐标
	long ey;	// 终止纵坐标

	// 构造函数（用于初始将数据置空）
	play_variable() : play_mode(OSD_STATIC), nRepeat(0), iHSpeed(0), iVSpeed(0),
		nDelayTime(0), sx(0), sy(0), ex(0), ey(0)
	{
	}
};

#endif