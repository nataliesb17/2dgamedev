#include "gf2d_mouse.h"
#include "entity.h"
#include "gf2d_sprite.h"
#include "gf2d_vector.h"
#include <SDL.h>

typedef struct
{
	Uint32 buttons; //buttons mask
	Vector2D position; //position of mouse
}MouseState;

typedef struct
{
	MouseState mouse[2]; //mouse state for the current and last frames
	Entity entity;
}Mouse;

static Mouse _mouse = { 0 };

void gf2d_mouse_load() {
	Entity *entity = NULL;
	entity = ent_new();

	entity->sprite = gf2d_sprite_load_all("images/pointer.png", 32, 32, 16);

	return entity;
}

void gf2d_mouse_update() {
	int x, y;
	memcpy(&_mouse.mouse[1], &_mouse.mouse[0], sizeof(MouseState));
	_mouse.mouse[0].buttons = SDL_GetMouseState(&x, &y);
	vector2d_set(_mouse.mouse[0].position, x, y);
}

void gf2d_mouse_draw() {
	gf2d_sprite_draw(
		&_mouse.entity,
		_mouse.mouse[0].position,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL,
		NULL);
}

int gf2d_mouse_moved() {
	if ((_mouse.mouse[0].position.x != _mouse.mouse[1].position.x) ||
		(_mouse.mouse[0].position.y != _mouse.mouse[1].position.y) ||
		(_mouse.mouse[0].buttons != _mouse.mouse[1].buttons))
	{
		return 1;
	}
	return 0;
}

int gf2d_mouse_button_pressed(int button) {
	int mask;
	mask = 1 << button;
	if ((_mouse.mouse[0].buttons & mask) &&
	   !(_mouse.mouse[1].buttons & mask))
	{
		return 1;
	}
	return 0;
}

int gf2d_mouse_button_held(int button) {
	int mask;
	mask = 1 << button;
	if ((_mouse.mouse[0].buttons & mask) &&
		(_mouse.mouse[1].buttons & mask))
	{
		return 1;
	}
	return 0;
}

int gf2d_mouse_button_released(int button) {
	int mask;
	mask = 1 << button;
	if (!(_mouse.mouse[0].buttons & mask) &&
		(_mouse.mouse[1].buttons & mask))
	{
		return 1;
	}
	return 0;
}

int gf2d_mouse_button_state(int button) {
	int mask;
	mask = 1 << button;
	return (_mouse.mouse[0].buttons & mask);
}

Vector2D gf2d_mouse_get_position() {
	return _mouse.mouse[0].position;
}

Vector2D gf2d_mouse_get_movement() {
	Vector2D dif;
	vector2d_sub(dif, _mouse.mouse[0].position, _mouse.mouse[1].position);
	return dif;
}

int gf2d_mouse_in_rect(Rect r) {
	return gf2d_point_in_rect(_mouse.mouse[0].position, r);
}

/*eol@eof*/