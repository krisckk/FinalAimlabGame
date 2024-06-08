#ifndef SCENE_SETTINGS_H
#define SCENE_SETTINGS_H
#include "game.h"
#include "shared.h"
#include "scene_menu.h"
typedef struct _Setting{
  ALLEGRO_BITMAP *settingsBackground;
  ALLEGRO_SAMPLE_INSTANCE *settingsThemesong;
} Setting;
Scene scene_settings_create(void);
extern double stamina;
static void Init(void);
static void Update(void);
static void Draw(void);
static void Destroy(void);
static void On_mouse_move(int a, int mouse_x, int mouse_y, int f);
static void On_mouse_down();
static void On_mouse_up();
static void On_mouse_scroll(int a, int mouse_x, int mouse_y, int mouse_dz);
#endif
