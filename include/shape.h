//
// Created by magicgh on 7/14/2020.
//

#ifndef LANDLORD_AI_SHAPE_H
#define LANDLORD_AI_SHAPE_H

#endif //LANDLORD_AI_SHAPE_H


typedef struct Point {
    int x, y;

    Point();

    Point(const int &x, const int &y);

    Point(const Point &t);

    friend Point operator+(const Point &a,const Point &b);
    friend Point operator-(const Point &a,const Point &b);
    Point &operator=(const Point &t);
    Point operator+=(const Point &t);
    Point operator-=(const Point &t);

} Vec;

class Rect {
private:
    Point position;
    Vec length;
public:
    Rect();

    Rect(const Point &position, const Vec &length);

    Rect(const Rect &t);

    void set(const Point &position, const Vec &length);

    void setLen(const Vec &length);

    void move(const Vec &direction);

    inline Point getUL() {
        return this->position;
    }

    inline Point getDR() {
        return Point(position.x + position.x, position.y + length.y);
    }

    inline Point getUR() {
        return Point(position.x + length.x, position.y);
    }

    inline Point getDL() {
        return Point(position.x, position.y + length.y);
    }

    inline int getUp() {
        return getUL().y;
    }

    inline int getDown() {
        return getDL().y;
    }

    inline int getLeft() {
        return getDL().x;
    }

    inline int getRight() {
        return getDR().x;
    }

    inline Vec getLen() {
        return this->length;
    }
};