#pragma once

#include <string>
#include <vector>
using namespace std;
enum ENUM_PLAY_STATE{
	PLAY_FIRST = 0,
	PLAY_TOP,
	PLAY_BOTTOM
};
enum ENUM_LYRICS_MODE
{
	LYRICS_MODE_SHOW = 0,	//�����ʾ
	LYRICS_MODE_BEGIN,		//��ʿ�ʼ�ݳ�
	LYRICS_MODE_HIDE		//�������
};

//callback��ϵͳ�Ľṹ��
typedef struct tagPlayLyricsState{
	ENUM_LYRICS_MODE elm;	//ģʽ 0:�����ʾ  1:��ʿ�ʼ�ݳ� 2:�������
	bool location;			//λ�� true:���� false:����
	string content;			//�������
	CWnd *pWnd;
}PLAYLYRICSSTATE, *LPPLAYLYRICSSTATE;

//ÿ���ֵ�ʱ��
typedef struct tagWordTimeContent
{
	int time;
	string content;
}WordTimeContent;

typedef vector<WordTimeContent> WRODTIMECONTENT_VEC;

//���и�ʽṹ��
typedef struct tagSingleLineLyrics
{
	long beginTime;							//���п�ʼʱ��
	long endTime;							//���н���ʱ��
	string contents;						//���о�����
	int	wordsize;							//һ���ֵĸ���
	WRODTIMECONTENT_VEC wordTimevec;		//����ʱ������
}SingleLineLyrics;

//���и������
typedef vector<SingleLineLyrics> SINGLELINELYRICS_VEC;

//��ʽṹ��
typedef struct tagKaraokeKSC
{
	int rows;									//����
	bool clear;									//����
	string songName;							//��������
	string singerName;							//��������
	SINGLELINELYRICS_VEC lpSingleLineLrcvec;	//���и������
	
	tagKaraokeKSC(){
		rows = 0;
		clear = false;
		songName = "";
		singerName = "";
	}
}KaraokeKSC, *LPKaraokeKSC;

typedef UINT (*LyricsCallback)(PLAYLYRICSSTATE lpParam); 

class CParseLyricsForKSC
{
public:
	CParseLyricsForKSC(const string path = "");
	virtual ~CParseLyricsForKSC(void);

public:
	LPKaraokeKSC Init(const string path = "");				//���ø��·��
	void Destory();											//����
	long Play(LyricsCallback callback);
	void SetWnd(CWnd* pParent);
	void vTerminateThread();
private:
	void SetStringReplace(string &strBase, string strSrc, string strDes);
	long time_to_Millisecond(string strTime);	//��Ƭmv time תΪ����
	static UINT uShowLyricsThread(LPVOID pParam);
private:
	LPKaraokeKSC		m_tagKaraokeObject; //��ʶ���
	string				m_strLyricsPath;	//����ļ�·��
	CWinThread*			m_showThread;
	CWnd*				m_pParent;
	bool				m_run;
};

typedef struct tagParamThread{
	CParseLyricsForKSC* pObj;
	LyricsCallback callback;
}LYRICSPARAMTHREAD, *LPLYRICSPARAMTHREAD;