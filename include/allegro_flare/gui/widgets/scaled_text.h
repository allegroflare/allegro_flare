#ifndef __UI_SCALED_TEXT_HEADER
#define __UI_SCALED_TEXT_HEADER




#include <allegro5/allegro_color.h>
#include <allegro_flare/gui/widget.h>




class UIScaledText : public UIWidget
{
protected:
   ALLEGRO_BITMAP *render;
   std::string font_filename;
   int font_size;
   float render_scale;
   ALLEGRO_COLOR font_color;
   std::string text;

   std::string _get_font_index_str();
   void refresh_render();

public:
   UIScaledText(UIWidget *parent, float x, float y, std::string text);

   void set_font_color(ALLEGRO_COLOR color);
   void set_text(std::string text);
   void set_font(std::string font_filename, int font_size);

   void on_draw() override;
};




#endif
