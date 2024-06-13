

#include <AllegroFlare/ProfilerRenderer.hpp>

#include <AllegroFlare/Vec2D.hpp>
#include <allegro5/allegro_color.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{


ProfilerRenderer::ProfilerRenderer(AllegroFlare::FontBin* font_bin, std::map<std::string, AllegroFlare::Timer>* timers, float x, float y)
   : font_bin(font_bin)
   , timers(timers)
   , x(x)
   , y(y)
{
}


ProfilerRenderer::~ProfilerRenderer()
{
}


void ProfilerRenderer::set_font_bin(AllegroFlare::FontBin* font_bin)
{
   this->font_bin = font_bin;
}


void ProfilerRenderer::set_timers(std::map<std::string, AllegroFlare::Timer>* timers)
{
   this->timers = timers;
}


void ProfilerRenderer::set_x(float x)
{
   this->x = x;
}


void ProfilerRenderer::set_y(float y)
{
   this->y = y;
}


AllegroFlare::FontBin* ProfilerRenderer::get_font_bin() const
{
   return font_bin;
}


std::map<std::string, AllegroFlare::Timer>* ProfilerRenderer::get_timers() const
{
   return timers;
}


float ProfilerRenderer::get_x() const
{
   return x;
}


float ProfilerRenderer::get_y() const
{
   return y;
}


void ProfilerRenderer::render()
{
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::ProfilerRenderer::render]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::ProfilerRenderer::render]: error: guard \"al_is_system_installed()\" not met");
   }
   if (!(al_is_primitives_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::ProfilerRenderer::render]: error: guard \"al_is_primitives_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::ProfilerRenderer::render]: error: guard \"al_is_primitives_addon_initialized()\" not met");
   }
   if (!(al_is_font_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::ProfilerRenderer::render]: error: guard \"al_is_font_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::ProfilerRenderer::render]: error: guard \"al_is_font_addon_initialized()\" not met");
   }
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::ProfilerRenderer::render]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::ProfilerRenderer::render]: error: guard \"font_bin\" not met");
   }
   if (!(timers))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::ProfilerRenderer::render]: error: guard \"timers\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::ProfilerRenderer::render]: error: guard \"timers\" not met");
   }
   ALLEGRO_FONT *font = obtain_font();
   ALLEGRO_COLOR bg_color = al_color_name("black");
   float w = 300;
   float line_height = 25;
   float pad = 20;
   float h = timers->size()*line_height + pad*2;
   int i=0;
   char buff[32];
   float target_microseconds = 16666;
   float horizontal_scale = 0.01f;

   // draw the background
   al_draw_filled_rounded_rectangle(x, y, x+w, y+h, 8, 8, bg_color);

   if (timers->empty())
   {
      // Draw empty state when no timers are present
      int font_line_height = al_get_font_line_height(font);
      ALLEGRO_COLOR timer_empty_text_color = ALLEGRO_COLOR{0.2, 0.2, 0.2, 0.2};
      std::string text = "Profiler is not tracking any timers. [Press F1 to close]";
      al_draw_text(
         font,
         timer_empty_text_color,
         x + w/2,
         y+h/2-font_line_height/2,
         ALLEGRO_ALIGN_CENTER,
         text.c_str()
      );
   }
   else
   {
      // Draw the graph
      ALLEGRO_COLOR bg_color = al_color_name("black");
      ALLEGRO_COLOR bar_color = al_color_name("orange");
      ALLEGRO_COLOR font_color = al_color_name("white");
      ALLEGRO_COLOR limit_bar_color = al_color_name("lightblue");

      for (auto &timer : (*timers))
      {
         int duration_microseconds = std::get<1>(timer).get_elapsed_time_microseconds();
         float bar_width = duration_microseconds * horizontal_scale;
         al_draw_filled_rectangle(
            x,
            y+pad+line_height*i+15,
            x+bar_width,
            y+pad+line_height*i+20,
            bar_color
         );

         al_draw_text(font, font_color, x+pad, y+pad+line_height*i, 0, std::get<0>(timer).c_str());
         sprintf(buff, "%d", duration_microseconds);
         al_draw_text(font, font_color, x+pad+300, y+pad+line_height*i, ALLEGRO_ALIGN_RIGHT, buff);
         i++;
      }

      // draws our marker at 16666 (the number of microseconds in a frame)
      al_draw_line(
         target_microseconds * horizontal_scale,
         0,
         target_microseconds * horizontal_scale,
         h,
         ALLEGRO_COLOR{0, 1, 1, 1},
         2.0
      );
   }

   return;
}

ALLEGRO_FONT* ProfilerRenderer::obtain_font()
{
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::ProfilerRenderer::obtain_font]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::ProfilerRenderer::obtain_font]: error: guard \"font_bin\" not met");
   }
   return font_bin->auto_get("Inter-Regular.ttf -26");
}


} // namespace AllegroFlare


