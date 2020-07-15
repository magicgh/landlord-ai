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
    Player *player[3], *landlord, *current_player, *last_player;

private:
    void init();

public:
    Game();
    void main();
    inline Player* nextPlayer(){
        return (current_player+1)%3;
    }
    inline bool isHuman(){
        return current_player == player[0];
    }
    void sendCard();
    void getLandlord();




};