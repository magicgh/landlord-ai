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
//出牌
void Game::discard() {
    if(last_player == current_player){//该玩家出牌后没有人再出牌
        last_player = nullptr;
        for (int i=0; i<3; i++){//清空出牌区
            player[i]->discard_set.reset();
            player[i]->no_discard = false;
        }
    }
    else{//清空 current_player 出牌区
        current_player->discard_set.reset();
        current_player->no_discard = false;
    }
    // Scene.ShowScene
    if(current_player == player[0]){//当前玩家为人
        if(current_player ->select_set.getCnt() && current_player->humanDiscard(last_player)) {//玩家已选牌并且符合规定
            //Scene Hide Discard Button
            last_player = current_player;
            if (current_player->discard_set.getType() == Bomb) //炸弹加倍
                times++;
        }
        else{//否则继续等待玩家选牌
            //Scene.ShowScene
            //Scene.Show Discard Button
        }
    }
    else{
        current_player->selectCards(last_player, landlord, prevPlayer(), nextPlayer());
        if(current_player->humanDiscard(last_player))
            last_player = current_player;
        if(current_player->discard_set.getType() == Bomb)
            times++;
    }
    //Scene.ShowScene
    if(last_player->cards.empty());
        //status = GAMEOVER;
    else current_player = nextPlayer();

}
void Game::main(){
    init();


    for(;is_run() ; delay_fps(FPS)) {

        current_scene->draw();

        if(current_scene == &start_scene){
            if(current_scene->button()==0){
                current_scene->bgm_switch();
                current_scene = &game_scene;
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

            // game_scene.drawCards(player[0]->discard_set.getCards(), player[0]->select_set.getCards());

            
        }

    }
    //getch();
    closegraph();
}