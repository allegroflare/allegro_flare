#ifndef __UI_DIAL_HEADER
#define __UI_DIAL_HEADER




#include <allegro_flare/widget.h>




namespace allegro_flare
{
   class UIDial : public UIWidget
   {
   protected:
      float val;
      float radius;
      float sensitivity;

   public:
      UIDial(UIWidget *parent, float x, float y, float size);

      void set_value(float unit_val);
      float get_value();

      void on_draw() override;
      void on_drag(float x, float y, float dx, float dy) override;
      void on_change() override;
      void on_mouse_down() override;
      void on_mouse_up() override;
   };
}




#endif
