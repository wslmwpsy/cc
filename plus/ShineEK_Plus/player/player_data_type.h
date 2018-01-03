#ifndef _PLAYER_DATA_TYPE_H_
#define _PLAYER_DATA_TYPE_H_


enum OSD_PLAY_MODE // ������Ļ��ʽ
{
	OSD_RIGHT_IN_UP_OUT		= 0,	// �ҽ��ϳ�
	OSD_UP_IN_UP_OUT		= 1,	// �Ͻ��ϳ�
	OSD_STRAIGHT_IN_UP_OUT		= 2,	// ֱ���ϳ�
	OSD_STRAIGHT_IN_STRAIGHT_OUT	= 3,	// ֱ��ֱ��
	OSD_RIGHT_IN_STRAIGHT_OUT	= 4,	// �ҽ�ֱ��
	OSD_STATIC			= 5,	// ��̬��ʾ
	OSD_RIGHT_TO_LEFT		= 6,	// �ҽ����
	OSD_LEFT_TO_RIGHT		= 7,	// ����ҳ�
	OSD_UP_TO_DOWN			= 8,	// �Ͻ��³�
	OSD_DOWN_TO_UP			= 9,	// �½��ϳ�
};


class text_osd_info
{
public:
	// ���캯�������ڳ�ʼ�������ÿգ�
	text_osd_info() : fgcl(RGB(255,0,0)), shcl(RGB(0,255,0))
	{
		memset(&lf, 0, sizeof(lf));
		lf.lfWidth = 20;
		lf.lfHeight = 40;
		lf.lfWeight = 400;
		lf.lfQuality = 3;
		lf.lfCharSet = 134;
		_tcscpy(lf.lfFaceName, L"����");
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
	TCHAR m_text[2048]; // ��Ϣ����
	long fgcl;	       // ǰ����ɫ��������ɫ��
	long shcl;	       // ��Ӱ��ɫ��������ɫ��
	LOGFONT lf;	       // ����������Ϣ
};

class play_variable
{
public:
	enum OSD_PLAY_MODE play_mode;	// ��ʾ
	long nRepeat;	// �ظ�����
	long iHSpeed;	// �����ٶ�
	long iVSpeed;	// �����ٶ�
	long nDelayTime; // ͣ��ʱ��
	long sx;	// ��ʼ������
	long sy;	// ��ʼ������
	long ex;	// ��ֹ������
	long ey;	// ��ֹ������

	// ���캯�������ڳ�ʼ�������ÿգ�
	play_variable() : play_mode(OSD_STATIC), nRepeat(0), iHSpeed(0), iVSpeed(0),
		nDelayTime(0), sx(0), sy(0), ex(0), ey(0)
	{
	}
};

#endif