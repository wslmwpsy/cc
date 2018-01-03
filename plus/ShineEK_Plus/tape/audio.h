// Audio.h: interface for the CAudio class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_AUDIO_H__8C8CE092_7B85_4094_930E_37330464B4E5__INCLUDED_)
#define AFX_AUDIO_H__8C8CE092_7B85_4094_930E_37330464B4E5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

typedef unsigned long DWORD_PTR;

#include <Mmsystem.h>
#include <dsound.h>

static BOOL	m_bPause = false;

class CAudio
{
public:
	void StartOne();		
	BOOL ContinueTape();
	BOOL PauseTape();
	void GetFilePathName(TCHAR * filePathName);
	void SetFilePathName(const TCHAR *filePathName);
	CAudio();
	virtual ~CAudio();

	BOOL Init();
	BOOL Fini();

	BOOL StartTape(const TCHAR* file);
	BOOL StopTape();

protected:
#pragma pack(push)
#pragma pack(1)
	struct WAVE_FILE_HEAD
	{
		WAVE_FILE_HEAD()
		{
			memset(this,0,sizeof(WAVE_FILE_HEAD));
			memcpy(file_head_.fileID,"RIFF",4);
			memcpy(chunk_head_.waveID,"WAVE",4);
			memcpy(chunk_head_.chunkID,"fmt ",4);
			memcpy(data_head_.dataID,"data",4);
			chunk_head_.nChunkSize = sizeof(chunk_head_)-12;
		}
		~WAVE_FILE_HEAD() {};

		struct FILE_HEAD
		{
			char fileID[4];
			UINT nLength;
		}file_head_;
		struct CHUNK_HEAD
		{
			char waveID[4];
			char chunkID[4];
			UINT nChunkSize;
			WORD wFormatTag;
			WORD nChannels;
			UINT nSamplesPerSec;
			UINT nAvgBytesPerSec;
			WORD nBlockAlign;
			WORD nBitsPerSample;
		}chunk_head_;
		struct DATA_HEAD
		{
			char dataID[4];
			UINT nSize;
		}data_head_;
	};
#pragma pack(pop)

	static DWORD WINAPI dsoundCapture(LPVOID pParam);

protected:

	BOOL		m_bInitialized;
	BOOL		m_bTaping;
	UINT		m_nFrameSize;
	HANDLE		m_hFile;
	bool            m_bStartRecord;

	LPDIRECTSOUNDCAPTURE8		m_pDsCapture;
	LPDIRECTSOUNDCAPTUREBUFFER	m_pDsCaptureBuffer;
	HANDLE						m_hCaptureEvent[4];

	TCHAR m_filePathName[256];
};

#endif // !defined(AFX_AUDIO_H__8C8CE092_7B85_4094_930E_37330464B4E5__INCLUDED_)
