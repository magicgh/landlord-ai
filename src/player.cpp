//
// Created by magicgh on 7/14/2020.
//

#include "player.h"
#include <vector>
#include <algorithm>

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

void Player::analyseSelection()
{
	int NumMax = 0,//同牌面的最大数量
		ValueMax = 0;//最大数量的最大权值

	//判断是否为王炸
	if (select_set.getCnt() == 2 &&
		select_set.getCardSet().find(16) != select_set.getCardSet().end() &&
		select_set.getCardSet().find(17) != select_set.getCardSet().end()){
		select_set.setType(Bomb);
		select_set.setValue(17);
		return;
	}
//找出相同牌面的最大数量，和最大权值
	for (auto mem : select_set.getCardSet()){
		if (mem.second >= NumMax && mem.first > ValueMax){
			NumMax = mem.second;
			ValueMax = mem.first;
		}
	}
	//根据牌面相同的最大数量判断类型
	switch (NumMax){
	case 4:
		if (select_set.getCnt() == 4){//炸弹
			select_set.setType(Bomb);
			select_set.setValue(ValueMax);
			return;
		}
		if (select_set.getCnt() == 6){//四带两张
			select_set.setType(FourSeq);
			select_set.setValue(ValueMax);
			return;
		}
		if (select_set.getCnt() == 8){//四带两对
			for (auto mem : select_set.getCardSet()){
				if (mem.second != 2 && mem.second != 4)//牌面不合规
					return;
			}
			select_set.setType(FourSeq);
			select_set.setValue(ValueMax);
			return;
		}
		return;//牌面不合规
	case 3:
	{
			  if (select_set.getCnt() == 3){//三条
				  select_set.setType(Three);
				  select_set.setValue(ValueMax);
				  return;
			  }
			  if (select_set.getCnt() == 4){//三带一张
				  select_set.setType(ThreePlus);
				  select_set.setValue(ValueMax);
				  return;
			  }
			  if (select_set.getCnt() == 5){//三带两张
				  for (auto mem : select_set.getCardSet()){
					  if (mem.second != 3 && mem.second != 2)
						  return;
				  }
				  select_set.setType(ThreePlus);
				  select_set.setValue(ValueMax);
				  return;
			  }
			  int begin = 0, n = 0;
			  for (auto mem : select_set.getCardSet()){//判断连续的3张牌面的最大数量
				  if (mem.second == 3){
					  if (!begin || begin == mem.first)
						  ++n;
					  if (!begin)
						  begin = mem.first;
					  if (begin != mem.first && n == 1){
						  n = 1;
						  begin = mem.first;
					  }
					  ++begin;
				  }
			  }
			  if (select_set.getCnt() == 3 * n){//三顺
				  select_set.setType(ThreeSeq);
				  select_set.setValue(ValueMax);
				  return;
			  }
			  if (select_set.getCnt() == 4 * n){//飞机带单张的翅膀
				  select_set.setType(Airplane);
				  select_set.setValue(ValueMax);
				  return;
			  }
			  if (select_set.getCnt() == 5 * n){//飞机带对子翅膀
				  for (auto mem : select_set.getCardSet()){
					  if (mem.second != 2 && mem.second != 3)//牌不合规
						  return;
				  }
				  select_set.setType(Airplane);
				  select_set.setValue(ValueMax);
				  return;
			  }
			  return;//牌不合规
	}
	case 2:
		if (select_set.getCnt() == 2){//一对
			select_set.setType(Double);
			select_set.setValue(ValueMax);
			return;
		}
		if (select_set.getCnt() >= 6 && !(select_set.getCnt() % 2)){//连对
			int begin = 0;
			for (auto mem : select_set.getCardSet()){//确定牌是连续的，并且都是成对的
				if (!begin)
					begin = mem.first;
				if (begin++ != mem.first || mem.second != 2)//牌不符合规定
					return;
			}
			select_set.setType(DoubleSeq);
			select_set.setValue(ValueMax);
			return;
		}
		return;//牌不符合规定
	case 1:
		if (select_set.getCnt() == 1){//单张
			select_set.setType(Single);
			select_set.setValue(ValueMax);
			return;
		}
		else if (select_set.getCnt() >= 5){//判断是否为顺子
			int begin = 0;
			for (auto mem : select_set.getCardSet()){
				if (!begin)
					begin = mem.first;
				if (begin++ != mem.first || mem.first >= 15)//牌不是连续的或者带了2及以上的牌
				return;
			}
			select_set.setType(SingleSeq);//单顺
			select_set.setValue(ValueMax);
			return;
		}
	default://下落，不符合规定
		return;
	}
}


