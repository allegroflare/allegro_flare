#ifndef __UI_TEXT_HEADER
#define __UI_TEXT_HEADER




#include <allegro5/allegro_font.h>
#include <allegro5/allegro_color.h>

#include <allegro_flare/gui/widget.h>




class UIText : public UIWidget
{
protected:
   std::string text;
   ALLEGRO_FONT *font;
   ALLEGRO_COLOR font_color;
   
public:
   UIText(UIWidget *parent, float x, float y, std::string text);

   std::string get_text();

   void set_font_and_text(ALLEGRO_FONT *font, std::string text); // used to be set()
   void set_text(std::string text);
   void set_font(ALLEGRO_FONT *font);
   void set_font_color(const ALLEGRO_COLOR &color);

   void on_draw() override;
};




#endif
