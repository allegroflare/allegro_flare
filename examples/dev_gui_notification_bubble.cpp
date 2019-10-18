#ifndef __UI_NOTIFICATION_BUBBLE_HEADER
#define __UI_NOTIFICATION_BUBBLE_HEADER




#include <allegro_flare/allegro_flare.h>
#include <AllegroFlare/Color.hpp>
#include <allegro_flare/widget.h>
#include <allegro_flare/box.h>

#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>




using namespace allegro_flare;
using namespace AllegroFlare;



class UINotificationBubble : public UIWidget
{
private:
   std::string text;
   bool paused;
   float spawn_time, lifespan;
   float opacity;
   ALLEGRO_FONT *font;

public:
   UINotificationBubble(UIWidget *parent, float x, float y, std::string text)
      : UIWidget(parent, "UINotificationBubble", new UISurfaceAreaBox(x, y, 280, 90))
      , text(text)
      , font(Framework::font("DroidSerif.ttf 20"))
      , spawn_time(Framework::time_now)
      , lifespan(4.0)
      , paused(false)
      , opacity(0)
   {
      Framework::motion().cmove_to(&this->opacity, 1.0, 0.5);

      this->surface_area->placement.align.x = 1.0;
      this->surface_area->placement.align.y = 1.0;
   }

   ~UINotificationBubble()
   {
      Framework::motion().clear_animations_on(&this->opacity);
   }

   void on_timer()
   {
      if (paused || delete_me) return;

      if ((Framework::time_now - spawn_time) > lifespan)
      {
         delete_me = true;
         Framework::motion().cmove_to(&this->opacity, 0, 0.6);
      }
   }

   void on_mouse_enter()
   {
      if (delete_me) return;

      paused = true;
      Framework::motion().cmove_to(&this->opacity, 1.0, 0.5);
   }

   void on_mouse_leave()
   {
      if (delete_me) return;

      paused = false;
      spawn_time  = Framework::time_now;
   }

   void on_draw()
   {
      if (delete_me) return;

      al_draw_filled_rounded_rectangle(0, 0, place.size.x, place.size.y, 6, 6, color::hex("#fce566", opacity));
      al_draw_text(font, color::hex("645710", opacity), 23, 20, 0, text.c_str());
   }
};




#endif




class NotificationBubbleTestProject : public UIScreen
{
public:
   float mouse_x;
   float mouse_y;
   UIText *bubble_count_text;
   NotificationBubbleTestProject(Display *display)
      : UIScreen(display)
      , mouse_x(display->width()/2)
      , mouse_y(display->height()/2)
      , bubble_count_text(NULL)
   {
      al_set_mouse_xy(display->al_display, mouse_x, mouse_y);
      new UIText(this, 40, 30, "Move the mouse and press any key to spawn a NotificationBubble.");
      bubble_count_text = new UIText(this, 40, 60, "Number of active bubbles: 0");
   }
   std::string get_random_quote()
   {
      return "Anyone who considers protocol unimportant has never dealt with a cat.\n-- R. Heinlein";
   }
   void on_mouse_move(float x, float y, float dx, float dy) override
   {
      mouse_x = x;
      mouse_y = y;
   }
   void on_mouse_down() override
   {
      new UINotificationBubble(this, mouse_x, mouse_y, get_random_quote());
   }
   void primary_timer_func() override
   {
      std::string message = "Number of active bubbles: ";
      message += tostring(this->num_children());
      bubble_count_text->set_text(message);

      UIScreen::primary_timer_func();
   }
};




int main(int argc, char *argv[])
{
   Framework::initialize();
   Display *display = Framework::create_display(1280, 800, false);

   NotificationBubbleTestProject *proj = new NotificationBubbleTestProject(display);

   Framework::run_loop();
   return 0;
}




