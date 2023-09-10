

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



namespace AllegroFlare
{
namespace MusicNotation
{



   float MusicNotation::_get_staff_position_offset(int staff_position)
   {
      return - staff_position * staff_line_distance * 0.5;
   }




   MusicNotation::MusicNotation(
         AllegroFlare::DrawingInterfaces::Base *drawing_interface,
         AllegroFlare::FontBin *font_bin,
         float staff_line_distance
      )
      : drawing_interface(drawing_interface)
      , staff_line_distance(staff_line_distance)
      , staff_line_thickness(staff_line_distance*0.1)
      , font_size_px((staff_line_distance*4) * 4)
      , quarter_note_spacing(staff_line_distance*5)
      , stem_thickness(staff_line_distance*0.15)
      , spacing_method(SPACING_AESTHETIC)
      , font_bin(font_bin)
      , current_note_duration(4)
      , current_note_is_rest(false)
      , current_accidental(0)
      , int_cast_y(true)
      , ignore_spaces(false)
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



   int MusicNotation::draw(float x, float y, std::string content, std::string output_file_basename)
   {
      if (!drawing_interface)
      {
         AllegroFlare::Logger::throw_error("MusicNotation::draw", "missing \"drawing_interface\"");
      }
      drawing_interface->prepare_surface(800, 500);

      int start_x = x;
      int x_cursor = 0;

      current_note_duration = 4;
      current_note_is_rest = false;
      uint32_t symbol = AllegroFlare::FontBravura::closed_note_head;
      uint32_t current_accidental_symbol = 0x0000;
      int current_octave = 0;
      bool force_rest_to_0_pos = true;
      bool rhythm_only = false;
      bool freeze_stems_up = false;
      ALLEGRO_COLOR color = color::white;
      ALLEGRO_COLOR staff_color = color::white;
      int num_dots = 0;
      int staff_pos = 0;

      for (int i=0; i<(int)content.size(); i++) // TODO make this an iterator
      {
         std::vector<int> multi_note;
         staff_pos = 0;
         num_dots = 0;

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
            // settings can be specified inline when contained in {} curly braces.
            // each setting is delimited by a space

            // find the closing brace
            std::size_t pos_opening_brace = i;
            std::size_t pos_closing_brace = content.find('}', pos_opening_brace);

            if (pos_closing_brace == std::string::npos)
            {
               // closing brace not found, output an error and abort continuing to render
               std::cout << "music string parse error: closing brace not found" << std::endl;
               i = content.size();
               continue;
            }
            else
            {
               std::string braced_string = content.substr(pos_opening_brace+1, pos_closing_brace - pos_opening_brace - 1);
               // TODO: parse the braced string for tokens here

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
         }
         case ' ': // Space
         {
            if (!ignore_spaces) x_cursor += staff_line_distance;
            continue;
         }
         case '$': // 4/4 or shift 4
         {
            draw_music_symbol(62692, start_x+x_cursor, y + staff_line_distance*2, color);
            draw_music_symbol(62693, start_x+x_cursor, y + staff_line_distance*2, color);
            x_cursor += get_music_symbol_width(62692);
            continue;
         }
         case '@': // 2/4 or shift 2
         {
            draw_music_symbol(62689, start_x+x_cursor, y + staff_line_distance*2, color);
            draw_music_symbol(62692, start_x+x_cursor, y + staff_line_distance*2, color);
            x_cursor += get_music_symbol_width(62692);
            continue;
         }
         case '#': // 3/4 or shift 3
         {
            draw_music_symbol(62691, start_x+x_cursor, y + staff_line_distance*2, color);
            draw_music_symbol(62692, start_x+x_cursor, y + staff_line_distance*2, color);
            x_cursor += get_music_symbol_width(62692);
            continue;
         }
         case '^': // 6/8 or shift 6
         {
            draw_music_symbol(62697, start_x+x_cursor, y + staff_line_distance*2, color);
            draw_music_symbol(62700, start_x+x_cursor, y + staff_line_distance*2, color);
            x_cursor += get_music_symbol_width(62697);
            continue;
         }
         case '~':
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
         case '|':
         {
            draw_music_symbol(AllegroFlare::FontBravura::barline, start_x+x_cursor, y + staff_line_distance*2, color);
            if (i != ((int)content.size()-1)) x_cursor += staff_line_distance*2;
            continue;
         }
         case ']':
         {
            draw_music_symbol(AllegroFlare::FontBravura::final_barline, start_x+x_cursor, y + staff_line_distance*2, color);
            x_cursor += get_music_symbol_width(AllegroFlare::FontBravura::final_barline);
            if (i != ((int)content.size()-1)) x_cursor += staff_line_distance;
            continue;
         }
         case '&':
         {
            if (rhythm_only) draw_music_symbol(AllegroFlare::FontBravura::percussion_clef_1, start_x+x_cursor, y, color);
            else draw_music_symbol(AllegroFlare::FontBravura::g_clef, start_x+x_cursor, y + staff_line_distance, color);
            x_cursor += get_music_symbol_width(AllegroFlare::FontBravura::g_clef);
            continue;
         }
         case '?':
         {
            if (rhythm_only) draw_music_symbol(AllegroFlare::FontBravura::percussion_clef_1, start_x+x_cursor, y, color);
            else draw_music_symbol(AllegroFlare::FontBravura::f_clef, start_x+x_cursor, y - staff_line_distance, color);
            x_cursor += get_music_symbol_width(AllegroFlare::FontBravura::f_clef);
            continue;
         }
         case '(':
         {
            // Scale degrees *not* in the [0-9] range can be contained in () parens.
            // Also, you can have multiple staff degrees for a single note by placing them in
            // parens separated by spaces i.g. "(0 4 -7 8 11 -16)"

            // find the closing brace
            std::size_t pos_opening_paren = i;
            std::size_t pos_closing_paren = content.find(')', pos_opening_paren);

            if (pos_closing_paren == std::string::npos)
            {
               // closing brace not found, output an error and abort continuing to render
               std::cout << "music string parse error: closing parenthesis ')' not found" << std::endl;
               i = content.size();
               continue;
            }
            else
            {
               std::string parened_string = content.substr(pos_opening_paren+1, pos_closing_paren - pos_opening_paren - 1);

               // set the cursor to the end of this braced section
               i = pos_closing_paren;

               std::vector<std::string> tokens = php::explode(" ", parened_string);
               for (auto &token : tokens)
                  multi_note.push_back(atoi(token.c_str()));

               staff_pos = atoi(tostring(parened_string).c_str()) + (current_octave * 7);
               break;
            }
         }
         default:
            staff_pos = atoi(tostring(content[i]).c_str()) + (current_octave * 7);
            break;
         }


         if (rhythm_only) staff_pos = 0;


         // look ahead to see if there are dots

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


         // beams

         // collect the beam data

         //if (adding_beams)
         //{
            //just_one_beam.add_beam_point(
               //start_x+x_cursor, y, staff_pos, get_music_symbol_width(AllegroFlare::FontBravura::quarter_note), this);
         //}



         // accidental

         //if (current_note_is_rest) current_accidental_symbol = 0x000;

         if (current_accidental_symbol != 0x0000)
         {
            draw_music_symbol(current_accidental_symbol, start_x+x_cursor-staff_line_distance*1.2, y + _get_staff_position_offset(staff_pos), color);
            current_accidental_symbol = 0x0000;
         }




         // notehead

         if (!current_note_is_rest)
         {
            //if (adding_beams)
            //{
               // render only note heads
               //if (current_note_duration >= 4) symbol = AllegroFlare::FontBravura::closed_note_head; 
               //else if (current_note_duration == 2) symbol = AllegroFlare::FontBravura::open_note_head; 
               //else if (current_note_duration == 1) symbol = AllegroFlare::FontBravura::whole_note_head;
            //}
            //else
            //{
               // render full notes
               if (current_note_duration == 8) symbol = AllegroFlare::FontBravura::eighth_note; 
               else if (current_note_duration == 4) symbol = AllegroFlare::FontBravura::quarter_note; 
               else if (current_note_duration == 2) symbol = AllegroFlare::FontBravura::half_note; 
               else if (current_note_duration == 1) symbol = AllegroFlare::FontBravura::whole_note;
               // use the flipped stem version (if necessairy)
               if (symbol >= (uint32_t)AllegroFlare::FontBravura::half_note && (staff_pos >= 0) && !freeze_stems_up)
                  symbol += 1;
            //}
         }
         else if (current_note_is_rest)
         {
            current_accidental = 0;
            if (current_note_duration == 4) symbol = AllegroFlare::FontBravura::quarter_rest; 
            else if (current_note_duration == 8) symbol = AllegroFlare::FontBravura::rest_8; 
            else if (current_note_duration == 2) symbol = AllegroFlare::FontBravura::half_rest; 
            else if (current_note_duration == 1) symbol = AllegroFlare::FontBravura::whole_rest;
         }


         if (current_note_is_rest && force_rest_to_0_pos) staff_pos = 0;


         //		set_blender(BLENDER_ADDITIVE);
         draw_ledger_lines_to(start_x+x_cursor, y, staff_pos, get_music_symbol_width(symbol), staff_color);
         //		set_blender(BLENDER_NORMAL);

         if (multi_note.empty())
            draw_music_symbol(symbol, start_x+x_cursor, y + _get_staff_position_offset(staff_pos), color);
         else
            for (unsigned i=0; i<multi_note.size(); i++)
               draw_music_symbol(symbol, start_x+x_cursor, y + _get_staff_position_offset(multi_note[i]), color);

         // draw the dots
         float dots_x_cursor = 0;
         if (num_dots > 0)
         {
            dots_x_cursor += get_music_symbol_width(symbol) + get_music_symbol_width(AllegroFlare::FontBravura::dot);
         }
         for (int i=0; i<num_dots; i++)
         {
            draw_music_symbol(AllegroFlare::FontBravura::dot, start_x+x_cursor+dots_x_cursor, y + _get_staff_position_offset(staff_pos), color);
            dots_x_cursor += get_music_symbol_width(AllegroFlare::FontBravura::dot) * 1.5;
         }



         // move the cursor over based on the spacing method
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
         //x_cursor += (((float)quarter_note_spacing / (current_note_duration))) * get_duration_scalar(current_note_duration);
      }

