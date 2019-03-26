#include "player.h"
#include "simple_logger.h"
#include "entity.h"
#include "collision.h"
#include "gf2d_gui.h"

void player_update(Entity *self, Space *space);


Entity *newPlayer(Vector2D position)
{
	Entity *entity = NULL;
	int i;

	entity = ent_new();

	if (!entity) {
		slog("can't determine the new player entity");
		return NULL;
	}
	vector2d_copy(entity->position, position);

	entity->sprite = gf2d_sprite_load_all("images/player_sheet.png", 64, 64, 5); //this is the player sprite
	entity->frame_num = 5;
	entity->hitbox = gf2d_shape_rect(position.x, position.y, 20, 20);
	entity->onGround = 0;
	entity->ability = 0;
	//entity->update = player_update;
	return entity;

}


void player_update(Entity *self, Space *space) {
	const Uint8 *keys;
	keys = SDL_GetKeyboardState(NULL);

	if (keys[SDL_SCANCODE_W])self->velocity.y -= 3; //up
	if (keys[SDL_SCANCODE_A])self->velocity.x -= .75; //left
	if (keys[SDL_SCANCODE_S] && self->onGround == 0)self->velocity.y += .75; //down, doesn't work if on ground
	if (keys[SDL_SCANCODE_D])self->velocity.x += .75; //right
	if (keys[SDL_SCANCODE_Z] && keys[SDL_SCANCODE_D] && self->ability == 2)self->velocity.x += 4; //air dash right
	if (keys[SDL_SCANCODE_Z] && keys[SDL_SCANCODE_A] && self->ability == 2)self->velocity.x -= 4; //air dash left

	vector2d_add(self->position, self->position, self->velocity);

	self->hitbox.s.c.x = self->position.x + 20;
	self->hitbox.s.c.y = self->position.y + 25;

	gf2d_shape_draw(self->hitbox, gf2d_color(1, 0, 0, 1),vector2d(0,0));

	Collision staticHit = gf2d_space_shape_test(space, self->hitbox);
	if (staticHit.collided >= 1) {
		if (staticHit.shape->id == 2) {
			if (staticHit.shape->ability == 1) {
				self->ability = 1;
				slog("earth pickup detected %i",self->ability);
				gui_setup_earth();
			}
			else if (staticHit.shape->ability == 2) {
				self->ability = 2;
				slog("air pickup detected %i", self->ability);
				gui_setup_air();
			}
			else if (staticHit.shape->ability == 3) {
				self->ability = 3;
				slog("fire pickup detected %i", self->ability);
				gui_setup_fire();
			}
			else if (staticHit.shape->ability == 4) {
				self->ability = 4;
				slog("water pickup detected %i", self->ability);
				gui_setup_water();
			}
		}
		if (staticHit.shape->id == 3) { //if player touches an obstacle
			if (staticHit.shape->obstacle == 1) { //if obstacle gets destroyed by earth ability
				if (self->ability == 1) {
					//destroy obstacle
				}
				else {

				}
			}
			if (staticHit.shape->obstacle == 2) { //if obstacle gets destroyed by air ability
				if (self->ability == 2) {
					//destroy obstacle
				}
				else {

				}
			}
			if (staticHit.shape->obstacle == 3) { //if obstacle gets destroyed by fire ability
				if (self->ability == 3) {
					//destroy obstacle
				}
				else {

				}
			}
			if (staticHit.shape->obstacle == 4) { //if obstacle gets destroyed by water ability
				if (self->ability == 4) {
					//destroy obstacle
				}
				else {

				}
			}
		}
		slog("collision detected");
		self->onGround = 1;
		self->velocity = vector2d(0, 0); 
	}
	else {
		self->velocity = vector2d(0, .75);
		self->onGround = 0;
	}

	slog("Position: %i, %i",self->velocity.x,self->velocity.y);
	
}









