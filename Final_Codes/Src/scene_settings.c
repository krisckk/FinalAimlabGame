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
static Button Back;
static void Init(void){
	Back = button_create(800, 1050, 200, 100, "Assets/Images/grayunhover.png", "Assets/Images/grayhover.png");
}
static void Update(void){
	Draw();
}
static void Draw(void){
	al_clear_to_color(al_map_rgb(0, 0, 0));
	drawButton(Back);
	al_draw_text(PoetFont, al_map_rgb(255, 255, 255), 900, 1067, ALLEGRO_ALIGN_CENTER, "Back");
}
static void Destroy(void){
}
static void On_mouse_move(int a, int mouse_x, int mouse_y, int f){
	Back.hovered = buttonHover(Back, mouse_x, mouse_y);
}
static void On_mouse_down(){
	if(Back.hovered){
		Back.clicked = true;
		game_log("you choose back");
		game_change_scene(scene_menu_create());
	}
}
static void On_mouse_up(){
}
Scene scene_settings_create(void){
    Scene scene;
	memset(&scene, 0, sizeof(Scene));
	scene.name = "Settings";
	scene.initialize = &Init;
    scene.update = &Update;
	scene.draw = &Draw;
    scene.destroy = &Destroy;
	scene.on_mouse_move = &On_mouse_move;
	scene.on_mouse_down = &On_mouse_down;
	scene.on_mouse_up = &On_mouse_up;
	game_log("Settings scene created");
	return scene;
}