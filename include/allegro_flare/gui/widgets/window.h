#ifndef FGUI_WINDOW_HEADER
#define FGUI_WINDOW_HEADER




#include <allegro_flare/gui/widget.h>




class FGUIWindow : public FGUIWidget
{
protected:
   ALLEGRO_COLOR background_color;

public:
   FGUIWindow(FGUIWidget *parent, float x, float y, float w, float h);

   void on_draw() override;
   void on_focus() override;
};




#endif
