#ifndef __AF_DRAW_WAVE_SAMPLE_HEADER
#define __AF_DRAW_WAVE_SAMPLE_HEADER




#include <allegro5/allegro.h>
#include <allegro5/allegro_audio.h>




//void graph_wav_sample(ALLEGRO_BITMAP *image, ALLEGRO_SAMPLE *sample);
void draw_wav_sample(ALLEGRO_BITMAP *dest, ALLEGRO_SAMPLE *sample);
void draw_wav_sample(ALLEGRO_BITMAP *dest, ALLEGRO_SAMPLE *sample, float samp_start, float samp_end);
void draw_wav_sample(float x, float y, float width, float height, float samp_start, float samp_end, ALLEGRO_SAMPLE *sample);




#endif
