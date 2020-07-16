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
    // TODO Scene.ShowScene
    if(current_player == player[0]){//当前玩家为人
        if(current_player ->select_set.getCnt() && current_player->humanDiscard(last_player)) {//玩家已选牌并且符合规定
            //TODO Scene Hide Discard Button
            last_player = current_player;
            if (current_player->discard_set.getType() == Bomb) //炸弹加倍
                times++;
        }
        else{//否则继续等待玩家选牌
            // TODO Scene.ShowScene
            //TODO Scene.Show Discard Button
        }
    }
    else{
        current_player->selectCards(last_player, landlord, prevPlayer(), nextPlayer());
        if(current_player->humanDiscard(last_player)) last_player = current_player;
        if(current_player->discard_set.getType() == Bomb) times++;
    }
    //TODO Scene.ShowScene
    if(last_player->cards.empty()) stage_ = GAMEOVER;
    else current_player = nextPlayer();

}
void Game::main(){
    init();

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
                stage_ = START;
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

void getLandlord() {

}


void Game::gameOver() {
    // XXX 目前不打算加分数显示，之后可考虑加上
    int score = base_score*times;
    bool is_people_win = 0; //人类玩家赢了吗
    current_player = landlord; //把地主设为当前玩家，方便获取上家和下家
    if(!landlord->cards.empty()){ //地主牌不为0，农民胜利
        landlord->score -= score*2;
        prevPlayer()->score += score, nextPlayer()->score += score;
        if(player[0] != landlord)   is_people_win = 1;
    }
    else{ //地主赢了
        landlord->score += score*2;
        prevPlayer()->score -= score, nextPlayer()->score -= score;
        if(player[0] == landlord) is_people_win = 1;
    }
    // TODO show scene

    /*
    if (is_people_win)
        //TODO A Message Box shows that Player wins
    else // TODO A Message Box shows that Player loses

    //TODO restart or quit
    */

}