g++ ./src/allegro_flare.cpp -I"./include" -I"E:/allegro-5.1.8-msvc-10.0/include"

g++ *.o -Wall -lallegro -lallegro_color -lallegro_primitives -lallegro_audio -lallegro_dialog -lallegro_image -lallegro_font -lallegro_ttf -lallegro_acodec -o slug