      //	set_blender(BLENDER_ADDITIVE);
      using std::max;
      if (rhythm_only) draw_line(start_x, y, start_x+x_cursor, y, staff_color, max(1.0f, staff_line_thickness));
      else draw_staff_lines(start_x, y, x_cursor, staff_line_distance, staff_color, staff_line_thickness);
      //al_draw_line(start_x-10, y, x+x_cursor+10, y, color::color(color::red, 0.3), 1.0);
      //	set_blender(BLENDER_NORMAL);


      drawing_interface->finish_surface();
      if (!output_file_basename.empty()) drawing_interface->save_file(output_file_basename);

      return x_cursor;
   }




   void MusicNotation::set_staff_line_distance(float distance)
   {
      throw std::runtime_error("MusicNotation::set_staff_line_distance: This method requires refactoring before it can "
                               "be used");

      // reload the font at the correct height
      //staff_line_distance = distance;
      //staff_line_thickness = distance * 0.1; // = staff_line_distance * 0.1
      //quarter_note_spacing = distance * 30; // = staff_line_distance * 30
      //if (font_bravura)
      //{
         //al_destroy_font(font_bravura);
         //font_bravura = al_load_font("data/music_notation/Bravura.otf", (int)(distance * 4), ALLEGRO_FLAGS_EMPTY);
      //}
   }




