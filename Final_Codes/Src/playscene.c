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
#include "winscene.h"
PlayScene *playscene;
ALLEGRO_TIMER* timercount;
ALLEGRO_TIMER* timer_countdown;
static ALLEGRO_SAMPLE_INSTANCE* SongInstance;
ALLEGRO_TIMER* button_update_timer = NULL;
double button_update_time = 0.0;
bool start = false;
Button LEFT_BTN;
extern bool key_pressed;
extern uint32_t GAME_TICK_CD;
bool start_game = false;
// define eunum
enum {
	LEFTB,
};

static void Init(void){
	// stop time
	//playscene_timer = al_create_timer(1.0f / 60);
	srandom(time(NULL));
	playscene = (PlayScene*)malloc(sizeof(PlayScene));
	playscene -> background = load_bitmap("Assets/Images/play_background2.jpg");
	playscene -> oneTofivepicture = load_bitmap("Assets/Images/1-5.png");
	playscene -> sixToninepicture = load_bitmap("Assets/Images/6-9.png");
	playscene -> tenpicture = load_bitmap("Assets/Images/10.png");
	playscene -> score = 0;
	playscene -> combo = 0;
	playscene -> currentcombo = 0;
	playscene -> clickedTime = 0;
	playscene -> combometer = 0;
	playscene -> highestcombo = 0;
	key_pressed = false;
	start_game = false;
	int dx = (int)random() % 1100;
	int dy = (int)random() % 500;
	if(stage_id == 1) LEFT_BTN = button_create(75 + dx, dy + SCREEN_H / 2- 150, 280, 280, "Assets/Images/hitbox_unhover.png", "Assets/Images/hitbox_hoverd.png");
	else if(stage_id == 2) LEFT_BTN = button_create(75 + dx, dy + SCREEN_H / 2 - 150, 140, 140, "Assets/Images/hitbox_unhover.png", "Assets/Images/hitbox_hoverd.png");
	else LEFT_BTN = button_create(75 + dx, dy + SCREEN_H / 2 - 150, 100, 100, "Assets/Images/hitbox_unhover.png", "Assets/Images/hitbox_hoverd.png");
	if(stage_id == 1) playscene -> PlaysceneThemsong = load_audio("Assets/Music/Unstoppable.wav");
	else if(stage_id == 2) playscene -> PlaysceneThemsong = load_audio("Assets/Music/DanceMonkey.ogg");
	else if(stage_id == 3) playscene -> PlaysceneThemsong = load_audio("Assets/Music/Voissurtonchemin.ogg");
	playscene -> Hitsound = load_audio("Assets/Music/Hitsound.ogg");
	SongInstance = al_create_sample_instance(playscene -> PlaysceneThemsong);
	al_set_sample_instance_gain(SongInstance, music_volume);
	al_attach_sample_instance_to_mixer(SongInstance, al_get_default_mixer());
	button_update_timer = al_create_timer(1.0f); // 60 FPS
    al_start_timer(button_update_timer);
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
		al_draw_scaled_bitmap(playscene -> background, 0, 0, 5020, 2824, 0, 0, SCREEN_W - 450, SCREEN_H, 0);
		al_draw_filled_rectangle(SCREEN_W - 450, 0, SCREEN_W, SCREEN_H, al_map_rgb(100, 100, 100));
		// text
		al_draw_textf(PoetFont, al_map_rgb(255, 255, 255), SCREEN_W - 225, 50, ALLEGRO_ALIGN_CENTER, "Stage   %d", stage_id);
		al_draw_textf(PoetFont, al_map_rgb(255, 255, 255), SCREEN_W - 225, 1075, ALLEGRO_ALIGN_CENTER, "Stamina   %.1f", stamina);
		 // draw score
  		al_draw_text(PoetFont, al_map_rgb(255, 255, 255), SCREEN_W - 350, 270, ALLEGRO_ALIGN_LEFT, "Score");
  		al_draw_textf(PoetFont, al_map_rgb(255, 255, 255), SCREEN_W - 125, 270, ALLEGRO_ALIGN_CENTER, "%d", playscene -> score);
		// draw song name
		if(stage_id == 1) al_draw_text(PoetFont, al_map_rgb(255, 255, 255), SCREEN_W - 225, 125, ALLEGRO_ALIGN_CENTER, "Unstoppable - Sia");
		else if(stage_id == 2) al_draw_multiline_text(PoetFont, al_map_rgb(255, 255, 255), SCREEN_W - 225, 125, 350, 50,ALLEGRO_ALIGN_CENTER, "Dance Monkey - Tones and I");
		else if(stage_id == 3) al_draw_multiline_text(PoetFont, al_map_rgb(255, 255, 255), SCREEN_W - 225, 125, 350, 50,ALLEGRO_ALIGN_CENTER, "Vois sur ton chemen - BENNET");
		// draw combometer
		al_draw_text(PoetFont, al_map_rgb(255, 255, 255), SCREEN_W - 225, 325, ALLEGRO_ALIGN_CENTER, "Combo");
		al_draw_textf(PoetFontEdit, al_map_rgb(255, 255, 255), 1590, 600, ALLEGRO_ALIGN_CENTER, "%d", playscene -> combometer);
		if(playscene -> combometer >= 1 && playscene -> combometer < 6){
			al_draw_scaled_bitmap(playscene -> oneTofivepicture, 0, 0, 2000, 2000, 1415, 475, 350, 400, 0);
		}
		else if(playscene -> combometer >= 6 && playscene -> combometer <= 9){
			al_draw_scaled_bitmap(playscene -> sixToninepicture, 0, 0, 3541, 3542, 1415, 475, 350, 400, 0);
		}
		else if(playscene -> combometer == 10){
			al_draw_scaled_bitmap(playscene -> tenpicture, 0, 0, 3168, 3946, 1415, 500, 350, 420, 0);
		}
		
		if(al_get_timer_count(timer_countdown) < 3){
			int countdown = 3 - al_get_timer_count(timer_countdown);
			al_draw_textf(PoetFont, al_map_rgb(255, 255, 255),  700, 600, ALLEGRO_ALIGN_CENTER, "COUNTDOWN %d !!!!", countdown);
			// after countdown start hitbox timer
			
		}
		else if(al_get_timer_count(timer_countdown) == 3){
			timercount = al_create_timer(1.0f);
			start = true;
			al_start_timer(timercount);
			al_play_sample_instance(SongInstance);
		}
		else {
			al_stop_timer(timer_countdown);
		}

		if(start && al_get_timer_count(timercount) >= 1){
			if(al_get_timer_count(timercount) >= 210){
				al_stop_timer(timercount);
				game_change_scene(winscene_create());
			}
			if (start && al_get_timer_count(timercount) >= 1) {
			// Check if it's time to update the button position
				if (al_get_timer_count(button_update_timer) - button_update_time >= 1.0) {
					game_log("button update");
					button_update_time = al_get_timer_count(button_update_timer);
					Button_update(&LEFT_BTN);
					if(playscene -> clickedTime < al_get_timer_count(timercount) - 1){
						playscene -> clickedTime = al_get_timer_count(timercount) - 1;
						playscene -> combometer = 0;
						if(playscene -> currentcombo > playscene -> highestcombo){
							playscene -> highestcombo = playscene -> currentcombo;
							playscene -> currentcombo = 0;
							game_log("New Highest Combo: %d", playscene -> highestcombo);
						}
					}
				}
        		// Draw the button
        		if(!LEFT_BTN.clicked)	{
					
						drawButton(LEFT_BTN);
						al_stop_samples();
					}

				}
    	}
	}
}


