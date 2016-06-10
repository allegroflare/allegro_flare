#ifndef __AF_MUSIC_NOTATION_HEADER
#define __AF_MUSIC_NOTATION_HEADER




#include <string>
#include <vector>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_font.h>
#include <allegro_flare/drawing_interface.h>




class MusicNotation
// TODO: escape all functions properly when there is drawing_interface==NULL;
{
public:
   enum spacing_method_t
   {
      SPACING_UNDEF = 0,
      SPACING_FIXED,
      SPACING_AESTHETIC
   };

private:
   class Beam
   {
   private:
      struct beam_point
      {
         public:
            float note_x;
            float note_y;
            float note_head_width;
            int note_staff_pos;
            beam_point(float note_x, float note_y, int note_staff_pos, float staff_line_distance, float note_head_width);
      };

      std::vector<beam_point> beam_points; // assuming left-to-right

   public:
      void add_beam_point(float note_x, float y_center, int note_staff_pos, float note_head_width, MusicNotation *notation_context);
      void clear();
      void draw(MusicNotation *notation_context, ALLEGRO_COLOR color);
      int get_num_points();
   };

   DrawingInterface *drawing_interface;

   // render metrics (all are relative to staff_line_distance)
   float staff_line_distance;
   float staff_line_thickness; // = staff_line_distance * 0.1
   float font_size_px; // = int(staff_line_distance*4) * 4
   float quarter_note_spacing; // = staff_line_distance * 30
   float stem_thickness; // = staff_line_distance * 0.2
   float beam_thickness; // = staff_line_distance * 0.4
   ALLEGRO_FONT *font_bravura; // size = staff_line_distance * 4
   spacing_method_t spacing_method;

   float _get_staff_position_offset(int staff_position);

   // render state
   int current_note_duration;
   bool current_note_is_rest;
   int current_accidental;
   int cursor_pos;
   bool int_cast_y;
   bool ignore_spaces;

   friend class beam_point;


   // meh
   Beam just_one_beam;

public:
   MusicNotation(DrawingInterface *drawing_interface=NULL, float staff_line_distance=10, std::string bravura_font_location="data/fonts/Bravura.otf");
   ~MusicNotation();

   int draw(float x, float y, std::string content, std::string output_file_basename="");

   void set_staff_line_distance(float distance);

   void draw_ledger_lines_to(float x, float y, int staff_pos, float head_width, const ALLEGRO_COLOR &color);
   void draw_staff_lines(float x, float y, float width, float line_distance, const ALLEGRO_COLOR &color, float thickness);
   void draw_music_symbol(int32_t symbol, float x, float y, const ALLEGRO_COLOR &color);
   int get_music_symbol_width(int32_t symbol);

   void draw_line(float x1, float y1, float x2, float y2, const ALLEGRO_COLOR &color, float thickness);
   void use_drawing_interface(DrawingInterface *drawing_interface);

   bool bravura_is_valid();


   // getters and setters

   float get_quarter_note_spacing();
   void set_spacing_method(spacing_method_t method);

   static float get_duration_fixed_width(int duration, float quarter_note_width, int num_dots);
   char duration_denominator_to_char(int denominator);
};




#endif
