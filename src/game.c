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

int main(int argc, char * argv[]) //display fire and water abilities
{
    /*variable declarations*/
    int done = 0;
    const Uint8 * keys;
    Sprite *sprite;
	Sprite *gui;
	Entity *player;
	Entity *enemy;
	Entity *fireBall;
	Entity *waterBall;

	Entity *door; //level transition!

	Entity *fireObs;
	Entity *waterObs;

	TileMap *map;
	int collided = 0;
	int playerHealth = 20;

	ParticleEmitter *pe;

	Collision collision;
	Space *space = NULL;
	static Body body[10000];  // not a pointer!
	Shape shape[2];           // not a pointer!
    
    int mx,my,i;
    float mf = 0;
    Sprite *mouse;
    Vector4D mouseColor = {39,135,27,255};
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
        vector4d(0,0,0,255),
        0);
    gf2d_graphics_set_frame_delay(16);
    gf2d_sprite_init(1024);
	entityManagerInit(1024);

	gui_setup_hud();
    SDL_ShowCursor(SDL_DISABLE);
    
    /*demo setup*/
    sprite = gf2d_sprite_load_image("images/backgrounds/bg_forest.png");
   // mouse = gf2d_sprite_load_all("images/pointer.png",32,32,16);

	//player
	player = newPlayer(vector2d(0, 0), player);

	//enemy
	enemy = newYEnemy(vector2d(290, 325), enemy); 

	//door = newDoor(vector2d(300,100), door);

	fireObs = newFireObstacle(vector2d(413, 245)); 
	waterObs = newWaterObstacle(vector2d(33, 135)); 

	pe = gf2d_particle_emitter_new_full(
		500000,
		100,
		5,
		PT_Shape,
		vector2d(575, 340),
		vector2d(2, 2),
		vector2d(0, -3),
		vector2d(2, 1),
		vector2d(0, 0.05),
		vector2d(0, 0.01),
		gf2d_color(0.85, 0.55, 0, 1),
		gf2d_color(-0.01, -0.02, 0, 0),
		gf2d_color(0.1, 0.1, 0, 0.1),
		&shape,
		0,
		0,
		0,
		"images/earth_ball.png",
		32,
		32,
		1,
		0,
		//        SDL_BLENDMODE_BLEND);
		SDL_BLENDMODE_ADD);

	gf2d_space_add_body(space, player);

	//pick ups
	waterBall = newWaterpickup(vector2d(213, 175), waterBall); 
	fireBall = newFirepickup(vector2d(213, 275), fireBall); //minus 25y and 87x
	map = tilemap_load("levels/tilemap.map");
	gui_set_health(playerHealth);
	vector2d_copy(path[0],map->start);
	vector2d_copy(path[1],map->end);

	//collision stuff starts here

	space = gf2d_space_new_full(
		3,
		gf2d_rect(0, 0, 1200, 700),
		0.1,
		vector2d(0, 0.1),
		1,
		20);

	//shape[1] = gf2d_shape_circle(0, 0, 10);
	//shape[2] = gf2d_shape_circle(10, 0, 15);
	//shape[3] = gf2d_shape_rect(-32, -32, 64, 64);
	//shape[0] = gf2d_shape_rect(-16, -16, 32, 32);

	gf2d_space_add_static_shape(space, gf2d_shape_rect(3, 390, 600, 26)); //lowest collider //minus 25y and 87x
	gf2d_space_add_static_shape(space, gf2d_shape_rect(328, 175, 26, 190)); //horizontal collider 
	gf2d_space_add_static_shape(space, gf2d_shape_rect(5, 175, 26, 220)); //horizontal collider left 
	gf2d_space_add_static_shape(space, gf2d_shape_rect(5, 235, 90, 26)); //small horizontal left
	gf2d_space_add_static_shape(space, gf2d_shape_rect(133, 155, 26, 190)); //horizontal collider middle 
	gf2d_space_add_static_shape(space, gf2d_shape_rect(133, 205, 280, 26)); //highest vertical collider

	gf2d_space_add_static_shape(space, fireBall->hitbox);
	gf2d_space_add_static_shape(space, waterBall->hitbox);

	gf2d_space_add_static_shape(space, waterObs->hitbox);
	gf2d_space_add_static_shape(space, fireObs->hitbox);

	gf2d_space_add_static_shape(space, door->hitbox);

	//tiles = newTile(vector2d(10, 10), tiles); //sets up tiles

	



    /*main game loop*/
    while(!done)
    {
        SDL_PumpEvents();   // update SDL's internal event structures
        keys = SDL_GetKeyboardState(NULL); // get the keyboard state for this frame
        /*update things here*/
        SDL_GetMouseState(&mx,&my);
        mf+=0.1;
        if (mf >= 16.0)mf = 0;
        
		gf2d_particle_emitter_update(pe);
		gf2d_particle_new_default(pe, 20);
        
        gf2d_graphics_clear_screen();// clears drawing buffers
        // all drawing should happen betweem clear_screen and next_frame
            //backgrounds drawn first
            gf2d_sprite_draw_image(sprite,vector2d(0,0));

			gf2d_particle_emitter_draw(pe);

			drawEntity(player);
			drawEntity(enemy);
			drawEntity(fireBall);
			drawEntity(door);
			drawEntity(waterBall);
			drawEntity(waterObs);
			drawEntity(fireObs);
			player_update(player,space,fireObs,waterObs,door);
			y_enemy_update(enemy);
			tilemap_draw(map, vector2d(0, 0));
			//tilemap_draw_path(path, 2, map, vector2d(86, 24));
			gf2d_space_update(space);
			gui_draw_hud();
			gf2d_space_draw(space, vector2d(0, 0));
			//UI elements last
            gf2d_sprite_draw(
                mouse,
                vector2d(mx,my),
                NULL,
                NULL,
                NULL,
                NULL,
                &mouseColor,
                (int)mf);
        gf2d_grahics_next_frame();// render current draw frame and skip to the next frame
        
        if (keys[SDL_SCANCODE_ESCAPE])done = 1; // exit condition
        //slog("Rendering at %f FPS",gf2d_graphics_get_frames_per_second());



    }
	gf2d_particle_emitter_free(pe);
	gf2d_space_free(space);
	slog("---==== END ====---");
	//levelTwo();
	return 0;
}

