#ifndef __AF_BRAVURA_FONT_HEADER
#define __AF_BRAVURA_FONT_HEADER




#include <stdint.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>




namespace bravura
{
   extern const int32_t barline;
   extern const int32_t final_barline;

   // clefs
   extern const int32_t g_clef;
   extern const int32_t g_clef_8vb;
   extern const int32_t g_clef_8va;
   extern const int32_t c_clef;
   extern const int32_t f_clef;
   extern const int32_t f_clef_8va;
   extern const int32_t percussion_clef_1;
   extern const int32_t percussion_clef_2;

   // accidentals (chromatic)
   extern const int32_t double_sharp;
   extern const int32_t double_flat;
   extern const int32_t flat;
   extern const int32_t natural;
   extern const int32_t sharp;

   // rests
   extern const int32_t whole_rest;
   extern const int32_t half_rest;
   extern const int32_t quarter_rest;
   extern const int32_t eighth_rest;
   extern const int32_t sixteenth_rest;
   extern const int32_t rest_8;
   extern const int32_t rest_16;
   extern const int32_t rest_32;
   extern const int32_t rest_64;
   extern const int32_t rest_128;

   // note heads
   extern const int32_t open_note_head;
   extern const int32_t closed_note_head;
   extern const int32_t double_whole_note_head;
   extern const int32_t whole_note_head;

   // notes
   extern const int32_t double_whole_note;
   extern const int32_t whole_note;
   extern const int32_t half_note;
   extern const int32_t half_note_down;
   extern const int32_t quarter_note;
   extern const int32_t quarter_note_down;
   extern const int32_t eighth_note;
   extern const int32_t eighth_note_down;
   extern const int32_t sixteenth_note;
   extern const int32_t sixteenth_note_down;
   extern const int32_t thirtysecond_note;
   extern const int32_t thirtysecond_note_down;

   // note parts
   extern const int32_t stem;
   extern const int32_t dot;

   // articulations
   extern const int32_t accent;
   extern const int32_t staccato;
   extern const int32_t tenuto;
   extern const int32_t marcato;
   extern const int32_t staccato_marcato;
   extern const int32_t staccato_accent;
   extern const int32_t staccato_tenuto;

   // dynamics
   extern const int32_t dynamic_r;
   extern const int32_t dynamic_s;
   extern const int32_t dynamic_z;
   extern const int32_t dynamic_p;
   extern const int32_t dynamic_m;
   extern const int32_t dynamic_f;

   // numbers
   extern const int32_t number_0;
   extern const int32_t number_1;
   extern const int32_t number_2;
   extern const int32_t number_3;
   extern const int32_t number_4;
   extern const int32_t number_5;
   extern const int32_t number_6;
   extern const int32_t number_7;
   extern const int32_t number_8;
   extern const int32_t number_9;
}




#endif
