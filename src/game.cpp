//
// Created by magicgh on 7/14/2020.
//

#include <game.h>

const char* TITLE = "Landlord";



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


void Game::main(){
    init();
    for(;is_run() ; delay_fps(FPS)) {
        cleardevice();
        current_scene->draw();
    }
    closegraph();
}