   void MusicNotation::draw_ledger_lines_to(float x, float y, int staff_pos, float head_width, const ALLEGRO_COLOR &color)
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
         if (staff_pos > 0) draw_line(x-hwidth, y-staff_line_distance*i+yoffset, x+hwidth, y-staff_line_distance*i+yoffset, color, thickness);
         else draw_line(x-hwidth, y+staff_line_distance*i+yoffset, x+hwidth, y+staff_line_distance*i+yoffset, color, thickness);

         if (++lines_drawn > MAX_LINES_TO_DRAW) break;
      }
   }




   void MusicNotation::draw_staff_lines(float x, float y, float width, float line_distance, const ALLEGRO_COLOR &color, float thickness)
   {
      float yoffset = 0.0; // sometimes 0.5?
      //yoffset = 0.5;
      //yoffset = -0.5;
      thickness = std::max<float>(1.0f, thickness);

      draw_line(x, y+yoffset, x+width, y+yoffset, color, thickness);
      for (int i=1; i<3; i++)
      {
         draw_line(x, y-line_distance*i+yoffset, x+width, y-line_distance*i+yoffset, color, thickness);
         draw_line(x, y+line_distance*i+yoffset, x+width, y+line_distance*i+yoffset, color, thickness);
      }
   }




   void MusicNotation::draw_music_symbol(int32_t symbol, float x, float y, const ALLEGRO_COLOR &color)
   {
      ALLEGRO_FONT *font_bravura = obtain_font_bravura();
      if (!drawing_interface)
      {
         draw_unicode_char(font_bravura, color, symbol, ALLEGRO_FLAGS_EMPTY, x, (int_cast_y) ? (int)(y-al_get_font_ascent(font_bravura)) : (y-al_get_font_ascent(font_bravura)));
      }
      else
      {
         drawing_interface->draw_ustr_chr(symbol, x, y, 0, 0, color, "Bravura", font_size_px, font_bravura);
      }
   }




   void MusicNotation::draw_line(float x1, float y1, float x2, float y2, const ALLEGRO_COLOR &color, float thickness)
   {
      drawing_interface->draw_line(x1, y1, x2, y2, color, thickness);
      //bravura::draw(font_bravura, color, symbol, NULL, x, (int_cast_y) ? (int)(y-al_get_font_ascent(font_bravura)) : (y-al_get_font_ascent(font_bravura)));
      //		drawing_interface->ustr_chr(symbol, x, y, 0, 0, color, "Bravura", font_size_px, font_bravura);
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


