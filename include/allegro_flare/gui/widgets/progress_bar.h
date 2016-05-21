#ifndef __UI_PROGRESS_BAR_HEADER
#define __UI_PROGRESS_BAR_HEADER




#include <allegro_flare/gui/widget.h>




class UIProgressBar : public UIWidget
{
protected:
   float val; // val from [0 - 1]
   float update_speed;
   ALLEGRO_COLOR bar_color;

public:
   UIProgressBar(UIWidget *parent, float x, float y, float w, float h);

   void set_val(float unit_val); // val from [0 - 1]
   void set_val(float _val, float min, float max);
   void set_update_speed(float speed_in_sec=0.4);

   void on_draw() override;
};



#endif
