/*
 * @Author: 
 * @Date: 2020-07-13 15:50:01
 * @LastEditTime: 2020-07-13 16:11:06
 * @LastEditors: Please set LastEditors
 * @Description: 
 * @FilePath: \landlord-ai\include\main_loop.h
 */ 

#ifndef MAIN_LOOP_H
#define MAIN_LOOP_H


class MainLoop {
private:
    MainLoop();
public:
    static void init();
    static void runGame();
};

#endif