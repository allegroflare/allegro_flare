

#include <AllegroFlare/MusicNotation/MusicNotation.hpp>



#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>
#include <AllegroFlare/FontBravura.hpp>
#include <AllegroFlare/Color.hpp>
#include <AllegroFlare/Useful.hpp>
#include <AllegroFlare/UsefulPHP.hpp>
#include <AllegroFlare/Logger.hpp>
#include <AllegroFlare/Testing/Comparison/ALLEGRO_COLOR.hpp>
#include <AllegroFlare/MusicNotation/TieRenderer.hpp>




static ALLEGRO_COLOR infer_color_name_or_hex(const std::string &name_or_hex)
{
   static const ALLEGRO_COLOR black{0, 0, 0, 1};
   if (strcmp("black", name_or_hex.c_str()) == 0) return black;

   // try name
   ALLEGRO_COLOR result = al_color_name(name_or_hex.c_str());
   // If al_color_name() returned black, try hex
   if (result == black) return al_color_html(name_or_hex.c_str());
   return result;
}




/*
static struct PitchToken
{
public:
   int staff_position;
   int accidental;
   bool accidental_natural;
};
*/



static struct NoteToken
{
public:
   int staff_position;
   int accidental;
   bool accidental_natural;
   int octave;
};



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



int MusicNotation::calculate_preferred_stem_direction(std::vector<PitchToken> multi_note)
{
   return 0;
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
      // Calculate our max and min staff position

      int min_staff_pos = get_min_staff_position(multi_note);
      int max_staff_pos = get_max_staff_position(multi_note);
      bool max_and_min_are_above = min_staff_pos < 0 && max_staff_pos < 0;
      bool max_and_min_are_below = min_staff_pos > 0 && max_staff_pos > 0;
      bool current_note_is_below_center_line = false;
      if (min_staff_pos == max_staff_pos == 0) current_note_is_below_center_line = true;
      else if (max_and_min_are_above) current_note_is_below_center_line = false;
      else if (max_and_min_are_below) current_note_is_below_center_line = true;
      else if (abs(min_staff_pos) < abs(max_staff_pos)) current_note_is_below_center_line = false; // TODO validate this



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

         // use the flipped stem version (if necessairy)
         if (symbol >= (uint32_t)AllegroFlare::FontBravura::half_note && (current_note_is_below_center_line) && !freeze_stems_up)
         //if (symbol >= (uint32_t)AllegroFlare::FontBravura::half_note && (staff_pos >= 0) && !freeze_stems_up)
         {
            symbol += 1;
         }
      }


      // Draw ledger lines

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



      // Render the notehead(s), accidentals, and dots

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

         // Draw the note

         draw_music_symbol(
            symbol,
            x,
            y + calculate_staff_position_y_offset(note.staff_position),
            color,
            font_size_px
         );

         // Draw the dots

         float dots_x_cursor = 0;
         bool note_head_is_on_line = (note.staff_position % 2 == 0);
         float dot_vertical_adjustment_from_being_on_line = note_head_is_on_line ? staff_line_distance * -0.5f : 0.0f;
         if (num_dots > 0)
         {
            dots_x_cursor += get_music_symbol_width(symbol) + get_music_symbol_width(AllegroFlare::FontBravura::dot);
         }
         for (int i=0; i<num_dots; i++)
         {
            // TODO: Alter the x-position based on the offset for this notehead
            draw_music_symbol(
               AllegroFlare::FontBravura::dot,
               x+dots_x_cursor,
               y + calculate_staff_position_y_offset(note.staff_position) + dot_vertical_adjustment_from_being_on_line,
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

      //} // if (note_info_accumulated_and_ready_for_render)

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
   int start_x = x;
   int x_cursor = 0;
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

            if (text_before_equals.compare("color") == 0) color = color::name(text_after_equals.c_str());
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
               .staff_position = result_staff_pos,
               .accidental = current_accidental,
               .accidental_natural = current_accidental_natural
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



