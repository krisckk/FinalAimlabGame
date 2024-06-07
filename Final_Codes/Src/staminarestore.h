#ifndef STAMINARESTORE_H
#define STAMINARESTORE_H
#include "game.h"
typedef struct _StaminarestoreScene
{
    ALLEGRO_BITMAP *background;
    ALLEGRO_SAMPLE *StaminarestoreThemsong;
    int slidervalue;
} StaminarestoreScene;
Scene scene_staminarestore_create(void);
extern Maincharacter *MC;
extern double stamina;
static void Init(void);
static void Update(void);
static void Draw(void);
static void Destroy(void);
static void On_mouse_move(int a, int mouse_x, int mouse_y, int f);
static void On_mouse_down();
static void On_mouse_up();
#endif