int levelTwo() //display earth and air abilities
{
	/*variable declarations*/
	int done = 0;
	const Uint8 * keys;
	Sprite *sprite;
	Sprite *gui;
	Entity *player;
	Entity *enemy;
	TileMap *map;
	Entity *airBall;
	Entity *earthBall;
	Entity *earthObs;
	int playerHealth = 20;

	Collision collision;
	Space *space = NULL;
	static Body body[10000];// not a pointer!
	Shape shape[2];// not a pointer!

	int mx, my, i;
	float mf = 0;
	Sprite *mouse;
	Vector4D mouseColor = { 39, 135, 27, 255 };
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
	SDL_ShowCursor(SDL_DISABLE);

	gui_setup_hud();

	/*demo setup*/
	sprite = gf2d_sprite_load_image("images/backgrounds/bg_forest.png");
	// mouse = gf2d_sprite_load_all("images/pointer.png",32,32,16);
	player = newPlayer(vector2d(0, 0), player);
	enemy = newXEnemy(vector2d(370, 190), enemy);
	gf2d_space_add_body(space, player);

	earthBall = newEarthpickup(vector2d(300, 300), earthBall);
	airBall = newAirpickup(vector2d(300, 405), airBall);

	earthObs = newEarthObstacle(vector2d(118,335));

	map = tilemap_load("levels/tilemap2.map");
	vector2d_copy(path[0], map->start);
	vector2d_copy(path[1], map->end);

	//collision stuff starts here

	space = gf2d_space_new_full(
		3,
		gf2d_rect(0, 0, 1200, 700),
		0.1,
		vector2d(0, 0.1),
		1,
		20);

	//shape[1] = gf2d_shape_circle(0, 0, 10);
	//shape[2] = gf2d_shape_circle(10, 0, 15);
	//shape[3] = gf2d_shape_rect(-32, -32, 64, 64);
	//shape[0] = gf2d_shape_rect(-16, -16, 32, 32);

	gf2d_space_add_static_shape(space, gf2d_shape_rect(80, 440, 260, 30)); //lowest collider
	gf2d_space_add_static_shape(space, gf2d_shape_rect(220, 335, 155, 30)); //next to column collider
	gf2d_space_add_static_shape(space, gf2d_shape_rect(155, 410, 92, 28)); //second lowest collider
	gf2d_space_add_static_shape(space, gf2d_shape_rect(155, 180, 92, 28)); //higher 3 spot collider
	gf2d_space_add_static_shape(space, gf2d_shape_rect(415, 200, 26, 190)); //horizontal collider right side
	gf2d_space_add_static_shape(space, gf2d_shape_rect(93, 200, 26, 190)); //horizontal collider left side
	gf2d_space_add_static_shape(space, gf2d_shape_rect(500, 440, 150, 30)); //lowest collider right side
	gf2d_space_add_static_shape(space, earthBall->hitbox);
	gf2d_space_add_static_shape(space, airBall->hitbox);
	gf2d_space_add_static_shape(space, earthObs->hitbox);
	//tiles = newTile(vector2d(10, 10), tiles); //sets up tiles


	/*main game loop*/
	while (!done)
	{
		SDL_PumpEvents();   // update SDL's internal event structures
		keys = SDL_GetKeyboardState(NULL); // get the keyboard state for this frame
		/*update things here*/
		SDL_GetMouseState(&mx, &my);
		mf += 0.1;
		if (mf >= 16.0)mf = 0;

		gf2d_graphics_clear_screen();// clears drawing buffers
		// all drawing should happen betweem clear_screen and next_frame
		//backgrounds drawn first
		gf2d_sprite_draw_image(sprite, vector2d(0, 0));
		drawEntity(player);
		drawEntity(enemy);
		drawEntity(earthBall);
		drawEntity(airBall);
		drawEntity(earthObs);
		player_update(player, space, earthObs);
		x_enemy_update(enemy);
		gui_draw_hud();
		tilemap_draw(map, vector2d(86, 24));
		//tilemap_draw_path(path, 2, map, vector2d(86, 24));
		gf2d_space_update(space);

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



	}
	gf2d_space_free(space);
	slog("---==== END ====---");
	return 0;
}

/*eol@eof*/
