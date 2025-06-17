

#include <AllegroFlare/MusicNotation/MusicNotation.hpp>



#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>
#include <AllegroFlare/FontBravura.hpp>
#include <AllegroFlare/Color.hpp>
#include <AllegroFlare/Useful.hpp>
#include <AllegroFlare/UsefulPHP.hpp>
#include <AllegroFlare/Logger.hpp>
#include <AllegroFlare/MusicNotation/TieRenderer.hpp>
#include <AllegroFlare/MusicNotation/AccidentalStacker.hpp>
#include <AllegroFlare/MusicNotation/ChordNoteheadPositionResolver.hpp>
#include <AllegroFlare/MusicNotation/ChordDotPositionCalculator.hpp>
#include <AllegroFlare/Logger.hpp>



//bool operator==(const ALLEGRO_COLOR& color, const ALLEGRO_COLOR& other_color);
//bool operator!=(const ALLEGRO_COLOR& color, const ALLEGRO_COLOR& other_color);
static bool operator==(const ALLEGRO_COLOR& color, const ALLEGRO_COLOR& other_color)
{
   if (color.r != other_color.r) return false;
   if (color.g != other_color.g) return false;
   if (color.b != other_color.b) return false;
   if (color.a != other_color.a) return false;
   return true;
}


static bool operator!=(const ALLEGRO_COLOR& color, const ALLEGRO_COLOR& other_color)
{
   return !(color == other_color);
}



static ALLEGRO_COLOR infer_color_name_or_hex(const std::string &name_or_hex)
{
   static const ALLEGRO_COLOR black{0, 0, 0, 1};
   if (strcmp("black", name_or_hex.c_str()) == 0) return black;

   // Try using name to generate color
   ALLEGRO_COLOR result = al_color_name(name_or_hex.c_str());
   // If the previous call returned black, try using the name_or_hex as a hex value
   if (result == black) return al_color_html(name_or_hex.c_str());
   return result;
}




using AllegroFlare::MusicNotation::Parser::PitchToken;



template <typename Container, typename T>
bool contains(Container container, T value) {
    return std::count(container.begin(), container.end(), value) > 0;
}



static int get_min_staff_position(const std::vector<PitchToken> &multi_note)
{
   if (multi_note.empty()) return 0;

   int min_staff_position = std::numeric_limits<int>::max();
   for (const PitchToken &token : multi_note)
   {
      if (token.staff_position < min_staff_position) min_staff_position = token.staff_position;
   }

   return min_staff_position;
}



static int get_max_staff_position(const std::vector<PitchToken> &multi_note)
{
   if (multi_note.empty()) return 0;

   int min_staff_position = std::numeric_limits<int>::min();
   for (const PitchToken &token : multi_note)
   {
      if (token.staff_position > min_staff_position) min_staff_position = token.staff_position;
   }

   return min_staff_position;
}



static std::pair<PitchToken, int> parse_pitch_token(std::string token_string)
{
   std::pair<PitchToken, int> result;
   PitchToken &result_pitch_token = result.first;
   int &result_octave = result.second;

   for (auto &c : token_string)
   {
      switch (c)
      {
         case '0': result_pitch_token.staff_position = 0; continue;
         case '1': result_pitch_token.staff_position = 1; continue;
         case '2': result_pitch_token.staff_position = 2; continue;
         case '3': result_pitch_token.staff_position = 3; continue;
         case '4': result_pitch_token.staff_position = 4; continue;
         case '5': result_pitch_token.staff_position = 5; continue;
         case '6': result_pitch_token.staff_position = 6; continue;
         case '7': result_pitch_token.staff_position = 7; continue;
         case ',': result_octave--; continue;
         case '\'': result_octave++; continue;
         case '-': result_pitch_token.accidental--; continue;
         case '+': result_pitch_token.accidental++; continue;
         case '#': result_pitch_token.accidental--; continue;
         case 'b': result_pitch_token.accidental++; continue;
         case '=': result_pitch_token.accidental_natural = true; continue;
         default:
            throw std::runtime_error("MusicNotation|parse_pitch_token error: unexpected token in pitch-only token");
         break;
      }
   }

   return result;
}




