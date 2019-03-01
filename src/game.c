#include <SDL.h>
#include "gf2d_graphics.h"
#include "gf2d_sprite.h"
#include "simple_logger.h"
#include "entity.h"
#include "gf2d_vector.h"
#include "player.h"
#include "tiles.h"

int main(int argc, char * argv[])
{
    /*variable declarations*/
    int done = 0;
    const Uint8 * keys;
    Sprite *sprite;
	Entity *player;
	Entity *tiles;
    
    int mx,my;
    float mf = 0;
    Sprite *mouse;
    Vector4D mouseColor = {39,135,27,255};
    
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
    SDL_ShowCursor(SDL_DISABLE);
    
    /*demo setup*/
    sprite = gf2d_sprite_load_image("images/backgrounds/bg_forest.png");
    mouse = gf2d_sprite_load_all("images/pointer.png",32,32,16);
	player = newPlayer(vector2d(0, 0), player);
	tiles = newTile(vector2d(10, 10), tiles); //sets up tiles

	/*create entity(player)*/
	/*player = ent_new();
	if (!player) {
		slog("unable to draw player");
		return;
	}
	else {
		player->position = vector2d(200, 310);
		player->scale = vector2d(0.2, 20);
		player->sprite = gf2d_sprite_load_all("images/space_bug.png", 128, 128, 16); //if connected to mouse, add = mouse =
		player->current_frame = 0;
		player->frame_num = 16;
	}
	*/
    /*main game loop*/
    while(!done)
    {
        SDL_PumpEvents();   // update SDL's internal event structures
        keys = SDL_GetKeyboardState(NULL); // get the keyboard state for this frame
        /*update things here*/
        SDL_GetMouseState(&mx,&my);
        mf+=0.1;
        if (mf >= 16.0)mf = 0;
        
        
        gf2d_graphics_clear_screen();// clears drawing buffers
        // all drawing should happen betweem clear_screen and next_frame
            //backgrounds drawn first
            gf2d_sprite_draw_image(sprite,vector2d(0,0));
			drawEntity(player);
			drawEntity(tiles); //draws the tiles hopefully
			update(player);
            
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
        slog("Rendering at %f FPS",gf2d_graphics_get_frames_per_second());



    }
    slog("---==== END ====---");
    return 0;
}
/*eol@eof*/