#ifndef __UI_SCROLL_AREA_HEADER
#define __UI_SCROLL_AREA_HEADER




#include <allegro5/bitmap.h>

#include <allegro_flare/gui/widget.h>

class UIScrollBar;




class UIScrollArea : public UIWidget
{
protected:
   UIScrollBar *v_slider;
   UIWidget *canvas;
   ALLEGRO_BITMAP *canvas_render;

public:
   UIScrollArea(UIWidget *parent, float x, float y, float w, float h, UIWidget *content_parent);

   UIWidget *get_canvas();
   void render_canvas();

   void mouse_axes_func(float mx, float my, float mdx, float mdy) override;
   void on_timer() override;
   void on_mouse_wheel() override;
   void draw_func() override;
};





#endif
