#ifndef __UI_PICKING_BUFFER_HEADER
#define __UI_PICKING_BUFFER_HEADER




#include <allegro_flare/widget.h>




class UIPickingBuffer : public UIWidget
{
public:
   static const int ID_MAX = 16777216;

   ALLEGRO_BITMAP *surface_render;
   int mouse_x, mouse_y;
   int depth;
   bool draw_surface_render;

   UIPickingBuffer(UIWidget *parent, float x, float y, int w, int h, int depth);
   void create_new_surface(int w, int h, int depth);
   void clear_surface();
   void on_mouse_move(float x, float y, float dx, float dy) override;
   void on_click() override;
   void on_draw() override;

   static int decode_id(ALLEGRO_COLOR color);
   static ALLEGRO_COLOR encode_id(int id);

   static std::string compose_on_click_id_message(int id);
   static int extract_on_click_id(std::string message);
   static bool is_on_click_id_message(std::string message);

private:
   static std::string MESSAGE_HEADER;
};




#endif