//拆分手牌牌型并组成基本牌集合
void Player::divideIntoGroups()
{
	if (analyse.size())//牌型集合非空，返回
		return;

	std::set<int> cardscopy(cards);//手牌副本
	std::map<int, int> needanalyse;//方便分析的权值-数量集合

	for (auto mem : cardscopy)
		++needanalyse[CardSet::convert(mem)];//根据手牌构造待分析集合

	if (needanalyse.find(16) != needanalyse.end() &&
		needanalyse.find(17) != needanalyse.end()){//满足条件存在王炸
		CardSet c = CardSet(Bomb, 17);
		for (int i = 16; i < 18; ++i){
			c.add(valueToNum(cardscopy, i));
			needanalyse.erase(i);
		}
		analyse.push_back(c);
	}

	for (auto mem : needanalyse){
		if (mem.second == 4){	//炸弹
			CardSet c = CardSet(Bomb, mem.first);
			for (int i = 0; i < 4; ++i){
				c.add(valueToNum(cardscopy, mem.first));
			}
			analyse.push_back(c);
			needanalyse[mem.first] = 0;
		}
	}
	//删除分析堆中数量为零的元素
	updateMap(needanalyse);

	//提前处理2
	if (needanalyse.find(15) != needanalyse.end()){
		CardSet c = CardSet(Void, 15);
		int n = needanalyse[15];
		switch (n){
		case 3:
			c.setType(Three);
			break;
		case 2:
			c.setType(Double);
			break;
		case 1:
			c.setType(Single);
			break;
		}
		for (int i = 0; i < n; ++i)
			c.add(valueToNum(cardscopy, 15));
		needanalyse.erase(15);
		analyse.push_back(c);
	}
	//查找单顺
	int begin, n;
	bool exist = true;
	while (exist && needanalyse.size()){
		begin = n = 0;
		for (auto b = needanalyse.begin(); b != needanalyse.end(); ++b){
			if (b->second > 0){//跳过为零的元素
				if (!begin)
					begin = b->first;
				if (begin == b->first)
					++n;
				++begin;
			}
			if (n == 5){//满足组成单顺的数量
				auto p = b;
				int first = p->first - 4;//单顺的第一个
				CardSet c = CardSet(SingleSeq, p->first);
				for (first; first <= p->first; ++first){
					c.add(valueToNum(cardscopy, first));
					--needanalyse[first];//减一
				}
				analyse.push_back(c);
				exist = true;
				break;//从开始重新查找
			}
			//连续牌面数量小于五个，重新计数；或者已到集合最后数量仍不满足
			auto end = needanalyse.end();
			if (begin - 1 != b->first || b == --end){
				if (b->second > 0){
					begin = b->first;
					++begin;
					n = 1;
				}
				else
					begin = n = 0;
				exist = false;
			}

		}
	}

	//删除分析堆中数量为零的元素
	updateMap(needanalyse);
	//如可能，继续往单顺中添加剩余牌
	for (auto mem : analyse){
		if (mem.getType() == SingleSeq){//针对每个单顺
			for (auto m : needanalyse){
				if (m.second > 0 && m.first == mem.getValue() + 1){//剩余牌中还有比单顺最大大一的牌
					mem.add(valueToNum(cardscopy, m.first));
					mem.setValue(mem.getValue()+1);
					--needanalyse[m.first];

				}
			}
		}
	}
	//删除分析堆中数量为零的元素
	updateMap(needanalyse);

	//如现有单顺中有可以对接成更长的单顺；或两个单顺元素相同，组合成双顺
	for (auto mem1 : analyse){
		if (mem1.getType() == SingleSeq){//单顺1
			for (auto mem2 : analyse){
				if (mem2.getType() == SingleSeq && mem1 != mem2){//单顺2，且和单顺1不是同一个
					if (mem1.getValue() < mem2.getValue()){//mem1在前
						if (mem1.getValue() == mem2.getValue() - mem2.getCnt()){//可以拼接
							for (auto m : mem2.getCards())
								mem1.add(m);
							mem1.setValue(mem2.getValue());
							mem2.setType(Void);
						}
					}
					else if (mem1.getValue() > mem2.getValue()){//mem1在后
						if (mem2.getValue() == mem1.getValue() - mem1.getCnt()){
							for (auto m : mem1.getCards())
								mem2.add(m);
							mem2.setValue(mem1.getValue());
							mem1.setType(Void);
						}
					}
					else{//测试是否完全一样，可以合并成双顺
						if (mem1.getCnt() == mem2.getCnt()){
							for (auto m : mem2.getCards())
								mem1.add(m);
							mem1.setType(DoubleSeq);
							mem2.setType(Void);
						}
					}
				}
			}
		}
	}
	if (needanalyse.empty()){//分析集合已空，返回
		deleteUnknown();
		sort(analyse.begin(), analyse.end(), cmp);
		return;
	}

	//双顺，只查找数量大于等于2的连续牌，并且3个以上相连
	begin = n = 0;
	auto last = --needanalyse.end();
	for (auto b = needanalyse.begin(); b != needanalyse.end(); ++b){
		if (b->second >= 2){
			if (!begin)
				begin = b->first;
			if (begin == b->first)
				++n;
			++begin;
		}
		if (begin && begin - 1 != b->first || b == last){//出现与之前不连续的,或已到集合最后
			if (n >= 3){
				auto p = b;
				if (begin - 1 != b->first)
					--p;
				CardSet c = CardSet(DoubleSeq, p->first);
				for (int i = n; i > 0; --i, --p){
					for (int j = 0; j < 2; ++j){
						c.add(valueToNum(cardscopy, p->first));
						--p->second;
					}
				}
				analyse.push_back(c);
			}
			if (b->second >= 2){
				n = 1;//当前分析牌是两张以上的
				begin = b->first;
				++begin;
			}
			else{
				n = 0;
				begin = 0;
			}
		}
	}

	//删除分析堆中数量为零的元素
	updateMap(needanalyse);

	//三顺
	//查找是否有重合的单顺和双顺组合成三顺
	for (auto mem1 : analyse){
		if (mem1.getType() == SingleSeq){
			for (auto mem2 : analyse){
				if (mem2.getType() == DoubleSeq){
					if (mem1.getValue() == mem2.getValue() && mem1.getCnt() * 2 == mem2.getCnt()){
						for (auto m : mem1.getCards())
							mem2.add(m);
						mem2.setType(ThreeSeq);
						mem1.setType(Void);
					}
				}
			}
		}
	}

	if (needanalyse.empty()){
		deleteUnknown();
		sort(analyse.begin(), analyse.end(), cmp);
		return;
	}
	//剩余牌中查找三顺
	begin = n = 0;
	last = --needanalyse.end();
	for (auto b = needanalyse.begin(); b != needanalyse.end(); ++b){
		if (b->second == 3){
			if (!begin)
				begin = b->first;
			if (begin == b->first)
				++n;
			++begin;
		}
		if (begin && begin - 1 != b->first || b == last){//出现与之前不连续的,或已到集合最后
			if (n >= 2){//存在2组及以上
				auto p = b;
				if (begin - 1 != b->first)
					--p;
				CardSet c = CardSet(ThreeSeq, p->first);
				for (int i = n; i > 0; --i, --p){
					for (int j = 0; j < 3; ++j){
						c.add(valueToNum(cardscopy, p->first));
						--p->second;
					}
				}
				analyse.push_back(c);
				if (b->second == 3){//当前分析牌为3张，
					n = 1;
					begin = b->first;
					++begin;
				}
				else{
					n = 0;
					begin = 0;
				}
			}
		}
	}
	//三条
	for (auto mem : needanalyse){
		if (mem.second == 3){
			CardSet c = CardSet(Three, mem.first);
			for (int i = 0; i < 3; ++i)
				c.add(valueToNum(cardscopy, mem.first));
			needanalyse[mem.first] = 0;
			analyse.push_back(c);
		}
	}

	//对子
	for (auto mem : needanalyse){
		if (mem.second == 2){
			CardSet c = CardSet(Double, mem.first);
			for (int i = 0; i < 2; ++i)
				c.add(valueToNum(cardscopy, mem.first));
			needanalyse[mem.first] = 0;
			analyse.push_back(c);
		}
	}
	//删除分析堆中数量为零的元素
	updateMap(needanalyse);

	//单牌
	for (auto mem : needanalyse){
		if (mem.second != 1)
			throw std::runtime_error("Still has singleness card");
		CardSet c = CardSet(Single, mem.first);
		c.add(valueToNum(cardscopy, mem.first));
		needanalyse[mem.first] = 0;
		analyse.push_back(c);
	}
	//删除分析堆中数量为零的元素
	updateMap(needanalyse);

	deleteUnknown();
	sort(analyse.begin(), analyse.end(), cmp);

}


