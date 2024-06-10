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
#include "scoreboard_scene.h"
#include "scene_menu_object.h"
#include "stageselect.h"

ScoreboardScene *Scoreboard;
static Button Stage1;
static Button Stage2;
static Button Stage3;
static Button Back;
static Button Nextpage;
static Button Prevpage;
char line[30][100];
char nameee[30][30];
int score[30];
int highest_combo[30];
char date[30][15];
char timeee[30][15];
int i = 0;
int page = 0;

static void Init(void){
    Scoreboard = (ScoreboardScene*)malloc(sizeof (ScoreboardScene));
    Scoreboard -> background = load_bitmap("Assets/Images/scoreboard_background.jpg");
    Scoreboard -> Themesong = load_audio("Assets/Music/Intestellar.ogg");
    play_bgm(Scoreboard -> Themesong, music_volume);

    Stage1 = button_create(200, 180 , 400, 150, "Assets/Images/grayunhover.png", "Assets/Images/grayhover.png");
    Stage2 = button_create(700, 180 , 400, 150, "Assets/Images/grayunhover.png", "Assets/Images/grayhover.png");
    Stage3 = button_create(1200, 180 , 400, 150, "Assets/Images/grayunhover.png", "Assets/Images/grayhover.png");
    Back = button_create(700, SCREEN_H - 250 , 400, 150, "Assets/Images/grayunhover.png", "Assets/Images/grayhover.png");
    Nextpage = button_create(1200, SCREEN_H - 250 , 400, 150, "Assets/Images/grayunhover.png", "Assets/Images/grayhover.png");
    Prevpage = button_create(200, SCREEN_H - 250 , 400, 150, "Assets/Images/grayunhover.png", "Assets/Images/grayhover.png");

    Stage1.clicked = true;
    read_scoreboard(1);
}


static void Update(void){
    Draw();
}

static void Draw(void){
    al_clear_to_color(al_map_rgb(0, 0, 0));
    al_draw_scaled_bitmap(Scoreboard -> background, 0, 0, 3000, 2000, 0, 0, SCREEN_W, SCREEN_H, 0);
    drawButton(Stage1);
    drawButton(Stage2);
    drawButton(Stage3);
    drawButton(Back);
    drawButton(Nextpage);
    drawButton(Prevpage);

    al_draw_text(PoetFont, al_map_rgb(255, 255, 255), 400, 220, ALLEGRO_ALIGN_CENTER, "Stage1");
    al_draw_text(PoetFont, al_map_rgb(255, 255, 255), 900, 220, ALLEGRO_ALIGN_CENTER, "Stage2");
    al_draw_text(PoetFont, al_map_rgb(255, 255, 255), 1400, 220, ALLEGRO_ALIGN_CENTER, "Stage3");
    al_draw_text(PoetFont, al_map_rgb(255, 255, 255), 400, SCREEN_H - 205, ALLEGRO_ALIGN_CENTER, "Prev");
    al_draw_text(PoetFont, al_map_rgb(255, 255, 255), 900, SCREEN_H - 205, ALLEGRO_ALIGN_CENTER, "Back");
    al_draw_text(PoetFont, al_map_rgb(255, 255, 255), 1400, SCREEN_H - 205, ALLEGRO_ALIGN_CENTER, "Next");
    al_draw_text(PoetFont, al_map_rgb(255, 255, 255), 300, 430, 0, "Name");
    al_draw_text(PoetFont, al_map_rgb(255, 255, 255), 700, 430, 0, "Score");
    al_draw_text(PoetFont, al_map_rgb(255, 255, 255), 900, 430, 0, "Combo");
    al_draw_text(PoetFont, al_map_rgb(255, 255, 255), 1100, 430, 0, "Date");
    al_draw_text(PoetFont, al_map_rgb(255, 255, 255), 1400, 430, 0, "Time");

    sort();
    for (int j = 0; j < 4; j++)
    {
        if (nameee[page*4+j] != NULL)
        {
            al_draw_textf(PoetFont, al_map_rgb(255, 255, 255), 300, 520 + 80 * j , 0, "%s", nameee[page*4+j]);
            al_draw_textf(PoetFont, al_map_rgb(255, 255, 255), 700, 520 + 80 * j , 0, "%d", score[page*4+j]);
            al_draw_textf(PoetFont, al_map_rgb(255, 255, 255), 900, 520 + 80 * j , 0, "%d", highest_combo[page*4+j]);
            al_draw_textf(PoetFont, al_map_rgb(255, 255, 255), 1100, 520 + 80 * j , 0, "%s", date[page*4+j]);
            al_draw_textf(PoetFont, al_map_rgb(255, 255, 255), 1400, 520 + 80 * j , 0, "%s", timeee[page*4+j]);


        }

    }

}

static void Destroy(void){
    al_destroy_bitmap(Scoreboard -> background);
    al_destroy_sample(Scoreboard -> Themesong);
    //al_destroy_timer(power_up_timer);
}

