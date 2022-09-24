#!/bin/sh
RESULT_FILENAME_1="/Users/markoates/Repos/allegro_flare/bin/data/maps/map1-0x.tmj"
RESULT_FILENAME_2="/Users/markoates/Repos/allegro_flare/bin/data/maps/map1b-0x.tmj"
/Applications/Tiled.app/Contents/MacOS/Tiled --export-map "/Users/markoates/Desktop/map1-03.tmx" $RESULT_FILENAME_1
/Applications/Tiled.app/Contents/MacOS/Tiled --export-map "/Users/markoates/Desktop/map1b-03.tmx" $RESULT_FILENAME_2
/Users/markoates/Repos/allegro_flare/bin/programs/wicked_tile_demo