//由三条、三顺完善成三带一和飞机；先找单牌，再找对子，均不够就保持原样
void Player::threePlusAndAirplane()
{
	int n,
		doublecount = 0,//统计对子的数量，方便下面的整合
		singlecount = 0;//统计单张数量

	for (auto mem : analyse){
		if (mem.getType() == Single)
			++singlecount;
		else if (mem.getType() == Double)
			++doublecount;
	}

	for (auto mem : analyse){//完善飞机
		if (mem.getType() == ThreeSeq){
			n = mem.getCnt() / 3;
			if (singlecount >= n){
				for (auto temp : analyse){
					if (temp.getType() == Single){
						for (auto m : temp.getCards())
							mem.add(m);
						temp.setType(Void);
						--singlecount;
						--n;
					}
					if (!n){
						mem.setType(Airplane);
						break;
					}
				}
			}
			else if (doublecount >= n){
				for (auto temp : analyse){
					if (temp.getType() == Double){
						for (auto m : temp.getCards())
							mem.add(m);
						temp.setType(Void);
						--doublecount;
						--n;
					}
					if (!n){
						mem.setType(Airplane);
						break;
					}
				}
			}
		}
	}
	for (auto mem : analyse){//完善三带一
		if (mem.getType() == Three){
			if (singlecount){
				for (auto temp : analyse){
					if (temp.getType() == Single){
						for (auto m : temp.getCards())
							mem.add(m);
						temp.setType(Void);
						--singlecount;
						mem.setType(ThreePlus);
						break;
					}
				}
			}
			else if (doublecount){
				for (auto temp : analyse){
					if (temp.getType() == Double){
						for (auto m : temp.getCards())
							mem.add(m);
						temp.setType(Void);
						--doublecount;
						mem.setType(ThreePlus);
						break;
					}
				}
			}
		}
	}
}


