#include <SDL.h>
#include "gf2d_graphics.h"
#include "gf2d_sprite.h"
#include "simple_logger.h"
#include "entity.h"
#include "gf2d_vector.h"
#include "player.h"
#include "level_build.h"
#include "gf2d_draw.h"
#include "collision.h"
#include "enemy.h"
#include "gf2d_gui.h"
#include "projectiles.h"
#include "obstacles.h"
#include "gf2d_particles.h"
#include "gf2d_mouse.h"
#include "gf2d_audio.h"
#include "saveload.h"

int main(int argc, char * argv[]) //display fire and water abilities
{
	level(1);
}

int level(int Level) {
	/*variable declarations*/
	int done = 0;
	const Uint8 * keys;
	Sprite *sprite;
	Sprite *gui;
	Entity *player;
	Entity *enemy;
	Entity *fireBall;
	Entity *waterBall;
	Entity *earthBall;
	Entity *airBall;
	Mix_Music *music;

	SaveFiles save;

	Entity *fireObs;
	Entity *waterObs;
	Entity *earthObs;

	TileMap *map;
	int collided = 0;
	int playerHealth = 100;

	Sprite *mouse;
	Vector4D mouseColor = { 39, 135, 27, 255 };

	Collision collision;
	Space *space = NULL;
	static Body body[10000];  // not a pointer!
	Shape shape[2];           // not a pointer!

	int mx, my, i;
	float mf = 0;
	static Vector2D path[2];

	/*program initializtion*/
	init_logger("gf2d.log");
	slog("---==== BEGIN ====---");
	gf2d_graphics_initialize(
		"Eli the Elemental Tulip",
		640,
		480,
		640,
		480,
		vector4d(0, 0, 0, 255),
		0);
	gf2d_graphics_set_frame_delay(16);
	gf2d_sprite_init(1024);
	entityManagerInit(1024);
	gf2d_audio_init(256, 16, 4, 1, 1, 1);

	gui_setup_hud();
	SDL_ShowCursor(SDL_DISABLE);

	/*demo setup*/
	sprite = gf2d_sprite_load_image("images/backgrounds/bg_forest.png");
	mouse = gf2d_sprite_load_all("images/pointer.png", 32, 32, 16);
	music = Mix_LoadWAV("music/background.wav");
	Mix_PlayChannel(-1, music, -1);

	space = gf2d_space_new_full(
		3,
		gf2d_rect(0, 0, 1200, 700),
		0.1,
		vector2d(0, 0.1),
		1,
		20);

	//player
	player = newPlayer(vector2d(0, 0), player);

	//LEVEL ONE
	if (Level == 1) {
		enemy = newYEnemy(vector2d(290, 325), enemy);

		fireObs = newFireObstacle(vector2d(413, 245));
		waterObs = newWaterObstacle(vector2d(33, 135));

		waterBall = newWaterpickup(vector2d(213, 175), waterBall);
		fireBall = newFirepickup(vector2d(213, 275), fireBall);

		map = tilemap_load("levels/tilemap.map");

		//All Colliders
		gf2d_space_add_static_shape(space, gf2d_shape_rect(3, 390, 600, 26)); //lowest collider //minus 25y and 87x
		gf2d_space_add_static_shape(space, gf2d_shape_rect(328, 175, 26, 190)); //horizontal collider 
		gf2d_space_add_static_shape(space, gf2d_shape_rect(5, 175, 26, 220)); //horizontal collider left 
		gf2d_space_add_static_shape(space, gf2d_shape_rect(5, 235, 90, 26)); //small horizontal left
		gf2d_space_add_static_shape(space, gf2d_shape_rect(70, 288, 90, 26)); //small horizontal right bottom
		gf2d_space_add_static_shape(space, gf2d_shape_rect(150, 313, 140, 26)); //horizontal below fire ability
		gf2d_space_add_static_shape(space, gf2d_shape_rect(72, 155, 90, 26)); //small horizontal right top
		gf2d_space_add_static_shape(space, gf2d_shape_rect(133, 155, 26, 190)); //horizontal collider middle 
		gf2d_space_add_static_shape(space, gf2d_shape_rect(133, 205, 280, 26)); //highest vertical collider


		gf2d_space_add_static_shape(space, fireBall->hitbox);
		gf2d_space_add_static_shape(space, waterBall->hitbox);

		gf2d_space_add_static_shape(space, waterObs->hitbox);
		gf2d_space_add_static_shape(space, fireObs->hitbox);

	}

	//LEVEL TWO
	if (Level == 2) {
		enemy = newYEnemy(vector2d(290, 325), enemy);

		airBall = newAirpickup(vector2d(132, 150));
		gf2d_space_add_static_shape(space, airBall->hitbox);

		map = tilemap_load("levels/tilemap2.map");

		//Colliders
		gf2d_space_add_static_shape(space, gf2d_shape_rect(132, 180, 26, 26)); //small ones
		gf2d_space_add_static_shape(space, gf2d_shape_rect(520, 365, 26, 26));
		gf2d_space_add_static_shape(space, gf2d_shape_rect(620, 365, 26, 26));
		gf2d_space_add_static_shape(space, gf2d_shape_rect(327, 288, 26, 52));

		gf2d_space_add_static_shape(space, gf2d_shape_rect(70, 288, 90, 26)); //medium ones
		gf2d_space_add_static_shape(space, gf2d_shape_rect(150, 313, 140, 26));
		gf2d_space_add_static_shape(space, gf2d_shape_rect(0, 391, 230, 26));

	}

	//LEVEL THREE
	if (Level == 3) {
		enemy = newYEnemy(vector2d(1000,1000), enemy);
		earthBall = newEarthpickup(vector2d(132, 150));
		earthObs = newEarthObstacle(vector2d(280, 345));
		gf2d_space_add_static_shape(space, earthObs->hitbox);
		gf2d_space_add_static_shape(space, earthBall->hitbox);
		map = tilemap_load("levels/tilemap3.map");

		gf2d_space_add_static_shape(space, gf2d_shape_rect(3, 390, 650, 26));
	}

	////LEVEL FOUR
	if (Level == 4) {
		enemy = newYEnemy(vector2d(1000,1000), enemy);
		map = tilemap_load("levels/tilemap4.map");
	}

	gui_set_health(playerHealth); //set health here

	/*main game loop*/
	while (!done)
	{
		SDL_PumpEvents();   // update SDL's internal event structures
		keys = SDL_GetKeyboardState(NULL); // get the keyboard state for this frame
		/*update things here*/
		SDL_GetMouseState(&mx, &my);
		mf += 0.1;
		if (mf >= 16.0)mf = 0;

		//gf2d_particle_emitter_update(pe);
		//gf2d_particle_new_default(pe, 20);

		gf2d_graphics_clear_screen();// clears drawing buffers
		// all drawing should happen betweem clear_screen and next_frame
		//backgrounds drawn first
		gf2d_sprite_draw_image(sprite, vector2d(0, 0));

		drawAllEntities();
		player_update(player, space, fireObs, waterObs, earthObs, enemy, music, Level);
		y_enemy_update(enemy);
		tilemap_draw(map, vector2d(0, 0));

		spawn_pickup(vector2d(mx, my));

		//tilemap_draw_path(path, 2, map, vector2d(86, 24));
		gf2d_space_update(space);
		gui_draw_hud();
		gf2d_space_draw(space, vector2d(0, 0));
		//UI elements last
		gf2d_sprite_draw(
			mouse,
			vector2d(mx, my),
			NULL,
			NULL,
			NULL,
			NULL,
			&mouseColor,
			(int)mf);
		gf2d_grahics_next_frame();// render current draw frame and skip to the next frame

		if (keys[SDL_SCANCODE_ESCAPE])done = 1; // exit condition
		//slog("Rendering at %f FPS",gf2d_graphics_get_frames_per_second());

		if (keys[SDL_SCANCODE_B]) {
			save_file(&save, player, fireBall);
			slog("player position saved");
		}

		if (keys[SDL_SCANCODE_N]) {
			read_file(&save);
			load_file(&save, player, fireBall);
			slog("player position loaded");
		}

	}
	//gf2d_particle_emitter_free(pe);
	//Mix_HaltMusic();
	gf2d_space_free(space);
	slog("---==== END ====---");
	level(Level + 1);
	return 0;
}
/*eol@eof*/
