#ifndef EQUIPMENT_H
#define EQUIPMENT_H
#include "game.h"
#include "Home.h"
typedef struct _EquipmentScene
{
    ALLEGRO_BITMAP *background;
    ALLEGRO_SAMPLE *EquipmentThemsong;
    ALLEGRO_BITMAP *sniper;
} EquipmentScene;
Scene scene_equipment_create(void);
static void Init(void);
static void Update(void);
static void Draw(void);
static void Destroy(void);
static void On_mouse_down();
static void On_mouse_move(int a, int mouse_x, int mouse_y, int f);
#endif