#include "CShockwaveFlash.h"


class CFlashPlayer : public CShockwaveFlash
{
public:
	CFlashPlayer();
	virtual ~CFlashPlayer();

	void EnableNotification();

protected:
	static CFlashPlayer* pPlayerThis;
	static LRESULT Proc(HWND, UINT, WPARAM, LPARAM);
	FARPROC m_proc;
public:
	//改变拦截flash消息的标示
	void change_intercept_msg_flag(bool flag);
};

class game_flash_player : public CShockwaveFlash
{
public:
	game_flash_player();
	~game_flash_player();
	void EnableNotification(void);
protected:
	static game_flash_player* pGameThis;
	static LRESULT GameWndProc(HWND, UINT, WPARAM, LPARAM);
private:
	FARPROC m_game_proc;
};

class new_flash_player : public CShockwaveFlash
{
public:
	new_flash_player();
	~new_flash_player();
protected:
private:
};