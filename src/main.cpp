#include "card_iter.h"
#include <iostream>

int main() {
    CardIter card_manager;
    card_manager.Shuffle();
    for(int i = 0; i < CARDS_COUNT; ++i) {
        std::cout << card_manager.DealCard() << std::endl;
    }
    return 0;
}
