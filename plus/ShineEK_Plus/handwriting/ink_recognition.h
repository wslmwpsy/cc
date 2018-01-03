#pragma once

#include "sink_event.h"

enum INK_RECOGNIZER_LANGUAGE
{
	INK_RECOGNIZER_LANGUAGE_US_ENGLISH=0,          //��ʽӢ��
	INK_RECOGNIZER_LANGUAGE_SIMPLIFIED_CHINESE,    //��������
	INK_RECOGNIZER_LANGUAGE_TRADITIONAL_CHINESE,   //��������
	INK_RECOGNIZER_LANGUAGE_JAPANESE,              //����
	INK_RECOGNIZER_LANGUAGE_KOREA,                 //����
	
	INK_RECOGNIZER_LANGUAGE_MAX_INDEX,
};

class ink_recognition
{
public:
	ink_recognition(void);
	~ink_recognition(void);

	/*
	���ܣ���ʼ���ؼ�
	������
		hwnd����д�������þ��
		result_nums��ʶ����������ָ���
	����ֵ��
		true���ɹ�
		false��ʧ��
	*/
	bool init_ink_control(HWND hwnd,int result_nums,long left,long right,long top,long bottom);

	/*
	���ܣ�ʶ����д
	������
	    void
	����ֵ��
	    true���ɹ�
		false��ʧ��
	*/
	bool on_recognizer(void);

	/*
	���ܣ����
	������
	    void
	����ֵ��
	    true���ɹ�
		false��ʧ��
	*/
	bool clear_window(void);

	/*
	���ܣ��õ�ʶ��������ַ���
	������
	    result_string������ַ���
	����ֵ��
	    true���ɹ�
		false��ʧ��
	*/
	bool get_recognize_result(CString *result_string);

	/*
	���ܣ��ı�����
	������
	   language������
   ����ֵ��
       true���ɹ�
	   false��ʧ��
	*/
	bool set_language(INK_RECOGNIZER_LANGUAGE language);

	/*
	���ܣ����û�������
	������
	    color����ɫ
		width�����ʿ��
	����ֵ��
	    true���ɹ�
		false��ʧ��
	*/
	bool set_pen_attribute(long color,float width);

private:
	HWND m_parent_hwnd;  //�����
	CMyInkEvents m_InkEvents; //�¼�
	CComPtr<IInkCollector>          m_spIInkCollector;
	CComPtr<IInkDisp>               m_spIInkDisp;
	CComPtr<IInkRectangle>          m_spIInkRectangle;
	CComPtr<IInkRecognizerGuide>    m_spIInkREcognizeGuide;
	CComPtr<IInkRecognizerContext>  m_spIInkRecoContext;
	CComPtr<IInkRecognizers>        m_spIInkRecognizers;

	int m_recognize_alternate_nums; //ʶ����������ָ��� 
	CString   *m_recognize_result;  //�洢ʶ��������ַ�
	long m_recognizers_count;       //����ʶ���������

	int m_ink_language_index[INK_RECOGNIZER_LANGUAGE_MAX_INDEX];
};
