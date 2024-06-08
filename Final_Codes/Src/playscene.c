#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/events.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Home.h"
#include "game.h"
#include "shared.h"

#include "scene_menu.h"
#include "scene_settings.h"
#include "scene_menu_object.h"
#include "MainCharacter.h"
#include "playscene.h"
#include "stageselect.h"
#include "staminarestore.h"

PlayScene *playscene;
ALLEGRO_TIMER *playscene_timer;
static Button LEFT_BTN;
static Button MIDDLE_BTN;
static Button RIGHT_BTN;
extern bool key_pressed;
bool start_game = false;

static void Init(void){
	// stop time
	playscene_timer = al_create_timer(1.0f / 60);
	playscene = (PlayScene*)malloc(sizeof(PlayScene));
	key_pressed = false;
	start_game = false;
	LEFT_BTN = button_create(75, SCREEN_H / 2- 150, 400, 400, "Assets/Images/hitbox_unhover.png", "Assets/Images/hitbox_hoverd.png");
	MIDDLE_BTN = button_create(75 + 400, SCREEN_H / 2- 150, 400, 400, "Assets/Images/hitbox_unhover.png", "Assets/Images/hitbox_hoverd.png");
	RIGHT_BTN = button_create(75 + 800, SCREEN_H / 2- 150, 400, 400, "Assets/Images/hitbox_unhover.png", "Assets/Images/hitbox_hoverd.png");
}
static void Update(void){
	Draw();
}

static void Draw(void){
	
	if(start_game == false){
		al_clear_to_color(al_map_rgb(0, 0, 0));
		al_draw_text(minecraftFont, al_map_rgb(255, 255, 255), SCREEN_W/2, SCREEN_H/2 -50, ALLEGRO_ALIGN_CENTER, "Press ENTER to start");
	}
	else{
		// information block at the right side of the screen
		al_draw_filled_rectangle(SCREEN_W - 450, 0, SCREEN_W, SCREEN_H, al_map_rgb(100, 100, 100));
		// text
		al_draw_textf(PoetFont, al_map_rgb(255, 255, 255), SCREEN_W - 225, 50, ALLEGRO_ALIGN_CENTER, "Stage   %d", stage_id);
		al_draw_textf(PoetFont, al_map_rgb(255, 255, 255), SCREEN_W - 225, 1075, ALLEGRO_ALIGN_CENTER, "Stamina   %.1f", stamina);
		
		// draw song name
		if(stage_id == 1) al_draw_text(PoetFont, al_map_rgb(255, 255, 255), SCREEN_W - 225, 125, ALLEGRO_ALIGN_CENTER, "Unstoppable - Sia");

		// draw hitboxes
		drawButton(LEFT_BTN);
		drawButton(MIDDLE_BTN);
		drawButton(RIGHT_BTN);
	}
	
}

static void Destroy(void){
	//free(playscene);
}

static void On_key_down(int keycode){
	if(!key_pressed && keycode == ALLEGRO_KEY_ENTER){
		game_log("Enter key pressed");
		al_start_timer(playscene_timer);
		key_pressed = true;
	}
}

static void On_key_up(int keycode){
	if(keycode == ALLEGRO_KEY_ENTER){
		game_log("Enter key released");
		start_game = true;
	}
}

static void Draw_hitboxes(int id){

}

static void hitboxes_setup(void){

}

Scene scene_playscene_create(int stage){
	Scene scene;
	memset(&scene, 0, sizeof(Scene));
	scene.name = "Play";
	scene.initialize = &Init;
	scene.update = &Update;
	scene.draw = &Draw;
	scene.destroy = &Destroy;
	scene.on_key_down = &On_key_down;
	scene.on_key_up = &On_key_up;
	game_log("Play scene created");
	stage_id = stage;
	return scene;
}
