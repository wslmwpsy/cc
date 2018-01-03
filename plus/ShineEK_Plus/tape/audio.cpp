#include "StdAfx.h"
#include "audio.h"

#pragma comment(lib,"dsound")
#pragma comment(lib,"dxguid")

#define SAFE_RELEASE(p) if(p) { (p)->Release(); (p)=NULL; }
#define RECORD_SAMPLE_RATE         48000     //音频采样率


CAudio::CAudio()
	:m_bInitialized(FALSE)
	,m_bTaping(FALSE)
	,m_pDsCapture(NULL)
	,m_pDsCaptureBuffer(NULL)

{
	memset(m_filePathName, 0, sizeof(m_filePathName));
}

CAudio::~CAudio()
{
	Fini();
}

BOOL CAudio::Init()
{
	if(m_bInitialized) return TRUE;

	HRESULT hr = DirectSoundCaptureCreate8(NULL,&m_pDsCapture,NULL);
	if(FAILED(hr))
		return FALSE;

	PCMWAVEFORMAT pcmwf;
	DSCBUFFERDESC dsb;
	
	memset(&pcmwf,0,sizeof(PCMWAVEFORMAT)); 
	pcmwf.wf.wFormatTag = WAVE_FORMAT_PCM; 
	pcmwf.wf.nChannels = 2; 
	pcmwf.wf.nSamplesPerSec = RECORD_SAMPLE_RATE;
	pcmwf.wBitsPerSample = 16;
	pcmwf.wf.nBlockAlign = pcmwf.wf.nChannels*pcmwf.wBitsPerSample/8;
	pcmwf.wf.nAvgBytesPerSec = pcmwf.wf.nChannels*pcmwf.wBitsPerSample*pcmwf.wf.nSamplesPerSec/8; 
	
	m_nFrameSize = 100*2*RECORD_SAMPLE_RATE*2/1000;
	memset(&dsb,0,sizeof(DSCBUFFERDESC));
	dsb.dwSize = sizeof(DSCBUFFERDESC);
	dsb.lpwfxFormat = (LPWAVEFORMATEX)&pcmwf;
	dsb.dwBufferBytes = 2*m_nFrameSize;
	
	hr = m_pDsCapture->CreateCaptureBuffer(&dsb,&m_pDsCaptureBuffer,NULL);
	if(FAILED(hr))
	{
		SAFE_RELEASE(m_pDsCapture);
		return FALSE;
	}
	
	LPDIRECTSOUNDNOTIFY8 lpDsNotify = NULL;
	hr = m_pDsCaptureBuffer->QueryInterface(IID_IDirectSoundNotify8,(LPVOID*)&lpDsNotify);
	if(FAILED(hr))
	{
		SAFE_RELEASE(m_pDsCapture);
		SAFE_RELEASE(m_pDsCaptureBuffer);
		return FALSE;
	}

	for(int i=0;i<4;++i)
	{
		m_hCaptureEvent[i] = CreateEvent(NULL,FALSE,FALSE,NULL);
	}

	DSBPOSITIONNOTIFY dsbp[2];
	dsbp[0].dwOffset = m_nFrameSize-1;
	dsbp[0].hEventNotify = m_hCaptureEvent[0];
	dsbp[1].dwOffset = 2*m_nFrameSize-1;
	dsbp[1].hEventNotify = m_hCaptureEvent[1];
	lpDsNotify->SetNotificationPositions(2,dsbp);
	SAFE_RELEASE(lpDsNotify);
	
	DWORD id;
	HANDLE hIn = CreateThread(NULL,0,dsoundCapture,(LPVOID)this,0,&id);
	CloseHandle(hIn);

	m_bInitialized = TRUE;
	return TRUE;
}

BOOL CAudio::Fini()
{
	if(!m_bInitialized) return FALSE;

	StopTape();
	SetEvent(m_hCaptureEvent[2]);
	WaitForSingleObject(m_hCaptureEvent[3],INFINITE);
	SAFE_RELEASE(m_pDsCaptureBuffer);
	SAFE_RELEASE(m_pDsCapture);

	for(int i=0;i<4;++i)
	{
		CloseHandle(m_hCaptureEvent[i]);
		m_hCaptureEvent[i]=NULL;
	}

	m_bInitialized = FALSE;
	return TRUE;
}

