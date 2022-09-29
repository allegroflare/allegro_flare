

#include <AllegroFlare/Prototypes/MindDive/Hud/Hud.hpp>

#include <AllegroFlare/Elements/Stopwatch.hpp>
#include <AllegroFlare/Vec2D.hpp>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
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


Hud::Hud(AllegroFlare::FontBin* font_bin, AllegroFlare::Timer* timer, std::string slate_text)
   : font_bin(font_bin)
   , timer(timer)
   , slate_text(slate_text)
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


AllegroFlare::FontBin* Hud::get_font_bin() const
{
   return font_bin;
}


AllegroFlare::Timer* Hud::get_timer() const
{
   return timer;
}


void Hud::initialize()
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "Hud" << "::" << "initialize" << ": error: " << "guard \"(!initialized)\" not met";
      throw std::runtime_error(error_message.str());
   }
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "Hud" << "::" << "initialize" << ": error: " << "guard \"al_is_system_installed()\" not met";
      throw std::runtime_error(error_message.str());
   }
   if (!(al_is_primitives_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "Hud" << "::" << "initialize" << ": error: " << "guard \"al_is_primitives_addon_initialized()\" not met";
      throw std::runtime_error(error_message.str());
   }
   if (!(al_is_font_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "Hud" << "::" << "initialize" << ": error: " << "guard \"al_is_font_addon_initialized()\" not met";
      throw std::runtime_error(error_message.str());
   }
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "Hud" << "::" << "initialize" << ": error: " << "guard \"font_bin\" not met";
      throw std::runtime_error(error_message.str());
   }
   if (!(timer))
   {
      std::stringstream error_message;
      error_message << "Hud" << "::" << "initialize" << ": error: " << "guard \"timer\" not met";
      throw std::runtime_error(error_message.str());
   }
   if (!(al_get_current_display))
   {
      std::stringstream error_message;
      error_message << "Hud" << "::" << "initialize" << ": error: " << "guard \"al_get_current_display\" not met";
      throw std::runtime_error(error_message.str());
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

   camera.setup_dimentional_projection(backbuffer_sub_bitmap);

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
   float x = 1920/2;
   float y = 1080/2;
   ALLEGRO_FONT *font = obtain_font();
   float text_width = al_get_text_width(font, slate_text.c_str());
   float text_height = al_get_font_line_height(font);
   float h_text_width = text_width/2;
   float h_text_height = text_height/2;
   AllegroFlare::Vec2D padding = {30, 20};

   al_draw_text(font, ALLEGRO_COLOR{1, 1, 1, 1}, x, y-h_text_height, ALLEGRO_ALIGN_CENTER, slate_text.c_str());
   return;
}

void Hud::render()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "Hud" << "::" << "render" << ": error: " << "guard \"initialized\" not met";
      throw std::runtime_error(error_message.str());
   }
   render_slate();
   render_stopwatch();
   return;
}

ALLEGRO_FONT* Hud::obtain_font()
{
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "Hud" << "::" << "obtain_font" << ": error: " << "guard \"font_bin\" not met";
      throw std::runtime_error(error_message.str());
   }
   return font_bin->auto_get("Inter-Bold.ttf -90");
}


} // namespace Hud
} // namespace MindDive
} // namespace Prototypes
} // namespace AllegroFlare


