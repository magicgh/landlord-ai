//
// Created by magicgh on 7/14/2020.
//

#include "cards.h"


Cards::Cards() {
    for(int i = 0; i < POKER_NUM; i++)
        card[i] = i;
    reset();
}
void Cards::shuffle() {
    std::default_random_engine generator (time(nullptr));
    std::uniform_int_distribution<unsigned int> u(0, POKER_NUM-1);
    for (int i = 1; i < 54; i++){
        int index = u(generator);
        std::swap(card[i], card[index]);
    }
}

int Cards::deal() {
    return !cnt ? -1 : card[--cnt];
}

void Cards::reset() {
    shuffle();
    cnt = 54;
}