namespace AllegroFlare
{
namespace MusicNotation
{



float MusicNotation::calculate_staff_position_y_offset(int staff_position)
{
   return - staff_position * staff_line_distance * 0.5;
}



MusicNotation::MusicNotation(
      AllegroFlare::DrawingInterfaces::Base *drawing_interface,
      AllegroFlare::FontBin *font_bin,
      float staff_line_distance
   )
   : drawing_interface(drawing_interface)
   , font_bin(font_bin)
   , staff_line_distance(staff_line_distance)
   , quarter_note_spacing(staff_line_distance * 5)
   , spacing_method(SPACING_AESTHETIC)
   , int_cast_y(true)
{
}



MusicNotation::~MusicNotation()
{
}



float get_duration_scalar(int duration)
{
   if (duration <= 1) return 0.65;
   switch(duration)
   {
   case 2: return 0.8; break;
   case 4: return 0.9; break;
   case 8: return 0.95; break;
   default: break;
   }
   if (duration >= 16) return 1.0;
   return 1.0;
}



float get_duration_aesthetic_width(int duration, float quarter_note_width, int num_dots)
{
   float return_width = quarter_note_width;
   float dot_spacing_width = 0;

   if (duration <= 1) return_width = quarter_note_width*4 * 0.65;
   else if (duration == 2) return_width = quarter_note_width*2 * 0.8;
   else if (duration == 4) return_width = quarter_note_width;
   else if (duration == 8) return_width = quarter_note_width/2 * 1.1;
   else if (duration >= 16) return_width = quarter_note_width/4 * 1.4;

   int next_dot_duration = 1;
   for (int i=0; i<num_dots; i++)
   {
      next_dot_duration = next_dot_duration * 2;
      dot_spacing_width += (float) return_width / next_dot_duration;
   }

   return return_width + dot_spacing_width;
}



float MusicNotation::get_duration_fixed_width(int duration, float quarter_note_width, int num_dots)
{
   float return_width = quarter_note_width;
   float dot_spacing_width = 0;

   return_width = quarter_note_width*4/duration;

   int next_dot_duration = 1;
   for (int i=0; i<num_dots; i++)
   {
      next_dot_duration = next_dot_duration * 2;
      dot_spacing_width += (float) return_width / next_dot_duration;
   }

   return return_width + dot_spacing_width;
}



void MusicNotation::prepare_drawing_surface()
{
   if (!drawing_interface)
   {
      AllegroFlare::Logger::throw_error("MusicNotation::draw", "missing \"drawing_interface\"");
   }
   drawing_interface->prepare_surface(800, 500);
}



void MusicNotation::finish_drawing_surface(std::string output_file_basename)
{
   drawing_interface->finish_surface();
   if (!output_file_basename.empty()) drawing_interface->save_file(output_file_basename);
}



float MusicNotation::draw(float x, float y, std::string content, std::string output_file_basename)
{
   float x_cursor = 0;

   prepare_drawing_surface();
   x_cursor = draw_raw(x, y, content);
   finish_drawing_surface(output_file_basename);

   return x_cursor;
}



namespace {

struct PitchTokenComparator
{
   bool operator()(const PitchToken& token1, const PitchToken& token2) const
   {
      // TODO: Test this comparitor
      if (token1.staff_position != token2.staff_position)
         return token1.staff_position < token2.staff_position;

      int token1_accidental_weight = token1.accidental_natural ? 0 : token1.accidental;
      int token2_accidental_weight = token2.accidental_natural ? 0 : token2.accidental;

      return token1_accidental_weight < token2_accidental_weight;
   }
};

}



static void sort_and_make_unique(std::vector<PitchToken> &multi_note) // Consider adding this to the MusicNotation class
{
   // TODO: Consider modifying this method to return a sorted object rather than modify the existing one
   std::set<PitchToken, PitchTokenComparator> result_multi_note;

   for (auto &note : multi_note)
   {
      result_multi_note.insert(note);
   }

   multi_note.clear();
   for (auto &note : result_multi_note)
   {
      multi_note.push_back(note);
   }
}



float MusicNotation::draw_stacked_accidentals_on(
      float x,
      float y,
      std::vector<PitchToken> multi_note,
      const ALLEGRO_COLOR &color,
      float font_size_px
   )
{
   // TODO: Replace the technique in this function with a stacking technique.
   // See: https://blog.dorico.com/2014/03/development-diary-part-six/#:~:text=The%20basic%20rule%20for%20stacking,the%20fourth%20column%2C%20and%20so

   // Solve the stacking order for the accidentals and get the result
   AllegroFlare::MusicNotation::AccidentalStacker accidental_stacker(multi_note);
   accidental_stacker.solve();
   std::vector<std::pair<AllegroFlare::MusicNotation::AccidentalStacker::AccidentalType, std::pair<int, int>>> stack =
      accidental_stacker.get_stack();

   // Calculate some render result data
   float column_width = staff_line_distance;
   int num_columns = accidental_stacker.calculate_num_columns();
   float initial_x_offset_to_first_column = staff_line_distance * 1.2;

   // Draw each of the accidentals in their position
   for (auto &accidental_stack_info : stack)
   {
      int column = accidental_stack_info.second.first;
      int staff_position = accidental_stack_info.second.second;
      AllegroFlare::MusicNotation::AccidentalStacker::AccidentalType accidental_type = accidental_stack_info.first;
      uint32_t local_current_accidental_symbol = 0x0000;

      switch(accidental_type)
      {
         case AllegroFlare::MusicNotation::AccidentalStacker::AccidentalType::SHARP:
            local_current_accidental_symbol = AllegroFlare::FontBravura::sharp;
         break;

         case AllegroFlare::MusicNotation::AccidentalStacker::AccidentalType::FLAT:
            local_current_accidental_symbol = AllegroFlare::FontBravura::flat;
         break;

         case AllegroFlare::MusicNotation::AccidentalStacker::AccidentalType::NATURAL:
            local_current_accidental_symbol = AllegroFlare::FontBravura::natural;
         break;

         default:
            AllegroFlare::Logger::throw_error(
               "AllegroFlare::MusicNotation::MusicNotation::draw_raw",
               "Rendering accidentals other than flat, sharp, and natural is not supported."
            );
         break;
      }

      //if (note.accidental == -1) local_current_accidental_symbol = AllegroFlare::FontBravura::flat;
      //else if (note.accidental == 1) local_current_accidental_symbol = AllegroFlare::FontBravura::sharp;
      //else if (note.accidental < -2 || note.accidental > 2)
      //{
         //AllegroFlare::Logger::throw_error(
            //"AllegroFlare::MusicNotation::MusicNotation::draw_raw",
            //"Rendering accidentals other than flat, sharp, and natural is not supported."
         //);
      //}

      float column_width = staff_line_distance;
      draw_music_symbol(
         local_current_accidental_symbol,
         x - initial_x_offset_to_first_column + column_width * column,
         y + calculate_staff_position_y_offset(staff_position),
         color,
         font_size_px
      );
   }

   
   // TODO: Test this return value width
   return initial_x_offset_to_first_column + num_columns * column_width; // TODO: Confirm if "num_columns" requires a -1


// TODO: Move this code to a separate function so it can be used as a backup to stacking
/*
   sort_and_make_unique(multi_note); // TODO: Remove this call and the function itself

   // TODO: Implement this function
   for (auto &note : multi_note)
   {
      // Draw the accidental

      uint32_t local_current_accidental_symbol = 0x0000;

      if (note.accidental_natural)
      {
         local_current_accidental_symbol = AllegroFlare::FontBravura::natural;
      }
      else if (note.accidental != 0)
      {
         // TODO: Calculate symbol for more extended accidental cases
         if (note.accidental == -1) local_current_accidental_symbol = AllegroFlare::FontBravura::flat;
         else if (note.accidental == 1) local_current_accidental_symbol = AllegroFlare::FontBravura::sharp;
         else if (note.accidental < -2 || note.accidental > 2)
         {
            AllegroFlare::Logger::throw_error(
               "AllegroFlare::MusicNotation::MusicNotation::draw_raw",
               "Rendering accidentals other than flat, sharp, and natural is not supported."
            );
         }
      }

      bool accidental_is_present = (local_current_accidental_symbol != 0x0000);
      if (accidental_is_present)
      {
         draw_music_symbol(
            local_current_accidental_symbol,
            x-staff_line_distance*1.2,
            y + calculate_staff_position_y_offset(note.staff_position),
            color,
            font_size_px
         );
      }
   }
*/

   return 0; // TODO: Return the width of the render
}



StemDirection MusicNotation::calculate_preferred_stem_direction(const std::vector<PitchToken>& multi_note)
{
   // TODO: Test this method
   StemDirection result = StemDirection::UNDEFINED;

   int min_staff_pos = get_min_staff_position(multi_note);
   int max_staff_pos = get_max_staff_position(multi_note);
   int abs_min_staff_pos = abs(min_staff_pos);
   int abs_max_staff_pos = abs(max_staff_pos);

   // Max and min are both above the center line
   if (min_staff_pos < 0 && max_staff_pos < 0) return StemDirection::UP;

   // Max and min are below the center line
   if (min_staff_pos > 0 && max_staff_pos > 0) return StemDirection::DOWN;

   // Max and min are equally distant from the center line (this typically means the stem will go down, but can conform
   // to surrounding stems if desired - if all other stems in the measure are up, this stem should be up as well.)
   if (abs_min_staff_pos == abs_max_staff_pos) return StemDirection::EVEN;

   // Here out, there are no edge cases. The furthest note from the center is either above or below
   if (abs_min_staff_pos > abs_max_staff_pos) return StemDirection::UP;
   if (abs_max_staff_pos > abs_min_staff_pos) return StemDirection::DOWN;

   throw std::runtime_error("MusicNotation::calculate_preferred_stem_direction: case not handled");
   return StemDirection::UNDEFINED;
}



float MusicNotation::draw_note_fragment(
      float x,
      float y,
      std::vector<PitchToken> multi_note,
      bool current_note_is_rest,
      int current_note_duration,
      int num_dots,
      bool freeze_stems_up,
      float staff_line_thickness,
      ALLEGRO_COLOR staff_color,
      ALLEGRO_COLOR color,
      float font_size_px
   )
{
   uint32_t symbol = AllegroFlare::FontBravura::closed_note_head;
   uint32_t note_head_symbol = 0x0000;
   // Calculate our max and min staff position

   StemDirection preferred_stem_direction_from_note_positions = calculate_preferred_stem_direction(multi_note);
   bool stem_direction_is_undefined_or_even = contains<std::vector<StemDirection>, StemDirection>(
      {
         StemDirection::EVEN,
         StemDirection::UNDEFINED,
      },
      preferred_stem_direction_from_note_positions
   );
   StemDirection stem_direction =
      freeze_stems_up ? StemDirection::UP :
         (stem_direction_is_undefined_or_even ? StemDirection::DOWN : preferred_stem_direction_from_note_positions);


   bool rendering_stem = true; // TODO: Turn this to false and render stems manually
   

   // Calculate which primary symbol to render, which should either be a note-with-stem or rest

   if (current_note_is_rest)
   {
      if (current_note_duration == 1) symbol = AllegroFlare::FontBravura::whole_rest;
      else if (current_note_duration == 2) symbol = AllegroFlare::FontBravura::half_rest;
      else if (current_note_duration == 4) symbol = AllegroFlare::FontBravura::quarter_rest;
      else if (current_note_duration == 8) symbol = AllegroFlare::FontBravura::rest_8;
      else if (current_note_duration == 16) symbol = AllegroFlare::FontBravura::rest_16;
      else if (current_note_duration == 32) symbol = AllegroFlare::FontBravura::rest_32;
      else if (current_note_duration == 64) symbol = AllegroFlare::FontBravura::rest_64;
      else
      {
         AllegroFlare::Logger::throw_error(
            "AllegroFlare::MusicNotation::MusicNotation::draw_raw",
            "Rendering durations faster than a 1/64 rest is not supported."
         );
      }
   }
   else // (!current_note_is_rest)
   {
      switch(current_note_duration)
      {
         case 1:
            note_head_symbol = AllegroFlare::FontBravura::whole_note_head;
         break;

         case 2:
            note_head_symbol = AllegroFlare::FontBravura::open_note_head;
         break;

         case 4:
         case 8:
         case 16:
         case 32:
         case 64:
            note_head_symbol = AllegroFlare::FontBravura::closed_note_head;
         break;

         default:
            AllegroFlare::Logger::throw_error(
               "AllegroFlare::MusicNotation::MusicNotation::draw_raw",
               "Inferring the notehead symbol for this duration (" + std::to_string(current_note_duration)
                  + ") is not supported."
            );
         break;
      }

      if (!rendering_stem)
      {
         switch(current_note_duration)
         {
            case 1:
               symbol = AllegroFlare::FontBravura::whole_note_head;
               //note_head_symbol = AllegroFlare::FontBravura::whole_note_head;
            break;

            case 2:
               symbol = AllegroFlare::FontBravura::open_note_head;
               //note_head_symbol = AllegroFlare::FontBravura::open_note_head;
            break;

            case 4:
            case 8:
            case 16:
            case 32:
            case 64:
               symbol = AllegroFlare::FontBravura::closed_note_head;
               //note_head_symbol = AllegroFlare::FontBravura::closed_note_head;
            break;

            default:
               AllegroFlare::Logger::throw_error(
                  "AllegroFlare::MusicNotation::MusicNotation::draw_raw",
                  "Inferring the notehead symbol for this duration (" + std::to_string(current_note_duration)
                     + ") is not supported."
               );
            break;
         }
      }
      else // if (rendering_stem)
      {
         if (current_note_duration == 1) symbol = AllegroFlare::FontBravura::whole_note;
         else if (current_note_duration == 2) symbol = AllegroFlare::FontBravura::half_note;
         else if (current_note_duration == 4) symbol = AllegroFlare::FontBravura::quarter_note;
         else if (current_note_duration == 8) symbol = AllegroFlare::FontBravura::eighth_note;
         else if (current_note_duration == 16) symbol = AllegroFlare::FontBravura::sixteenth_note;
         else if (current_note_duration == 32) symbol = AllegroFlare::FontBravura::thirtysecond_note;
         else if (current_note_duration == 64) symbol = AllegroFlare::FontBravura::sixtyfourth_note;
         else
         {
            AllegroFlare::Logger::throw_error(
               "AllegroFlare::MusicNotation::MusicNotation::draw_raw",
               "Rendering durations faster than a 1/64 note is not supported."
            );
         }

         //if (preferred_stem_direction == 
         //contains
         bool symbol_contains_stem = AllegroFlare::FontBravura::has_stem(symbol);
         if (symbol_contains_stem)
         {
            switch(stem_direction)
            {
               case StemDirection::UP:
                  // do nothing
               break;

               case StemDirection::DOWN:
                  symbol += 1;
               break;

               case StemDirection::UNDEFINED:
               case StemDirection::EVEN:
                  AllegroFlare::Logger::throw_error(
                     "AllegroFlare::MusicNotation::MusicNotation",
                     "Unexpectedly reached stem_direction evaluation to either UNDEFINED or EVEN"
                  );
               break;
            }
         }
      }
   }



   // Render the notehead(s), accidentals, and dots

   float accidental_stack_result_width = draw_stacked_accidentals_on(x, y, multi_note, color, font_size_px);

   AllegroFlare::MusicNotation::ChordNoteheadPositionResolver chord_notehead_position_resolver(multi_note);
   chord_notehead_position_resolver.solve();
   std::vector<std::pair<int, ChordNoteheadPositionResolver::PositionType>> notehead_positions =
      chord_notehead_position_resolver.get_positions();

   float notehead_width_px = get_music_symbol_width(symbol) * 0.9;
   bool this_note_cluster_has_seconds = chord_notehead_position_resolver.get_seconds_exist();


   // Calculate which side the STEMSIDE should resolve to

   ChordNoteheadPositionResolver::PositionType stemside_resolves_to =
      ChordNoteheadPositionResolver::PositionType::UNDEFINED;

   switch(stem_direction)
   {
      case StemDirection::UP:
         stemside_resolves_to = ChordNoteheadPositionResolver::PositionType::LEFT;
      break;

      case StemDirection::DOWN:
         stemside_resolves_to = this_note_cluster_has_seconds ? 
            ChordNoteheadPositionResolver::PositionType::RIGHT
            : ChordNoteheadPositionResolver::PositionType::LEFT;
      break;

      default:
         AllegroFlare::Logger::throw_error(
            "AllegroFlare::MusicNotation::MusicNotation::draw_raw",
            "Unhandled StemDirection when evaluating the stem_direction"
         );
      break;
   }


   // Calculate the position of the augmentation dots

   std::set<int> augmentation_dots_staff_positions = {};
   if (num_dots > 0)
   {
      AllegroFlare::MusicNotation::ChordDotPositionCalculator chord_dot_position_calculator(multi_note);
      augmentation_dots_staff_positions = chord_dot_position_calculator.calculate_dot_staff_positions();
   }


   // Draw ledger lines

   if (current_note_is_rest)
   {
      int min_staff_pos = get_min_staff_position(multi_note);
      int max_staff_pos = get_max_staff_position(multi_note);

      if (min_staff_pos < 0)
      {
         draw_ledger_lines_to(
            x,
            y,
            min_staff_pos,
            staff_line_thickness,
            get_music_symbol_width(symbol),
            staff_color
         );
      }

      if (max_staff_pos > 0)
      {
         draw_ledger_lines_to(
            x,
            y,
            max_staff_pos,
            staff_line_thickness,
            get_music_symbol_width(symbol),
            staff_color
         );
      }
   }
   else // if (!current_note_is_rest)
   {
      int min_left = chord_notehead_position_resolver.lowest_staff_position_on_left_column();
      int max_left = chord_notehead_position_resolver.highest_staff_position_on_left_column();
      int min_right = chord_notehead_position_resolver.lowest_staff_position_on_right_column();
      int max_right = chord_notehead_position_resolver.highest_staff_position_on_right_column();
      int min_stemside = chord_notehead_position_resolver.lowest_staff_position_on_stemside_column();
      int max_stemside = chord_notehead_position_resolver.highest_staff_position_on_stemside_column();

      if (stemside_resolves_to == ChordNoteheadPositionResolver::PositionType::LEFT)
      {
         min_left = std::min(min_left, min_stemside);
         max_left = std::max(max_left, max_stemside);
      }
      else if (stemside_resolves_to == ChordNoteheadPositionResolver::PositionType::RIGHT)
      {
         min_right = std::min(min_right, min_stemside);
         max_right = std::max(max_right, max_stemside);
      }
      else
      {
         AllegroFlare::Logger::throw_error(
            "AllegroFlare::MusicNotation::MusicNotation::draw_raw",
            "Unhandled StemDirection when evaluating the max and min staff_position on left and right columns"
         );
      }

      // Draw the left column ledger lines

      if (min_left < 0)
      {
         draw_ledger_lines_to(
            x,
            y,
            min_left,
            staff_line_thickness,
            get_music_symbol_width(symbol),
            staff_color
         );
      }

      if (max_left > 0)
      {
         draw_ledger_lines_to(
            x,
            y,
            max_left,
            staff_line_thickness,
            get_music_symbol_width(symbol),
            staff_color
         );
      }

      // Draw the right column ledger lines

      if (min_right < 0)
      {
         draw_ledger_lines_to(
            x + notehead_width_px,
            y,
            min_right,
            staff_line_thickness,
            get_music_symbol_width(symbol),
            staff_color
         );
      }

      if (max_right > 0)
      {
         draw_ledger_lines_to(
            x + notehead_width_px,
            y,
            max_right,
            staff_line_thickness,
            get_music_symbol_width(symbol),
            staff_color
         );
      }
   } // else // if (!current_note_is_rest)


   // Draw note heads (with or without stems, depending on context)

   float max_notehead_x_offset = std::numeric_limits<int>::min();

   for (auto &note : notehead_positions)
   {
      //const bool LEFT = 0;
      //const bool RIGHT = 1;
      int note_staff_position = note.first;
      ChordNoteheadPositionResolver::PositionType notehead_resolved_position = note.second;
      ChordNoteheadPositionResolver::PositionType note_stem_position =
         ChordNoteheadPositionResolver::PositionType::LEFT;

      switch(notehead_resolved_position)
      {
         case ChordNoteheadPositionResolver::PositionType::STEMSIDE:
            note_stem_position = stemside_resolves_to;
         break;

         case ChordNoteheadPositionResolver::PositionType::LEFT:
            note_stem_position = ChordNoteheadPositionResolver::PositionType::LEFT;
         break;

         case ChordNoteheadPositionResolver::PositionType::RIGHT:
            note_stem_position = ChordNoteheadPositionResolver::PositionType::RIGHT;
         break;

         default:
            AllegroFlare::Logger::throw_error(
               "AllegroFlare::MusicNotation::MusicNotation::draw_raw",
               "Unhandled ChordNotePositionResolver::PositionType when evaluating the note_stem_position"
            );
         break;
      }


      // Draw the note

      float notehead_x_offset = (
            (note_stem_position == ChordNoteheadPositionResolver::PositionType::LEFT) ? 0 : notehead_width_px);


      // Accumulate the maximum note offset (for the augmentation dots, if they are in a chord)

      if (notehead_x_offset > max_notehead_x_offset) max_notehead_x_offset = notehead_x_offset;


      bool is_outset_from_normal_note_position_for_the_stem =
               (
                  stem_direction == StemDirection::UP
                  && note_stem_position == ChordNoteheadPositionResolver::PositionType::RIGHT
               )
            || (
                  this_note_cluster_has_seconds && stem_direction == StemDirection::DOWN
                  && note_stem_position == ChordNoteheadPositionResolver::PositionType::LEFT
               )
            ;


      draw_music_symbol(
         is_outset_from_normal_note_position_for_the_stem ? note_head_symbol : symbol, // HACK, use
         //symbol,
         x + notehead_x_offset,
         y + calculate_staff_position_y_offset(note_staff_position),
         color,
         font_size_px
      );

      // Draw the dots
      // TODO: Take into account shared dots within chord noteheads

      /*
      float dots_x_cursor = 0;
      bool note_head_is_on_line = (note_staff_position % 2 == 0);
      float dot_vertical_adjustment_from_being_on_line = note_head_is_on_line ? staff_line_distance * -0.5f : 0.0f;
      if (num_dots > 0)
      {
         dots_x_cursor += get_music_symbol_width(symbol) + get_music_symbol_width(AllegroFlare::FontBravura::dot);
      }
      for (int i=0; i<num_dots; i++)
      {
         draw_music_symbol(
            AllegroFlare::FontBravura::dot,
            x + notehead_x_offset + dots_x_cursor,
            y + calculate_staff_position_y_offset(note_staff_position) + dot_vertical_adjustment_from_being_on_line,
            color,
            font_size_px
         );
         dots_x_cursor += get_music_symbol_width(AllegroFlare::FontBravura::dot) * 1.6;
      }
      */
   }


   // Draw the augmentation dots
   for (auto &augmentation_dot_staff_position : augmentation_dots_staff_positions)
   {
      float dots_x_cursor = 0;

      if (num_dots > 0)
      {
         dots_x_cursor += get_music_symbol_width(symbol) + get_music_symbol_width(AllegroFlare::FontBravura::dot);
      }
      for (int i=0; i<num_dots; i++)
      {
         draw_music_symbol(
            AllegroFlare::FontBravura::dot,
            x + max_notehead_x_offset + dots_x_cursor,
            y + calculate_staff_position_y_offset(augmentation_dot_staff_position),
            color,
            font_size_px
         );

         dots_x_cursor += get_music_symbol_width(AllegroFlare::FontBravura::dot) * 1.6;
      }
   }


   // Move the cursor over based on the spacing method

   float result_render_width = 0;

   switch (spacing_method)
   {
      case SPACING_FIXED:
         result_render_width = get_duration_fixed_width(current_note_duration, quarter_note_spacing, num_dots);
      break;

      case SPACING_AESTHETIC:
      case SPACING_UNDEF:
      default:
         result_render_width = get_duration_aesthetic_width(current_note_duration, quarter_note_spacing, num_dots);
      break;
   }


   return result_render_width;
}



float MusicNotation::draw_raw(float x, float y, std::string content)
{
   // Calculate some common rendering metrics
   float staff_line_thickness = staff_line_distance * 0.1; // TODO: Consider providing "staff_line_thickness" as
                                                           // an overrideable parameter
   float font_size_px = (staff_line_distance * 4) * 4;
   float stem_thickness = staff_line_distance * 0.15f;

   // Create some render state variables
   float start_x = x;
   float x_cursor = 0; // TODO: Recently changed from int, see if/how it affects
   int current_note_duration = 4;
   int current_note_staff_position = 0;
   bool current_note_is_rest = false;
   int current_accidental = 0;
   bool current_accidental_natural = false;
   uint32_t current_accidental_symbol = 0x0000;

   bool force_rest_to_0_pos = true;
   bool rhythm_only = false;
   bool freeze_stems_up = false;
   ALLEGRO_COLOR color = color::white;
   ALLEGRO_COLOR staff_color = color::white;
   bool ignore_spaces = false;

   // More render state variables
   int current_octave = 0;
   int num_dots = 0;
   std::vector<PitchToken> multi_note;
   bool context_change_token_found = true;
   bool one_off_render_token_found = true;
   bool multinote_token_found = true;
   bool note_info_accumulated_and_ready_for_render = false;

   for (int i=0; i<(int)content.size(); i++)
   {
      multi_note.clear();
      num_dots = 0;


      // Current note context and render setting change token cases

      context_change_token_found = true;
      switch (content[i])
      {
      case '0':
      case '1':
      case '2':
      case '3':
      case '4':
      case '5':
      case '6':
      case '7':
         current_note_staff_position = content[i] - '0';
         note_info_accumulated_and_ready_for_render = true;
      break;
      case 'w': current_note_duration = 1; continue;
      case 'h': current_note_duration = 2; continue;
      case 'q': current_note_duration = 4; continue;
      case 'e': current_note_duration = 8; continue;
      case 's': current_note_duration = 16; continue;
      case 't': current_note_duration = 32; continue;
      case 'i': current_note_duration = 64; continue;
      case 'r': current_note_is_rest = true; continue;
      case 'n': current_note_is_rest = false; continue;
      case '-': current_accidental = -1; continue;
      case '+': current_accidental = 1; continue;
      case '=': current_accidental_natural = true; continue;
      case '#': current_accidental = -1; continue;
      case 'b': current_accidental = 1; continue;
      case '\'': current_octave++; continue;
      case ',': current_octave--; continue;
      case '{':
      {
         // NOTE: settings for rendering can be specified in the music string when contained in {} curly braces.
         // each setting is delimited by a space.  An example:
         // "{freeze_stems_up spacing=fixed staff_color=orange}"

         // find the closing brace
         std::size_t pos_opening_brace = i;
         std::size_t pos_closing_brace = content.find('}', pos_opening_brace);

         if (pos_closing_brace == std::string::npos)
         {
            // Closing brace not found, throw an error
            std::stringstream error_message;
            error_message << "music string parse error: expected closing curly brace '}' not found";
            AllegroFlare::Logger::throw_error("MusicNotation::draw", error_message.str());
         }

         // Parse the braced string for tokens
         std::string braced_string = content.substr(pos_opening_brace+1, pos_closing_brace - pos_opening_brace - 1);
         std::vector<std::string> tokens = php::explode(" ", braced_string);
         for (unsigned t=0; t<tokens.size(); t++)
         {
            std::size_t pos_of_equals = tokens[t].find("=");
            std::string text_before_equals = "";
            std::string text_after_equals = "";
            if (pos_of_equals != std::string::npos)
            {
               text_before_equals = tokens[t].substr(0, pos_of_equals);
               text_after_equals = tokens[t].substr(pos_of_equals+1);
            }

            if (text_before_equals.compare("color") == 0)
            {
               //color = color::name(text_after_equals.c_str());
               color = infer_color_name_or_hex(text_after_equals);
            }
            else if (text_before_equals.compare("staff_color") == 0)
            {
               staff_color = infer_color_name_or_hex(text_after_equals);
            }
            else if (tokens[t] == "freeze_stems_up") freeze_stems_up = true;
            else if (tokens[t] == "ignore_spaces") ignore_spaces = true;
            else if (tokens[t] == "rhythm_only") rhythm_only = true;
            else if (tokens[t].find("spacing=fixed")==0) spacing_method = MusicNotation::SPACING_FIXED;
            else if (tokens[t].find("spacing=aesthetic")==0) spacing_method = MusicNotation::SPACING_AESTHETIC;
         }

         // set the cursor to the end of this braced section
         i = pos_closing_brace;
         continue;
      }
      case '(':
      {
         // TODO: Test this feature of multi_note

         // Clusters of notes are to be contained in () parens, separated by spaces
         // "(0 =,4 -7 3 ,1 ''+6)"

         // Find the closing brace
         std::size_t pos_opening_paren = i;
         std::size_t pos_closing_paren = content.find(')', pos_opening_paren);

         if (pos_closing_paren == std::string::npos)
         {
            // Closing brace not found, throw an error
            std::stringstream error_message;
            error_message << "music string parse error: expected closing parenthesis ')' not found";
            AllegroFlare::Logger::throw_error("MusicNotation::draw", error_message.str());
         }

         // Capture the content of the string within the parens
         std::string parened_string = content.substr(pos_opening_paren+1, pos_closing_paren - pos_opening_paren - 1);

         // Pull out each token
         i = pos_closing_paren;
         std::vector<std::string> tokens = php::explode(" ", parened_string);
         int multi_note_local_octave = 0;
         for (auto &token : tokens)
         {
            // TODO: Test this parsing
            std::pair<PitchToken, int> parsed_token_info = parse_pitch_token(token);
            int change_in_octave_context_for_this_parsed_token = parsed_token_info.second;
            multi_note_local_octave += change_in_octave_context_for_this_parsed_token;

            PitchToken &parsed_pitch_token = parsed_token_info.first;
            parsed_pitch_token.staff_position += (multi_note_local_octave * 7) + (current_octave * 7);

            multi_note.push_back(parsed_pitch_token);
         }

         note_info_accumulated_and_ready_for_render = true;

         break;
      }
      default: context_change_token_found = false; break;
      }



      // Render one-off token cases

      one_off_render_token_found = true;
      switch (content[i])
      {
      case ' ': // Space
      {
         if (!ignore_spaces) x_cursor += staff_line_distance;
         continue;
      }
      case '$': // 4/4 or shift 4
      {
         draw_music_symbol(62692, start_x+x_cursor, y + staff_line_distance*2, color, font_size_px);
         draw_music_symbol(62693, start_x+x_cursor, y + staff_line_distance*2, color, font_size_px);
         x_cursor += get_music_symbol_width(62692);
         continue;
      }
      case '@': // 2/4 or shift 2
      {
         draw_music_symbol(62689, start_x+x_cursor, y + staff_line_distance*2, color, font_size_px);
         draw_music_symbol(62692, start_x+x_cursor, y + staff_line_distance*2, color, font_size_px);
         x_cursor += get_music_symbol_width(62692);
         continue;
      }
      case '#': // 3/4 or shift 3
      {
         draw_music_symbol(62691, start_x+x_cursor, y + staff_line_distance*2, color, font_size_px);
         draw_music_symbol(62692, start_x+x_cursor, y + staff_line_distance*2, color, font_size_px);
         x_cursor += get_music_symbol_width(62692);
         continue;
      }
      case '^': // 6/8 or shift 6
      {
         draw_music_symbol(62697, start_x+x_cursor, y + staff_line_distance*2, color, font_size_px);
         draw_music_symbol(62700, start_x+x_cursor, y + staff_line_distance*2, color, font_size_px);
         x_cursor += get_music_symbol_width(62697);
         continue;
      }
      case '|':
      {
         draw_music_symbol(
            AllegroFlare::FontBravura::barline,
            start_x+x_cursor,
            y + staff_line_distance*2,
            color,
            font_size_px
         );
         if (i != ((int)content.size()-1)) x_cursor += staff_line_distance*2;
         continue;
      }
      case ']':
      {
         draw_music_symbol(
            AllegroFlare::FontBravura::final_barline,
            start_x+x_cursor,
            y + staff_line_distance*2,
            color,
            font_size_px
         );
         x_cursor += get_music_symbol_width(AllegroFlare::FontBravura::final_barline);
         if (i != ((int)content.size()-1)) x_cursor += staff_line_distance;
         continue;
      }
      case '&':
      {
         if (rhythm_only)
         {
            draw_music_symbol(AllegroFlare::FontBravura::percussion_clef_1, start_x+x_cursor, y, color, font_size_px);
         }
         else
         {
            draw_music_symbol(AllegroFlare::FontBravura::g_clef, start_x+x_cursor, y + staff_line_distance, color, font_size_px);
         }
         x_cursor += get_music_symbol_width(AllegroFlare::FontBravura::g_clef);
         continue;
      }
      case '?':
      {
         if (rhythm_only)
         {
            draw_music_symbol(AllegroFlare::FontBravura::percussion_clef_1, start_x+x_cursor, y, color, font_size_px);
         }
         else
         {
            draw_music_symbol(AllegroFlare::FontBravura::f_clef, start_x+x_cursor, y - staff_line_distance, color, font_size_px);
         }
         x_cursor += get_music_symbol_width(AllegroFlare::FontBravura::f_clef);
         continue;
      }
      case '~': // TODO: This should be moved to a deferred rendered object
      {
         // TODO: Render a tie to the next note
         float start_y = y + staff_line_distance*2; // TODO: Provide an accurate start y for this tie
         float length = 100;
         float height = 20;
         float narrow_line_thickness = staff_line_thickness * 0.75;
         float thick_line_thickness = staff_line_thickness * 1.5;

         AllegroFlare::MusicNotation::TieRenderer tie_renderer(
            { (float)start_x+x_cursor, start_y },
            length,
            height,
            color,
            narrow_line_thickness,
            thick_line_thickness
         );
         tie_renderer.render();
         continue;
      }
      default: one_off_render_token_found = false; break;
      }



      // Capture note and/or notes

      if (note_info_accumulated_and_ready_for_render)
      {



      // look ahead to count the number of consecutive dots
      // TODO: Take this section and move it ahead of the rendering (or extract the code below it)

      int look_ahead_delta = 1;
      while (i+look_ahead_delta < (int)content.size())
      {
         if (content[i+1] == '.')
         {
            num_dots++;
            i++;
         }
         else break;
      }



      // If the symbol is singular, put it into a "multi_note" cluster group so it can be handled by the renderer

      if (multi_note.empty())
      {
         // Calculate the final staff_position including the octave
         int result_staff_pos = current_note_staff_position + (current_octave * 7);

         // Freeze rests to staff_pos = 0
         if (current_note_is_rest && force_rest_to_0_pos) result_staff_pos = 0;

         // For rhythmic staff, fix the staff position to 0
         if (rhythm_only) result_staff_pos = 0;

         multi_note.push_back(
            PitchToken{
               result_staff_pos,
               current_accidental,
               current_accidental_natural
               //.staff_position = result_staff_pos,
               //.accidental = current_accidental,
               //.accidental_natural = current_accidental_natural
            }
         );

         // Reset the accidentals now that they've been used
         current_accidental = 0;
         current_accidental_natural = false;
      }




      // Draw the actual note fragment

      float result_render_width = draw_note_fragment(
            start_x + x_cursor,
            y,
            multi_note,
            current_note_is_rest,
            current_note_duration,
            num_dots,
            freeze_stems_up,
            staff_line_thickness,
            staff_color,
            color,
            font_size_px
         );

      x_cursor += result_render_width;

      } // if (note_info_accumulated_and_ready_for_render)

      note_info_accumulated_and_ready_for_render = false;
   }



   // Draw the staff lines

   if (rhythm_only) draw_line(start_x, y, start_x+x_cursor, y, staff_color, std::max(1.0f, staff_line_thickness));
   else draw_staff_lines(start_x, y, x_cursor, staff_line_distance, staff_color, staff_line_thickness);



   // Return the length of the rendered measure

   return x_cursor;
}



void MusicNotation::set_staff_line_distance(float staff_line_distance)
{
   this->staff_line_distance = staff_line_distance;
   // TODO: Find out how to know when quarter_note_spacing should be automatically updated
   quarter_note_spacing = staff_line_distance * 5;
}



void MusicNotation::draw_ledger_lines_to(
      float x,
      float y,
      int staff_pos,
      float staff_line_thickness,
      float head_width,
      const ALLEGRO_COLOR &color
   )
{
   using std::max;
   float hwidth = staff_line_distance*2.4 / 2;
   //ALLEGRO_COLOR color = color::green;
   //float yoffset = -0.5;
   float yoffset = 0;
   float thickness = max(1.0f, staff_line_thickness);

   x += head_width/2;

   // for performance reasons, we'll cap the number of lines to a reasonable number
   const int MAX_LINES_TO_DRAW = 60;
   int lines_drawn = 0;

   for (int i=3; i<abs(staff_pos/2)+1; i++)
   {
      if (staff_pos > 0)
      {
         draw_line(
            x-hwidth,
            y-staff_line_distance*i+yoffset,
            x+hwidth,
            y-staff_line_distance*i+yoffset,
            color,
            thickness
         );
      }
      else
      {
         draw_line(
            x-hwidth,
            y+staff_line_distance*i+yoffset,
            x+hwidth,
            y+staff_line_distance*i+yoffset,
            color,
            thickness
         );
      }

      if (++lines_drawn > MAX_LINES_TO_DRAW) break;
   }
}



void MusicNotation::draw_staff_lines(
      float x,
      float y,
      float width,
      float line_distance,
      const ALLEGRO_COLOR &color,
      float thickness
   )
{
   thickness = std::max<float>(1.0f, thickness);

   draw_line(x, y, x+width, y, color, thickness);
   for (int i=1; i<3; i++)
   {
      draw_line(x, y-line_distance*i, x+width, y-line_distance*i, color, thickness);
      draw_line(x, y+line_distance*i, x+width, y+line_distance*i, color, thickness);
   }
}



void MusicNotation::draw_accidental(int32_t symbol, float x, float y, const ALLEGRO_COLOR &color, float font_size_px)
{
   draw_music_symbol(symbol, x, y, color, font_size_px);
}



void MusicNotation::draw_music_symbol(int32_t symbol, float x, float y, const ALLEGRO_COLOR &color, float font_size_px)
{
   ALLEGRO_FONT *font_bravura = obtain_font_bravura();
   if (!drawing_interface)
   {
      draw_unicode_char(
         font_bravura,
         color,
         symbol,
         ALLEGRO_FLAGS_EMPTY,
         x,
         (int_cast_y) ? (int)(y-al_get_font_ascent(font_bravura)) : (y-al_get_font_ascent(font_bravura))
      );
   }
   else
   {
      drawing_interface->draw_ustr_chr(symbol, x, y, 0, 0, color, "Bravura", font_size_px, font_bravura);
   }
}



void MusicNotation::draw_line(float x1, float y1, float x2, float y2, const ALLEGRO_COLOR &color, float thickness)
{
   drawing_interface->draw_line(x1, y1, x2, y2, color, thickness);
}



int MusicNotation::get_music_symbol_width(int32_t symbol)
{
   ALLEGRO_FONT *font_bravura = obtain_font_bravura();

   static ALLEGRO_USTR *ustr = NULL;
   if (!ustr) ustr = al_ustr_new("");
   al_ustr_set_chr(ustr, 0, symbol);
   return al_get_ustr_width(font_bravura, ustr);
}



ALLEGRO_FONT *MusicNotation::obtain_font_bravura()
{
   if (!font_bin) AllegroFlare::Logger::throw_error("MusicNotation::obtain_font_bravura: error: missing font_bin");

   int font_size = -(staff_line_distance*4 * 4);
   std::stringstream font_identifier;
   font_identifier << "Bravura.otf " << font_size;
   return font_bin->operator[](font_identifier.str());
}



float MusicNotation::get_quarter_note_spacing()
{
   return this->quarter_note_spacing;
}



void MusicNotation::set_quarter_note_spacing(int quarter_note_spacing)
{
   this->quarter_note_spacing = quarter_note_spacing;
}



void MusicNotation::set_spacing_method(spacing_method_t method)
{
   this->spacing_method = method;
}



char MusicNotation::duration_denominator_to_char(int denominator)
{
   switch (denominator)
   {
   case 1: return 'w'; break;
   case 2: return 'h'; break;
   case 4: return 'q'; break;
   case 8: return 'e'; break;
   case 16: return 's'; break;
   case 32: return 't'; break;
   case 64: return 'i'; break;
   default: return 'q';
   }
}



} // namespace MusicNotation
} // namespace AllegroFlare



