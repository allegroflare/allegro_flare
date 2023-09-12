

#include <AllegroFlare/FontBravura.hpp>
#include <set>



namespace AllegroFlare
{


      const int32_t FontBravura::barline = 57392;
      const int32_t FontBravura::final_barline = 57394;

      // clefs
      const int32_t FontBravura::g_clef = 57424;
      const int32_t FontBravura::g_clef_8vb = 57426;
      const int32_t FontBravura::g_clef_8va = 57427;
      const int32_t FontBravura::c_clef = 57436;
      const int32_t FontBravura::f_clef = 57441;
      const int32_t FontBravura::f_clef_8va = 57444;
      const int32_t FontBravura::percussion_clef_1 = 57448;
      const int32_t FontBravura::percussion_clef_2 = 57449;

      // accidentals (chromatic)
      const int32_t FontBravura::double_sharp = 57923;
      const int32_t FontBravura::double_flat = 57924;
      const int32_t FontBravura::flat = 57920;
      const int32_t FontBravura::natural = 57921;
      const int32_t FontBravura::sharp = 57922;

      // rests
      const int32_t FontBravura::whole_rest = 58546;
      const int32_t FontBravura::half_rest = 58547;
      const int32_t FontBravura::quarter_rest = 58548;
      const int32_t FontBravura::eighth_rest = 58549;
      const int32_t FontBravura::sixteenth_rest = 58550;
      const int32_t FontBravura::rest_8 = eighth_rest;
      const int32_t FontBravura::rest_16 = sixteenth_rest;
      const int32_t FontBravura::rest_32 = 58551;
      const int32_t FontBravura::rest_64 = 58552;
      const int32_t FontBravura::rest_128 = 58553;

      // note heads
      const int32_t FontBravura::open_note_head = 57507;
      const int32_t FontBravura::closed_note_head = 57508;
      const int32_t FontBravura::double_whole_note_head = 57504;
      const int32_t FontBravura::whole_note_head = 57506;

      // notes
      const int32_t FontBravura::double_whole_note = 57776;
      const int32_t FontBravura::whole_note = 57778;
      const int32_t FontBravura::half_note = 57779;
      const int32_t FontBravura::half_note_down = 57780;
      const int32_t FontBravura::quarter_note = 57781;
      const int32_t FontBravura::quarter_note_down = 57782;
      const int32_t FontBravura::eighth_note = 57783;
      const int32_t FontBravura::eighth_note_down = 57784;
      const int32_t FontBravura::sixteenth_note = 57785;
      const int32_t FontBravura::sixteenth_note_down = 57786;
      const int32_t FontBravura::thirtysecond_note = 57787;
      const int32_t FontBravura::thirtysecond_note_down = 57788;
      const int32_t FontBravura::sixtyfourth_note = 57789;
      const int32_t FontBravura::sixtyfourth_note_down = 57790;

      // note parts
      const int32_t FontBravura::stem = 119141;
      const int32_t FontBravura::dot = 119149;

      // articulations
      const int32_t FontBravura::accent = 119163;
      const int32_t FontBravura::staccato = 119164;
      const int32_t FontBravura::tenuto = 119165;
      const int32_t FontBravura::marcato = 119167;
      const int32_t FontBravura::staccato_marcato = 119168;
      const int32_t FontBravura::staccato_accent = 119169;
      const int32_t FontBravura::staccato_tenuto = 119170;

      // dynamics
      const int32_t FontBravura::dynamic_r = 119180;
      const int32_t FontBravura::dynamic_s = 119181;
      const int32_t FontBravura::dynamic_z = 119182;
      const int32_t FontBravura::dynamic_p = 119183;
      const int32_t FontBravura::dynamic_m = 119184;
      const int32_t FontBravura::dynamic_f = 119185;

      // numbers
      const int32_t FontBravura::number_0 = 57472;
      const int32_t FontBravura::number_1 = 57473;
      const int32_t FontBravura::number_2 = 57474;
      const int32_t FontBravura::number_3 = 57475;
      const int32_t FontBravura::number_4 = 57476;
      const int32_t FontBravura::number_5 = 57477;
      const int32_t FontBravura::number_6 = 57478;
      const int32_t FontBravura::number_7 = 57479;
      const int32_t FontBravura::number_8 = 57480;
      const int32_t FontBravura::number_9 = 57481;


      bool has_stem(int32_t character)
      {
         static const std::set<int32_t> stemmed_characters = {
            FontBravura::half_note,
            FontBravura::half_note_down,
            FontBravura::quarter_note,
            FontBravura::quarter_note_down,
            FontBravura::eighth_note,
            FontBravura::eighth_note_down,
            FontBravura::sixteenth_note,
            FontBravura::sixteenth_note_down,
            FontBravura::thirtysecond_note,
            FontBravura::thirtysecond_note_down,
            FontBravura::sixtyfourth_note,
            FontBravura::sixtyfourth_note_down,
         };

         return (stemmed_characters.count(character) != 0);
      }
      bool has_up_stem(int32_t character)
      {
         static const std::set<int32_t> up_stemmed_characters = {
            FontBravura::half_note,
            FontBravura::quarter_note,
            FontBravura::eighth_note,
            FontBravura::sixteenth_note,
            FontBravura::thirtysecond_note,
            FontBravura::sixtyfourth_note,
         };

         return (up_stemmed_characters.count(character) != 0);
      }
      bool has_down_stem(int32_t character)
      {
         static const std::set<int32_t> down_stemmed_characters = {
            FontBravura::half_note_down,
            FontBravura::quarter_note_down,
            FontBravura::eighth_note_down,
            FontBravura::sixteenth_note_down,
            FontBravura::thirtysecond_note_down,
            FontBravura::sixtyfourth_note_down,
         };

         return (down_stemmed_characters.count(character) != 0);
      }


} // namespace AllegroFlare


