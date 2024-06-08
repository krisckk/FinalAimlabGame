#ifndef _PLAYSCENE_H_
#define _PLAYSCENE_H_
#include "game.h"
#include "utility.h"
#include "time.h"

//stage id 
int stage_id;

typedef struct _PlayScene
{
	ALLEGRO_BITMAP *background;
	ALLEGRO_SAMPLE *PlaysceneThemsong;
	double hitbox_x[1];
	double hitbox_y[1];
	int score;
	int combo;
} PlayScene;

Scene scene_playscene_create(int stage);

static void Init(void);
static void Update(void);
static void Draw(void);
static void Destroy(void);
static void On_mouse_move(int a, int mouse_x, int mouse_y, int f);
static void On_mouse_down();
static void On_mouse_up();
static void On_key_down(int keycode);
static void On_key_up(int keycode);
static void Draw_hitboxes(int id);
static void hitboxes_setup(void);
#endif