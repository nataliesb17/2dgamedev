#ifndef GF2D_MOUSE_H
#define GF2D_MOUSE_H

#include "gf2d_vector.h"
#include "gf2d_shape.h"

/**
* @brief load a mouse graphic from an entity
* @param entity the file to use to load the mouse info
* @note automatically frees previously loaded entity info
*/
void gf2d_mouse_load();

/**
* @brief call once per frame to update the mouse info
*/
void gf2d_mouse_update();

/**
* @brief draws the mouse to screen
* @note should probs be last thing done each frame
*/
void gf2d_mouse_draw();

/**
* @brief check if the mouse has moved since last frame
* gf2d_mouse_update() must have been called or this returns 0
* @return 1 if the mouse has changed state
*/
int gf2d_mouse_moved();

/**
* @brief check if the mouse is down at the moment
* @param button the button number to check (left is 0, right is 1)
* @return 1 if it is down, 0 otherwise
*/
int gf2d_mouse_button_state(int button);

/**
* @brief check if the mouse was pressed this frame
* @param button the button number to check (left is 0, right is 1)
* @return 1 if it has, 0 otherwise
*/
int gf2d_mouse_button_pressed(int button);

/**
* @brief check if the mouse was held this frame
* @param button the button number to check (left is 0, right is 1)
* @return 1 if it has, 0 otherwise
*/
int gf2d_mouse_button_held(int button);

/**
* @brief check if the mouse was pressed this frame
* @param button the button number to check (left is 0, right is 1)
* @return 1 if it has, 0 otherwise
*/
int gf2d_mouse_button_released(int button);

/**
* @brief check the state of the mouse button
* @param button the button number to check (left is 0, right is 1)
* @return 1 if it is down, 0 otherwise
*/
int gf2d_mouse_button_state(int button);

/**
* @brief get the current mouse position
* @return a vector containing the mouse position info, will be -1,-1 if never updated
*/
Vector2D gf2d_mouse_get_position();

/**
* @brief get the change in position from the last frame
* @return a vector containing the change in mouse position
*/
Vector2D gf2d_mouse_get_movement();

/**
* @brief check if the mouse is in the given rect
* @param r the rectangle to check against
* @return 1 if it is within the rect, 0 otherwise
*/
int gf2d_mouse_in_rect(Rect r);

#endif