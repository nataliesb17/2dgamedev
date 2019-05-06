#ifndef BUTTON_H
#define BUTTON_H

#include "gf2d_color.h"

typedef struct {
	Color highColor; //color used when button is highlighted
	Color pressColor; //color used while pressed
}ButtonElement;

/**
* @brief sets the element to be the button
* @param button the button to use
*/
void gf2d_make_button(ButtonElement *button);




#endif