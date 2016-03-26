#ifndef __AF_SCROLL_AREA_HEADER
#define __AF_SCROLL_AREA_HEADER




#include <allegro5/bitmap.h>

#include <allegro_flare/gui/widget.h>

class FGUIScrollBar;




class FGUIScrollArea : public FGUIWidget
{
protected:
   FGUIScrollBar *v_slider;
   FGUIWidget *canvas;
   ALLEGRO_BITMAP *canvas_render;

public:
   FGUIScrollArea(FGUIWidget *parent, float x, float y, float w, float h, FGUIWidget *content_parent);

   FGUIWidget *get_canvas();
   void render_canvas();

   void mouse_axes_func(float mx, float my, float mdx, float mdy) override;
   void on_timer() override;
   void on_mouse_wheel() override;
   void draw_func() override;
};





#endif
