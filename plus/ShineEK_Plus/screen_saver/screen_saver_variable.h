#ifndef _SCREEN_SAVER_VARIABLE_H_
#define _SCREEN_SAVER_VARIABLE_H_

//屏保的定时器ID
enum SCREEN_SAVER_TIMER_EVENT_ID
{
	REPAINT_TIMER_EVENT_ID=200,
	SWITCH_SCREEN_SAVER_TIMER_EVENT_ID,
};

//屏保最大图片数
#define SCREEN_SAVER_MAX_PICTURE_COUNT  100

//屏保的显示方式
enum SCREEN_SAVER_SHOW_MODE
{
	SCREEN_SAVER_NO_ANIMATION,   //直接显示没有动画效果
	SCREEN_SAVER_RIGHT_TO_LEFT,  //从右到左
	SCREEN_SAVER_LEFT_TO_RIGHT,  //从左到右
	SCREEN_SAVER_MIDDLE_TO_SIDES_X, //水平方向从中间到两边
	SCREEN_SAVER_MIDDLE_TO_SIDES_Y, //垂直方向从中间到两边
	SCREEN_SAVER_CENTER_TO_AROUND,  //从中心到四周
	SCREEN_SAVER_ZOON_IN,           //放大

	SCREEN_SAVER_SHOW_MODE_COUNT, //显示模式的种数
};


#endif