/*
 * @Author: Eric Feng
 * @Date: 2020-07-13 16:19:53
 * @LastEditTime: 2020-07-14 22:17:02
 * @LastEditors: Please set LastEditors
 * @Description: Text outer.
 * @FilePath: \landlord-ai\include\components\text.h
 */

<<<<<<< HEAD
#ifndef COMPONENTS_TEXT_H
#define COMPONENTS_TEXT_H

class _text{

};

#endif
=======
#pragma once
<<<<<<< HEAD
>>>>>>> f15c3b2 (pressed)
=======

#include <string>
#include "graphics.h"


class Text {
public:
    Text(LPCSTR text_str = "", Rect rect_pos = Rect(), LPCSTR font_face = "黑体");
    ~Text();

    void SetText(LPCSTR text_str);
    void SetPos(Rect rect_pos);
    void PutText();

private:
    void _Destroy();

    LPCSTR out_text_;
    LPCSTR font_face_;
    Rect rect_pos_;
};
>>>>>>> 08c9ded (Add Text)
