/*
 * @Author: Eric Feng
 * @Date: 2020-07-14 16:14:35
 * @LastEditTime: 2020-07-14 22:31:29
 * @LastEditors: Please set LastEditors
 * @Description: Image class
 * @FilePath: \landlord-ai\src\image.cpp
 */ 

#include "components.h"

/*
 *********************************
 * Image
 *********************************
 */

Image::Image() {
    pos_ = Point(0, 0);
    img_ = nullptr;
}

Image::~Image() {
    _Destroy();
}

void Image::Init(LPCTSTR pImgFile) {
    _LoadFile(pImgFile);
}

void Image::Init(LPCTSTR pImgFile, Point pos) {
    _LoadFile(pImgFile);
    pos_ = pos;
}

/*
 * Set position
 */
void Image::SetPos(Point pos) {
    pos_ = pos;
}

/*
 * Put image on window
 */
void Image::PutImage() {
    putimage(pos_.x, pos_.y, img_);
}

/*
 * Load image file
 */
void Image::_LoadFile(LPCTSTR pImgFile) {
    if(img_) {
        delimage(img_);
        img_ = nullptr;
    }

    img_ = newimage();
    getimage(img_, pImgFile);
}

/*
 * Destroy image 
 */
void Image::_Destroy() {
    if(img_) {
        delimage(img_);
        img_ = nullptr;
    }
}

/*
 *********************************
 * Text
 *********************************
 */

Text::Text(LPCSTR text_str, Rect rect_pos, LPCSTR font_face):
    out_text_(text_str), rect_pos_(rect_pos), font_face_(font_face) {}

Text::~Text() {}

/*
 * Text::SetText(LPCSTR text_str):
 *  :param text_str: String of the text
 *  Set contents of a text.
 */
void Text::SetText(LPCSTR text_str) {
    out_text_ = text_str;
}

/*
 * Text::SetPos(Rect rect_pos):
 *  :param rect_pos: Rectangle of text
 *  Set rectangle of a text.
 */
void Text::SetPos(Rect rect_pos) {
    rect_pos_ = rect_pos;
}

/*
 * Text::PutText():
 *  Put text on window
 */
void Text::PutText() {
    setfont(0, 0, font_face_);
    outtextrect(
                rect_pos_.getUL().x,
                rect_pos_.getUL().y,
                rect_pos_.getLen().x,
                rect_pos_.getLen().y,
                out_text_
            );
}

void Text::_Destroy() {}