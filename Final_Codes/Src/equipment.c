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
#include "stageselect.h"
#include "equipment.h"
EquipmentScene *equipmentscene;

static void Init(void){
	equipmentscene = (EquipmentScene*)malloc(sizeof(EquipmentScene));
	equipmentscene -> background = load_bitmap("Assets/Images/equipmentbackground.jpg");
    equipmentscene -> sniper = load_bitmap("Assets/Images/Sniper.png");
	equipmentscene -> EquipmentThemsong = load_audio("Assets/Music/Time.ogg");
	play_bgm(equipmentscene -> EquipmentThemsong, music_volume);
}
static void Update(void){
    Draw();
}
static void Draw(void){
	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_draw_scaled_bitmap(equipmentscene -> background, 0, 0, 3740, 2493, 0, 0, SCREEN_W, SCREEN_H, 0);
    al_draw_scaled_bitmap(equipmentscene -> sniper, 0, 0, 2500, 2500, 650, 600, 500, 250, ALLEGRO_ALIGN_CENTER);
}
static void Destroy(void){
	al_destroy_bitmap(equipmentscene -> background);
	al_destroy_sample(equipmentscene -> EquipmentThemsong);
}

static void On_mouse_down(){

}
static void On_mouse_move(int a, int mouse_x, int mouse_y, int f){

}

Scene scene_equipment_create(void){
    Scene scene;
	memset(&scene, 0, sizeof(Scene));
	scene.name = "Equipment";
	scene.initialize = &Init;
    scene.update = &Update;
	scene.draw = &Draw;
    scene.destroy = &Destroy;
	scene.on_mouse_down = &On_mouse_down;
    scene.on_mouse_move = &On_mouse_move;
	game_log("Equipment scene created");
	return scene;
}