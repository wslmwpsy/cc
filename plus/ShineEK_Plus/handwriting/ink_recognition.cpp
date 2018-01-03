#include "StdAfx.h"
#include ".\ink_recognition.h"

//ink
#include <msinkaut.h>
#include <msinkaut_i.c>
#include <tpcerror.h>

ink_recognition::ink_recognition(void)
{
	m_spIInkRecoContext = NULL;
	m_spIInkDisp = NULL;
	m_spIInkCollector = NULL;
	m_recognize_result = NULL;
}

ink_recognition::~ink_recognition(void)
{
	clear_window();
	m_spIInkDisp.Release();
	// Disable ink input and release the InkCollector object
	if (m_spIInkCollector != NULL)
	{
		m_InkEvents.UnadviseInkCollector();
		m_InkEvents.Release();
		m_spIInkCollector->SetEventInterest(ICEI_DefaultEvents,VARIANT_FALSE);
		m_spIInkCollector->put_Enabled(VARIANT_FALSE);
		m_spIInkCollector.Release();
	}

	// Detach the strokes collection from the recognition context 
	// and stop listening to the recognition events
	if (m_spIInkRecoContext != NULL)
	{
		m_spIInkRecoContext->EndInkInput();
		m_spIInkRecoContext->StopBackgroundRecognition();
		m_spIInkRecoContext.Release();
	}

	// Release the other objects and collections
	m_spIInkRecognizers.Release();
	m_spIInkCollector.Release();
	m_spIInkRecoContext.Release();
	m_spIInkREcognizeGuide.Release();
	m_spIInkRectangle.Release();
	if (m_recognize_result)
	{
		delete []m_recognize_result;
		m_recognize_result = NULL;
	}
}

