#ifndef _SINK_EVENT_H_
#define _SINK_EVENT_H_
//atl
#include <atlbase.h>
#include <atlwin.h>
#include <atlcom.h>
#include <comdef.h>

#include "TpcConpt.h"

//inkcollector���͵���Ϣ
enum INK_COLLECTOR_MSG
{
	MSG_INK_COLLECTOR_STROKE,   //�ռ������һ�ʻ������͵���Ϣ
};

/////////////////////////////////////////////////////////
//                                          
// class CMyInkEvents
// 
// The CMyInkEvents class overrides the default implementation 
// of the stroke event handler specified in the class 
// InkCollectorEvents. 
//
// It is important to note that there are two steps in 
// receiving an event using this class:
//
// 1. It is necessary to add an override of the event function 
//    to this class.
// 
// 2. Use IInkCollector::SetEventInterest to ensure that the 
//    InkCollector generates the event.  Stroke, CursorInRange, 
//    CursorOutOfRange are the only event interests that are on
//    by default.
//
/////////////////////////////////////////////////////////
class CMyInkEvents : public InkCollectorEvents
{
public:

	// Event: Stroke
	virtual void Stroke(
		IInkCursor* Cursor,
		IInkStrokeDisp* Stroke,
		VARIANT_BOOL *Cancel)
	{
		// Demonstrate that we received the event notification.
		PostMessage(m_hWnd,MSG_INK_COLLECTOR_STROKE,NULL,NULL);
	}

	CMyInkEvents()
	{
		m_hWnd = NULL;
	}

	HRESULT Init(HWND hWnd)
	{
		m_hWnd = hWnd;
		return InkCollectorEvents::Init();
	}    
private:
	HWND m_hWnd;
};


#endif