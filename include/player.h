/*
 * @Author: Billy Zhang
 * @Date: 2020-07-13 15:59:11
 * @LastEditTime: 2020-07-17 03:38:40
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
    bool test, no_discard;//是否送下家走，是否弃牌标志，is_discard改为no_discard
    std::set<int> cards; //手牌
    std::set<int> discards; //出牌手牌
    CardSet discard_set ;//出牌集合
    std::vector<CardSet> analyse; //分析后拆分的牌型集合
    CardSet select_set; //选牌集合
    int score;
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

    void select(int rank);
    void selectCards(Player* last_player, Player* landlord, Player* prev_player, Player* next_player, bool hint = false);//AI选牌
    void selfDiscard(Player* last_player, Player* landlord, Player* prev_player, Player* next_player);//直接出牌 myself
    void friendDiscard(Player* last_player, Player* landlord, Player* prev_player, Player* next_player);//跟友方牌 friend
    void enemyDiscard(bool hint,Player* last_player, Player* landlord, Player* prev_player, Player* next_player);//跟敌方牌 enemy
    bool robotDiscard(Player *last_player);//AI出牌,Discard
    bool humanDiscard(Player *last_player);//玩家出牌 human discard


    void getSingle(Player *last_player);//need single
    void getDouble(Player *last_player);//need double
    void getSingleSeq(Player *last_player);//need single seq
    void getThreePlus(Player *last_player);//need three plus
    void getAirplane(Player *last_player);//need airplane
    bool discardAndClear();
    void pass();
    int valueToNum(std::set<int> cardscopy, int value); 
    std::set<int> getDiscardCards();

    //freshMap
    void updateMap(std::map<int, int> &m);//freshenmap
    static bool cmp(CardSet c1, CardSet c2); //my compare

};

