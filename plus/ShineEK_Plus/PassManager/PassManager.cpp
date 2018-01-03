#include "StdAfx.h"
#include "PassManager.h"


CPassManager::CPassManager(void)
{
	m_nIndex = 0;
	m_nIceInitCount = 0;
	m_nIceAddSecond = 0;
	m_nGoalScore = 0;
	m_nContinueCount = 0;
	m_nCurIce = 0;
	m_nCurTime = 100;
	m_enState = UN_ACROSS;
	m_nSongIndex = -1;
	m_nSongCount = 0;
	m_nPageCount = 0;
	m_nCurPage = 1;
	memset(m_szPrize, 0x00, sizeof(m_szPrize));
	memset(&m_cur_song, 0x00, sizeof(HUNDRED_SECONDS_PRIZE_SONG));
	m_vec_song.clear();
}

CPassManager::~CPassManager(void)
{
	m_vec_song.clear();
}

void CPassManager::InitVariable()
{
	m_nIndex = 0;
	m_nIceInitCount = 8;
	m_nIceAddSecond = 4;
	m_nGoalScore = 10;
	m_nContinueCount = 4;
	m_nCurIce = 0;
	m_nCurTime = 100;
	m_enState = UN_ACROSS;
	m_nSongIndex = -1;
	m_nSongCount = 0;
	m_nPageCount = 0;
	m_nCurPage = 1;
	memset(m_szPrize, 0x00, sizeof(m_szPrize));
	memset(&m_cur_song, 0x00, sizeof(HUNDRED_SECONDS_PRIZE_SONG));
	m_vec_song.clear();
}


void CPassManager::SetIndex(const int nIndex)
{
	m_nIndex = nIndex;
}
int CPassManager::GetIndex()
{
	return m_nIndex;
}

void CPassManager::SetCurIce(const int nCount)
{
	m_nCurIce = nCount;
}
int CPassManager::GetCurIce()
{
	return m_nCurIce;
}

void CPassManager::SetIceInitCount(const int nCount)
{
	m_nIceInitCount = nCount;
}
int CPassManager::GetIceInitCount()
{
	return m_nIceInitCount;
}
//冰块增长的时间间隔，单位秒
void CPassManager::SetIceAddSecond(const int nSecond)
{
	m_nIceAddSecond = nSecond;
}
int CPassManager::GetIceAddSecond()
{
	return m_nIceAddSecond;
}
//每句目标分数
void CPassManager::SetGoalScore(const int nScore)
{
	m_nGoalScore = nScore;
}
int CPassManager::GetGoalScore()
{
	return m_nGoalScore;
}
//连续达到的次数可扔锤子
void CPassManager::SetContinueCount(const int nCount)
{
	m_nContinueCount = nCount;
}
int CPassManager::GetContinueCount()
{
	return m_nContinueCount;
}
void CPassManager::SetCurTime(const int nCount)
{
	m_nCurTime = nCount;
}
int CPassManager::GetCurTime()
{
	return m_nCurTime;
}

void CPassManager::SetPrize(const TCHAR *pszPrize)
{
	if (wcslen(pszPrize) > 256)	return;

	_tcscpy(m_szPrize, pszPrize);
}
TCHAR *CPassManager::GetPrize()
{
	return m_szPrize;
}

void CPassManager::SetCurSongIndex(const int nIndex)
{
	m_nSongIndex = nIndex;
}
int CPassManager::GetCurSongIndex()
{
	return m_nSongIndex;
}

//歌曲总数
void CPassManager::SetSongCount(const int nCount)
{
	m_nSongCount = nCount;
}
int CPassManager::GetSongCount()
{
	m_nSongCount = m_vec_song.size();

	return m_nSongCount;
}
//歌曲总页数,每页5首
void CPassManager::SetPageCount(const int nCount)
{
	m_nPageCount = nCount;
}
int CPassManager::GetPageCount()
{
	m_nPageCount = m_nSongCount/5 + (m_nSongCount%5)?1:0;
	return m_nPageCount;
}
//当前页
void CPassManager::SetCurPage(const int nCount)
{
	m_nCurPage = nCount;
}
int CPassManager::GetCurPage()
{
	return m_nCurPage;
}
//	0未挑战 1即将挑战 2正在挑战 3成功 4失败
void CPassManager::SetState(enum PASS_STATE state)
{
	m_enState = state;
}
enum PASS_STATE CPassManager::GetState()
{
	return m_enState;
}

void CPassManager::SetCurSong(HUNDRED_SECONDS_PRIZE_SONG* song)
{
	memcpy(&m_cur_song, song, sizeof(HUNDRED_SECONDS_PRIZE_SONG));
}
HUNDRED_SECONDS_PRIZE_SONG* CPassManager::GetCurSong()
{
	return &m_cur_song;
}

void CPassManager::PushBackSong(HUNDRED_SECONDS_PRIZE_SONG pSong)
{
	m_vec_song.push_back(pSong);
}
HUNDRED_SECONDS_PRIZE_SONG* CPassManager::GetSongByIndex(int nIndex)
{
	if (nIndex < 0 || m_vec_song.size() < nIndex )
		return NULL;
	
	return &m_vec_song[nIndex];
}