#ifndef __FGUI_DIAL_HEADER
#define __FGUI_DIAL_HEADER




#include <allegro_flare/gui/widget.h>




class FGUIDial : public FGUIWidget
{
protected:
   float val;
   float radius;
   float sensitivity;

public:
   FGUIDial(FGUIWidget *parent, float x, float y, float size);

   void set_value(float unit_val);
   float get_value();

   void on_draw() override;
   void on_drag(float x, float y, float dx, float dy) override;
   void on_change() override;
   void on_mouse_down() override;
   void on_mouse_up() override;
};





#endif