void Player::deleteUnknown()
{
	auto b = analyse.begin();
	while (b != analyse.end()){
		if ((*b).getType() == Void){
			b = analyse.erase(b);
		}
		else
			++b;
	}
}



//电脑选牌
void Player::selectCards(bool hint, Player* last_player, Player* landlord, Player* prev_player, Player* next_player)
{
	if (analyse.empty())//是否需要重新分析手牌
		divideIntoGroups();
	threePlusAndAirplane();
	deleteUnknown();
	sort(analyse.begin(), analyse.end(), cmp);

	if (analyse.size() == 2){//手数为2，且有适合的炸弹直接出
		for (auto mem : analyse){
			if (mem.getType() == Bomb){
				if (last_player != nullptr &&//如果自己是接别人的牌
					last_player->discard_set.getType() == Bomb &&//别人最后出牌为炸弹，
					mem.getValue() <= last_player->discard_set.getValue())//且自己的炸弹不大于对方时，
					continue;//不能选择改牌
				select_set = mem;
				return;
			}
		}
	}

	if (last_player == nullptr)
		selfDiscard(last_player,landlord,prev_player,next_player);//直接出牌
	else if (!hint && this != landlord && last_player != landlord)
		friendDiscard(last_player,landlord,prev_player,next_player);//跟友方牌：最后出牌的是友方,并且不是提示
	else
		enemyDiscard(hint,last_player,landlord,prev_player,next_player);//跟敌方的牌或提示
}

