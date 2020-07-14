/*
 * @Author: Eric Feng
 * @Date: 2020-07-13 15:57:29
 * @LastEditTime: 2020-07-14 11:38:32
 * @LastEditors: Please set LastEditors
 * @Description: Cardgroup manager.
 * @FilePath: \landlord-ai\include\card_iter.h
 */ 

#ifndef CARD_ITER_H
#define CARD_ITER_H

#define CARDS_COUNT 54

typedef unsigned int uint;

/*
Card
    id_: Identity of a card reffers to its color and number.
    is_dealed_: If the Card is dealed to a player. True if dealed.
    1  ♥1  2  ♥2  3  ♥3  4  ♥4  5  ♥5  6  ♥6  7  ♥7  8  ♥8  9  ♥9  10 ♥10
    11 ♥J  12 ♥Q  13 ♥K  14 ♦1  15 ♦2  16 ♦3  17 ♦4  18 ♦5  19 ♦6  20 ♦7
    21 ♦8  22 ♦9  23 ♦10 24 ♦J  25 ♦Q  26 ♦K  27 ♠1  28 ♠2  29 ♠3  30 ♠4
    31 ♠5  32 ♠6  33 ♠7  34 ♠8  35 ♠9  36 ♠10 37 ♠J  38 ♠Q  39 ♠K  40 ♣1
    41 ♣2  42 ♣3  43 ♣4  44 ♣5  45 ♣6  46 ♣7  47 ♣8  48 ♣9  49 ♣10 50 ♣J
    51 ♣Q  52 ♣K  53 BigJoker   54 Joker
*/
struct Card {
    int id_;
    bool is_dealed_;
};

/*
 * CardIter:
 *  Shuffle(): Randomly shuffle cardgroup.
 *  DealCard(): Deal a card from cardgroup.
 */
class CardIter {
public:
    CardIter();
    CardIter(uint seed);

    void Shuffle();             // Random shuffle cards
    int DealCard();             // Deal a card. Return id of a card
    void Reset();               // Reset card group

private:
    uint random_seed_;          // Random shuffle seed
    Card cards_[CARDS_COUNT];   // Card group
    uint card_idx_;              // Index of the card dealed
};


#endif