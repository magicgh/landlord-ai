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
<<<<<<< HEAD
    Cards card_heap_;
<<<<<<< HEAD
    int times,questioned;//倍率,叫地主次数
=======
    int landlord_cards[3];
    Status stage_;
>>>>>>> fdddaab (Game stage)
=======
    Cards card_heap_;//发牌堆
    int landlord_cards[3];//地主专属牌
    int call_score[3];//各家叫地主的分数
    Status stage_;//游戏进度
<<<<<<< HEAD
    int times,questioned, base_score, first_call;//倍率,询问叫地主次数,本局基本分, 第一个叫地主的玩家
>>>>>>> 388f1f5 (:sparkles: add some feature to game.h)
=======
    int times, questioned, base_score, first_call;//倍率,询问叫地主次数,本局基本分, 第一个叫地主的玩家
>>>>>>> 9dc6b60 (:sparkles: Implement Game::main)

private:
    void init();

public:
    Game();
    ~Game();
    void main();
    //当前玩家的下家在玩家指针数组中的下标
    inline int nextPlayerIndex(){
        for(int i = 0; i < 3; i++)
            if(player[i] == current_player)
                return (i+1)%3;
        return -1;
    }
    //获取当前玩家的下家
    inline Player* nextPlayer(){
        return player[nextPlayerIndex()];
    }

    inline int prevPlayerIndex(){
        for(int i = 0; i < 3; i++)
            if(player[i] == current_player)
                return (i+2)%3;
        return -1;
    }
    //获取当前玩家的上家
    inline Player* prevPlayer(){
        return player[prevPlayerIndex()];
    }

    inline bool isHumanTurn(){
        return current_player == player[0];
    }
<<<<<<< HEAD
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
=======
    //获取游戏的当前进度
    inline Status getStatus() {
        return stage_;
    }
    inline void switchScene(Scene *s){
        current_scene = s;
    }
    void sendCard();//发牌
    void getLandlord(int result); //叫地主
    void sendLandlordCard(); //发地主牌
    void pass(); //过牌
    void gameOver(); //游戏结束
    void hint(); //出牌提示
<<<<<<< HEAD
    void discard();
    void sendScore(int result); //设置真人玩家叫地主的分数


>>>>>>> 388f1f5 (:sparkles: add some feature to game.h)
=======
    void discard(int type);
    void discardClear();
    void update();
>>>>>>> 30695cc (:hammer: Basic functions realize)

};