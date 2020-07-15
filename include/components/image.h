/*
 * @Author: Eric Feng
 * @Date: 2020-07-13 16:14:50
 * @LastEditTime: 2020-07-15 10:19:01
 * @LastEditors: Please set LastEditors
 * @Description: Image class
 * @FilePath: \landlord-ai\include\components\image.h
 */

#pragma once

#include "graphics.h"

struct Point;
class Rect;

/*
 * Image:
 *  One image handler.
 */
class Image{
public:
    Image();
    Image(const Image &other);
    ~Image();

    void Init(LPCTSTR pImgFile);                // Initialize Image obj
    void Init(LPCTSTR pImgFile, Point pos);
    void SetPos(Point pos);                     // Set postition of the image
    void PutImage();                            // Put image on window

    friend class Button;

    Image & operator =(const Image &other);

private:
    void _LoadFile(LPCTSTR pImgFile);           // Load image from file
    void _Destroy();                            // Destroy image obj

    PIMAGE img_;                                // Image variable
    Rect rect_pos_;                             // Position
};
