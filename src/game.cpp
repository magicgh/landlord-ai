//
// Created by magicgh on 7/14/2020.
//

<<<<<<< HEAD
#include "game.h"

=======
#include <game.h>

const char* TITLE = "Landlord";
>>>>>>> f15c3b2 (pressed)



Game::Game() {
    current_scene = &start_scene;
    landlord = current_player = last_player = -1;
}
void Game::init(){
    initgraph(WIDTH,HEIGHT,0x0);
    setcaption(TITLE);
    setbkcolor(WHITE);
    setbkmode(TRANSPARENT);
    delay_ms(0);

}


<<<<<<< HEAD
void gameMain() {

<<<<<<< HEAD

    for(;is_run() ; delay_fps(FPS)) {
        cleardevice();
        current_scene->draw();

    }
=======
=======
void Game::main(){
    init();
>>>>>>> 09257bc (:sparkles: add game framework)
    for(;is_run() ; delay_fps(FPS)) {
        cleardevice();
        current_scene->draw();
    }
    closegraph();
>>>>>>> f15c3b2 (pressed)
}