#ifndef SCOREBOARD_SCENE_H
#define SCOREBOARD_SCENE_H
#include "game.h"
#include "allegro5/allegro_audio.h"

typedef struct _ScoreboardScene
{
    ALLEGRO_BITMAP *background;
    ALLEGRO_SAMPLE *Themesong;

} ScoreboardScene;
Scene scene_scoreboard_create(void);
static void Init(void);
//static void StatusUpdate(void);
static void Update(void);
static void Draw(void);
static void Destroy(void);
static void On_key_down(int key_code);
static void On_key_up(int key_code);
static void On_mouse_move(int a, int mouse_x, int mouse_y, int f);
static void On_mouse_down();
static void On_mouse_up();
void read_scoreboard(int stage);
void reset();
void sort();
#endif