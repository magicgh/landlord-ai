//
// Created by magicgh on 7/14/2020.
//

#include "game.h"


StartScene start_scene;
GameScene game_scene;
EndScene end_scene;
ExplainScene explain_scene;
Scene *current_scene=&start_scene;


void gameInit (){
    initgraph(WIDTH,HEIGHT,0x0);
    setcaption(TITLE);
    setbkcolor(WHITE);
    setbkmode(TRANSPARENT);
    delay_ms(0);

}


void gameMain() {


    for(;is_run() ; delay_fps(FPS)) {
        cleardevice();
        current_scene->draw();

    }
}