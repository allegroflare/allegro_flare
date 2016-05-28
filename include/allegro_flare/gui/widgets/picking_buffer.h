#ifndef __AF_UI_PICKING_BUFFER_HEADER
#define __AF_UI_PICKING_BUFFER_HEADER



#include <allegro_flare/gui/widget.h>


class UIPickingBuffer : public UIWidget
{
public:
   static const int ID_MAX = 16777216;

   ALLEGRO_BITMAP *surface_render;
   int mouse_x, mouse_y;
   int depth;
   bool draw_surface_render;

   UIPickingBuffer(UIWidget *parent, float x, float y, int w, int h, int depth);
   void clear_surface();
   void on_mouse_move(float x, float y, float dx, float dy) override;
   void on_click() override;
   void on_draw() override;

   static int decode_id(ALLEGRO_COLOR color);
   static ALLEGRO_COLOR encode_id(int id);
};



#endif