void Player::selfDiscard(Player* last_player, Player* landlord, Player* prev_player, Player* next_player)
{
	if (analyse.size() == 1){//剩最后一手牌
		select_set = analyse[0];
		return;
	}

	if (analyse.size() == 2){//剩两手牌，出最大的那组
		//“查看”其它玩家手牌，只为分析剩余牌中的最大的
		int maxNum = 0;
		Player *p = prev_player;
		if (*p->cards.rbegin() > maxNum)
			maxNum = *p->cards.rbegin();
		p = next_player;
		if (*p->cards.rbegin() > maxNum)
			maxNum = *p->cards.rbegin();
		for (auto mem : analyse){//如果手中有比剩余牌还大的一手牌，就先打出该牌
			if (mem.getValue() > CardSet::convert(maxNum)){
				select_set = mem;
				return;
			}
		}
		//否则，打出牌类型最大的牌
		select_set = analyse[1];
		return;
	}
	if (next_player->cards.size() == 1){//下家手牌数为1
		if (this != landlord && last_player != landlord){//下家为友方
			//没试验过下家牌，就打出最小的一张；否则就正常出牌
			if (!test){
				if (analyse[0].getType() == Single &&
					analyse[0].getValue() == CardSet::convert(*(cards.begin()))){
					select_set = analyse[0];
					return;
				}
				else{
					select_set.add(*(cards.begin()));
					select_set.setType(Single);
					select_set.setValue(select_set.getCardSet().begin()->first);
					//拆牌了！要重新分析牌
					analyse.clear();
					return;
				}

			}

		}
		else{//下家为敌方剩1牌
			//待实现！！
			//思路是尽量不出单牌，只有单牌了的话就从大到小出
		}
	}
	//正常顺序出牌：(A以上的牌尽量不直接出、炸弹不直接出)
	//单牌→对子→双顺→单顺→三条、三带一、飞机
	for (auto mem : analyse){
		if ((mem.getType() == Single || mem.getType() == Double) &&
			mem.getValue() >= 15 || mem.getType() == Bomb)
			continue;
		select_set = mem;
		return;
	}
	select_set = analyse[0];
	return;
}


void Player::friendDiscard(Player* last_player, Player* landlord, Player* prev_player, Player* next_player)
{
	if (last_player != landlord && prev_player == landlord){
		return;//上家为地主，但最后出牌方为友方，则不出牌
	}
	for (auto mem : analyse){//查找相应牌
		if (mem.getType() == last_player->discard_set.getType() &&
			mem.getCnt() == last_player->discard_set.getCnt() &&
			mem.getValue() > last_player->discard_set.getValue()){

			select_set = mem;
			break;
		}
	}
	if (analyse.size() > 2 && select_set.getValue() > 14)
		select_set.reset();//手牌手数大于2，并且所选牌权值大于14（A），则不出牌
	return;
}

