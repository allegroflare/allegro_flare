#ifndef __AFGUI_SLIDER_HEADER
#define __AFGUI_SLIDER_HEADER




#include <allegro_flare/gui.h>




class FGUIVerticalSlider : public FGUIWidget
{
protected:
   float val;
   float mouse_y;
   int num_notches;
   float wheel_sensitivity;
   ALLEGRO_COLOR slider_color;

public:
   FGUIVerticalSlider(FGUIWidget *parent, float x, float y, float w, float h);

   void set_notches(int num_notches);
   void set_val_by_y(float y);
   void set_val(float val);
   float get_val();
   float get_val(float min, float max); // a helper function, places the normalized value within the [min-max] domain.
   void set_color(ALLEGRO_COLOR col);

   void on_draw() override;
   void on_mouse_move(float x, float y, float dx, float dy) override;
   void on_mouse_down() override;
   void on_drag(float x, float y, float dx, float dy) override;
   void on_key_char() override;
   void on_mouse_wheel() override;
};









#endif