BOOL CAudio::StartTape(const TCHAR* file)
{
	if(!m_bInitialized || m_bTaping) return FALSE;

	m_hFile = CreateFile(file,GENERIC_READ|GENERIC_WRITE,FILE_SHARE_READ,NULL,CREATE_ALWAYS,0,NULL);
	if(INVALID_HANDLE_VALUE == m_hFile)
		return FALSE;
	SetFilePointer(m_hFile,sizeof(WAVE_FILE_HEAD),0,FILE_BEGIN);
	HRESULT hr = m_pDsCaptureBuffer->Start(DSCBSTART_LOOPING);
	if(FAILED(hr)) 
	{
		return FALSE;
	}

	SetFilePathName(file);
	m_bTaping = TRUE;
	return TRUE;
}


BOOL CAudio::StopTape()
{
	if(!m_bInitialized || !m_bTaping) return FALSE;
	HRESULT hr = m_pDsCaptureBuffer->Stop();
	if(FAILED(hr)) return FALSE;

	if (m_hFile)
	{
		DWORD wt,fs;
		FlushFileBuffers(m_hFile);
		SetFilePointer(m_hFile,0,0,FILE_BEGIN);
		WAVE_FILE_HEAD head;
		head.chunk_head_.wFormatTag = WAVE_FORMAT_PCM;
		head.chunk_head_.nSamplesPerSec = RECORD_SAMPLE_RATE;
		head.chunk_head_.nChannels = 2;
		head.chunk_head_.nBitsPerSample = 16;
		head.chunk_head_.nBlockAlign = 4;
		head.chunk_head_.nAvgBytesPerSec = RECORD_SAMPLE_RATE*2*2;
		fs = GetFileSize(m_hFile,NULL);
		head.file_head_.nLength = fs-sizeof(head.file_head_);
		head.data_head_.nSize = fs-sizeof(WAVE_FILE_HEAD);
		WriteFile(m_hFile,&head,sizeof(WAVE_FILE_HEAD),&wt,NULL);
		CloseHandle(m_hFile);
		m_hFile = NULL;
	}

	m_bTaping = FALSE;
	return TRUE;
}

DWORD CAudio::dsoundCapture(LPVOID pParam)
{
	CAudio* pAudio = (CAudio*)pParam;

	HRESULT hr;
	LPVOID ptr = NULL;
	DWORD wt,bytes = 0;

	while(TRUE)
	{
		//返回值：促使该函数返回的事件的ID
		DWORD id = WaitForMultipleObjects(3,pAudio->m_hCaptureEvent,FALSE,INFINITE);
		if(id == 2)
		{
			//表示要进行反初始化，该线程要终止
			break;
		}

		if(id)
			hr = pAudio->m_pDsCaptureBuffer->Lock(pAudio->m_nFrameSize,pAudio->m_nFrameSize,&ptr,&bytes,NULL,NULL,0L);
		else
			hr = pAudio->m_pDsCaptureBuffer->Lock(0,pAudio->m_nFrameSize,&ptr,&bytes,NULL,NULL,0L);
		if(SUCCEEDED(hr))
		{
			if((m_bPause==FALSE) && (pAudio->m_hFile))
			{
				WriteFile(pAudio->m_hFile,ptr,bytes,&wt,NULL);
			}
			pAudio->m_pDsCaptureBuffer->Unlock(ptr,bytes,NULL,0);
		}
	}
	//把事件置为有信号状态，让反初始化完成
	SetEvent(pAudio->m_hCaptureEvent[3]);

	return 0;
}

#undef SAFE_RELEASE

void CAudio::SetFilePathName(const TCHAR *filePathName)
{
	_tcscpy(m_filePathName, filePathName);
}

BOOL CAudio::PauseTape()
{
	m_bPause = TRUE;
	return TRUE;
}

BOOL CAudio::ContinueTape()
{
	m_bPause = FALSE;
	return TRUE;
}

void CAudio::GetFilePathName(TCHAR *filePathName)
{
	_tcscpy(filePathName, m_filePathName);
}

void CAudio::StartOne()
{
	m_bStartRecord = TRUE;
}