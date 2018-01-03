#pragma once
#include "../message.h"
#include <vector>
using namespace std;

// ����ά �ؿ�������
class CPassManager
{
public:
	CPassManager(void);
	~CPassManager(void);

	void InitVariable();
	//�ؿ�����
	void SetIndex(const int nIndex);
	int GetIndex();
	//ʣ�������
	void SetCurIce(const int nCount);
	int GetCurIce();
	//�����ܸ���
	void SetIceInitCount(const int nCount);
	int GetIceInitCount();
	//����������ʱ��������λ��
	void SetIceAddSecond(const int nSecond);
	int GetIceAddSecond();
	//ÿ��Ŀ�����
	void SetGoalScore(const int nScore);
	int GetGoalScore();
	//�����ﵽ�Ĵ������Ӵ���
	void SetContinueCount(const int nCount);
	int GetContinueCount();
	//ʣ��ʱ��(0-100)
	void SetCurTime(const int nCount);
	int GetCurTime();
	//������Ϣ
	void SetPrize(const TCHAR *pszPrize);
	TCHAR *GetPrize();
	//��������
	void SetSongCount(const int nCount);
	int GetSongCount();
	//������ҳ��,ÿҳ5��
	void SetPageCount(const int nCount);
	int GetPageCount();
	//��ǰҳ
	void SetCurPage(const int nCount);
	int GetCurPage();

	//��ǰ���ĸ�������
	void SetCurSongIndex(const int nIndex);
	int GetCurSongIndex();
	//���ر�־ 0δ��ս 1������ս 2������ս 3�ɹ� 4ʧ��
	void SetState(enum PASS_STATE state);
	enum PASS_STATE GetState();
	//��ǰ������Ϣ
	void SetCurSong(HUNDRED_SECONDS_PRIZE_SONG* pSong);
	HUNDRED_SECONDS_PRIZE_SONG* GetCurSong();

	void PushBackSong(HUNDRED_SECONDS_PRIZE_SONG pSong);
	HUNDRED_SECONDS_PRIZE_SONG *GetSongByIndex(int nIndex);
public:
	int		m_nIndex;				//�ؿ�����
	int		m_nIceInitCount;			//��ʼ��������
	int		m_nIceAddSecond ;		//�������ӵ�ʱ����
	int		m_nContinueCount;	//�ﵽ�������������������Ӵ���
	int		m_nGoalScore;		//�Ӵ��ӵ�Ŀ�����

	int		m_nCurIce;			//ʣ�������
	int		m_nCurTime;				//ʣ��ʱ��(0-100)
	TCHAR	m_szPrize[256];			//������Ϣ

	int		m_nSongIndex;			//��ǰ���ĸ�������
	int		m_nSongCount;
	int		m_nPageCount;
	int		m_nCurPage;

	enum PASS_STATE		m_enState;			//���ر�־ 0δ��ս 1������ս 2�ɹ� 3ʧ��
	HUNDRED_SECONDS_PRIZE_SONG m_cur_song;	//��ǰ������Ϣ

	vector<HUNDRED_SECONDS_PRIZE_SONG> m_vec_song;	//
};

