#!/bin/bash


SET ALLEGRO_INCLUDE_DIR = "E:/allegro-5.1.8-msvc-10.0/include"

g++ ./src/allegro_flare.cpp -I"./include" -I$ALLEGRO_INCLUDE_DIR

g++ *.o -Wall -lallegro -lallegro_color -lallegro_primitives -lallegro_audio -lallegro_dialog -lallegro_image -lallegro_font -lallegro_ttf -lallegro_acodec -o allegro_flare

