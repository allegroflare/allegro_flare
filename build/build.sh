#!/bin/bash


PROJECT_BASE="~/Programs/allegro_flare/allegro_flare"
INCLUDE_DIR="$PROJECT_BASE/include"
SOURCE_DIR="$PROJECT_BASE/src"
LIB_DESTINATION_DIR="$PROJECT_BASE/lib"

ALLEGRO_INCLUDE_DIR="/home/mark/Libraries/allegro-5.1.8/include/"
ALLEGRO_LIB_DIR="~/Libraries/allegro-5.1.8/build/lib/"
# -I"$ALLEGRO_INCLUDE_DIR" -L"ALLEGRO_LIB_DIR"



g++ -c -Wall ./../src/allegro_flare.cpp -I"./include/" -I"/home/mark/Libraries/allegro-5.1.8/include/" ./build/allegro_flare.o


# g++ *.o -Wall -lallegro -lallegro_color -lallegro_primitives -lallegro_audio -lallegro_dialog -lallegro_image -lallegro_font -lallegro_ttf -lallegro_acodec -o allegro_flare

