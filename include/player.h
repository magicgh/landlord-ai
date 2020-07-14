/*
 * @Author: Billy Zhang
 * @Date: 2020-07-13 15:59:11
 * @LastEditTime: 2020-07-13 16:09:26
 * @LastEditors: Please set LastEditors
 * @Description: 
 * @FilePath: \landlord-ai\include\player.h
 */

#pragma once
#include <vector>
#include "card_set.h"

class Player {
protected:
    bool test, is_discard;//是否送下家走，是否弃牌标志
    std::set<int> cards; //手牌
    CardSet discard_set ;//出牌集合
    std::vector<CardSet> analyse; //分析后拆分的牌型集合
    CardSet select_set; //选牌集合
public:
    Player();
    void reset();
    bool isValid();
    inline void addCard(int num){
        cards.insert(num);
    }
    inline int countCard(){
        return cards.size();
    }
    void discard();
    void analyseSelection();
    void getBaseScore();
    void divideIntoGroups();
    void threePlusAndAirplane();
    void deleteUnknown();
    void selectCards();
    void robotDiscard();
    void discardAsFriend();
    void discardAsEnemy();
    void getSingle();
    void getDouble();
    void getSingleSeq();
    void getThreePlus();
    void getAirplane();
    void discardAndClear();
    void pass();
    int valueToNum();
    void updateMap();
    static bool cmp(CardSet c1, CardSet c2);

};

