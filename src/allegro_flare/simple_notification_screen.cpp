



#include <allegro_flare/simple_notification_screen.h>

#include <algorithm>
#include <allegro_flare/allegro_flare.h>
#include <AllegroFlare/UsefulPHP.hpp>




namespace allegro_flare
{
   SimpleNotificationScreen::SimpleNotification::SimpleNotification(std::string text, ALLEGRO_FONT *font, ALLEGRO_COLOR box_color, ALLEGRO_COLOR text_color)
      : text(text)
      , font(font)
      , lifespan(5)
      , can_die(false)
      // TODO: remove the initialization complexity here
      , num_lines(std::count(text.begin(), text.end(), '\n') + 1)
      , text_width(al_get_text_width(font, text.c_str()))
      , text_height(al_get_font_line_height(font) * num_lines)
      , box_color(box_color)
      , text_color(text_color)
   {
      std::vector<std::string> lines = AllegroFlare::php::explode("\n", text);
      text_width = al_get_text_width(font, lines[0].c_str());
      for (unsigned i=0; i<lines.size(); i++)
      {
         float width = al_get_text_width(font, lines[i].c_str());
         if (width > text_width) text_width = width;
      }
   }




   SimpleNotificationScreen::~SimpleNotificationScreen()
   {
   }




   void SimpleNotificationScreen::SimpleNotification::draw(float x_cursor, float y_cursor)
   {
      if (can_die) return;

      std::vector<std::string> lines = AllegroFlare::php::explode("\n", text);

      for (unsigned i=0; i<lines.size(); i++)
      {
         al_draw_text(font, AllegroFlare::color::color(text_color, AllegroFlare::limit<float>(0, 1, lifespan)), x_cursor, y_cursor-text_height+al_get_font_line_height(font)*i, ALLEGRO_ALIGN_RIGHT, lines[i].c_str());
      }
   }




   bool SimpleNotificationScreen::SimpleNotification::update()
   {
      lifespan -= 1/60.0f;
      if (lifespan < 0) can_die = true;
      return !can_die;
   }




   SimpleNotificationScreen::SimpleNotificationScreen(Display *display, ALLEGRO_FONT *font)
      : Screen(display)
      , motion(20)
      , font(font)
      , notifications()
   {
      instance = this;
   }




   void SimpleNotificationScreen::primary_timer_func()
   {
      motion.update(Framework::time_now);

      float x_cursor = display->width()-20;
      float y_cursor = display->height()-20;
      float padding_x = 16;
      float padding_y = 9;
      float margin = 6;
      float border_radius = 5;

      for (unsigned i=0; i<notifications.size(); i++)
      {
         if (notifications[i].update())
         {
            al_draw_filled_rounded_rectangle(
                  x_cursor-notifications[i].text_width - padding_x*2,
                  y_cursor-notifications[i].text_height - padding_y*2,
                  x_cursor,
                  y_cursor,
                  border_radius,
                  border_radius,
                  AllegroFlare::color::color(notifications[i].box_color, AllegroFlare::limit<float>(0.0, 1.0, notifications[i].lifespan) * 0.2));

            float line_width = 3.0;
            float h_line_width = line_width/2;
            al_draw_rounded_rectangle(
                  x_cursor-notifications[i].text_width - padding_x*2 + h_line_width,
                  y_cursor-notifications[i].text_height - padding_y*2 + h_line_width,
                  x_cursor - h_line_width,
                  y_cursor - h_line_width,
                  border_radius,
                  border_radius,
                  AllegroFlare::color::color(notifications[i].box_color,  0.15),
                  h_line_width);

            notifications[i].draw(x_cursor - padding_x, y_cursor - padding_y);

            y_cursor -= (notifications[i].text_height + padding_y*2 + margin);
         }
         else
         {
            notifications.erase(notifications.begin() + i);
            i--;
            continue;
         }
      }
   }




   void SimpleNotificationScreen::spawn_notification(std::string text)
   {
      if (!instance)
      {
         std::cout << "error[SimpleNotificationScreen.spawn_notification()] instance is NULL" << std::endl;
         return;
      }

      bring_to_front(this);
      notifications.push_back(SimpleNotification(text, font));
   }




   SimpleNotificationScreen *SimpleNotificationScreen::instance = NULL;
}