static void Destroy(void){
	//free(playscene);
	al_destroy_timer(timercount);
	al_destroy_timer(button_update_timer);
	al_stop_sample_instance(SongInstance);
	al_destroy_sample_instance(SongInstance);
	al_destroy_sample(playscene -> Hitsound);
}

static void On_mouse_down(){
	if(LEFT_BTN.hovered){
		LEFT_BTN.clicked = true;
		if (playscene -> combometer < 10) playscene -> combometer++;
		playscene -> score += 10 + 1 * playscene -> combometer;
		playscene -> combo++;
		playscene -> currentcombo++;
		game_log("CurrentCombo: %d", playscene -> currentcombo);
		game_log("Score: %d", playscene -> score);
		game_log("Combo: %d", playscene -> combo);
		playscene -> clickedTime++;
		play_audio(playscene -> Hitsound, music_volume - 0.3);
	}
}

static void On_mouse_move(int a, int mouse_x, int mouse_y, int f){
	LEFT_BTN.hovered = buttonHover(LEFT_BTN, mouse_x, mouse_y);
}

static void On_key_down(int keycode){
	if(!key_pressed && keycode == ALLEGRO_KEY_ENTER){
		game_log("Enter key pressed");
		key_pressed = true;
		timer_countdown = al_create_timer(1.0f);
		al_start_timer(timer_countdown);
		// timercount = al_create_timer(1.0f);
		// al_start_timer(timercount);
	}
	if(keycode == ALLEGRO_KEY_T){
		game_log("T key pressed, cheat mode to winscene");
		al_stop_timer(timercount);
		game_change_scene(winscene_create());
	}
	else if(keycode == ALLEGRO_KEY_P){
		game_log("P key pressed, add 100 points");
		playscene -> score += 100;
	}
}

static void On_key_up(int keycode){
	if(keycode == ALLEGRO_KEY_ENTER){
		game_log("Enter key released");
		start_game = true;
	}
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
	scene.on_mouse_move = &On_mouse_move;
	scene.on_mouse_down = &On_mouse_down;
	game_log("Play scene created");
	stage_id = stage;
	return scene;
}
