//
// Created by magicgh on 7/14/2020.
//

<<<<<<< HEAD
#include "game.h"

=======
#include <game.h>

const char* TITLE = "Landlord";
>>>>>>> f15c3b2 (pressed)

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

<<<<<<< HEAD

    for(;is_run() ; delay_fps(FPS)) {
        cleardevice();
        current_scene->draw();

    }
=======
    for(;is_run() ; delay_fps(FPS)) {
        cleardevice();
        current_scene->draw();
    }

    closegraph();
>>>>>>> f15c3b2 (pressed)
}