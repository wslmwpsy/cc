// Machine generated IDispatch wrapper class(es) created by Microsoft Visual C++

// NOTE: Do not modify the contents of this file.  If this class is regenerated by
//  Microsoft Visual C++, your modifications will be overwritten.


#include "stdafx.h"
#include "shplayocx.h"

/////////////////////////////////////////////////////////////////////////////
// CShPlayOCX

IMPLEMENT_DYNCREATE(CShPlayOCX, CWnd)

/////////////////////////////////////////////////////////////////////////////
// CShPlayOCX properties

CString CShPlayOCX::GetGszFileName()
{
	CString result;
	GetProperty(0x1, VT_BSTR, (void*)&result);
	return result;
}

void CShPlayOCX::SetGszFileName(LPCTSTR propVal)
{
	SetProperty(0x1, VT_BSTR, propVal);
}

short CShPlayOCX::GetTrackNo()
{
	short result;
	GetProperty(0x2, VT_I2, (void*)&result);
	return result;
}

void CShPlayOCX::SetTrackNo(short propVal)
{
	SetProperty(0x2, VT_I2, propVal);
}

short CShPlayOCX::GetHwidth()
{
	short result;
	GetProperty(0x3, VT_I2, (void*)&result);
	return result;
}

void CShPlayOCX::SetHwidth(short propVal)
{
	SetProperty(0x3, VT_I2, propVal);
}

short CShPlayOCX::GetHheight()
{
	short result;
	GetProperty(0x4, VT_I2, (void*)&result);
	return result;
}

void CShPlayOCX::SetHheight(short propVal)
{
	SetProperty(0x4, VT_I2, propVal);
}

long CShPlayOCX::GetMpegStream()
{
	long result;
	GetProperty(0x5, VT_I4, (void*)&result);
	return result;
}

void CShPlayOCX::SetMpegStream(long propVal)
{
	SetProperty(0x5, VT_I4, propVal);
}

long CShPlayOCX::GetStepFrames()
{
	long result;
	GetProperty(0x6, VT_I4, (void*)&result);
	return result;
}

void CShPlayOCX::SetStepFrames(long propVal)
{
	SetProperty(0x6, VT_I4, propVal);
}

CString CShPlayOCX::GetGszWavFileName()
{
	CString result;
	GetProperty(0x7, VT_BSTR, (void*)&result);
	return result;
}

void CShPlayOCX::SetGszWavFileName(LPCTSTR propVal)
{
	SetProperty(0x7, VT_BSTR, propVal);
}

/////////////////////////////////////////////////////////////////////////////
// CShPlayOCX operations

