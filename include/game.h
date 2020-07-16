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
    Cards card_heap_;//发牌堆
    int landlord_cards[3];//地主专属牌
    int call_score[3];//各家叫地主的分数
    Status stage_;//游戏进度
    int times, questioned, base_score, first_call;//倍率,询问叫地主次数,本局基本分, 第一个叫地主的玩家

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
    //获取游戏的当前进度
    inline Status getStatus() {
        return stage_;
    }
    inline void switchScene(Scene *s){
        current_scene = s;
    }
    void sendCard();//发牌
    void getLandlord(); //叫地主
    void sendLandlordCard(); //发地主牌
    void pass(); //过牌
    void gameOver(); //游戏结束
    void hint(); //出牌提示
    void discard();
    void sendScore(int result); //设置真人玩家叫地主的分数



};