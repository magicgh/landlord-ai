//
// Created by magicgh on 7/14/2020.
//


#pragma once


#include "game.h"
#include <graphics.h>
#include "constant.h"
#include "scene.h"
#include "player.h"

class Game{
private:
    StartScene start_scene;
    GameScene game_scene;
    EndScene end_scene;
    ExplainScene explain_scene;
    Scene *current_scene;
    int landlord, current_player, last_player; //编号
    Player player[3];

private:
    void init();

public:
    Game();
    void main();
    inline int nextPlayer(){
        return (current_player+1)%3;
    }
    inline bool isHuman(){
        return current_player == 0;
    }
    void sendCard();
    void getLandlord();




};