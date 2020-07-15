#include "game.h"

const char* TITLE = "Landlord";

int button()
{
    while (1) {
        mouse_msg mouseMsg = getmouse();
        if (mouseMsg.is_left() && mouseMsg.is_down()) {
            int x = mouseMsg.x;
            int y = mouseMsg.y;
            if (x >= 650 && x <= 950) {
                if(y >= 127 && y <= 222) return 0;
                else if(y >= 257 && y <= 344) return 1;
                else if(x >= 382 && x <= 470) return 2;
            }
        }
    }
}

Game::Game() {
    current_scene = &start_scene;
    landlord = current_player = last_player = nullptr;
    for (int i = 0; i < 3; i++){
        player[i] = new Player();
    }
}

Game::~Game() {
    for (int i = 0; i < 3; ++i)
        delete player[i];
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
    StartScene start_scene;
    GameScene game_scene;
    EndScene end_scene;
    ExplainScene explain_scene;

    Scene *current_scene=&start_scene;

    for(;is_run() ; delay_fps(FPS)) {
        cleardevice();
        current_scene->draw();

        if(current_scene == &start_scene){
            if(button()==0) current_scene = &game_scene;
            else if(button()==1) current_scene = &explain_scene;
            else break;
        }
    }
    getch();
    closegraph();
}