



#include <allegro_flare/allegro_flare.h>
#include <allegro_flare/screen.h>
#include <allegro5/allegro_font.h>
#include <AllegroFlare/FontBin.hpp>




using namespace allegro_flare;



class UnicodeFontViewerExample : public Screen
{
private:
   FontBin fonts;
   ALLEGRO_FONT *unicode_font, *ui_font, *ui_font_mini;
   int32_t unicode_range_start;

public:
   UnicodeFontViewerExample(Display *display, std::string font_identifier_str);

   void draw_unicode_character(ALLEGRO_FONT *font, ALLEGRO_COLOR color, int32_t icon, int flags, float x, float y);

   void primary_timer_func() override;

   void key_char_func() override;
};




UnicodeFontViewerExample::UnicodeFontViewerExample(Display *display, std::string font_identifier_str)
   : Screen(display)
   , fonts()
   , unicode_font(fonts[font_identifier_str])
   , ui_font(nullptr)
   , ui_font_mini(nullptr)
   , unicode_range_start(0x1D000)
{
   fonts.set_path("data/fonts");

   ui_font = fonts["DroidSans.ttf 20"];
   ui_font_mini = fonts["DroidSans.ttf 9"];
}




void UnicodeFontViewerExample::draw_unicode_character(ALLEGRO_FONT *font, ALLEGRO_COLOR color, int32_t icon, int flags, float x, float y)
{
   static ALLEGRO_USTR *ustr = NULL;
   if (!ustr) ustr = al_ustr_new("");
   al_ustr_set_chr(ustr, 0, icon);
   al_draw_ustr(font, color, x, y, flags, ustr);
}




void UnicodeFontViewerExample::primary_timer_func()
{
   int32_t unicode_range_end = unicode_range_start+0x00ff;

   al_draw_text(ui_font, color::white, 20, 20, ALLEGRO_FLAGS_EMPTY, "Press the RIGHT ARROW and LEFT ARROW keys to flip through the pages");
   al_draw_text(ui_font, color::white, 20, 60, ALLEGRO_FLAGS_EMPTY, tostring("range " + tostring(unicode_range_start) + "-" + tostring(unicode_range_end)).c_str());

   //int y=90;
   int line = 0;
   int num_rows = 30;
   int line_height = 80;
   int row_width = 45;
   int row = 0;
   for (int32_t character=unicode_range_start; character<=unicode_range_end; character++)
   {
      int x = 100 + row*row_width;
      int y = 100 + line*line_height;
      draw_unicode_character(unicode_font, color::black, character, ALLEGRO_ALIGN_CENTER, x, y);
      al_draw_text(ui_font_mini, color::white, x, y, ALLEGRO_FLAGS_EMPTY, tostring(character).c_str());
      row += 1;
      if (row > num_rows) { row = 0; line++; }
   }
}




void UnicodeFontViewerExample::key_char_func()
{
   switch(Framework::current_event->keyboard.keycode)
   {
   case ALLEGRO_KEY_RIGHT:
      unicode_range_start += 0x0100;
      break;
   case ALLEGRO_KEY_LEFT:
      unicode_range_start -= 0x0100;
      break;
   }
}




int main(int argc, char **argv)
{
   Framework::initialize();
   Display *display = Framework::create_display();
   UnicodeFontViewerExample *program = new UnicodeFontViewerExample(display, "Bravura.otf 40");
   Framework::run_loop();
   return 0;
}




