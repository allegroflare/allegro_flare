#ifndef FGUI_CHECKBOX_HEADER
#define FGUI_CHECKBOX_HEADER




#include <allegro_flare/gui/widget.h>




class FGUICheckbox : public FGUIWidget
{
protected:
   bool checked;
   placement2d check_placement;
   ALLEGRO_COLOR check_color;
   float check_opacity;

public:
   FGUICheckbox(FGUIWidget *parent, float x, float y, float size);

   void toggle();
   bool is_checked();
   bool set_as_checked();
   bool set_as_unchecked();
   void set_color(ALLEGRO_COLOR color);

   void on_click() override;
   void on_key_char() override;
   void on_joy_down() override;
   void on_draw() override;
   void on_change() override;
};





#endif
