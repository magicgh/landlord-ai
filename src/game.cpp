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
                else if(y >= 382 && y <= 470) return 2;
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
    card_heap_.reset();
    card_heap_.shuffle();
}

void Game::sendCard() {
    for(int i = 0; i < 17; ++i) {
        player[0]->addCard(card_heap_.deal());
        player[1]->addCard(card_heap_.deal());
        player[2]->addCard(card_heap_.deal());
    }
    
}

void Game::main(){
    init();
    StartScene start_scene;
    GameScene game_scene;
    EndScene end_scene;
    ExplainScene explain_scene;

    start_scene.init();
    game_scene.init();
    end_scene.init();
    explain_scene.init();

    Scene *current_scene=&start_scene;
    current_scene->BgmPlay();

    for(;is_run() ; delay_fps(FPS)) {

        current_scene->draw();

        int state = current_scene->button();

        if(current_scene == &start_scene){
            if(state==0){
                current_scene->BgmPause();
                current_scene = &game_scene;
                game_scene.shuffle();
                current_scene->BgmPlay();
            }
            else if(state==1) {
                current_scene->BgmPause();
                current_scene = &explain_scene;
                current_scene->BgmPlay();
            }
            else break;
        }

        else if(current_scene == &explain_scene && state){
            current_scene->BgmPause();
            current_scene = &start_scene;
            current_scene->BgmPlay();
        }

        else if(current_scene == &end_scene && state){
            current_scene->BgmPause();
            current_scene = &game_scene;
            game_scene.shuffle();
            current_scene->BgmPlay();
        }

        else if(current_scene == &game_scene){
            game_scene.work(state);

            if(game_scene.size()==0){
                end_scene.SetType(0);
                current_scene->draw();
                current_scene->BgmPause();
                current_scene = &end_scene;
                current_scene->BgmPlay();
            }
        }
    }
    closegraph();
}