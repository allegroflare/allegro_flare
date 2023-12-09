#pragma once


#include <string>
#include <cstdint> // Needed for int32_t


namespace AllegroFlare
{
   class FontBravura
   {
   public:

      static const int32_t barline;
      static const int32_t final_barline;

      // clefs
      static const int32_t g_clef;
      static const int32_t g_clef_8vb;
      static const int32_t g_clef_8va;
      static const int32_t c_clef;
      static const int32_t f_clef;
      static const int32_t f_clef_8va;
      static const int32_t percussion_clef_1;
      static const int32_t percussion_clef_2;

      // accidentals (chromatic)
      static const int32_t double_sharp;
      static const int32_t double_flat;
      static const int32_t flat;
      static const int32_t natural;
      static const int32_t sharp;

      // rests
      static const int32_t whole_rest;
      static const int32_t half_rest;
      static const int32_t quarter_rest;
      static const int32_t eighth_rest;
      static const int32_t sixteenth_rest;
      static const int32_t rest_8;
      static const int32_t rest_16;
      static const int32_t rest_32;
      static const int32_t rest_64;
      static const int32_t rest_128;

      // note heads
      static const int32_t open_note_head;
      static const int32_t closed_note_head;
      static const int32_t double_whole_note_head;
      static const int32_t whole_note_head;

      // notes
      static const int32_t double_whole_note;
      static const int32_t whole_note;
      static const int32_t half_note;
      static const int32_t half_note_down;
      static const int32_t quarter_note;
      static const int32_t quarter_note_down;
      static const int32_t eighth_note;
      static const int32_t eighth_note_down;
      static const int32_t sixteenth_note;
      static const int32_t sixteenth_note_down;
      static const int32_t thirtysecond_note;
      static const int32_t thirtysecond_note_down;
      static const int32_t sixtyfourth_note;
      static const int32_t sixtyfourth_note_down;

      // note parts
      static const int32_t stem;
      static const int32_t dot;

      // articulations
      static const int32_t accent;
      static const int32_t staccato;
      static const int32_t tenuto;
      static const int32_t marcato;
      static const int32_t staccato_marcato;
      static const int32_t staccato_accent;
      static const int32_t staccato_tenuto;

      // dynamics
      static const int32_t dynamic_r;
      static const int32_t dynamic_s;
      static const int32_t dynamic_z;
      static const int32_t dynamic_p;
      static const int32_t dynamic_m;
      static const int32_t dynamic_f;

      // numbers
      static const int32_t number_0;
      static const int32_t number_1;
      static const int32_t number_2;
      static const int32_t number_3;
      static const int32_t number_4;
      static const int32_t number_5;
      static const int32_t number_6;
      static const int32_t number_7;
      static const int32_t number_8;
      static const int32_t number_9;

      static const bool has_stem(int32_t character);
      static const bool has_up_stem(int32_t character);
      static const bool has_down_stem(int32_t character);
   };
}



