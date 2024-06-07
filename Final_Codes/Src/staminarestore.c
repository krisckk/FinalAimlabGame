#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/events.h>
#include <allegro5/allegro.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Home.h"
#include "game.h"
#include "shared.h"
#include "utility.h"
#include "scene_menu.h"
#include "scene_settings.h"
#include "scene_menu_object.h"
#include "MainCharacter.h"
#include "staminarestore.h"
StaminarestoreScene* staminarestoreScene;
static Button Back;
static Button Restore;
static void Init(void){
	staminarestoreScene = (StaminarestoreScene*)malloc(sizeof(StaminarestoreScene));
    staminarestoreScene -> StaminarestoreThemsong = load_audio("Assets/Music/Time.ogg");
    staminarestoreScene -> background = load_bitmap("Assets/Images/staminarestorebackground.jpg");
	play_bgm(staminarestoreScene -> StaminarestoreThemsong, music_volume);
	Back = button_create(800, 1050, 200, 100, "Assets/Images/grayunhover.png", "Assets/Images/grayhover.png");
	Restore = button_create(600, 350, 600, 200, "Assets/Images/grayunhover.png", "Assets/Images/grayhover.png");
}
static void Update(void){
	Draw();
	if(Restore.clicked){
		if(stamina < 100.0)	stamina = stamina + 0.5;
		if(stamina == 100.0) Restore.clicked = false;
	}
}
static void Draw(void){
	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_draw_scaled_bitmap(staminarestoreScene -> background, 0, 0, 5824, 3624, 0, 0, SCREEN_W, SCREEN_H + 200, 0);
	al_draw_filled_rounded_rectangle(800, 1000 - 4 * stamina, 1000, 1000, 10, 10, al_map_rgb(0, 255, 0));
	al_draw_rounded_rectangle(800, 600, 1000, 1000, 10, 10, al_map_rgb(96, 96, 96), 10);
	al_draw_filled_rectangle(850, 565, 950, 600, al_map_rgb(96, 96, 96));
	drawButton(Back);
	drawButton(Restore);
	al_draw_text(PoetFont, al_map_rgb(255, 255, 255), 900, 1067, ALLEGRO_ALIGN_CENTER, "Back");
	al_draw_text(PoetFont, al_map_rgb(255, 255, 255), 900, 420, ALLEGRO_ALIGN_CENTER, "Restore");

}
static void Destroy(void){
	al_destroy_bitmap(staminarestoreScene -> background);
	al_destroy_sample(staminarestoreScene -> StaminarestoreThemsong);
}
static void On_mouse_move(int a, int mouse_x, int mouse_y, int f){
	Back.hovered = buttonHover(Back, mouse_x, mouse_y);
	Restore.hovered = buttonHover(Restore, mouse_x, mouse_y);
}
static void On_mouse_down(){
	if(Back.hovered){
		Back.clicked = true;
		Restore.clicked = false;
		game_log("you choose back");
		game_change_scene(scene_home_create());
	}
	else if(Restore.hovered){
		Back.clicked = false;
		Restore.clicked = true;
		game_log("Restore stamina");
	}
}
static void On_mouse_up(){
}
Scene scene_staminarestore_create(void){
    Scene scene;
	memset(&scene, 0, sizeof(Scene));
	scene.name = "Stamina Restore";
	scene.initialize = &Init;
    scene.update = &Update;
	scene.draw = &Draw;
    scene.destroy = &Destroy;
	scene.on_mouse_move = &On_mouse_move;
	scene.on_mouse_down = &On_mouse_down;
	scene.on_mouse_up = &On_mouse_up;
	game_log("Staminarestore scene created");
	return scene;
}