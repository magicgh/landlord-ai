/*
 * @Author: Leo Zhang
 * @Date: 2020-07-13 10:30:00
 * @LastEditTime: 2020-07-14 22:44:06
 * @LastEditors: Please set LastEditors
 * @Description: MouseState class
 * @FilePath: \landlord-ai\include\components\mouse_state.h
 */



#pragma once

#include <graphics.h>

#ifndef MOUSE_STATE_H_
#define MOUSE_STATE_H_

//鼠标按键状态
enum mouse_key_state {
	MOUSE_UP = 0,			//按键松开
	MOUSE_DOWN = 1,			//按键按下
};

//鼠标状态类
//可以保存鼠标按键状态，获取单击，双击事件
//需要在每一帧处理鼠标消息事件之前调用 resetState(), 进行按键状态重置
//需要对每一个鼠标消息使用 handleMouseMsg(mousemsg) 进行处理

class MouseState
{
private:
	//鼠标按键的状态(MOUSE_DOWN 或 MOUSE_UP)
	mouse_key_state curMouseState[3];

	int xClick[3], yClick[3];
	bool clickEvent[3];				//鼠标点击事件
	bool releaseEvent[3];			//鼠标释放事件

	bool isPressMsg[3];				//是鼠标点击消息
	bool isReleaseMsg[3];			//是鼠标释放消息 

	//鼠标双击(0, 1, 2分别是左中右)
	bool doubleClickEvent[3];		//鼠标双击事件
	double interval;			//双击触发的两次点击最大时间间隔
	double clickTimes[3];	//记录点击的时间，用于判断双击

public:
	MouseState();

	//设置双击触发的两次点击最大时间间隔（单位：秒）
	void setIntervalTime(double time_seconds);

	//获取双击时间间隔
	double getINtervalTime() { return interval; }

	//重置鼠标按键状态，必须在每一帧中，处理鼠标消息之前调用
	void resetState();

	//鼠标消息处理函数
	void handleMouseMsg(mouse_msg msg);

	//鼠标是否有单击事件产生
	bool hasLeftClick() { return clickEvent[0]; }
	bool hasMidClick() { return clickEvent[1]; }
	bool hasRightClick() { return clickEvent[2]; }

	//鼠标是否有按键松开事件产生
	bool hasLeftRelease() { return releaseEvent[0]; }
	bool hasMidRelease() { return releaseEvent[1]; }
	bool hasRightRelease() { return releaseEvent[2]; }

	//鼠标是否有双击事件产生
	bool hasLeftDoubleClick() { return doubleClickEvent[0]; }
	bool hasMidDoubleClick() { return doubleClickEvent[1]; }
	bool hasRightDoubleClick() { return doubleClickEvent[2]; }

	//是否是鼠标按键按下的消息，只针对一条鼠标消息
	bool isLeftPressMsg() { return isPressMsg[0]; }
	bool isMidPressMsg() { return isPressMsg[1]; }
	bool isRightPressMsg() { return isPressMsg[2]; }

	//是否是鼠标按键松开的消息，只针对一条鼠标消息
	bool isLeftReleaseMsg() { return isReleaseMsg[0]; }
	bool isMidtReleaseMsg() { return isReleaseMsg[1]; }
	bool isRightReleaseMsg() { return isReleaseMsg[2]; }

	//获取内部按键状态数组，方便循环检测
	const bool* getKeysPress() { return isPressMsg; }
	const bool* getKeysRelease() { return isReleaseMsg; }
	const bool* getKeysClick() { return clickEvent; }
	const bool* getKeysDoubleClick() { return doubleClickEvent; }
	const mouse_key_state* getKeysState() { return curMouseState; }

	//判断鼠标现在是否处于按下状态
	bool isLeftDown() { return curMouseState[0] == MOUSE_DOWN; }
	bool isMidDown() { return curMouseState[1] == MOUSE_DOWN; }
	bool isRightDown() { return curMouseState[2] == MOUSE_DOWN; }

	//获取鼠标单击点击位置，需要在鼠标单击事件发生后获取才有效
	void getLeftClickPos(int* x, int* y);
	void getMidClickPos(int* x, int* y);
	void getRightClickPos(int* x, int* y);

private:
	//检测鼠标双击
	void checkDoubleClick(int keyType);
};
#endif //! MOUSE_STATE_H_
