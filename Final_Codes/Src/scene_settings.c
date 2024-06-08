#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/events.h>
#include <allegro5/allegro.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
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
Setting *setting;
static ALLEGRO_SAMPLE_INSTANCE* settingsThemesongInstance = NULL;

static void Init(void){
	setting = (Setting*)malloc(sizeof(Setting));
	setting -> settingsBackground = load_bitmap("Assets/Images/settingsbackground.jpg");
	setting -> settingsThemesong = load_audio("Assets/Music/HonorHim.ogg");
	settingsThemesongInstance = al_create_sample_instance(setting->settingsThemesong);
    al_set_sample_instance_gain(settingsThemesongInstance, music_volume);
    al_attach_sample_instance_to_mixer(settingsThemesongInstance, al_get_default_mixer());
    al_play_sample_instance(settingsThemesongInstance);
	Back = button_create(800, 970, 200, 100, "Assets/Images/grayunhover.png", "Assets/Images/grayhover.png");
}
static void Update(void){
	Draw();
}
static void Draw(void) {
    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_draw_scaled_bitmap(setting->settingsBackground, 0, 0, 1328, 746, 0, 0, SCREEN_W, SCREEN_H + 200, 0);
    drawButton(Back);
    char staminachar[32]; // Increase the buffer size to a reasonable value
    snprintf(staminachar, sizeof(staminachar), "%.1f", stamina); // Use snprintf to safely convert stamina to a string
    al_draw_text(PoetFont, al_map_rgb(255, 255, 255), 650, 450, ALLEGRO_ALIGN_CENTER, "Stamina :");
	al_draw_text(PoetFont, al_map_rgb(255, 255, 255), 640, 740, ALLEGRO_ALIGN_CENTER, "Music Volume :");
	// Draw the circle outline
    al_draw_circle(1150, 760, 120, al_map_rgb(247, 36, 36), 10.0);
    // Calculate the radius of the filled circle based on the music_volume
    float radius = (music_volume / 0.5) * 60;
	float percentage = (music_volume);
	char percentagechar[32];
	snprintf(percentagechar, sizeof(percentagechar), "%.1f", percentage);
    // Draw the filled circle
    al_draw_filled_circle(1150, 760, radius, al_map_rgb(101, 5, 5));
	al_draw_text(PoetFont, al_map_rgb(255,255, 255), 1150, 740, ALLEGRO_ALIGN_CENTER, percentagechar);

	al_draw_text(PoetFont, al_map_rgb(255, 255, 255), 1150, 450, ALLEGRO_ALIGN_CENTER, staminachar);
    al_draw_text(PoetFont, al_map_rgb(255, 255, 255), 900, 992, ALLEGRO_ALIGN_CENTER, "Back");
}
static void Destroy(void) {
    if (settingsThemesongInstance) {
        al_stop_sample_instance(settingsThemesongInstance);
        al_destroy_sample_instance(settingsThemesongInstance);
        settingsThemesongInstance = NULL;
    }
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
static void On_mouse_scroll(int a, int mouse_x, int mouse_y, int mouse_dz) {
    if (settingsThemesongInstance) {
        al_stop_sample_instance(settingsThemesongInstance);
        al_destroy_sample_instance(settingsThemesongInstance);
        settingsThemesongInstance = NULL;
    }

    // Adjust the music_volume based on the mouse scroll direction
    if (mouse_dz > 0) {
        // Scroll up, increase the volume
        music_volume = fminf(music_volume + 0.1f, 1.0f); // Limit the maximum volume to 1.0
    } else if (mouse_dz < 0) {
        // Scroll down, decrease the volume
        music_volume = fmaxf(music_volume - 0.1f, 0.0f); // Limit the minimum volume to 0.0
    }

    // Create a new audio instance with the updated volume
    settingsThemesongInstance = al_create_sample_instance(setting->settingsThemesong);
    al_set_sample_instance_gain(settingsThemesongInstance, music_volume);
    al_attach_sample_instance_to_mixer(settingsThemesongInstance, al_get_default_mixer());
    al_play_sample_instance(settingsThemesongInstance);
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
	scene.on_mouse_scroll = &On_mouse_scroll;
	game_log("Settings scene created");
	return scene;
}