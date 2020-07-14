/*
 * @Author: Eric Feng
 * @Date: 2020-07-14 16:14:35
 * @LastEditTime: 2020-07-14 16:48:47
 * @LastEditors: Eric Feng
 * @Description: Image class
 * @FilePath: \landlord-ai\src\image.cpp
 */ 

#include "components/image.h"

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