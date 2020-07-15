//
// Created by magicgh on 7/14/2020.
//


#pragma once


<<<<<<< HEAD
#include "constant.h"
#include "scene.h"
#include <graphics.h>
=======
#include "game.h"
#include <graphics.h>
#include "constant.h"
#include "scene.h"
<<<<<<< HEAD
>>>>>>> f15c3b2 (pressed)
=======
#include "player.h"
>>>>>>> 09257bc (:sparkles: add game framework)

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