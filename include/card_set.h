//
// Created by magicgh on 7/14/2020.
//

#pragma once
#include <map>
#include <set>
enum Type{
    Void, //空
    Single, //单张
    Double, //对子
    Three, //三条
    SingleSeq, //单顺
    DoubleSeq, //双顺
    ThreeSeq, //三顺
    ThreePlus, //三带一（一张或一对）
    Airplane, //飞机
    FourSeq, //四带二（两张或两对）
    Bomb, //炸弹、王炸
};
class CardSet{
private:
    std::map<int,int> card_set;
    std::set<int> cards;
    Type type;
    int value, cnt;
public:
    CardSet();
    CardSet(Type t, int val);
    CardSet& operator = (const CardSet &t);
    void add(int num);
    void remove(int num);
    void reset();
    static int convert(int num);
    inline int getCnt(){
        return cnt;
    }
    inline void setCnt(const int &cnt){
        this->cnt = cnt;
    }
    inline int getValue(){
        return value;
    }
    inline void setValue(const int &value){
        this->value = value;
    }
    inline Type getType(){
        return type;
    }
    inline void setType(const Type &type){
        this->type = type;
    }
    // 0-53 转换为 3-17, A(14), B(15), 小王(16), 大王(17)

    inline std::map<int,int>& getCardSet(){//返回左值
        return this->card_set;
    }

    inline std::set<int>& getCards(){//返回左值
        return this->cards;
    }

    bool operator ==(CardSet& obj);
    bool operator !=(CardSet& obj);
};