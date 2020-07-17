#include "game.h"
#include <random>
#include <set>

const char* TITLE = "Landlord";

void Game::update() {
    game_scene.sethand(player[0]->cards);
    game_scene.setselect(player[0]->select_set.getCards());
    game_scene.setdeal(player[0]->discard_set.getCards(),player[1]->getDiscardCards(),player[2]->getDiscardCards());
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

    update();

    for(int i = 0; i < 3; ++i)
        landlord_cards[i] = card_heap_.deal();
}

//出牌
void Game::discardClear() {
    if(last_player == current_player){//该玩家出牌后没有人再出牌
        last_player = nullptr;
        for (int i=0; i<3; i++){//清空出牌区
            player[i]->discards.clear();
            player[i]->discard_set.reset();
            player[i]->no_discard = false;
        }
    }
    else{//清空 current_player 出牌区
        current_player->discard_set.reset();
        current_player->no_discard = false;
    }
    update();
}

void Game::discard(int type) {
    discardClear();
    game_scene.draw();
    if(current_player == player[0])
    {
        if(type > 0)
        {
            player[0]->select(type);
            update();
            return;
        }
        else if(type == -1) {
            if (current_player->select_set.getCnt() && current_player->humanDiscard(last_player))
            {
                update();

                last_player = current_player;

                if (current_player->discard_set.getType() == Bomb) //炸弹加倍
                    times++;


                if (last_player->cards.empty()) {
                    stage_ = GAMEOVER;
                    return;
                }
            }
            else
            {
                current_player->select_set.reset();
                update();
                return;
            }
        }

        current_player = nextPlayer();

        update();

        game_scene.draw();
    }
    while(current_player != player[0])
    {
        discardClear();

        current_player->selectCards(last_player, landlord, prevPlayer(), nextPlayer());

        if(current_player->robotDiscard(last_player)){

            last_player = current_player;

            if(current_player->discard_set.getType() == Bomb) times++;

            update();

            if (last_player->cards.empty()) {
                stage_ = GAMEOVER;
                return;
            }
        }

        current_player = nextPlayer();

        update();
        game_scene.draw();
    }

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
                current_scene->BgmPlay();
            }
            else if(state==1) {
                current_scene->BgmPause();
                current_scene = &explain_scene;
                current_scene->BgmPlay();
            }
            else break;
        }

        else if(current_scene == &explain_scene){
            if(state){
                current_scene->BgmPause();
                current_scene = &start_scene;
                current_scene->BgmPlay();
            }
        }

        else if(current_scene == &end_scene){
            if(state){
                current_scene->BgmPause();
                current_scene = &game_scene;
                stage_ = START;
                current_scene->BgmPlay();
            }
        }

        if(current_scene == &game_scene){

            switch (getStatus())
            {
            case START:
                // 游戏开局初始化
                questioned = 0;
                times = 1;
                base_score = 0;
                landlord = current_player = last_player = nullptr;
                for(int i = 0; i < 3; ++i) {
                    landlord_cards[i] = call_score[i] = 0;
                    player[i]->cards.clear();
                    player[i]->discard_set.reset();
                    player[i]->select_set.reset();
                    player[i]->discards.clear();
                }
                
                // 洗牌
                card_heap_.reset();
                card_heap_.shuffle();

                sendCard(); // 发牌

                game_scene.ready();

                stage_ = GETLANDLORD; // 进行叫地主阶段

                break;

            case GETLANDLORD:
                getLandlord(state); // 选取地主

                if(stage_ == SENDLANDLORDCARDS)
                {
                    sendLandlordCard();
                    //game_scene.draw();
                }

                break;

            case DISCARD:

                discard(state);

                break;

            case GAMEOVER:
                gameOver(); // 输出Game over信息

                             // 切换游戏终止场景
                current_scene->BgmPause();
                current_scene = &end_scene;
                current_scene->BgmPlay();

                break;
            
            default:
                exit(1);
                break;
            }

            //game_scene.draw();
        }
    }
    closegraph();
}

// 叫地主询问
void Game::getLandlord(int result) {
    int i;

    while(1){

        i = -1;

        if (!questioned){
            // 随机生成确定开始询问的玩家(使用均匀分布)
            std::default_random_engine e((UINT)time(nullptr));
            std::uniform_int_distribution<unsigned> u(0, 2);

            first_call = i = u(e);
        }

        else if (questioned == 3){//所有玩家都已询问过
            if (last_player){//给出分数最高的为地主
                current_player = landlord = last_player;
                last_player = nullptr;
            }
            else{//若均为叫牌，重新开始游戏
                stage_ = START;
            }
            if (landlord)//地主已经确定，进入给地主发牌阶段
                stage_ = SENDLANDLORDCARDS;
            return;
        }

        if (i == -1)//不是第一次询问，确定要询问的下家
            i = nextPlayerIndex();

        if (i == 0){
            current_player = player[i];
            call_score[0] = result;
            if (result == 3){
                base_score = result;
                landlord = player[0];
                last_player = nullptr;
            }
            else if (result > base_score){
                base_score = result;
                last_player = player[0];
            }
            ++questioned;
        }
        else{//否则直接调用玩家的AI函数
            current_player = player[i];
            int result = current_player->getBaseScore(questioned, base_score);
            call_score[i] = result;
            if (result == 3){//给出三分就直接当地主
                base_score = result;
                landlord = current_player;
                last_player = nullptr;
            }
            else if (result > base_score){//否则，给出分数大于上次给分玩家
                base_score = result;
                last_player = current_player;//就把该玩家记录下来
            }
            ++questioned;
        }
        if (landlord)//地主已确定，进入发地主牌阶段
        {
            stage_ = SENDLANDLORDCARDS;
            return;
        }
    }
}

void Game::sendLandlordCard() {
    std::set<int> landlord_cards_set;

    for(auto iter: landlord_cards) {
        landlord->addCard(iter);
        landlord_cards_set.insert(iter);
    }
    for(int i=0;i<3;i++)
        if(landlord == player[i])
            game_scene.Order(i);

    update();
    game_scene.begin();

    // TODO: 玩家和电脑牌传给game_scene

    // 进入出牌阶段
    stage_ = DISCARD;
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
        end_scene.SetType(1);
    }
    else{ //地主赢了
        landlord->score += score*2;
        prevPlayer()->score -= score, nextPlayer()->score -= score;
        if(player[0] == landlord) is_people_win = 1;
        end_scene.SetType(0);
    }
    // TODO show scene

    /*
    if (is_people_win)
        //TODO A Message Box shows that Player wins
    else // TODO A Message Box shows that Player loses

    //TODO restart or quit
    */
}