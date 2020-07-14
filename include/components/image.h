/*
 * @Author: Eric Feng
 * @Date: 2020-07-13 16:14:50
 * @LastEditTime: 2020-07-14 16:49:26
 * @LastEditors: Eric Feng
 * @Description: Image class
 * @FilePath: \landlord-ai\include\components\image.h
 */

#pragma once

#include "graphics.h"
#include "shape.h"

class Image{
public:
    Image();
    ~Image();

    void Init(LPCTSTR pImgFile);                // Initialize Image obj
    void Init(LPCTSTR pImgFile, Point pos);
    void SetPos(Point pos);                     // Set postition of the image
    void PutImage();                            // Put image on window

private:
    void _LoadFile(LPCTSTR pImgFile);           // Load image from file
    void _Destroy();                            // Destroy image obj

    PIMAGE img_;
    Point pos_;
};
<<<<<<< HEAD

#endif
=======
>>>>>>> f15c3b2 (pressed)
