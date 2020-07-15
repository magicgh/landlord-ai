/*
 * @Author: Eric Feng
 * @Date: 2020-07-13 16:14:34
 * @LastEditTime: 2020-07-15 10:34:43
 * @LastEditors: Please set LastEditors
 * @Description:
 * @FilePath: \landlord-ai\include\components\button.h
 */

#pragma once

typedef struct Point Vec;
class Image;

/*
 * Button:
 *  One button handler.
 */
class Button {
public:
    Button();
    Button(const Button &other);

    // Intitialize
    void Init(Image focus_img,                  // Image show when mouse focus
              Image unfocus_img = Image(),      // Image show when mouse unfocus. Image() if equal to focus_img
              Image press_img = Image(),        // Image show when press mouse
              Point pos = Point(),              // Button position
              Vec scale = Vec()                 // Button scale. (NULL to auto detect image size)
            );

    void PutButton();                           // Draw Button on window

    void SetPos(Point pos);                     // Set Position

    const Rect GetRect();                       // Get Button Rectangle

    void SetFocus(int focus = 1);               // Set mouse on focus

    void SetPress(int pressed = 1);             // Set mouse pressed


private:
    int is_pressed_, on_focus_;                 // If pressed, if on focus. 1 if true
    Image unfocus_img_, focus_img_, press_img_; // Focus, unfocus, pressed images
    Rect rect_pos_;                             // Position and scale
};