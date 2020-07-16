/*
 * @Author: Billy Zhang
 * @Date: 2020-07-13 15:59:11
 * @LastEditTime: 2020-07-15 23:50:56
 * @LastEditors: Please set LastEditors
 * @Description: 
 * @FilePath: \landlord-ai\include\player.h
 */

#pragma once
#include <vector>
#include <algorithm>
#include "stdexcept"
#include <set>
#include <map>
#include "card_set.h"

class Player {
    friend class Game;
protected:
    bool test, is_discard;//是否送下家走，是否弃牌标志
    std::set<int> cards; //手牌
    CardSet discard_set ;//出牌集合
    std::vector<CardSet> analyse; //分析后拆分的牌型集合
    CardSet select_set; //选牌集合
public:
    Player();
    void reset();
    bool isValid(Player *last_player);
    inline void addCard(int num){
        cards.insert(num);
    }
    //getRemain()
    inline int countCard(){
        return cards.size();
    }
    void analyseSelection();
    int getBaseScore(int questioned, int current_score);
    void divideIntoGroups(); 
    void threePlusAndAirplane();
    void deleteUnknown(); //

    void selectCards(bool hint, Player* last_player, Player* landlord, Player* prev_player, Player* next_player);//AI选牌
    void selfDiscard(Player* last_player, Player* landlord, Player* prev_player, Player* next_player);//直接出牌
    void friendDiscard(Player* last_player, Player* landlord, Player* prev_player, Player* next_player);//跟友方牌
    void enemyDiscard(bool hint,Player* last_player, Player* landlord, Player* prev_player, Player* next_player);//跟敌方牌
    bool robotDiscard();//AI出牌
    bool humanDiscard(Player *last_player);//玩家出牌


    void getSingle(Player *last_player);
    void getDouble(Player *last_player);
    void getSingleSeq(Player *last_player);
    void getThreePlus(Player *last_player);
    void getAirplane(Player *last_player);
    bool discardAndClear();
    void pass();
    int valueToNum(std::set<int> cardscopy, int value); 
    //freshMap
    void updateMap(std::map<int, int> &m);
    static bool cmp(CardSet c1, CardSet c2);

};

