

#include <allegro5/allegro_font.h>
#include <AllegroFlare/Screens/Base.hpp>
#include <AllegroFlare/Frameworks/Full.hpp>
#include <AllegroFlare/FontBin.hpp>
#include <AllegroFlare/Color.hpp>



class UnicodeFontViewerExample : public AllegroFlare::Screens::Base
{
private:
   AllegroFlare::FontBin fonts;
   std::string font_identifier_str;
   ALLEGRO_FONT *unicode_font, *ui_font, *ui_font_mini;
   int32_t unicode_range_start;

public:
   UnicodeFontViewerExample(std::string font_identifier_str)
      : AllegroFlare::Screens::Base()
      , fonts()
      , font_identifier_str(font_identifier_str)
      , unicode_font(nullptr)
      , ui_font(nullptr)
      , ui_font_mini(nullptr)
      , unicode_range_start(0x1D100) // bravura characters start at range -> unicode_range_start(0x1D100)
   {}

   ~UnicodeFontViewerExample()
   {
      fonts.clear();
   }

   void init()
   {
      fonts.set_full_path("/Users/markoates/Repos/allegro_flare/bin/data/fonts");

      unicode_font = fonts[font_identifier_str];
      ui_font = fonts["Inter-Medium.ttf 20"];
      ui_font_mini = fonts["Inter-Medium.ttf 9"];
   }

   void draw_unicode_character(ALLEGRO_FONT *font, ALLEGRO_COLOR color, int32_t icon, int flags, float x, float y)
   {
      static ALLEGRO_USTR *ustr = NULL;
      if (!ustr) ustr = al_ustr_new("");
      al_ustr_set_chr(ustr, 0, icon);
      al_draw_ustr(font, color, x, y, flags, ustr);
   }

   void primary_timer_func() override
   {
      int32_t unicode_range_end = unicode_range_start+0x00ff;
      ALLEGRO_COLOR white = AllegroFlare::Color::White;
      ALLEGRO_COLOR black = AllegroFlare::Color::Black;
      std::stringstream range_string;

      range_string << "you are currently viewing the range " << unicode_range_start << "-" << unicode_range_end;

      al_draw_text(ui_font, white, 20, 20, 0, "Press the RIGHT ARROW and LEFT ARROW keys to flip through the pages");
      al_draw_text(ui_font, white, 20, 60, 0, range_string.str().c_str());

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
         draw_unicode_character(unicode_font, white, character, ALLEGRO_ALIGN_CENTER, x, y);
         std::stringstream character_number_as_str;
         character_number_as_str << character;
         al_draw_text(ui_font_mini, white, x, y, 0, character_number_as_str.str().c_str());
         row += 1;
         if (row > num_rows) { row = 0; line++; }
      }
   }

   void key_char_func(ALLEGRO_EVENT *ev) override
   {
      switch(ev->keyboard.keycode)
      {
      case ALLEGRO_KEY_RIGHT:
         unicode_range_start += 0x0100;
         break;
      case ALLEGRO_KEY_LEFT:
         unicode_range_start -= 0x0100;
         break;
      }
   }
};


int main(int argc, char **argv)
{
   AllegroFlare::Frameworks::Full framework;
   framework.initialize();

   UnicodeFontViewerExample unicode_font_viewer_example("Bravura.otf 40");
   unicode_font_viewer_example.init();
   framework.register_screen("unicode_font_viewer_example", &unicode_font_viewer_example);

   framework.activate_screen("unicode_font_viewer_example");

   framework.run_loop();

   return 0;
}


