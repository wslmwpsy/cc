#pragma once
#include "../message.h"
#include <vector>
using namespace std;

// 百秒夺奖 关卡管理类
class CPassManager
{
public:
	CPassManager(void);
	~CPassManager(void);

	void InitVariable();
	//关卡索引
	void SetIndex(const int nIndex);
	int GetIndex();
	//剩余冰块数
	void SetCurIce(const int nCount);
	int GetCurIce();
	//冰块总个数
	void SetIceInitCount(const int nCount);
	int GetIceInitCount();
	//冰块增长的时间间隔，单位秒
	void SetIceAddSecond(const int nSecond);
	int GetIceAddSecond();
	//每句目标分数
	void SetGoalScore(const int nScore);
	int GetGoalScore();
	//连续达到的次数可扔锤子
	void SetContinueCount(const int nCount);
	int GetContinueCount();
	//剩余时间(0-100)
	void SetCurTime(const int nCount);
	int GetCurTime();
	//奖励信息
	void SetPrize(const TCHAR *pszPrize);
	TCHAR *GetPrize();
	//歌曲总数
	void SetSongCount(const int nCount);
	int GetSongCount();
	//歌曲总页数,每页5首
	void SetPageCount(const int nCount);
	int GetPageCount();
	//当前页
	void SetCurPage(const int nCount);
	int GetCurPage();

	//当前唱的歌曲索引
	void SetCurSongIndex(const int nIndex);
	int GetCurSongIndex();
	//闯关标志 0未挑战 1即将挑战 2正在挑战 3成功 4失败
	void SetState(enum PASS_STATE state);
	enum PASS_STATE GetState();
	//当前歌曲信息
	void SetCurSong(HUNDRED_SECONDS_PRIZE_SONG* pSong);
	HUNDRED_SECONDS_PRIZE_SONG* GetCurSong();

	void PushBackSong(HUNDRED_SECONDS_PRIZE_SONG pSong);
	HUNDRED_SECONDS_PRIZE_SONG *GetSongByIndex(int nIndex);
public:
	int		m_nIndex;				//关卡索引
	int		m_nIceInitCount;			//初始冰块数量
	int		m_nIceAddSecond ;		//冰块增加的时间间隔
	int		m_nContinueCount;	//达到分数的连续次数可以扔锤子
	int		m_nGoalScore;		//扔锤子的目标分数

	int		m_nCurIce;			//剩余冰块数
	int		m_nCurTime;				//剩余时间(0-100)
	TCHAR	m_szPrize[256];			//奖励信息

	int		m_nSongIndex;			//当前唱的歌曲索引
	int		m_nSongCount;
	int		m_nPageCount;
	int		m_nCurPage;

	enum PASS_STATE		m_enState;			//闯关标志 0未挑战 1正在挑战 2成功 3失败
	HUNDRED_SECONDS_PRIZE_SONG m_cur_song;	//当前歌曲信息

	vector<HUNDRED_SECONDS_PRIZE_SONG> m_vec_song;	//
};

