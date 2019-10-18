#ifndef __UI_WINDOW_HEADER
#define __UI_WINDOW_HEADER




#include <allegro_flare/widget.h>




namespace allegro_flare
{
   class UIWindow : public UIWidget
   {
   protected:
      ALLEGRO_COLOR background_color;
      bool bring_to_front_on_focus;

   public:
      UIWindow(UIWidget *parent, float x, float y, float w, float h);
      void set_bring_to_front_on_focus(bool val=false);

      void on_draw() override;
      void on_focus() override;
   };
}



#endif
