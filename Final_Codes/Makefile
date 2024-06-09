.PHONY: clean

CC=gcc
SRC=Src
UNAME_S := $(shell uname -s 2>/dev/null || echo Windows)
ifeq ($(UNAME_S), Linux)
	CCFLAGS=$$(pkg-config allegro-5 allegro_font-5 allegro_ttf-5 allegro_audio-5 allegro_image-5 allegro_primitives-5 allegro_acodec-5 --libs --cflags)
	INCLUDE=/usr/include/allegro5
endif
ifeq ($(UNAME_S), Windows)
	ALLEGRO_DIR=C:/allegro
	CCFLAGS=$(ALLEGRO_DIR)/lib/liballegro.dll.a $(ALLEGRO_DIR)/lib/liballegro_font.dll.a $(ALLEGRO_DIR)/lib/liballegro_ttf.dll.a $(ALLEGRO_DIR)/lib/liballegro_audio.dll.a $(ALLEGRO_DIR)/lib/liballegro_image.dll.a $(ALLEGRO_DIR)/lib/liballegro_primitives.dll.a $(ALLEGRO_DIR)/lib/liballegro_acodec.dll.a -lgdi32 -lwinmm
 	INCLUDE=$(ALLEGRO_DIR)/include
endif
ifeq ($(UNAME_S), Darwin)
	CCFLAGS=$$(pkg-config allegro-5 allegro_main-5 allegro_font-5 allegro_ttf-5 allegro_audio-5 allegro_image-5 allegro_primitives-5 allegro_acodec-5 --libs --cflags)
	INCLUDE=/opt/homebrew/Cellar/allegro/5.2.9.0/include
endif
#REVISE INCLUDE path if you have installed different version or install path.

DBG = -g -fsanitize=address
WARNINGS = -Wall -Wextra # add `$(WARNINGS)`  compile flag in line 26 and 29 if you want additional compile check warnings
objects= main.o game.o map.o playscene.o scene_menu.o scene_menu_object.o scene_settings.o shared.o utility.o Home.o MainCharacter.o stageselect.o staminarestore.o equipment.o winscene.o

all: aimlab 

aimlab: $(objects)
	$(CC) -lm $(CCFLAGS) $(DBG) -o aimlab $^

%.o: $(SRC)/%.c $(SRC)/%.h
	$(CC) -I$(INCLUDE) $(DBG) -c $< -o $@

%.o: $(SRC)/%.c
	$(CC) -I$(INCLUDE) $(DBG) -c $< -o $@

clean:
	rm aimlab *.o