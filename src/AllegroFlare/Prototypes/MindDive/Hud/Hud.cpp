

#include <AllegroFlare/Prototypes/MindDive/Hud/Hud.hpp>

#include <AllegroFlare/Color.hpp>
#include <AllegroFlare/Elements/Stopwatch.hpp>
#include <AllegroFlare/Vec2D.hpp>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Prototypes
{
namespace MindDive
{
namespace Hud
{


Hud::Hud(AllegroFlare::FontBin* font_bin, AllegroFlare::Timer* timer, std::string slate_text, ALLEGRO_COLOR slate_text_color)
   : font_bin(font_bin)
   , timer(timer)
   , slate_text(slate_text)
   , slate_text_color(slate_text_color)
   , backbuffer_sub_bitmap(nullptr)
   , initialized(false)
   , camera({})
{
}


Hud::~Hud()
{
}


void Hud::set_font_bin(AllegroFlare::FontBin* font_bin)
{
   this->font_bin = font_bin;
}


void Hud::set_timer(AllegroFlare::Timer* timer)
{
   this->timer = timer;
}


void Hud::set_slate_text(std::string slate_text)
{
   this->slate_text = slate_text;
}


void Hud::set_slate_text_color(ALLEGRO_COLOR slate_text_color)
{
   this->slate_text_color = slate_text_color;
}


AllegroFlare::FontBin* Hud::get_font_bin() const
{
   return font_bin;
}


AllegroFlare::Timer* Hud::get_timer() const
{
   return timer;
}


std::string Hud::get_slate_text() const
{
   return slate_text;
}


ALLEGRO_COLOR Hud::get_slate_text_color() const
{
   return slate_text_color;
}


void Hud::show_win_slate()
{
   slate_text = "-- WIN --";
   slate_text_color = AllegroFlare::Color::Gold;
   return;
}

void Hud::show_die_slate()
{
   slate_text = "/////////////// FAIL ///////////////";
   slate_text_color = AllegroFlare::Color::Red;
   return;
}

void Hud::show_ready_slate()
{
   slate_text = "-- READY --";
   slate_text_color = AllegroFlare::Color::Orange;
   return;
}

void Hud::clear_slate()
{
   slate_text = "";
   slate_text_color = AllegroFlare::Color::White;
   return;
}

void Hud::initialize()
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::MindDive::HudHud::initialize]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::MindDive::HudHud::initialize]: error: guard \"(!initialized)\" not met");
   }
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::MindDive::HudHud::initialize]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::MindDive::HudHud::initialize]: error: guard \"al_is_system_installed()\" not met");
   }
   if (!(al_is_primitives_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::MindDive::HudHud::initialize]: error: guard \"al_is_primitives_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::MindDive::HudHud::initialize]: error: guard \"al_is_primitives_addon_initialized()\" not met");
   }
   if (!(al_is_font_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::MindDive::HudHud::initialize]: error: guard \"al_is_font_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::MindDive::HudHud::initialize]: error: guard \"al_is_font_addon_initialized()\" not met");
   }
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::MindDive::HudHud::initialize]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::MindDive::HudHud::initialize]: error: guard \"font_bin\" not met");
   }
   if (!(timer))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::MindDive::HudHud::initialize]: error: guard \"timer\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::MindDive::HudHud::initialize]: error: guard \"timer\" not met");
   }
   if (!(al_get_current_display()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::MindDive::HudHud::initialize]: error: guard \"al_get_current_display()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::MindDive::HudHud::initialize]: error: guard \"al_get_current_display()\" not met");
   }
   // TODO: have a destroy mechanism, need to destory the backbuffer on destruction
   ALLEGRO_BITMAP *backbuffer = al_get_backbuffer(al_get_current_display());
   if (!backbuffer) throw std::runtime_error("MindDive/Hud/Hud error: no backbuffer");

   backbuffer_sub_bitmap = al_create_sub_bitmap(
      backbuffer,
      0,
      0,
      al_get_bitmap_width(backbuffer),
      al_get_bitmap_height(backbuffer)
   );

   camera.setup_dimensional_projection(backbuffer_sub_bitmap);

   initialized = true;
   return;
}

void Hud::render_stopwatch()
{
   AllegroFlare::Elements::Stopwatch stopwatch(font_bin, timer);
   stopwatch.render();
   return;
}

void Hud::render_slate()
{
   if (slate_text.empty()) return;

   float x = 1920/2;
   float y = 1080/2;
   ALLEGRO_FONT *font = obtain_font();
   float text_width = al_get_text_width(font, slate_text.c_str());
   float text_height = al_get_font_line_height(font);
   float h_text_width = text_width/2;
   float h_text_height = text_height/2;
   AllegroFlare::Vec2D padding = {30, 20};

   al_draw_text(font, slate_text_color, x, y-h_text_height, ALLEGRO_ALIGN_CENTER, slate_text.c_str());
   return;
}

void Hud::render()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::MindDive::HudHud::render]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::MindDive::HudHud::render]: error: guard \"initialized\" not met");
   }
   ALLEGRO_STATE previous_state;
   al_store_state(&previous_state, ALLEGRO_STATE_TARGET_BITMAP);
   al_set_target_bitmap(backbuffer_sub_bitmap);

   render_slate();
   render_stopwatch();

   al_restore_state(&previous_state);
   return;
}

ALLEGRO_FONT* Hud::obtain_font()
{
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::MindDive::HudHud::obtain_font]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::MindDive::HudHud::obtain_font]: error: guard \"font_bin\" not met");
   }
   return font_bin->auto_get("Inter-Bold.ttf -90");
}


} // namespace Hud
} // namespace MindDive
} // namespace Prototypes
} // namespace AllegroFlare


