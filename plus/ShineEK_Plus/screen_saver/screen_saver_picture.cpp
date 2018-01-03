#include "StdAfx.h"
#include ".\screen_saver_picture.h"

screen_saver_picture::screen_saver_picture(void)
{
}

screen_saver_picture::~screen_saver_picture(void)
{
}

void screen_saver_picture::set_screen_rect(int screen_width,int screen_height)
{
	m_screen_width = screen_width;
	m_screen_height = screen_height;
}
void screen_saver_picture::unload_picture(void)
{
	FreePictureData();
}

BOOL screen_saver_picture::Show(HDC hDC, LPRECT pDrawRect,enum SCREEN_SAVER_SHOW_MODE show_mode)
{
	if (hDC == NULL || m_IPicture == NULL)
		return FALSE;

	HRESULT hrP = NULL;
	long Width  = 0;
	long Height = 0;
	RECT DrawRect;
	RECT picture_rect;

	m_IPicture->get_Width(&Width);
	m_IPicture->get_Height(&Height);

	DrawRect.left = pDrawRect->left;
	DrawRect.right = pDrawRect->right;
	DrawRect.top = pDrawRect->top;
	DrawRect.bottom = pDrawRect->bottom;

	switch(show_mode)
	{
	default:
	case SCREEN_SAVER_NO_ANIMATION:   //ֱ����ʾû�ж���Ч��
	case SCREEN_SAVER_RIGHT_TO_LEFT:  //���ҵ���
    case SCREEN_SAVER_LEFT_TO_RIGHT:  //������
	case SCREEN_SAVER_MIDDLE_TO_SIDES_X: //ˮƽ������м䵽����
	case SCREEN_SAVER_MIDDLE_TO_SIDES_Y: //��ֱ������м䵽����
	case SCREEN_SAVER_CENTER_TO_AROUND:  //�����ĵ�����
		{
			//�õ�ͼƬ�����ش�С
			// Get Current DPI - Dot Per Inch
			int CurrentDPI_X = GetDeviceCaps(hDC,LOGPIXELSX);
			int CurrentDPI_Y = GetDeviceCaps(hDC,LOGPIXELSY);
            long picture_width = MulDiv(Width, CurrentDPI_X, HIMETRIC_INCH);
			long picture_height  = MulDiv(Height,  CurrentDPI_Y, HIMETRIC_INCH);

			//������ʾ������ѡ��ͼƬ��ʾ����
			picture_rect.left = (DrawRect.left*picture_width)/m_screen_width;
			picture_rect.top = (DrawRect.top*picture_height)/m_screen_height;
			picture_rect.right = (DrawRect.right*picture_width)/m_screen_width;
			picture_rect.bottom = (DrawRect.bottom*picture_height)/m_screen_height;


			// convert pixels	to himetric 
			picture_rect.left	= MulDiv(picture_rect.left, HIMETRIC_INCH, CurrentDPI_X);
			picture_rect.top	= MulDiv(picture_rect.top, HIMETRIC_INCH, CurrentDPI_Y);
			picture_rect.right	= MulDiv(picture_rect.right, HIMETRIC_INCH, CurrentDPI_X);
			picture_rect.bottom	= MulDiv(picture_rect.bottom, HIMETRIC_INCH, CurrentDPI_Y);
		}
		break;
	case SCREEN_SAVER_ZOON_IN:             //�Ŵ�
		{
			picture_rect.left = 0;
			picture_rect.top = 0;
			picture_rect.right = Width;
			picture_rect.bottom = Height;
		}
		break;
	}

	hrP = m_IPicture->Render(hDC,
		DrawRect.left,                  // ��hdc�ϵ�ˮƽ����
		DrawRect.top,                   // ��hdc�ϵĴ�ֱ����
		DrawRect.right - DrawRect.left, // ˮƽ���
		DrawRect.bottom - DrawRect.top, // ��ֱ�߶�
		picture_rect.left,              //��Դͼ���ϵ�ˮƽƫ��
		Height-picture_rect.top,        //��Դͼ���ϵĴ�ֱƫ��
		picture_rect.right - picture_rect.left,  //��Դͼ����ˮƽ����������
		picture_rect.top-picture_rect.bottom,    //��Դͼ���ϴ�ֱ���������� 
		&DrawRect);

	if (SUCCEEDED(hrP)) return(TRUE);
	return(FALSE);
}