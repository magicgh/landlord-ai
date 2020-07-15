/*
 * @Author: Eric Feng
 * @Date: 2020-07-14 16:14:35
 * @LastEditTime: 2020-07-15 10:43:54
 * @LastEditors: Please set LastEditors
 * @Description: Image class
 * @FilePath: \landlord-ai\src\image.cpp
 */ 

#include "shape.h"
#include "components.h"

/*
 *********************************
 * Image
 *********************************
 */

Image::Image() {
    rect_pos_ = Rect();
    img_ = nullptr;
}

Image::Image(const Image &other) {
    img_ = newimage();
    getimage(img_, other.img_, 0, 0, getwidth(other.img_), getheight(other.img_));
    rect_pos_ = other.rect_pos_;
}

Image::~Image() {
    _Destroy();
}

/*
 * Image::Init(LPCTSTR pImgFile):
 *  Load image from pImgFile path.
 */
void Image::Init(LPCTSTR pImgFile) {
    _LoadFile(pImgFile);
}

void Image::Init(LPCTSTR pImgFile, Point pos) {
    _LoadFile(pImgFile);
    rect_pos_.set(pos, Vec(getwidth(img_), getheight(img_)));
}

/*
 * Image::SetPos(Point pos):
 *  Set position
 */
void Image::SetPos(Point pos) {
    rect_pos_.set(pos, rect_pos_.getLen());
}

/*
 * Put image on window
 */
void Image::PutImage() {
    putimage(rect_pos_.getLeft(), rect_pos_.getUp(), img_);
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

Image & Image::operator =(const Image &other) {
    this->img_ = newimage();
    getimage(this->img_, other.img_, 0, 0, getwidth(other.img_), getheight(other.img_));
    this->rect_pos_ = other.rect_pos_;

    return *this;
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

/*
 *********************************
 * Button
 *********************************
 */
Button::Button():
    press_img_(Image()), focus_img_(Image()), unfocus_img_(Image()), 
    rect_pos_(Rect()), is_pressed_(0) {}

Button::Button(const Button &other):
    press_img_(other.press_img_), focus_img_(other.focus_img_), unfocus_img_(other.unfocus_img_),
    rect_pos_(other.rect_pos_), is_pressed_(0) {}

void Button::Init(
    Image focus_img,
    Image unfocus_img,
    Image press_img,
    Point pos,
    Vec scale
) {
    focus_img_ = focus_img;

    if(unfocus_img.img_ == nullptr)
        unfocus_img_ = focus_img;
    else
        unfocus_img_ = focus_img;

    if(press_img.img_ == nullptr)
        press_img_ = focus_img;
    else 
        press_img_ = press_img;
    
    if(scale.x == 0 && scale.y == 0) {
        scale.x = getwidth(focus_img_.img_);
        scale.y = getheight(focus_img_.img_);
    }

    rect_pos_ = Rect(pos, scale);
}

void Button::PutButton() {
    if(is_pressed_) {
        press_img_.SetPos(rect_pos_.getUL());
        press_img_.PutImage();
    }
    else if(on_focus_) {
        focus_img_.SetPos(rect_pos_.getUL());
        focus_img_.PutImage();
    }
    else {
        unfocus_img_.SetPos(rect_pos_.getUL());
        unfocus_img_.PutImage();
    }
}

void Button::SetPos(Point pos) {
    rect_pos_.set(pos, rect_pos_.getLen());
}

const Rect Button::GetRect() {
    return rect_pos_;
}

void Button::SetFocus(int focus) {
    on_focus_ = focus;
}

void Button::SetPress(int pressed) {
    is_pressed_ = pressed;
}