//
// Created by magicgh on 7/14/2020.
//

#include "card_set.h"

CardSet::CardSet():type(Void), value(0), cnt(0) {};

CardSet::CardSet(Type t, int val):type(t), value(val), cnt(0) {};

CardSet & CardSet::operator=(const CardSet &t) {
    this->cards = t.cards, this->card_set = t.card_set;
    this->value = t.value, this->type = t.type;
    this->cnt = t.cnt;
    return *this;
}

void CardSet::add(int num) {
    cards.insert(num);
    card_set[convert(num)]++;
    cnt++;
}

void CardSet::remove(int num) {
    if(cards.find(num) == cards.end()) return;
    cards.erase(num);
    int converted_num = convert(num);
    if(!(--card_set[converted_num]))
        card_set.erase(converted_num);
    cnt --;
}
void CardSet::reset() {
    cards.clear(), card_set.clear();
    type = Void, value = cnt = 0;
}

int CardSet::convert(int num) {
    return num > 1 ? (num-1) % 13 + 2 : num + 16;
}