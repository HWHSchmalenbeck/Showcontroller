#include "Arduino.h"
#include "Controller.h"

Color::Color(const int red_color, const int green_color, const int blue_color) {
    if (!(red_color != NULL && red_color >= 0 && red_color <= 255) || !(green_color != NULL && green_color >= 0 && green_color <= 255) || !(blue_color != NULL && blue_color >= 0 && blue_color <= 255)) {
        // Error
        this->red = -1;
        this->green = -1;
        this->blue = -1;
        return;   
    }
    this->red = red_color;
    this->green = green_color;
    this->blue = blue_color;
}