static void On_key_down(int key_code) {

}

static void On_key_up(int key_code) {

}

static void On_mouse_move(int a, int mouse_x, int mouse_y, int f){
    Stage1.hovered = buttonHover(Stage1, mouse_x, mouse_y);
    Stage2.hovered = buttonHover(Stage2, mouse_x, mouse_y);
    Stage3.hovered = buttonHover(Stage3, mouse_x, mouse_y);
    Back.hovered = buttonHover(Back, mouse_x, mouse_y);
    Prevpage.hovered = buttonHover(Prevpage, mouse_x, mouse_y);
    Nextpage.hovered = buttonHover(Nextpage, mouse_x, mouse_y);

}

static void On_mouse_down(){
    if(Stage1.hovered){
        Stage1.clicked = true;
        Stage2.clicked = false;
        Stage3.clicked = false;
        game_log("stage1 scoreboard");
        reset();
        read_scoreboard(1);
    }
    if(Stage2.hovered){
        Stage1.clicked = false;
        Stage2.clicked = true;
        Stage3.clicked = false;
        game_log("stage2 scoreboard");
        reset();
        read_scoreboard(2);
    }
    if(Stage3.hovered){
        Stage1.clicked = false;
        Stage2.clicked = false;
        Stage3.clicked = true;
        game_log("stage3 scoreboard");
        reset();
        read_scoreboard(3);
    }
    if(Back.hovered){
        Back.clicked = true;
        game_log("BACK TO HOME");
        game_change_scene(scene_home_create());
    }
    if(Prevpage.hovered){
        Prevpage.clicked = true;
        Nextpage.clicked = false;

        if(page) page--;
        game_log("PREV PAGE");
    }
    if(Nextpage.hovered){
        Nextpage.clicked = true;
        Prevpage.clicked = false;

        if (page < i/4) page++;
        game_log("NEXT PAGE");
    }

}

static void On_mouse_up(){
    Nextpage.clicked = false;
    Prevpage.clicked = false;
}

void read_scoreboard(int id) {
    // Open the file in read mode
    const char *filename;
    if (id == 1) filename = "Stage1scoreboard.txt";
    else if (id == 2) filename = "Stage2scoreboard.txt";
    else if (id == 3) filename = "Stage3scoreboard.txt";

    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    /*while (fgets(line[i], sizeof(line[0]), file) != NULL) {
        game_log("%s",line[i]);
        i++;
    }
    */
    i = 0;
    while (fscanf(file, "%s", nameee[i]) != EOF) {
        fscanf(file, "%d", &score[i]);
        fscanf(file, "%d", &highest_combo[i]);
        fscanf(file, "%s", date[i]);
        fscanf(file, "%s", timeee[i]);
        //fgets(date[i], sizeof(char) * 15, file);
        //fgets(timeee[i], sizeof(char) * 15, file);

        game_log("%s %d %d %s %s",nameee[i], score[i], highest_combo[i], date[i], timeee[i]);
        i++;
    }

    fclose(file);
}

void reset(){
    memset(nameee,'\0',sizeof(nameee));
    memset(score,'\0',sizeof(score));
    memset(highest_combo,'\0',sizeof(highest_combo));
    memset(date,'\0',sizeof(date));
    memset(timeee,'\0',sizeof(timeee));
    i = 0;
    page = 0;
}

void sort(){

    int temp_int;
    char temp_str[30];

    for (int si = 0; si < i-1; si++) {
        // Last i elements are already in place
        for (int sj = 0; sj < i-si-1; sj++) {
            // Swap if the element found is greater than the next element
            if (score[sj] < score[sj+1]) {
                temp_int = score[sj];
                score[sj] = score[sj+1];
                score[sj+1] = temp_int;

                temp_int = highest_combo[sj];
                highest_combo[sj] = highest_combo[sj+1];
                highest_combo[sj+1] = temp_int;

                strcpy(temp_str, nameee[sj]);
                strcpy(nameee[sj], nameee[sj+1]);
                strcpy(nameee[sj+1], temp_str);

                strcpy(temp_str, date[sj]);
                strcpy(date[sj], date[sj+1]);
                strcpy(date[sj+1], temp_str);

                strcpy(temp_str, timeee[sj]);
                strcpy(timeee[sj], timeee[sj+1]);
                strcpy(timeee[sj+1], temp_str);
            }
        }
    }

}


Scene scene_scoreboard_create(void){
    Scene scene;
    memset(&scene, 0, sizeof(Scene));
    scene.name = "Scoreboard";
    scene.initialize = &Init;
    scene.update = &Update;
    scene.draw = &Draw;
    scene.destroy = &Destroy;
    scene.on_key_down = &On_key_down;
    scene.on_key_up = &On_key_up;
    scene.on_mouse_move = &On_mouse_move;
    scene.on_mouse_down = &On_mouse_down;
    scene.on_mouse_up = &On_mouse_up;
    game_log("Scoreboard scene created");
    return scene;
}