


#include <AllegroFlare/DrawingInterfaces/Allegro5.hpp>


#include <AllegroFlare/Useful.hpp>



using namespace AllegroFlare;


namespace AllegroFlare
{
namespace DrawingInterfaces
{



   Allegro5::Allegro5()
      : Base("DrawingInterfaces::Allegro5")
   {}




   Allegro5::~Allegro5()
   {}




   void Allegro5::prepare_surface(int surface_width, int surface_height)
   {
      // nothing is necessairy here
   }




   void Allegro5::finish_surface()
   {
      // nothing needed here
   }




   void Allegro5::draw_line(float x1, float y1, float x2, float y2, ALLEGRO_COLOR color, float thickness)
   {
      al_draw_line(x1, y1, x2, y2, color, thickness);
   }




   void Allegro5::draw_rectangle(float x1, float y1, float x2, float y2, ALLEGRO_COLOR outline_color, float thickness)
   {
      al_draw_rectangle(x1, y1, x2, y2, outline_color, thickness);
   }




   void Allegro5::draw_text(std::string text, float x, float y, float align_x, float align_y, ALLEGRO_COLOR color, std::string font_family, float font_size, ALLEGRO_FONT *font)
   {
      if (!font) return;
      int flags = 0;
      if (basically_equal(align_x, 0)) flags = ALLEGRO_FLAGS_EMPTY;
      al_draw_text(font, color, x, y - al_get_font_ascent(font), flags, text.c_str());
   }




   void Allegro5::draw_ustr_chr(int32_t ustr_char, float x, float y, float align_x, float align_y, ALLEGRO_COLOR color, std::string font_family, float font_size, ALLEGRO_FONT *font)
   {
      if (!font) return;
      ALLEGRO_USTR *ustr = al_ustr_new("");
      al_ustr_set_chr(ustr, 0, ustr_char);
      al_draw_ustr(font, color, x, y - al_get_font_ascent(font), ALLEGRO_FLAGS_EMPTY, ustr);
      al_ustr_free(ustr);
   }




   bool Allegro5::save_file(std::string file_basename)
   {
      // nothing needed here
      return true;
   }




   std::string Allegro5::get_output()
   {
      // nothing needed here
      return "";
   }



} // namespace DrawingInterfaces
} // namespace AllegroFlare



