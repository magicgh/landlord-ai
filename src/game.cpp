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
    for(int i = 0; i < 3; ++i) 
        landlord_cards[i] = card_heap_.deal();
}

void Game::main(){
    init();
    StartScene start_scene;
    GameScene game_scene;
    EndScene end_scene;
    ExplainScene explain_scene;

    Scene *current_scene=&start_scene;

    for(;is_run() ; delay_fps(FPS)) {

        current_scene->draw();

        if(current_scene == &start_scene){
            if(current_scene->button()==0){
                current_scene->bgm_switch();
                current_scene = &game_scene;
                stage_ = START;
            }
            else if(current_scene->button()==1) {
                current_scene->bgm_switch();
                current_scene = &explain_scene;
            }
            else break;
        }

        if(current_scene == &game_scene){
            if(game_scene.button() == 1) {
                current_scene = &end_scene;
                continue;
            } 

            // 检测游戏阶段
            switch (stage_)
            {
            case START:             // 发牌阶段
                sendCard();
                stage_ = GETLANDLORD;
                break;
            
            case GETLANDLORD:

                break;

            case SENDLANDLORDCARDS:
                break;

            case DISCARD:
                break;
            
            case GAMEOVER:
                break;

            default:
                break;
            }

            game_scene.drawCards(player[0]->discard_set.getCards(), player[0]->select_set.getCards());
            
        }

    }
    //getch();
    closegraph();
}

void getLandlord() {

}