bool ink_recognition::init_ink_control(HWND hwnd,int result_nums,long left,long right,long top,long bottom)
{
	try
	{

		HRESULT hr=0;
		INITCOMMONCONTROLSEX icc;

		for(int i = 0; i < INK_RECOGNIZER_LANGUAGE_MAX_INDEX; i++)
		{
			m_ink_language_index[i] = -1;
		}

		 // Register the common control classes used by the application
		icc.dwSize = sizeof(icc);
		icc.dwICC = ICC_LISTVIEW_CLASSES | ICC_BAR_CLASSES;
		::InitCommonControlsEx(&icc);

		m_parent_hwnd = hwnd;
		m_recognize_alternate_nums = result_nums;
		m_recognize_result = new CString[m_recognize_alternate_nums];
		if (NULL==m_recognize_result)
		{
			return false;
		}

		hr = CoCreateInstance(CLSID_InkRecognizerContext, 
			NULL, CLSCTX_INPROC_SERVER,
			IID_IInkRecognizerContext, 
			(void **) &m_spIInkRecoContext);
		if (FAILED(hr)) 
		{
			return false;
		}
		// Create the enumerator for the installed recognizers
		hr = m_spIInkRecognizers.CoCreateInstance(CLSID_InkRecognizers);
		if (FAILED(hr)) 
			return NULL;
		// Get the number of the recognizers known to the system
		m_recognizers_count=0;
		hr = m_spIInkRecognizers->get_Count(&m_recognizers_count);

		CComPtr<IInkRecognizer> spIInkRecognizer;

		for (LONG i = 0; i < m_recognizers_count; i++)
		{
			if (FAILED(m_spIInkRecognizers->Item(i, &spIInkRecognizer)))
				continue;

			// Filter out non-language recognizers by checking for
			// the languages supported by the recognizer - there'll be
			// none if it's a gesture or object recognizer.
			CComVariant vLanguages;
			if (SUCCEEDED(spIInkRecognizer->get_Languages(&vLanguages)))
			{
				if ((VT_ARRAY == (VT_ARRAY & vLanguages.vt))            // it should be an array
					&& (NULL != vLanguages.parray)
					&& (0 < vLanguages.parray->rgsabound[0].cElements)) // with at least one element
				{
					// This is a language recognizer. Add its name to the menu.
					CComBSTR bstrName;
					if (SUCCEEDED(spIInkRecognizer->get_Name(&bstrName)))
					{
						if (_tcsstr(bstrName, L"English (US)"))
						{
							m_ink_language_index[INK_RECOGNIZER_LANGUAGE_US_ENGLISH] = i;
						}
						else if (_tcsstr(bstrName, L"中文(简体)"))
						{
							m_ink_language_index[INK_RECOGNIZER_LANGUAGE_SIMPLIFIED_CHINESE] = i;
						}
						else if (_tcsstr(bstrName, L"日本語"))
						{
							m_ink_language_index[INK_RECOGNIZER_LANGUAGE_JAPANESE] = i;
						}
						else if (_tcsstr(bstrName, L"한글"))
						{
							m_ink_language_index[INK_RECOGNIZER_LANGUAGE_KOREA] = i;
						}
					}
				}
			}
			spIInkRecognizer.Release();
		}

		// Create the InkCollector object.
		hr = CoCreateInstance(CLSID_InkCollector, 
			NULL, CLSCTX_INPROC_SERVER, 
			IID_IInkCollector, 
			(void **) &m_spIInkCollector);
		if (FAILED(hr)) 
			return false;

		// Get a pointer to the Ink object
		hr = m_spIInkCollector->get_Ink(&m_spIInkDisp);
		if (FAILED(hr)) 
			return false;

		hr = m_InkEvents.Init(hwnd);
		// Set up connection between Ink Collector and our event sink        
		hr = m_InkEvents.AdviseInkCollector(m_spIInkCollector);
		if (FAILED(hr))
		{
			return false;
		}

		// Tell InkCollector the window to collect ink in
		hr = m_spIInkCollector->put_hWnd((long)hwnd);
		if (FAILED(hr)) 
			return false;
		m_spIInkCollector->SetEventInterest(ICEI_AllEvents,VARIANT_TRUE);

		// Enable ink input in the window
		hr = m_spIInkCollector->put_Enabled(VARIANT_TRUE);
		if (FAILED(hr)) 
			return false;

		hr = m_spIInkRectangle.CoCreateInstance(CLSID_InkRectangle);
		if (FAILED(hr))
		{
			return false;
		}
		m_spIInkRectangle->put_Left(left);
		m_spIInkRectangle->put_Right(right);
		m_spIInkRectangle->put_Top(top);
		m_spIInkRectangle->put_Bottom(bottom);

		hr = m_spIInkREcognizeGuide.CoCreateInstance(CLSID_InkRecognizerGuide);
		if (FAILED(hr))
		{
			return false;
		}
		m_spIInkREcognizeGuide->put_Rows(1);
		m_spIInkREcognizeGuide->put_Columns(1);
		m_spIInkREcognizeGuide->put_Midline(0);
		m_spIInkREcognizeGuide->put_DrawnBox(m_spIInkRectangle);
		m_spIInkREcognizeGuide->put_WritingBox(m_spIInkRectangle);
		m_spIInkRecoContext->putref_Guide(m_spIInkREcognizeGuide);

		return true;
	}
	catch (...)
	{
		
	}
	return false;
}

bool ink_recognition::on_recognizer(void)
{
	try
	{
		HRESULT hr;
		CComPtr<IInkStrokes>   pIInkStrokes = NULL;

		// Get a pointer to the ink stroke collection
		// This collection is a snapshot of the entire ink object
		hr = m_spIInkDisp->get_Strokes(&pIInkStrokes);
		if (FAILED(hr)) 
			return false;

		// Pass the stroke collection to the recognition context
		hr = m_spIInkRecoContext->putref_Strokes(pIInkStrokes);
		if (SUCCEEDED(hr)) 
		{
			// Recognize
			IInkRecognitionResult* pIInkRecoResult = NULL;
			InkRecognitionStatus RecognitionStatus = IRS_NoError;
			hr = m_spIInkRecoContext->Recognize(&RecognitionStatus, &pIInkRecoResult);
			if (SUCCEEDED(hr) && (pIInkRecoResult!= NULL)) 
			{
				// Get the best lCount results
				HRESULT hr;
				IInkRecognitionAlternates *spIInkRecoAlternates = NULL;
				hr = pIInkRecoResult->AlternatesFromSelection(
					0,                              // in: selection start 
					-1,                             // in: selection length; -1 means "up to the last one"
					m_recognize_alternate_nums, // in: the number of alternates we're interested in
					&spIInkRecoAlternates           // out: the receiving pointer
					);

				// Count the returned alternates, it may be less then we asked for
				long lCount = 0;
				if (SUCCEEDED(hr) && SUCCEEDED(spIInkRecoAlternates->get_Count(&lCount)))
				{
					// Get the alternate strings
					CComPtr<IInkRecognitionAlternate> pIInkRecoAlternate = NULL;
					for (LONG iItem = 0; (iItem < lCount) && (iItem < m_recognize_alternate_nums); iItem++)
					{
						// Get the alternate string if there is one
						if (SUCCEEDED(spIInkRecoAlternates->Item(iItem, &pIInkRecoAlternate)))
						{
							BSTR bstr = NULL;
							if (SUCCEEDED(pIInkRecoAlternate->get_String(&bstr)))
							{
								m_recognize_result[iItem].Format(L"%s",bstr);
								SysFreeString(bstr);
							}
						}
						pIInkRecoAlternate = NULL;
					}
				}
			}
			if (m_spIInkRecoContext)
			{
				// Reset the recognition context
				m_spIInkRecoContext->putref_Strokes(NULL);
				//笔划设置为空之后，也要重新设置新的识别区域
				m_spIInkRecoContext->putref_Guide(m_spIInkREcognizeGuide);
			}
		}

		return true;
	}
	catch (...)
	{
		
	}
	return false;
}