void CShPlayOCX::Stop()
{
	InvokeHelper(0x8, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void CShPlayOCX::Play()
{
	InvokeHelper(0x9, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

long CShPlayOCX::OpenDrv()
{
	long result;
	InvokeHelper(0xa, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

void CShPlayOCX::CloseDrv()
{
	InvokeHelper(0xb, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

long CShPlayOCX::OpenFile()
{
	long result;
	InvokeHelper(0xc, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

void CShPlayOCX::Volume(short voll, short volr)
{
	static BYTE parms[] =
		VTS_I2 VTS_I2;
	InvokeHelper(0xd, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 voll, volr);
}

void CShPlayOCX::Balance(short soundtrack)
{
	static BYTE parms[] =
		VTS_I2;
	InvokeHelper(0xe, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 soundtrack);
}

short CShPlayOCX::GetState()
{
	short result;
	InvokeHelper(0xf, DISPATCH_METHOD, VT_I2, (void*)&result, NULL);
	return result;
}

void CShPlayOCX::TV()
{
	InvokeHelper(0x10, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void CShPlayOCX::VGA()
{
	InvokeHelper(0x11, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void CShPlayOCX::CloseFile()
{
	InvokeHelper(0x12, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void CShPlayOCX::Reset()
{
	InvokeHelper(0x13, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

long CShPlayOCX::Step()
{
	long result;
	InvokeHelper(0x14, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

void CShPlayOCX::StepBack()
{
	InvokeHelper(0x15, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void CShPlayOCX::Seek(long Position)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x16, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 Position);
}

long CShPlayOCX::Set(long flag, long value)
{
	long result;
	static BYTE parms[] =
		VTS_I4 VTS_I4;
	InvokeHelper(0x17, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
		flag, value);
	return result;
}

long CShPlayOCX::Get(long flag)
{
	long result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x18, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
		flag);
	return result;
}

long CShPlayOCX::CheckHardware()
{
	long result;
	InvokeHelper(0x19, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CShPlayOCX::ResetDriver()
{
	long result;
	InvokeHelper(0x1a, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CShPlayOCX::InitOSD(long nCards, LPCTSTR sPalOSDFile, long keyColor)
{
	long result;
	static BYTE parms[] =
		VTS_I4 VTS_BSTR VTS_I4;
	InvokeHelper(0x1b, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
		nCards, sPalOSDFile, keyColor);
	return result;
}

long CShPlayOCX::LoadOSDFile(LPCTSTR sOSDFile)
{
	long result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x1c, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
		sOSDFile);
	return result;
}

long CShPlayOCX::LoadBmpFile(LPCTSTR sBmpFile)
{
	long result;
	static BYTE parms[] =
		VTS_BSTR;
	InvokeHelper(0x1d, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
		sBmpFile);
	return result;
}

long CShPlayOCX::LoadText(LPCTSTR sText, long fgcl, long shcl, long lfHeight, long lfWidth, long lfEscapement, long lfOrientation, long lfWeight, short lfItalic, short lfUnderline, short lfStrikeOut, short lfCharSet, short lfOutPrecision, 
		short lfClipPrecision, short lfQuality, short lfPitchAndFamily, LPCTSTR lfFaceName)
{
	long result;
	static BYTE parms[] =
		VTS_BSTR VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I2 VTS_I2 VTS_I2 VTS_I2 VTS_I2 VTS_I2 VTS_I2 VTS_I2 VTS_BSTR;
	InvokeHelper(0x1e, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
		sText, fgcl, shcl, lfHeight, lfWidth, lfEscapement, lfOrientation, lfWeight, lfItalic, lfUnderline, lfStrikeOut, lfCharSet, lfOutPrecision, lfClipPrecision, lfQuality, lfPitchAndFamily, lfFaceName);
	return result;
}

long CShPlayOCX::UnloadOSD(long pOSDBuf)
{
	long result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x1f, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
		pOSDBuf);
	return result;
}

long CShPlayOCX::SetOSDBuf(long iCard, long iOSD, long pOSDBuf)
{
	long result;
	static BYTE parms[] =
		VTS_I4 VTS_I4 VTS_I4;
	InvokeHelper(0x20, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
		iCard, iOSD, pOSDBuf);
	return result;
}

long CShPlayOCX::GetOSDBuf(long iCard, long iOSD)
{
	long result;
	static BYTE parms[] =
		VTS_I4 VTS_I4;
	InvokeHelper(0x21, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
		iCard, iOSD);
	return result;
}

long CShPlayOCX::SetPlayVarOSD(long iCard, long iOSD, long play_mode, long nRepeat, long iHSpeed, long iVSpeed, long nDelayTime, long sx, long sy, long ex, long ey)
{
	long result;
	static BYTE parms[] =
		VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4 VTS_I4;
	InvokeHelper(0x22, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
		iCard, iOSD, play_mode, nRepeat, iHSpeed, iVSpeed, nDelayTime, sx, sy, ex, ey);
	return result;
}

long CShPlayOCX::GetPlayStateOSD(long iCard, long iOSD)
{
	long result;
	static BYTE parms[] =
		VTS_I4 VTS_I4;
	InvokeHelper(0x23, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
		iCard, iOSD);
	return result;
}

long CShPlayOCX::GetOSDScreenSizeW()
{
	long result;
	InvokeHelper(0x24, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CShPlayOCX::GetOSDScreenSizeH()
{
	long result;
	InvokeHelper(0x25, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CShPlayOCX::GetOSDSizeW(long pOSDBuf)
{
	long result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x26, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
		pOSDBuf);
	return result;
}

long CShPlayOCX::GetOSDSizeH(long pOSDBuf)
{
	long result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x27, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
		pOSDBuf);
	return result;
}

long CShPlayOCX::PlayOSD(long iCard, long iOSD)
{
	long result;
	static BYTE parms[] =
		VTS_I4 VTS_I4;
	InvokeHelper(0x28, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
		iCard, iOSD);
	return result;
}

long CShPlayOCX::StopOSD(long iCard, long iOSD)
{
	long result;
	static BYTE parms[] =
		VTS_I4 VTS_I4;
	InvokeHelper(0x29, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
		iCard, iOSD);
	return result;
}

long CShPlayOCX::FinishOSD()
{
	long result;
	InvokeHelper(0x2a, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CShPlayOCX::Command(long cmd, long flag, long value)
{
	long result;
	static BYTE parms[] =
		VTS_I4 VTS_I4 VTS_I4;
	InvokeHelper(0x2b, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
		cmd, flag, value);
	return result;
}

void CShPlayOCX::Pause()
{
	InvokeHelper(0x2c, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

void CShPlayOCX::OSDSetSwapper(long pSwapper)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x2d, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 pSwapper);
}

void CShPlayOCX::OSDSwitchKTV(long ktv)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x2e, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 ktv);
}

void CShPlayOCX::OSDKeyDown(long key)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x2f, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 key);
}

void CShPlayOCX::OSDListChanged(long list)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x30, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 list);
}

void CShPlayOCX::VODEnableDbDisplay(long e)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x31, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 e);
}

void CShPlayOCX::VODSetScreenWindow(long hwnd)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x32, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 hwnd);
}

void CShPlayOCX::VODShowScreenVideo(long e)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x33, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 e);
}

long CShPlayOCX::Preview_Open(LPCTSTR pMedia, long hwnd)
{
	long result;
	static BYTE parms[] =
		VTS_BSTR VTS_I4;
	InvokeHelper(0x34, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
		pMedia, hwnd);
	return result;
}

long CShPlayOCX::Preview_Close()
{
	long result;
	InvokeHelper(0x35, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CShPlayOCX::Preview_Control(long nCode, long argv0, long argv1)
{
	long result;
	static BYTE parms[] =
		VTS_I4 VTS_I4 VTS_I4;
	InvokeHelper(0x36, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
		nCode, argv0, argv1);
	return result;
}

long CShPlayOCX::TV_Open(LPCTSTR pDev, long hwnd, long nSignal)
{
	long result;
	static BYTE parms[] =
		VTS_BSTR VTS_I4 VTS_I4;
	InvokeHelper(0x37, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
		pDev, hwnd, nSignal);
	return result;
}

long CShPlayOCX::TV_Close()
{
	long result;
	InvokeHelper(0x38, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CShPlayOCX::TV_Control(long nCode, long argv0, long argv1)
{
	long result;
	static BYTE parms[] =
		VTS_I4 VTS_I4 VTS_I4;
	InvokeHelper(0x39, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
		nCode, argv0, argv1);
	return result;
}

long CShPlayOCX::Live_Open(long n, LPCTSTR pMedia)
{
	long result;
	static BYTE parms[] =
		VTS_I4 VTS_BSTR;
	InvokeHelper(0x3a, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
		n, pMedia);
	return result;
}

long CShPlayOCX::Live_Close(long n)
{
	long result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x3b, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
		n);
	return result;
}

long CShPlayOCX::Live_Control(long n, long nCode, long argv0, long argv1)
{
	long result;
	static BYTE parms[] =
		VTS_I4 VTS_I4 VTS_I4 VTS_I4;
	InvokeHelper(0x3c, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
		n, nCode, argv0, argv1);
	return result;
}

void CShPlayOCX::AboutBox()
{
	InvokeHelper(0xfffffdd8, DISPATCH_METHOD, VT_EMPTY, NULL, NULL);
}

long CShPlayOCX::WaveMixer_Play(LPCTSTR sWaveFile, long fLoop, long fMusicOut)
{
	long result;
	static BYTE parms[] =
		VTS_BSTR VTS_I4 VTS_I4;
	InvokeHelper(0x65, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
		sWaveFile, fLoop, fMusicOut);
	return result;
}

long CShPlayOCX::WaveMixer_Stop()
{
	long result;
	InvokeHelper(0x66, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

long CShPlayOCX::WaveMixer_SetTone(long nTone)
{
	long result;
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x67, DISPATCH_METHOD, VT_I4, (void*)&result, parms,
		nTone);
	return result;
}

long CShPlayOCX::WaveMixer_GetTone()
{
	long result;
	InvokeHelper(0x68, DISPATCH_METHOD, VT_I4, (void*)&result, NULL);
	return result;
}

void CShPlayOCX::Ctrl_SetNotifyWindow(long hwndNotify)
{
	static BYTE parms[] =
		VTS_I4;
	InvokeHelper(0x69, DISPATCH_METHOD, VT_EMPTY, NULL, parms,
		 hwndNotify);
}
