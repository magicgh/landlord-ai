/*
 * @Author: Eric Feng
 * @Date: 2020-07-13 16:02:11
 * @LastEditTime: 2020-07-14 11:48:42
 * @LastEditors: Eric Feng
 * @Description: In User Settings Edit
 * @FilePath: \landlord-ai\src\card_iter.cpp
 */ 

#include "card_iter.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <cstdio>
#include <cstdlib>
#include <ctime>

uint generate_radom_number(uint minn, uint maxx) {
    return minn + (rand() % (maxx - minn));
}

CardIter::CardIter() {
    random_seed_ = (unsigned int)time(NULL);
    srand(random_seed_);
    
    for(int i = 0; i < 54; ++i) {
        cards_[i].id_ = i;
        cards_[i].is_dealed_ = false;
    }

    card_idx_ = 0;
}

CardIter::CardIter(uint seed): 
    random_seed_(seed) {
    srand(random_seed_);

    for(int i = 0; i < 54; ++i) {
        cards_[i].id_ = i;
        cards_[i].is_dealed_ = false;
    }

    card_idx_ = 0;
}

/*
 * CardIter::Shuffle():
 *  Use card shuffle algorithm.
 */
void CardIter::Shuffle() {
    for(int i = 0; i < CARDS_COUNT; ++i) {
        int idx = generate_radom_number(i, CARDS_COUNT);
        if(idx != i) {
            Card tmp = cards_[i];
            cards_[i] = cards_[idx];
            cards_[idx] = tmp;
        }
    }
}

/*
 * CardIter::DealCard():
 *  Deal one card from cardgroup.
 *  return -1 if cardgroup is empty else return id of a card.
 */
int CardIter::DealCard() {
    while(card_idx_ < CARDS_COUNT) {
        if(!cards_[card_idx_].is_dealed_) {
            cards_[card_idx_].is_dealed_ = true;
            return cards_[card_idx_].id_;
        }
        card_idx_ ++;
    }
    return -1;
}

/*
 * CardIter::Reset():
 *  Reset all card to undeal mode.
 */
void CardIter::Reset() {
    for(int i = 0; i < 54; ++i) {
        cards_[i].id_ = i;
        cards_[i].is_dealed_ = false;
    }

    card_idx_ = 0;
}