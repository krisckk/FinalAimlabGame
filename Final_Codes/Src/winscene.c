#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_native_dialog.h>
#include <math.h>
#include "Home.h"
#include "scene_menu_object.h"
#include "scene_settings.h"
#include "scene_menu.h"
#include "utility.h"
#include "shared.h"
#include "winscene.h"
#include "stageselect.h"
#include "playscene.h"
#include "time.h"
extern PlayScene *playscene;
static ALLEGRO_BITMAP* Winbackground = NULL;
static Button Back;
static Button Stageselect;
static Button Name;
char name[20];
int keyhere = 0;
const char *c;
bool enter_name = false;


static void init() {
    int halfW = SCREEN_W / 2;
    int halfH = SCREEN_H / 2;
    Winbackground = load_bitmap("Assets/Images/play_background.jpg");
    Back = button_create(600, 850, 200, 100, "Assets/Images/grayunhover.png", "Assets/Images/grayhover.png");
    Stageselect = button_create(950, 850, 300, 100, "Assets/Images/grayunhover.png", "Assets/Images/grayhover.png");
    Name = button_create(halfW + 20 , halfH + 40 , 500, 100, "Assets/Images/grayunhover.png", "Assets/Images/grayhover.png");
    memset(name, 0, sizeof(name));
}

void save_data_to_file(const char *filename, const char *name, int combo, time_t current_time){
    FILE *file = fopen(filename, "a");
    if (file == NULL) {
        printf("Error opening file %s\n", filename);
        return;
    }
    char time_str[26];
    struct tm *localTime = localtime(&current_time);
    strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", localTime);
    fprintf(file, "%s %d %d %d %s\n", name, playscene -> score, playscene -> combo, playscene -> highestcombo, time_str);
    fclose(file);
    game_log("Data saved to file: %s", filename);
}


static void draw()
{
    int halfW = SCREEN_W / 2;
    int halfH = SCREEN_H / 2;
    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_draw_scaled_bitmap(Winbackground,0, 0,5539, 3116, 0, 0, SCREEN_W, SCREEN_H, 0);

    al_draw_text(PoetFont, al_map_rgb(255, 255, 255), halfW - 40, halfH - 100, ALLEGRO_ALIGN_RIGHT, "SCORE: ");
    al_draw_text(PoetFont, al_map_rgb(255, 255, 255), halfW - 40, halfH - 20, ALLEGRO_ALIGN_RIGHT, "COMBO: ");
    al_draw_text(PoetFont, al_map_rgb(255, 255, 255), halfW - 40, halfH + 60, ALLEGRO_ALIGN_RIGHT, "ENTER YOUR NAME: ");
    al_draw_textf(PoetFont, al_map_rgb(255, 255, 255), halfW + 40, halfH - 100, ALLEGRO_ALIGN_LEFT, "%d", playscene -> score);
    al_draw_textf(PoetFont, al_map_rgb(255, 255, 255), halfW + 40, halfH - 20, ALLEGRO_ALIGN_LEFT, "%d", playscene -> combo);

    drawButton(Back);
    drawButton(Stageselect);
    drawButton(Name);

    al_draw_text(PoetFont, al_map_rgb(255, 255, 255), 650, 865, 0, "Back");
    al_draw_text(PoetFont, al_map_rgb(255, 255, 255), 980, 865, 0, "Stageselect");

    al_draw_textf(PoetFont, al_map_rgb(255, 255, 255), halfW + 60 , halfH + 60 , ALLEGRO_ALIGN_LEFT, "%s", name);



}

static void on_mouse_move(int a, int mouse_x, int mouse_y, int f) {
    Back.hovered = buttonHover(Back, mouse_x, mouse_y);
    Stageselect.hovered = buttonHover(Stageselect, mouse_x, mouse_y);
    Name.hovered = buttonHover(Name, mouse_x, mouse_y);
}

static void on_mouse_down() {
    if(Back.hovered){
        Back.clicked = true;
        game_log("back to home");
        if (stage_id == 1) save_data_to_file("Stage1scoreboard.txt", name, playscene->combo, time(NULL)); // Save data before changing scene
        game_change_scene(scene_home_create());
    }

    if(Stageselect.hovered){
        Stageselect.clicked = true;
        game_log("back to stage");
        if (stage_id == 1) save_data_to_file("Stage1scoreboard.txt", name, playscene->combo, time(NULL)); // Save data before changing scene
        else if(stage_id == 2) save_data_to_file("Stage2scoreboard.txt", name, playscene->combo, time(NULL));
        else if(stage_id == 3) save_data_to_file("Stage3scoreboard.txt", name, playscene->combo, time(NULL));
        game_change_scene(scene_stageselect_create());
    }

    if(Name.hovered){
        Name.clicked = !Name.clicked;
        enter_name = !enter_name;
        if (enter_name) game_log("start entering name");
        if (!enter_name) game_log("stop entering name");

    }


}


static void destroy() {
    al_destroy_bitmap(Winbackground);

}

static void on_key_down(int keycode) {
    int halfW = SCREEN_W / 2;
    int halfH = SCREEN_H / 2;

    if (enter_name)
    {
        if (keycode == ALLEGRO_KEY_BACKSPACE)
        {
            if (keyhere)
            {
                keyhere--;
                name[keyhere] = '\0';
            }
        }
        else if (keycode == ALLEGRO_KEY_ENTER)
        {
            game_log("press enter to save name");
            enter_name = false;
            Name.clicked = false;
        }
        else if ((keycode >= ALLEGRO_KEY_A && keycode <= ALLEGRO_KEY_Z) ||
                 (keycode >= ALLEGRO_KEY_0 && keycode <= ALLEGRO_KEY_9) ||
                 keycode == ALLEGRO_KEY_SPACE) {
            char key = al_keycode_to_name(keycode)[0];
            game_log("enter a letter %c", key);
            name[keyhere] = key;
            keyhere++;
            name[keyhere] = '\0';  // Null-terminate the string
        }

        /*
        {
            c = al_keycode_to_name(keycode);
            game_log("enter a letter %c",*c);
            name[keyhere] = *c;
            keyhere++;
        }
        */

    }
}
Scene winscene_create(void) {
    Scene scene;
    memset(&scene, 0, sizeof(Scene));
    scene.name = "Win";
    scene.initialize = &init;
    scene.draw = &draw;
    scene.destroy = &destroy;
    scene.on_key_down = &on_key_down;
    scene.on_mouse_move = &on_mouse_move;
    scene.on_mouse_down = &on_mouse_down;
    game_log("Win scene created");
    return scene;
}
