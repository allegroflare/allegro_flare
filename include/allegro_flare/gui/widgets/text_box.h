#ifndef __AF_TEXT_BOX_OLD_HEADER
#define __AF_TEXT_BOX_OLD_HEADER




#include <string>
#include <allegro_flare/gui/widget.h>
#include <allegro5/allegro_font.h>




class FGUITextBox : public FGUIWidget
{
protected:
   ALLEGRO_FONT *font;
   ALLEGRO_COLOR text_color;
   std::string text;

public:
   FGUITextBox(FGUIWidget *parent, float x, float y, float w, float h, std::string text);

   void set_text(std::string text);
   void set_font(ALLEGRO_FONT *font);
   void set_text_color(ALLEGRO_COLOR color);

   std::string get_text();

   void on_draw() override;
};







#endif

