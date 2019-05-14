#include "player.h"
#include "simple_logger.h"
#include "entity.h"
#include "collision.h"
#include "gf2d_gui.h"
#include "obstacles.h"
#include "gf2d_audio.h"
#include "particles.h"
#include "gf2d_particles.h"
#include "gf2d_color.h"

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
	entity->hitbox.id = 0;
	entity->color = gf2d_color_to_vector4(gf2d_color(1, 1, 1, 1));
	//entity->rigidBody.shape = &entity->hitbox;
	//entity->update = player_update;

	return entity;

}


void player_update(Entity *self, Space *space, Entity *obstacle1, Entity *obstacle2, Entity *obstacle3, Entity *enemy, Mix_Music *music, int Level) {
	const Uint8 *keys;

	keys = SDL_GetKeyboardState(NULL);

	if (keys[SDL_SCANCODE_W])self->velocity.y -= 2; //Mix_PlayChannel(-1, music, 0); //up
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
		if (staticHit.shape->id == 4) {
			destroyEntity(enemy);
			slog("enemy detected");
		}
		if (staticHit.shape->id == 2) {
			if (staticHit.shape->ability == 1) {
				self->ability = 1;
				slog("earth pickup detected %i",self->ability);
				gui_setup_earth(); 
				self->color = gf2d_color_to_vector4(gf2d_color(0, 1, 0, 1));
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
				self->color = gf2d_color_to_vector4(gf2d_color(1, 0, 0, 1));
			}
			else if (staticHit.shape->ability == 4) {
				self->ability = 4;
				slog("water pickup detected %i", self->ability);
				gui_setup_water();
				self->color = gf2d_color_to_vector4(gf2d_color(0, 0, 1, 1));
			}
		}
		if (staticHit.shape->id == 3) { //if player touches an obstacle
			if (staticHit.shape->obstacle == 1) { //if obstacle gets destroyed by earth ability
				if (self->ability == 1) {
					slog("earth obstacle detected");
					gf2d_space_remove_body(space, &obstacle1->rigidBody);
					destroyEntity(obstacle3);
				}
				else {
					slog("can not be destroyed with current ability");
				}
			}
			if (staticHit.shape->obstacle == 3) { //if obstacle gets destroyed by fire ability
				if (self->ability == 3) {
					slog("fire obstacle detected");
					gf2d_space_remove_body(space, &obstacle1->rigidBody);
					destroyEntity(obstacle1);
				}
				else {
					slog("can not be destroyed with current ability");
				}
			}
			if (staticHit.shape->obstacle == 4) { //if obstacle gets destroyed by water ability
				if (self->ability == 4) {
					slog("water obstacle detected");
					gf2d_space_remove_body(space, &obstacle2->rigidBody);
					destroyEntity(obstacle2);
				}
				else {
					slog("can not be destroyed with current ability");
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

	//slog("Position: %i, %i",self->velocity.x,self->velocity.y);
	
}









