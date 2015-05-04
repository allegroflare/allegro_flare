#ifndef __AF_GENERATE_TEXTURES_HEADER
#define __AF_GENERATE_TEXTURES_HEADER



#include <allegro_flare/allegro_flare.h>

#include <allegro_flare/image_processing.h>




ALLEGRO_BITMAP *generate_circle_bitmap(float size=512, ALLEGRO_COLOR col=color::white, int padding=0);

ALLEGRO_BITMAP *generate_gradient_bitmap(float size=512, ALLEGRO_COLOR top_color=color::transparent, ALLEGRO_COLOR bottom_color=color::black, int padding=0);

ALLEGRO_BITMAP *generate_circle_gradient_bitmap(float size=512, ALLEGRO_COLOR top_color=color::transparent, ALLEGRO_COLOR bottom_color=color::black, int padding=0);

ALLEGRO_BITMAP *generate_noise_bitmap(float w, float h, float min_intensity=0.5, float max_intensity=0.7);

ALLEGRO_BITMAP *generate_wood_grain_bitmap(float w, float h, ALLEGRO_COLOR base_color=al_color_name("sienna"));



#endif

