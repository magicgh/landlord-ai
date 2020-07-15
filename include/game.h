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
    ~Game();
    void main();
    inline int nextPlayerIndex(){
        for(int i = 0; i < 3; i++)
            if(player[i] == current_player)
                return (i+1)%3;
    }
    inline Player* nextPlayer(){
        return player[nextPlayerIndex()];
    }

    inline int lastPlayerIndex(){
        for(int i = 0; i < 3; i++)
            if(player[i] == current_player)
                return (i+2)%3;
    }
    inline Player* lastPlayer(){
        return player[lastPlayerIndex()];
    }

    inline bool isHumanTurn(){
        return current_player == player[0];
    }
    void sendCard();
    void getLandlord();




};