void Player::enemyDiscard(bool hint,Player* last_player, Player* landlord, Player* prev_player, Player* next_player)
{
	auto lastdiscard = last_player->discard_set;//敌方出牌

	//拆成基本牌
	analyse.clear();
	divideIntoGroups();
	sort(analyse.begin(), analyse.end(), cmp);

	for (auto mem : analyse){//查看是否有相应牌，并且权值大
		if (mem.getType() == lastdiscard.getType() &&
			mem.getCnt() == lastdiscard.getCnt() &&
			mem.getValue() > lastdiscard.getValue()){

			select_set = mem;
			return;
		}
	}
	//需要拆牌
	switch (lastdiscard.getType()){
	case Single://敌方出的是单牌
		getSingle(last_player);
		break;
	case Double:
		getDouble(last_player);
		break;
	case SingleSeq:
		getSingleSeq(last_player);
		break;
	case Three:
		break;
	case ThreePlus://三带一
		getThreePlus(last_player);
		break;
	case Airplane://飞机，需要组合
		getAirplane(last_player);
		break;
	default:
		break;
	}
	if (select_set.getCnt())
		return;
	//敌方剩一张牌，或有适合的炸弹，就出炸弹
	if (hint || lastdiscard.getCnt() > 3 || lastdiscard.getValue() > 14){
		for (auto mem : analyse){
			if (mem.getType() == Bomb){
				if (last_player->discard_set.getType() == Bomb &&//如果别人最后出牌为炸弹，
					mem.getValue() <= last_player->discard_set.getValue())//且自己的炸弹不大于对方时，
					continue;//不能选择改牌
				select_set = mem;
				return;
			}
		}
	}
	return;
}

//电脑出牌
bool Player::robotDiscard()
{
	if (select_set.getCnt() == 0){//电脑选牌区为空，说明不出
		is_discard = true;
		return false;
	}
	//否则正常打出
	return discardAndClear();
}

//玩家出牌
bool Player::humanDiscard(Player *last_player)
{
	if (!isValid(last_player)){//选牌不符合规定
		select_set.reset();//清空选牌
		return false;//不允许出
	}
	//否则正常打出，并分析是否拆牌
	return discardAndClear();
}



void Player::getSingle(Player *last_player)
{
	auto last_discard = last_player->discard_set;//敌方出牌

	for (auto mem : analyse){
		if (mem.getType() == SingleSeq && mem.getCnt() > 5){//首先,拆单顺数量大于5的
			if (mem.getCardSet().begin()->first > last_discard.getValue()){
				select_set.add(*mem.getCards().begin());
				select_set.setValue(mem.getCardSet().begin()->first);
				select_set.setType(Single);
				analyse.clear();//拆牌了，一定要清空
				return;
			}
			else if (mem.getCardSet().rbegin()->first > last_discard.getValue()){
				select_set.add(*(mem.getCards().rbegin()));
				select_set.setValue(mem.getValue());
				select_set.setType(Single);
				analyse.clear();//拆牌了，一定要清空
				return;
			}
		}
	}
	for (auto mem : analyse){
		if (mem.getType() == Three){//其次,拆三条
			if (mem.getCardSet().begin()->first > last_discard.getValue()){
				select_set.add(*mem.getCards().begin());
				select_set.setValue(mem.getCardSet().begin()->first);
				select_set.setType(Single);
			    analyse.clear();//拆牌了，一定要清空
				return;
			}
		}
	}
	for (auto mem : analyse){
		if (mem.getType() == Double){//再者,拆对子
			if (mem.getCardSet().begin()->first > last_discard.getValue()){
				select_set.add(*mem.getCards().begin());
				select_set.setValue(mem.getCardSet().begin()->first);
				select_set.setType(Single);
				analyse.clear();//拆牌了，一定要清空
				return;
			}
		}
	}
}


