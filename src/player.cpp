//
// Created by magicgh on 7/14/2020.
//

#include "player.h"

void Player::reset() {
    test = is_discard = 0;
    cards.clear(), analyse.clear(), select_set.reset(), discard_set.reset();
}
Player::Player(): test(0), is_discard(0){};

int Player::getBaseScore(int questioned, int current_score) {
    if (questioned == 2 && current_score == 0)//如果前两位都未叫牌，直接3分当地主，你懂得~
        return 3;
    int sum = 0;
    std::map<int, int> need_analyse;//方便分析的权值-数量集合
    for (auto mem : cards)
        ++need_analyse[CardSet::convert(mem)];//根据手牌构造待分析集合

    if (need_analyse.find(16) != need_analyse.end() &&
            need_analyse.find(17) != need_analyse.end())//存在王炸
        sum += 8;
    else if (need_analyse.find(16) != need_analyse.end())//一张小王
        sum += 3;
    else if (need_analyse.find(17) != need_analyse.end())//一张大王
        sum += 4;

    if (need_analyse.find(15) != need_analyse.end())//2的数量
        sum += 2 * need_analyse[15];

    for (auto mem : need_analyse){
        if (mem.second == 4)//炸弹
            sum += 6;
    }
    int result;
    if (sum >= 7) result = 3;
    else if (sum >= 5 && sum < 7) result = 2;
    else if (sum >= 3 && sum < 5) result = 1;
    else result = 0;
    return (result > current_score ? result : 0);
}
bool Player::isValid(Player *last_player) {
    //game last_player 接口待写
    if (last_player && last_player->discard_set.getCnt() != select_set.getCnt() &&
            select_set.getCnt() != 4 && select_set.getCnt() != 2)//跟牌，但数量不符且不可能为炸弹
        return false;

    select_set.setType(Void);
    // AnalyseSelection();//分析所选牌的类型及权值，没写完

    if (select_set.getType() == Void)//所选牌不符合规定
        return false;

    if (last_player){
        if (select_set.getType() == Bomb &&
            (last_player->discard_set.getType() != Bomb ||
                    select_set.getValue() > last_player->discard_set.getValue()))
            return true;
        if (select_set.getType() != last_player->discard_set.getType() ||
                select_set.getType() != last_player->discard_set.getCnt())//类型不符或数量不符
            return false;
        if (select_set.getValue() <= last_player->discard_set.getValue())//选牌不大于上家牌
            return false;
    }
    return 1;
}
