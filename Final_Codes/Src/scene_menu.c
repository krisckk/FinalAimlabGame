#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_native_dialog.h>
#include <math.h>
#include "Home.h"
#include "scene_menu_object.h"
#include "scene_settings.h"
#include "scene_menu.h"
#include "utility.h"
#include "shared.h"

/* Internal Variables*/
static ALLEGRO_BITMAP* Menubackground = NULL;
static ALLEGRO_BITMAP* AimlabIcon = NULL;
static ALLEGRO_BITMAP* Audacity = NULL;
static ALLEGRO_SAMPLE* menuBGM;

// [HACKATHON 3]
// TARGET : use a clickable button to enter setting scene.
// For `Button` struct(object) is defined in `scene_menu_object.h` and `scene_menu_object.c`
// STRONGLY recommend you trace both of them first. 

// TODO-HACKATHON 3-1: Declare variable for button
// Uncomment and fill the code below
static Button btnSettings;

static void init() {

	// TODO-HACKATHON 3-2: Create button to settings
	// Uncomment and fill the code below
	btnSettings = button_create(SCREEN_W - 70, 20, 50, 50, "Assets/settings.png", "Assets/settings2.png");
	Menubackground = load_bitmap("Assets/Images/Menubackground.jpg");
	AimlabIcon = load_bitmap("Assets/Images/Aimlab.png");
	Audacity = load_bitmap("Assets/Images/Audacity.png");
	menuBGM = load_audio("Assets/Music/LisanAlGaib.ogg");
	play_bgm(menuBGM, music_volume);
}


static void draw() 
{

	al_clear_to_color(al_map_rgb(0, 0, 0));
	int halfW = SCREEN_W / 2;
	int halfH = SCREEN_H / 2;
	//draw title image
	al_draw_scaled_bitmap(
		Menubackground,
		0, 0,
		3000, 2000,
		0, 0,
		SCREEN_W, SCREEN_H,
		0
	);
	al_draw_scaled_bitmap(AimlabIcon, 0, 0, 64, 64, halfW - 600, halfH - 100, 240, 240, 0);
    al_draw_scaled_bitmap(Audacity, 0, 0, 64, 64, halfW + 360, halfH - 100, 240, 240, 0);
    al_draw_text(darkknightFont, al_map_rgb(255, 255, 255), halfW - 175, halfH - 100, 0, "AIM LAB MUSIC");
    al_draw_text(minecraftFont, al_map_rgb(255, 255, 255), halfW - 275, halfH + 50, 0, "Press ENTER to start");

	// TODO-HACKATHON 3-3: Draw button
	// Uncomment and fill the code below
	drawButton(btnSettings);

}

static void on_mouse_move(int a, int mouse_x, int mouse_y, int f) {
	//	TODO-HACKATHON 3-7: Update button's status(hovered), and utilize the function `pnt_in_rect`, which you just implemented
	//	Uncomment and fill the code below
	btnSettings.hovered = buttonHover(btnSettings, mouse_x, mouse_y);
}


//	TODO-HACKATHON 3-8: When btnSettings clicked, switch to settings scene
//  `game_change_scene` is defined in `game.h`.
//  You can check line 121 `scene_menu.c` to see how to use this function.
//  And find the corresponding function for `scene_setting`
// 	Utilize the member defined in struct `Button`.
//  The logic here is 
//  `if clicked the mouse` && `mouse position is in the area of button`
// 	      `Enter the setting scene`
//	Uncomment and fill the code below
static void on_mouse_down() {
	if (btnSettings.hovered)
		game_change_scene(scene_settings_create());
}


static void destroy() {
	al_destroy_bitmap(Menubackground);
	al_destroy_bitmap(AimlabIcon);
	al_destroy_bitmap(Audacity);
	//	TODO-HACKATHON 3-10: Destroy button images
	//	Uncomment and fill the code below
	al_destroy_sample(menuBGM);
	al_destroy_bitmap(btnSettings.hovered_img);
	al_destroy_bitmap(btnSettings.default_img);
	
}

static void on_key_down(int keycode) {

	switch (keycode) {
		case ALLEGRO_KEY_ENTER:
			game_change_scene(scene_home_create());
			break;
		default:
			break;
	}
}

// TODO-IF: Add more event callback functions such as update, ...

// Functions without 'static', 'extern' prefixes is just a normal
// function, they can be accessed by other files using 'extern'.
// Define your normal function prototypes below.

// The only function that is shared across files.
Scene scene_menu_create(void) {

	Scene scene;
	memset(&scene, 0, sizeof(Scene));
	scene.name = "Menu";
	scene.initialize = &init;
	scene.draw = &draw;
	scene.destroy = &destroy;
	scene.on_key_down = &on_key_down;
	scene.on_mouse_move = &on_mouse_move;
	scene.on_mouse_down = &on_mouse_down;
	
	// -------------------------------------



	// TODO-IF: Register more event callback functions such as keyboard, mouse, ...
	game_log("Menu scene created");
	return scene;
}