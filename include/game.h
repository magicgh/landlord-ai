//
// Created by magicgh on 7/14/2020.
//


#pragma once


#include "graphics.h"
#include "constant.h"
#include "scene.h"
#include "player.h"
#include "cards.h"

//游戏进度状态
enum Status{
	START,              // 游戏开始
	GETLANDLORD,        // 叫地主阶段
	SENDLANDLORDCARDS,  // 发地主牌阶段
	DISCARD,            // 出牌阶段
	GAMEOVER            // 游戏结束
};

class Game{

    friend class Player;
    friend class Scene;

private:
    StartScene start_scene;
    GameScene game_scene;
    EndScene end_scene;
    ExplainScene explain_scene;
    Scene *current_scene;
    Player *player[3], *landlord, *current_player, *last_player;
    Cards card_heap_;
    int landlord_cards[3];
    Status stage_;
    int times,questioned;//倍率,叫地主次数

private:
    void init();

public:
    Game();
    ~Game();
    void main();
    inline int nextPlayerIndex(){
        for(int i = 0; i < 3; i++)
            if(player[i] == current_player)
                return (i+1)%3;
        return -1;
    }
    inline Player* nextPlayer(){
        return player[nextPlayerIndex()];
    }

    inline int prevPlayerIndex(){
        for(int i = 0; i < 3; i++)
            if(player[i] == current_player)
                return (i+2)%3;
        return -1;
    }
    inline Player* prevPlayer(){
        return player[prevPlayerIndex()];
    }

    inline bool isHumanTurn(){
        return current_player == player[0];
    }

    inline Status getStatus() {
        return stage_;
    }

    void sendCard();
    void getLandlord();

    void discard();


};