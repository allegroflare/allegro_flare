



#define ALLEGRO_UNSTABLE

#include <allegro_flare/gui/widgets/picking_buffer.h>

#include <sstream>
#include <allegro5/allegro_primitives.h>
#include <allegro_flare/gui/surface_areas/box.h>
#include <allegro_flare/useful.h> // for to_string




UIPickingBuffer::UIPickingBuffer(UIWidget *parent, float x, float y, int w, int h, int depth)
   : UIWidget(parent, new UISurfaceAreaBox(x, y, w, h))
   , surface_render(NULL)
   , mouse_x(0)
   , mouse_y(0)
   , draw_surface_render(true)
{
   attr.set(UI_ATTR__UI_WIDGET_TYPE, "UIPickingBuffer");
   attr.set("id", "PickingBuffer" + tostring(get_num_created_widgets()));

   create_new_surface(place.size.x, place.size.y, depth);
   clear_surface();
}




std::string UIPickingBuffer::MESSAGE_HEADER = "on_click_id ";




void UIPickingBuffer::create_new_surface(int w, int h, int depth)
{
   if (surface_render) al_destroy_bitmap(surface_render);

   int previous_depth = al_get_new_bitmap_depth();
   int previous_samples = al_get_new_bitmap_samples();
   ALLEGRO_STATE previous_state;
   al_store_state(&previous_state, ALLEGRO_STATE_BITMAP);

   al_set_new_bitmap_depth(depth);
   al_set_new_bitmap_samples(0);
   surface_render = al_create_bitmap(w, h);

   al_restore_state(&previous_state);
   al_set_new_bitmap_depth(previous_depth);
   al_set_new_bitmap_samples(previous_samples);
}




void UIPickingBuffer::clear_surface()
{
   ALLEGRO_STATE state;
   al_store_state(&state, ALLEGRO_STATE_TARGET_BITMAP);
   al_set_target_bitmap(surface_render);
   al_clear_to_color(color::transparent);
   al_restore_state(&state);
}




void UIPickingBuffer::on_mouse_move(float x, float y, float dx, float dy)
{
   place.transform_coordinates(&x, &y);
   mouse_x = x;
   mouse_y = y;
}




void UIPickingBuffer::on_click()
{
   if (surface_render)
   {
      if (mouse_x < 0 || mouse_x > al_get_bitmap_width(surface_render)) return;
      if (mouse_y < 0 || mouse_y > al_get_bitmap_height(surface_render)) return;

      int clicked_id = decode_id(al_get_pixel(surface_render, mouse_x, mouse_y));
      send_message_to_parent(UIPickingBuffer::compose_on_click_id_message(clicked_id));
   }
}




void UIPickingBuffer::on_draw()
{
   if (draw_surface_render)
   {
      al_draw_rectangle(0, 0, place.size.x, place.size.y, color::green, 8);
      al_draw_bitmap(surface_render, 0, 0, 0);
   }
}




int UIPickingBuffer::decode_id(ALLEGRO_COLOR color)
{
   unsigned char r, g, b, a;
   al_unmap_rgba(color, &r, &g, &b, &a);

   return r + (g * 256) + (b * 65536);
}




ALLEGRO_COLOR UIPickingBuffer::encode_id(int id)
{
   ALLEGRO_COLOR color;
   unsigned char r = id % 256;
   unsigned char g = id / 256;
   unsigned char b = id / 65536;
   unsigned char a = (id == 0) ? 0 : 255;

   return al_map_rgba(r, g, b, a);
}




std::string UIPickingBuffer::compose_on_click_id_message(int id)
{
   std::stringstream ss;
   ss << MESSAGE_HEADER << id;
   return ss.str();
}




int UIPickingBuffer::extract_on_click_id(std::string message)
{
   if (strncmp(message.c_str(), MESSAGE_HEADER.c_str(), MESSAGE_HEADER.size()) == 0)
   {
      int extracted_id = atoi(message.substr(MESSAGE_HEADER.size()).c_str());
      return extracted_id;
   }
   return 0;
}




bool UIPickingBuffer::is_on_click_id_message(std::string message)
{
   return strncmp(message.c_str(), MESSAGE_HEADER.c_str(), MESSAGE_HEADER.size()) == 0;
}