void Player::getDouble(Player *last_player)
{
	auto last_discard = last_player->discard_set;//敌方出牌

	for (auto mem : analyse){
		if (mem.getType() == Three){//拆三条
			if (mem.getCardSet().begin()->first > last_discard.getValue()){
				auto b = mem.getCards().begin();
				for (int i = 0; i < 2; ++i)
					select_set.add(*b++);
				select_set.setValue(mem.getCardSet().begin()->first);
				select_set.setType(Double);
				analyse.clear();//拆牌了，一定要清空
				return;
			}
		}
	}
	for (auto mem : analyse){
		int i = 0, m = 0;
		if (mem.getType() == ThreeSeq){//拆三顺
			if (mem.getCardSet().begin()->first > last_discard.getValue()){
				auto b = mem.getCards().begin();
				for (int i = 0; i < 2; ++i)
					select_set.add(*b++);
				select_set.setValue(mem.getCardSet().begin()->first);
				select_set.setType(Double);
				analyse.clear();//拆牌了，一定要清空
				return;
			}
			else if (mem.getCardSet().rbegin()->first > last_discard.getValue()){
				select_set.add(*(mem.getCards().rbegin()));
				select_set.setValue(mem.getValue());
				select_set.setType(Double);
				analyse.clear();//拆牌了，一定要清空
				return;
			}
		}
	}
}



void Player::getSingleSeq(Player *last_player)
{
	auto last_discard = last_player->discard_set;//敌方出牌

	for (auto mem : analyse){
		if (mem.getType() == SingleSeq &&
			mem.getValue() > last_discard.getValue() &&
			mem.getCnt() > last_discard.getCnt()){//拆更长的单顺
			if (mem.getCnt() - (mem.getValue() - last_discard.getValue()) >= last_discard.getCnt()){
				//长单顺是从短单顺的开始的元素或更小的元素开始的
				for (int i = last_discard.getValue() - last_discard.getCnt() + 2, j = 0;
					j < last_discard.getCnt(); ++j)
					select_set.add(valueToNum((mem.getCards()), i + j));
				select_set.setValue(last_discard.getValue() + 1);
				select_set.setType(SingleSeq);
				analyse.clear();//拆牌了，一定要清空
				return;
			}
			else{//长单顺的开始元素比短单顺的开始元素大
				int i = 0;
				auto b = mem.getCards().begin();
				for (; i < last_discard.getCnt(); ++i, ++b)
					select_set.add(*b);
				select_set.setValue(CardSet::convert(*--b));
				select_set.setType(SingleSeq);
				analyse.clear();//拆牌了，一定要清空
				return;
			}
		}
	}
}

void Player::getThreePlus(Player *last_player)
{
	auto b = analyse.begin();
	for (; b != analyse.end(); ++b){//查找比对方三张相同牌的牌面大的三条
		if ((*b).getType() == Three && (*b).getValue() > last_player->discard_set.getValue()){
			break;
		}
	}
	if (b == analyse.end())//如果没有
		return;//跳出
	if (last_player->discard_set.getCnt() == 4){//最后出牌为三带一张
		if (analyse[0].getType() == Single){//有单牌
			for (auto m : analyse[0].getCards())
				(*b).add(m);
			(*b).setType(ThreePlus);
			analyse[0].setType(Void);
			select_set = *b;
			return;
		}
		else{//需要拆牌
			for (auto mem : analyse){
				if (mem.getType() == SingleSeq && mem.getCnt() > 5){//首先,拆单顺数量大于5的
					select_set = *b;
					select_set.add(*mem.getCards().begin());
					select_set.setType(ThreePlus);
					analyse.clear();//拆牌了，一定要清空
					return;
				}
			}
			for (auto mem : analyse){
				if (mem.getType() == Three && mem != *b && mem.getValue() < 14){//其次,拆三条
					select_set = *b;
					select_set.add(*mem.getCards().begin());
					select_set.setType(ThreePlus);
					analyse.clear();//拆牌了，一定要清空
					return;
				}
			}
			for (auto mem : analyse){
				if (mem.getType() == Double && mem.getValue() < 14){//再者,拆对子
					select_set = *b;
					select_set.add(*mem.getCards().begin());
					select_set.setType(ThreePlus);
					analyse.clear();//拆牌了，一定要清空
					return;
				}
			}
		}
	}
	else{//三带一对
		for (auto mem : analyse){//先找对子
			if (mem.getType() == Double && mem.getValue() < 14){
				for (auto m : mem.getCards())
					(*b).add(m);
				(*b).setType(ThreePlus);
				mem.setType(Void);
				select_set = *b;
				return;
			}
		}
		for (auto mem : analyse){
			if (mem.getType() == Three && mem != *b && mem.getValue() < 14){//其次,拆三条
				select_set = *b;
				for (int i = 0; i < 3; ++i)
					select_set.add(*mem.getCards().begin());
				select_set.setType(ThreePlus);
				analyse.clear();//拆牌了，一定要清空
				return;
			}
		}
	}
}

