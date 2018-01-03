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
	case SCREEN_SAVER_NO_ANIMATION:   //直接显示没有动画效果
	case SCREEN_SAVER_RIGHT_TO_LEFT:  //从右到左
    case SCREEN_SAVER_LEFT_TO_RIGHT:  //从左到右
	case SCREEN_SAVER_MIDDLE_TO_SIDES_X: //水平方向从中间到两边
	case SCREEN_SAVER_MIDDLE_TO_SIDES_Y: //垂直方向从中间到两边
	case SCREEN_SAVER_CENTER_TO_AROUND:  //从中心到四周
		{
			//得到图片的像素大小
			// Get Current DPI - Dot Per Inch
			int CurrentDPI_X = GetDeviceCaps(hDC,LOGPIXELSX);
			int CurrentDPI_Y = GetDeviceCaps(hDC,LOGPIXELSY);
            long picture_width = MulDiv(Width, CurrentDPI_X, HIMETRIC_INCH);
			long picture_height  = MulDiv(Height,  CurrentDPI_Y, HIMETRIC_INCH);

			//按照显示比例，选择图片显示区域
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
	case SCREEN_SAVER_ZOON_IN:             //放大
		{
			picture_rect.left = 0;
			picture_rect.top = 0;
			picture_rect.right = Width;
			picture_rect.bottom = Height;
		}
		break;
	}

	hrP = m_IPicture->Render(hDC,
		DrawRect.left,                  // 在hdc上的水平坐标
		DrawRect.top,                   // 在hdc上的垂直坐标
		DrawRect.right - DrawRect.left, // 水平宽度
		DrawRect.bottom - DrawRect.top, // 垂直高度
		picture_rect.left,              //在源图像上的水平偏移
		Height-picture_rect.top,        //在源图像上的垂直偏移
		picture_rect.right - picture_rect.left,  //在源图像上水平拷贝的数量
		picture_rect.top-picture_rect.bottom,    //在源图像上垂直拷贝的数量 
		&DrawRect);

	if (SUCCEEDED(hrP)) return(TRUE);
	return(FALSE);
}