#ifndef __AF_SIMPLE_NOTIFICATION_SCREEN
#define __AF_SIMPLE_NOTIFICATION_SCREEN




#include <allegro5/allegro_color.h>
#include <allegro5/allegro_font.h>
#include <AllegroFlare/Color.hpp>
#include <AllegroFlare/Motion.hpp>
#include <allegro_flare/screen.h>



namespace allegro_flare
{
   class SimpleNotificationScreen : public Screen
   {
   private:
      AllegroFlare::Motion motion;
      ALLEGRO_FONT *font;
      static SimpleNotificationScreen *instance;

      class SimpleNotification
      {
      public:
         std::string text;
         ALLEGRO_FONT *font;
         float lifespan;
         bool can_die;
         int num_lines;
         float text_width;
         float text_height;
         ALLEGRO_COLOR box_color, text_color;

         SimpleNotification(std::string text, ALLEGRO_FONT *font, ALLEGRO_COLOR box_color = AllegroFlare::color::aliceblue, ALLEGRO_COLOR text_color = AllegroFlare::color::black);
         void draw(float x_cursor, float y_cursor);
         bool update();
      };

      std::vector<SimpleNotification> notifications;

   public:
      SimpleNotificationScreen(Display *display, ALLEGRO_FONT *font);
      virtual ~SimpleNotificationScreen();

      void primary_timer_func() override;
      void spawn_notification(std::string text);
   };
}



#endif
