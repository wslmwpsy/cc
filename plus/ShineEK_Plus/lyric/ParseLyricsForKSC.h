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
	LYRICS_MODE_SHOW = 0,	//歌词显示
	LYRICS_MODE_BEGIN,		//歌词开始演唱
	LYRICS_MODE_HIDE		//歌词隐藏
};

//callback给系统的结构体
typedef struct tagPlayLyricsState{
	ENUM_LYRICS_MODE elm;	//模式 0:歌词显示  1:歌词开始演唱 2:歌词隐藏
	bool location;			//位置 true:上面 false:下面
	string content;			//歌词内容
	CWnd *pWnd;
}PLAYLYRICSSTATE, *LPPLAYLYRICSSTATE;

//每个字的时间
typedef struct tagWordTimeContent
{
	int time;
	string content;
}WordTimeContent;

typedef vector<WordTimeContent> WRODTIMECONTENT_VEC;

//单行歌词结构体
typedef struct tagSingleLineLyrics
{
	long beginTime;							//单行开始时间
	long endTime;							//单行结束时间
	string contents;						//单行句内容
	int	wordsize;							//一行字的个数
	WRODTIMECONTENT_VEC wordTimevec;		//单字时间数组
}SingleLineLyrics;

//总行歌词数组
typedef vector<SingleLineLyrics> SINGLELINELYRICS_VEC;

//歌词结构体
typedef struct tagKaraokeKSC
{
	int rows;									//行数
	bool clear;									//清理
	string songName;							//歌曲名称
	string singerName;							//歌星名称
	SINGLELINELYRICS_VEC lpSingleLineLrcvec;	//总行歌词数组
	
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
	LPKaraokeKSC Init(const string path = "");				//设置歌词路径
	void Destory();											//销毁
	long Play(LyricsCallback callback);
	void SetWnd(CWnd* pParent);
	void vTerminateThread();
private:
	void SetStringReplace(string &strBase, string strSrc, string strDes);
	long time_to_Millisecond(string strTime);	//照片mv time 转为毫秒
	static UINT uShowLyricsThread(LPVOID pParam);
private:
	LPKaraokeKSC		m_tagKaraokeObject; //歌词对象
	string				m_strLyricsPath;	//歌词文件路径
	CWinThread*			m_showThread;
	CWnd*				m_pParent;
	bool				m_run;
};

typedef struct tagParamThread{
	CParseLyricsForKSC* pObj;
	LyricsCallback callback;
}LYRICSPARAMTHREAD, *LPLYRICSPARAMTHREAD;