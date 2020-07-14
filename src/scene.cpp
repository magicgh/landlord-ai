/*
 * @Author: XuanLi
 * @Date: 2020-07-13 15:54:40
 * @LastEditTime: 2020-07-13 16:10:15
 * @LastEditors: Please set LastEditors
 * @Description:
 * @FilePath: \landlord-ai\src\scene.cpp
 */

#include "scene.h"
#include <iostream>
#include <graphics.h>
void Scene::BeginMenu() {
    const int Windows_length = 800;
    const int Windows_width = 450;
    PlaySound(TEXT("menu.wav"),NULL,SND_FILENAME | SND_ASYNC);
    flag:
    initgraph(Windows_length,Windows_width,0);
    PIMAGE img = newimage();
    getimage(img,"begin.jpg");
    putimage(0,0,img);
    while(1){
        if(this->menu_choice==1) Game();
        else if(this->menu_choice==2) GameExplain();
        else if(this->menu_choice==3) QuitGame();
        else goto flag;
    }
}
void Scene::QuitGame() {

}

void Scene::GameExplain() {
    initgraph(Windows_length,Windows_width,0);
    PIMAGE img = newimage();
    getimage(img,"explain.jpg");
    putimage(0,0,img);
    while(1) {
        if() this->BeginMenu();
    }
}

void  Scene::Game() {

}