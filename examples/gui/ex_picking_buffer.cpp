


#include <allegro_flare/allegro_flare.h>


#define SCREEN_W (1920/3*2)
#define SCREEN_H (1080/3*2)


class Project : public UIScreen
{
public:
   UIPickingBuffer *picking_buffer;
   UIButton *refresh_button;
   UIButton *toggle_picking_buffer_visibility_button;
   UIText *info_message;

   Project(Display *display)
      : UIScreen(display)
      , picking_buffer(new UIPickingBuffer(this, SCREEN_W/2, SCREEN_H/2, SCREEN_W/3, SCREEN_H/3, 0))
      , refresh_button(new UIButton(this, SCREEN_W/2 - 100, SCREEN_H/4*3, 120, 60, "Refresh"))
      , toggle_picking_buffer_visibility_button(new UIButton(this, SCREEN_W/2 + 100, SCREEN_H/4*3, 120, 60, "Hide"))
      , info_message(new UIText(this, SCREEN_W/2, SCREEN_H/4, ""))
   {
      draw_new_ids();
   }
   void draw_new_ids()
   {
      picking_buffer->clear_surface();

      ALLEGRO_STATE previous_state;
      al_store_state(&previous_state, ALLEGRO_STATE_TARGET_BITMAP);
      al_set_target_bitmap(picking_buffer->surface_render);

      for (unsigned i=0; i<10; i++)
      {
         float x = random_int(0, picking_buffer->place.size.x);
         float y = random_int(0, picking_buffer->place.size.y);
         float r = random_float(10, 30);
         float id = random_int(1, 100);

         al_draw_filled_circle(x, y, r, UIPickingBuffer::encode_id(id));
      }

      al_restore_state(&previous_state);
   }
   void on_message(UIWidget *sender, std::string message) override
   {
      if (sender == refresh_button)
      {
         draw_new_ids();
      }
      else if (sender == toggle_picking_buffer_visibility_button)
      {
         picking_buffer->draw_surface_render = !picking_buffer->draw_surface_render;
         toggle_picking_buffer_visibility_button->set_text(picking_buffer->draw_surface_render ? "Hide" : "Show");
      }
      else if (sender == picking_buffer)
      {
         if (picking_buffer->is_on_click_id_message(message))
         {
            int id = picking_buffer->extract_on_click_id(message);
            info_message->set_text(tostring("You clicked on ID #") + tostring(id));
         }
      }
   }
};


int main(int argc, char **argv)
{
   Framework::initialize();
   Display *display = Framework::create_display(SCREEN_W, SCREEN_H);
   Project project = Project(display);
   Framework::run_loop();
   return 0;
}


