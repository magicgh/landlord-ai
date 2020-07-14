//
// Created by magicgh on 7/14/2020.
//

#include "card_set.h"

CardSet::CardSet():type(Unknown), value(0), cnt(0) {};

CardSet::CardSet(Type t, int val):type(t), value(val), cnt(0) {};

CardSet & CardSet::operator=(CardSet &t) {
    this->card = t.card, this->card_set = t.card_set;
    this->value = t.value, this->type = t.type;
    this->cnt = t.cnt;
    return *this;
}

void CardSet::add(int num) {
    card.insert(num);
    card_set[convert(num)]++;
    count++;
}

void CardSet::remove(int num) {
    if(cards.find(num) == cards.end()) return;
    card.erase(num);
    int converted_num = convert(num);
    if(!(--card_set[converted_num]))
        card_set.erase(converted_num);
    count --;
}
void CardSet::reset() {
    card.clear(), card_set.clear();
    type = Unknown, value = cnt = 0;
}

int CardSet::convert(int num) {
    return num > 1 ? (num-1) % 13 + 2 : num + 16;
}