//
// Created by magicgh on 7/14/2020.
//


#pragma once


<<<<<<< HEAD
<<<<<<< HEAD
#include "constant.h"
#include "scene.h"
#include <graphics.h>
=======
#include "game.h"
#include <graphics.h>
=======
#include "graphics.h"
>>>>>>> 2db127b (feat: add player.cpp)
#include "constant.h"
#include "scene.h"
<<<<<<< HEAD
>>>>>>> f15c3b2 (pressed)
=======
#include "player.h"
<<<<<<< HEAD
>>>>>>> 09257bc (:sparkles: add game framework)
=======
#include "cards.h"
>>>>>>> 38dbc88 (Game things)

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
<<<<<<< HEAD
    int times,questioned;//倍率,叫地主次数
=======
    int landlord_cards[3];
    Status stage_;
>>>>>>> fdddaab (Game stage)

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
<<<<<<< HEAD
    void sendCard();
    void getLandlord();

    void discard();
=======

    inline Status getStatus() {
        return stage_;
    }
>>>>>>> fdddaab (Game stage)

    void sendCard();
    void getLandlord();

};