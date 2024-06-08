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
static Button Back;

static void Init(void){
	equipmentscene = (EquipmentScene*)malloc(sizeof(EquipmentScene));
	equipmentscene -> background = load_bitmap("Assets/Images/equipmentbackground.jpg");
    equipmentscene -> sniper = load_bitmap("Assets/Images/Sniper.png");
    equipmentscene -> armor = load_bitmap("Assets/Images/armor.png");
    equipmentscene -> staff = load_bitmap("Assets/Images/cannon.png");
    equipmentscene -> armorstand = load_bitmap("Assets/Images/armorstand.png");
    equipmentscene -> woodentable = load_bitmap("Assets/Images/woodtable.png");
	equipmentscene -> EquipmentThemsong = load_audio("Assets/Music/Time.ogg");
    equipmentscene -> wallshelf = load_bitmap("Assets/Images/wallshelf.png");
    equipmentscene -> gunrack = load_bitmap("Assets/Images/gunrack.png");
    equipmentscene -> gunrack2 = load_bitmap("Assets/Images/gunrack.png");
	play_bgm(equipmentscene -> EquipmentThemsong, music_volume);
    Back = button_create(800, 1080, 200, 100, "Assets/Images/grayunhover.png", "Assets/Images/grayhover.png");
}
static void Update(void){
    Draw();
}
static void Draw(void){
	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_draw_scaled_bitmap(equipmentscene -> background, 0, 0, 3740, 2493, 0, 0, SCREEN_W, SCREEN_H, 0);
    al_draw_scaled_bitmap(equipmentscene -> wallshelf, 0, 0, 2000, 2000, 1250, 750, 500, 900, 0);
    al_draw_scaled_bitmap(equipmentscene -> gunrack, 0, 0, 2500, 2500, 780, 690, 200, 850, 0);
    al_draw_scaled_bitmap(equipmentscene -> gunrack2, 0, 0, 2500, 2500, 950, 690, 200, 850, 0);
    al_draw_scaled_bitmap(equipmentscene -> sniper, 0, 0, 2500, 2500, 650, 600, 500, 250, ALLEGRO_ALIGN_CENTER);
    al_draw_scaled_bitmap(equipmentscene -> armorstand, 0, 0, 2000, 2000, 265, 500, 1000, 1100, 0);
    al_draw_scaled_bitmap(equipmentscene -> armor, 0, 0, 2000, 2000, 200, 550, 1000, 1100, 0);
    al_draw_scaled_bitmap(equipmentscene -> staff, 0, 0, 2000, 2000, 1350, 600, 800, 800, 0);
    drawButton(Back);
    al_draw_text(PoetFont, al_map_rgb(255, 255, 255), 900, 1067, ALLEGRO_ALIGN_CENTER, "Back");

}
static void Destroy(void){
	al_destroy_bitmap(equipmentscene -> background);
	al_destroy_sample(equipmentscene -> EquipmentThemsong);
}

static void On_mouse_down(){
    if(Back.hovered){
        Back.clicked = true;
        game_log("you choose back");
        game_change_scene(scene_home_create());
    }
}
static void On_mouse_move(int a, int mouse_x, int mouse_y, int f){
    Back.hovered = buttonHover(Back, mouse_x, mouse_y);
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