void Player::getAirplane(Player *last_player)
{
	analyse.clear();
	divideIntoGroups();
	sort(analyse.begin(), analyse.end(), cmp);

	int wing = 0,//翅膀类型
		n = 0;//单顺中三张牌的个数
	for (auto mem : last_player->discard_set.getCardSet()){
		if (mem.second == 3)
			++n;
	}
	if (last_player->discard_set.getCnt() == 5 * n)//飞机翅膀为对子
		wing = 2;
	else{//飞机翅膀为单张
		while (last_player->discard_set.getCnt() != 4 * n)
			--n;
		wing = 1;
	}
	auto b = analyse.begin();
	for (; b != analyse.end(); ++b){
		if ((*b).getType() == ThreeSeq &&
			(*b).getCnt() == 3 * n &&
			(*b).getValue() > last_player->discard_set.getValue())
			break;
	}
	if (b == analyse.end())
		return;
	int count = 0;
	for (auto mem : analyse){
		if (mem.getType() == (wing == 1 ? Single : Double))
			++count;
	}
	if (count < n)
		return;
	for (auto mem : analyse){
		if (mem.getType() == (wing == 1 ? Single : Double)){
			for (auto m : mem.getCards())
				(*b).add(m);
			mem.setType(Void);
			--n;
		}
		if (!n)
			break;
	}
	(*b).setType(Airplane);
	select_set = *b;
	return;
}

bool Player::discardAndClear()
{
	discard_set = select_set;//把选牌放入出牌区：打出选牌
	bool needclear = true;//本次出牌是否为拆牌，需要更新分析牌堆
	for (auto b = analyse.begin(); b != analyse.end(); ++b){
		if ((*b).getType() == select_set.getType() &&
			(*b).getValue() == select_set.getValue() &&
			(*b).getCnt() == select_set.getCnt()){//不是拆牌
			analyse.erase(b);
			needclear = false;//不需要清空
			break;
		}
	}
	if (needclear)//需要清空，下次出牌要重新分析
		analyse.clear();

	for (auto mem : select_set.getCards()){
		cards.erase(mem);//从手牌中删除打出牌
	}
	select_set.reset();//清空选牌区
	return true;
}

void Player::pass()
{
	is_discard = true;
	select_set.reset();
	return;
}



int Player::valueToNum(std::set<int> cardscopy, int value)
{
	if (value<3 || value>17 || cardscopy.empty())
		throw std::runtime_error("Value not in set!");

	if (value == 16 && cardscopy.find(52) != cardscopy.end()){
		cardscopy.erase(52);
		return 52;
	}
	else if (value == 17 && cardscopy.find(53) != cardscopy.end()){
		cardscopy.erase(53);
		return 53;
	}
	else{
		for (int i = (value - 3) * 4, j = 0; j < 4; ++j){
			if (cardscopy.find(i + j) != cardscopy.end()){
				cardscopy.erase(i + j);
				return i + j;
			}

		}
		throw std::runtime_error("Value not in set!");
	}
}

void Player::updateMap(std::map<int, int> &m)
{
	bool notcomplete = true;
	while (notcomplete){
		notcomplete = false;
		auto b = m.begin();
		for (; b != m.end(); ++b){
			if (b->second == 0){
				m.erase(b);
				notcomplete = true;
				break;
			}
		}
	}
}

bool Player::cmp(CardSet c1, CardSet c2)
{
	if (c1.getType() != c2.getType())
		return c1.getType() < c2.getType();
	else
		return c1.getValue() < c2.getValue();
}