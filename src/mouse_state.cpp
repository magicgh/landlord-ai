/*
 * @Author: Leo Zhang
 * @Date: 2020-07-13 16:30:00
 * @LastEditTime: 2020-07-14 22:44:06
 * @LastEditors: Please set LastEditors
 * @Description: MouseState class
 * @FilePath: \landlord-ai\src\mouse_state.cpp
 */ 



#define SHOW_CONSOLE
#include <graphics.h>
#include "components/mouse_state.h"

MouseState::MouseState()
{
	interval = 0.4f;
	
	for (int i = 0; i < 3; i++) {
		curMouseState[i] = MOUSE_UP;
		clickEvent[i] = false;
		releaseEvent[i] = false;

		doubleClickEvent[i] = false;
		
		xClick[i] = yClick[i] = 0;

		//初始赋一个较小的负值
		clickTimes[i] = -1000;

		isPressMsg[i] = isReleaseMsg[i] = false;
	}
}

//设置双击触发的两次点击最大时间间隔（单位：秒）
void MouseState::setIntervalTime(double time_seconds)
{
	interval = (time_seconds > 0) ? time_seconds : 0;
}

//重置鼠标按键状态，必须在每一帧中，处理鼠标消息之前调用
void MouseState::resetState()
{
	for (int i = 0; i < 3; i++) {

		clickEvent[i] = false;
		releaseEvent[i] = false;

		doubleClickEvent[i] = false;

		isPressMsg[i] = isReleaseMsg[i] = false;
	}
}


//鼠标消息处理函数
void MouseState::handleMouseMsg(mouse_msg msg)
{
	bool isKey[3] = { msg.is_left(), msg.is_mid(), msg.is_right()};
	
	for (int i = 0; i < 3; i++) {
		isPressMsg[i] = false;
		isReleaseMsg[i] = false;
	}
	//点击事件检查
	for (int i = 0; i < 3; i++) {
		if (isKey[i]) {
			//鼠标点击
			if (msg.is_down()) {
				isPressMsg[i] = true;
				isReleaseMsg[i] = false;
				curMouseState[i] = MOUSE_DOWN;
				clickEvent[i] = true;
				xClick[i] = msg.x;
				yClick[i] = msg.y;
			}
			//鼠标松开
			else if (msg.is_up()) {
				isPressMsg[i] = false;
				isReleaseMsg[i] = true;
				curMouseState[i] = MOUSE_UP;
			}

			checkDoubleClick(i);

			//鼠标消息只能属于一个键,其它键不用再检测
			break;
		}
	}
}

//检测鼠标双击事件
void MouseState::checkDoubleClick(int keyType) {
	double curTime = fclock();
	/*鼠标双击事件检查*/
	if (clickEvent[keyType]) {
		if (curTime - clickTimes[keyType] > interval) {
			clickTimes[keyType] = curTime;
		}
		else {
			doubleClickEvent[keyType] = true;
			clickTimes[keyType] = 0;
		}
	}							
}

//获取鼠标点击位置
void MouseState::getLeftClickPos(int* x, int* y)
{
	*x = xClick[0];
	*y = yClick[0];
}
void MouseState::getMidClickPos(int* x, int* y)
{
	*x = xClick[1];
	*y = yClick[1];
}
void MouseState::getRightClickPos(int* x, int* y)
{
	*x = xClick[2];
	*y = yClick[2];
}
