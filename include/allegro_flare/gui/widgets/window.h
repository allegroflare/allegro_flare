#ifndef __UI_WINDOW_HEADER
#define __UI_WINDOW_HEADER




#include <allegro_flare/gui/widget.h>




class UIWindow : public UIWidget
{
protected:
   ALLEGRO_COLOR background_color;

public:
   UIWindow(UIWidget *parent, float x, float y, float w, float h);

   void on_draw() override;
   void on_focus() override;
};




#endif
