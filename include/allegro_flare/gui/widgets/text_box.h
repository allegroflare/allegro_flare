#ifndef __UI_TEXT_BOX_HEADER
#define __UI_TEXT_BOX_HEADER




#include <string>
#include <allegro_flare/gui/widget.h>
#include <allegro5/allegro_font.h>




class UITextBox : public UIWidget
{
protected:
   ALLEGRO_FONT *font;
   ALLEGRO_COLOR text_color;
   std::string text;

public:
   UITextBox(UIWidget *parent, float x, float y, float w, float h, std::string text);

   void set_text(std::string text);
   void set_font(ALLEGRO_FONT *font);
   void set_text_color(ALLEGRO_COLOR color);

   std::string get_text();

   void on_draw() override;
};




#endif
