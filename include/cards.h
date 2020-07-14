//
// Created by magicgh on 7/14/2020.
//

#include <random>
#include "time.h"
#include "constant.h"
#pragma once

class Cards{
private:
    int card[POKER_NUM], cnt;
public:
    Cards();
    void shuffle(); //洗牌
    int deal(); //发牌
    void reset();

};