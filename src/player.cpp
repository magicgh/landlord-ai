//
// Created by magicgh on 7/14/2020.
//

#include "player.h"

void Player::reset() {
    test = is_discard = 0;
    cards.clear(), analyse.clear(), select_set.reset(), discard_set.reset();
}
Player::Player(): test(0), is_discard(0){};


