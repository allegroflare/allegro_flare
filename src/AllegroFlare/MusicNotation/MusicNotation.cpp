

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




static struct PitchToken
{
public:
   int staff_position;
   int accidental;
   bool accidental_natural; // TODO: Work in accidental natural
};



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
   bool current_note_is_rest = false;
   uint32_t symbol = AllegroFlare::FontBravura::closed_note_head;
   uint32_t current_accidental_symbol = 0x0000;

   bool force_rest_to_0_pos = true;
   bool rhythm_only = false;
   bool freeze_stems_up = false;
   ALLEGRO_COLOR color = color::white;
   ALLEGRO_COLOR staff_color = color::white;
   bool ignore_spaces = false;

   // More render state variables
   int current_octave = 0;
   int staff_pos = 0;
   int num_dots = 0;
   std::vector<PitchToken> multi_note;
   bool context_change_token_found = true;
   bool one_off_render_token_found = true;
   bool multinote_token_found = true;

   for (int i=0; i<(int)content.size(); i++)
   {
      multi_note.clear();
      num_dots = 0;


      // Current note context and render setting change token cases

      context_change_token_found = true;
      switch (content[i])
      {
      case 'w': current_note_duration = 1; continue;
      case 'h': current_note_duration = 2; continue;
      case 'q': current_note_duration = 4; continue;
      case 'e': current_note_duration = 8; continue;
      case 's': current_note_duration = 16; continue;
      case 't': current_note_duration = 32; continue;
      case 'i': current_note_duration = 64; continue;
      case 'r': current_note_is_rest = true; continue;
      case 'n': current_note_is_rest = false; continue;
      case '-': current_accidental_symbol = AllegroFlare::FontBravura::flat; continue;
      case '+': current_accidental_symbol = AllegroFlare::FontBravura::sharp; continue;
      case '=': current_accidental_symbol = AllegroFlare::FontBravura::natural; continue;
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

      multinote_token_found = true;
      switch (content[i])
      {
      case '(':
      {
         // TODO: Test this feature of multi_note

         // Scale degrees *not* in the [0-9] range can be contained in () parens.
         // Also, you can have multiple staff degrees for a single note by placing them in
         // parens separated by spaces i.g. "(0 4 -7 8 11 -16)"

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
            parsed_pitch_token.staff_position += (multi_note_local_octave * 7);

            multi_note.push_back(parsed_pitch_token);
         }

         break;
      }
      default: multinote_token_found = false; break;
      }



      // Assume this token is the staff position, and continue forward with the render

      bool assume_this_token_is_a_staff_position =
         (!context_change_token_found && !one_off_render_token_found && !multinote_token_found);
      if (assume_this_token_is_a_staff_position)
      {
         staff_pos = atoi(tostring(content[i]).c_str()) + (current_octave * 7);
      }



      // For rhythmic staff, fix the staff position to 0

      if (rhythm_only) staff_pos = 0;



      // look ahead to count the number of consecutive dots

      int look_ahead_delta = 1;
      while (i+look_ahead_delta < (int)content.size())
      {
         if (content[i+1] == '.')
         {
            num_dots++;
            i++;
            //look_ahead_delta++;
         }
         else break;
      }



      // Draw an accidental (to the left size of the x_cursor)

      bool accidental_is_present = (current_accidental_symbol != 0x0000);
      if (accidental_is_present)
      {
         draw_music_symbol(
            current_accidental_symbol,
            start_x+x_cursor-staff_line_distance*1.2,
            y + calculate_staff_position_y_offset(staff_pos),
            color,
            font_size_px
         );
         current_accidental_symbol = 0x0000;
      }



      // Calculate which primary symbol to render, a note-with-stem or rest

      if (current_note_is_rest)
      {
         if (current_note_duration == 4) symbol = AllegroFlare::FontBravura::quarter_rest;
         else if (current_note_duration == 8) symbol = AllegroFlare::FontBravura::rest_8;
         else if (current_note_duration == 2) symbol = AllegroFlare::FontBravura::half_rest;
         else if (current_note_duration == 1) symbol = AllegroFlare::FontBravura::whole_rest;
      }
      else // (!current_note_is_rest)
      {
         if (current_note_duration == 8) symbol = AllegroFlare::FontBravura::eighth_note;
         else if (current_note_duration == 4) symbol = AllegroFlare::FontBravura::quarter_note;
         else if (current_note_duration == 2) symbol = AllegroFlare::FontBravura::half_note;
         else if (current_note_duration == 1) symbol = AllegroFlare::FontBravura::whole_note;

         // use the flipped stem version (if necessairy)
         if (symbol >= (uint32_t)AllegroFlare::FontBravura::half_note && (staff_pos >= 0) && !freeze_stems_up)
         {
            symbol += 1;
         }
      }


      if (current_note_is_rest && force_rest_to_0_pos) staff_pos = 0;



      // Draw ledger lines

      draw_ledger_lines_to(
         start_x+x_cursor,
         y,
         staff_pos,
         staff_line_thickness,
         get_music_symbol_width(symbol),
         staff_color
      );



      // Draw symbol

      if (multi_note.empty())
      {
         draw_music_symbol(
            symbol,
            start_x+x_cursor,
            y + calculate_staff_position_y_offset(staff_pos),
            color,
            font_size_px
         );
      }
      else
      {
         // TODO: Replace "multi_note" to use staff position
         for (unsigned i=0; i<multi_note.size(); i++)
         {
            draw_music_symbol(
               symbol,
               start_x+x_cursor,
               y + calculate_staff_position_y_offset(multi_note[i].staff_position),
               color,
               font_size_px
            );
         }
      }



      // Draw the dots

      float dots_x_cursor = 0;
      bool note_head_is_on_line = (staff_pos % 2 == 0);
      float dot_vertical_adjustment_from_being_on_line = note_head_is_on_line ? staff_line_distance * -0.5f : 0.0f;
      if (num_dots > 0)
      {
         dots_x_cursor += get_music_symbol_width(symbol) + get_music_symbol_width(AllegroFlare::FontBravura::dot);
      }
      for (int i=0; i<num_dots; i++)
      {
         draw_music_symbol(
            AllegroFlare::FontBravura::dot,
            start_x+x_cursor+dots_x_cursor,
            y + calculate_staff_position_y_offset(staff_pos) + dot_vertical_adjustment_from_being_on_line,
            color,
            font_size_px
         );
         dots_x_cursor += get_music_symbol_width(AllegroFlare::FontBravura::dot) * 1.6;
      }



      // Move the cursor over based on the spacing method

      switch (spacing_method)
      {
         case SPACING_FIXED:
            x_cursor += get_duration_fixed_width(current_note_duration, quarter_note_spacing, num_dots);
         break;

         case SPACING_AESTHETIC:
         case SPACING_UNDEF:
         default:
            x_cursor += get_duration_aesthetic_width(current_note_duration, quarter_note_spacing, num_dots);
         break;
      }
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