bool ink_recognition::clear_window(void)
{
	try
	{
		if (m_spIInkDisp)
		{
			// Delete all strokes from the Ink
			m_spIInkDisp->DeleteStrokes(0);
			// Update the window
			InvalidateRect(m_parent_hwnd, NULL, TRUE);
		}

		return true;
	}
	catch (...)
	{
		
	}
	return false;
}

bool ink_recognition::get_recognize_result(CString *result_string)
{
	try
	{
		for (int i=0;i<m_recognize_alternate_nums;i++)
		{
			result_string[i].Format(L"%s",m_recognize_result[i].GetBuffer(0));
		}
		return true;
	}
	catch (...)
	{
		
	}
	return false;
}

bool ink_recognition::set_language(INK_RECOGNIZER_LANGUAGE language)
{
	try
	{
		// Get a pointer to the recognizer object from the recognizer collection  
		// Use DefaultRecognizer method to get a pointer to the default recognizer
		// or use index for any other one
		HRESULT hr;
		CComPtr<IInkRecognizer> spIInkRecognizer;
		CComPtr<IInkRecognizerContext> spNewContext;

		if (m_ink_language_index[language] < 0)
		{
			return false;
		}

		if(language>m_recognizers_count)
		{
			//使用默认的
			// The first parameter is the language id, passing 0 means that the language 
			// id will be retrieved using the user default-locale identifier
			hr = m_spIInkRecognizers->GetDefaultRecognizer(0, &spIInkRecognizer);
		}
		else
		{
			hr = m_spIInkRecognizers->Item(m_ink_language_index[language], &spIInkRecognizer);
		}

		if (FAILED(hr))
		{
			return false;
		}
		// Create a new recognition context
		hr = spIInkRecognizer->CreateRecognizerContext(&spNewContext);
		if (FAILED(hr))
		{
			return false;
		}
		// Detach and release the old context 
		if (m_spIInkRecoContext != NULL)
		{
			// Reset and release the recognition context
			m_spIInkRecoContext->putref_Strokes(NULL);
			m_spIInkRecoContext=NULL;
		}
		// Get the recognizer's capabilities flags.
		// (use IRC__DontCare if get_Capabilities fails)
		InkRecognizerCapabilities dwCapabilities;
		if (FAILED(spIInkRecognizer->get_Capabilities(&dwCapabilities)))
		{
			dwCapabilities = IRC_DontCare; 
		}
		// Reset the Input Scope to baseline
		CComBSTR bstrFactoid(FACTOID_DEFAULT);
		if (FAILED(spNewContext->put_Factoid(bstrFactoid)))
		{
			return false;
		}

		// Use the new context
		m_spIInkRecoContext.Attach(spNewContext.Detach());


		return true;
	}
	catch (...)
	{
		
	}
	return false;
}

bool ink_recognition::set_pen_attribute(long color,float width)
{
	try
	{
		CComPtr<IInkDrawingAttributes> current_attributes;
		HRESULT hr=0;

        //得到默认属性
		hr = m_spIInkCollector->get_DefaultDrawingAttributes(&current_attributes);
		if (FAILED(hr))
		{
			return false;
		}
		//改变颜色
		hr = current_attributes->put_Color(color);
		if (FAILED(hr))
		{
			return false;
		}
		//改变画笔宽度
		hr = current_attributes->put_Width(width);
		if (FAILED(hr))
		{
			return false;
		}
		return true;
	}
	catch (...)
	{
	}
	return false;
}