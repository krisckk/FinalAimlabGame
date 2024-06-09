#ifndef WINSCENE_H
#define WINSCENE_H
#include "game.h"
Scene winscene_create(void);
void save_data_to_file(const char *filename, const char *name, int combo, time_t current_time);
extern char name[20];
#endif
