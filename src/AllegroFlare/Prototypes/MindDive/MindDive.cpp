

#include <AllegroFlare/Prototypes/MindDive/MindDive.hpp>

#include <AllegroFlare/Elements/Stopwatch.hpp>
#include <AllegroFlare/Useful.hpp>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Prototypes
{
namespace MindDive
{


MindDive::MindDive(AllegroFlare::BitmapBin* bitmap_bin, AllegroFlare::FontBin* font_bin)
   : bitmap_bin(bitmap_bin)
   , font_bin(font_bin)
   , tunnel_mesh()
   , surfer({0, 0})
   , timer()
   , surfer_velocity({0, 0})
   , camera()
   , initialized(false)
{
}


MindDive::~MindDive()
{
}


AllegroFlare::BitmapBin* MindDive::get_bitmap_bin() const
{
   return bitmap_bin;
}


AllegroFlare::FontBin* MindDive::get_font_bin() const
{
   return font_bin;
}


AllegroFlare::Prototypes::MindDive::TunnelMesh &MindDive::get_tunnel_mesh_ref()
{
   return tunnel_mesh;
}


void MindDive::set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin)
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "MindDive" << "::" << "set_bitmap_bin" << ": error: " << "guard \"(!initialized)\" not met";
      throw std::runtime_error(error_message.str());
   }
   this->bitmap_bin = bitmap_bin;
   return;
}

void MindDive::set_font_bin(AllegroFlare::FontBin* font_bin)
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "MindDive" << "::" << "set_font_bin" << ": error: " << "guard \"(!initialized)\" not met";
      throw std::runtime_error(error_message.str());
   }
   this->font_bin = font_bin;
   return;
}

void MindDive::initialize()
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "MindDive" << "::" << "initialize" << ": error: " << "guard \"(!initialized)\" not met";
      throw std::runtime_error(error_message.str());
   }
   if (!(bitmap_bin))
   {
      std::stringstream error_message;
      error_message << "MindDive" << "::" << "initialize" << ": error: " << "guard \"bitmap_bin\" not met";
      throw std::runtime_error(error_message.str());
   }
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "MindDive" << "::" << "initialize" << ": error: " << "guard \"font_bin\" not met";
      throw std::runtime_error(error_message.str());
   }
   camera.size.x = 1920;
   camera.size.y = 1080;
   camera.set_zoom(2.0f);

   tunnel_mesh.set_bitmap_bin(bitmap_bin);
   tunnel_mesh.initialize();

   initialized = true;
   return;
}

void MindDive::start_timer()
{
   timer.start();
   return;
}

void MindDive::pause_timer()
{
   timer.pause();
   return;
}

void MindDive::reset_timer()
{
   timer.reset();
   return;
}

void MindDive::reset_surfer_to_beginning()
{
   surfer.x = tunnel_mesh.infer_real_width() / 2;
   surfer.y = tunnel_mesh.infer_real_height() - tunnel_mesh.obtain_tile_height() / 2;
   surfer_velocity.x = 0;
   surfer_velocity.y = 0;
   reset_timer();
   start_timer();
   return;
}

void MindDive::surfer_move_right()
{
   surfer_velocity.x = 2;
   return;
}

void MindDive::surfer_move_left()
{
   surfer_velocity.x = -2;
   return;
}

void MindDive::surfer_accelerate()
{
   surfer_velocity.y = -2;
   return;
}

void MindDive::surfer_stop()
{
   surfer_velocity.y = 0;
   return;
}

void MindDive::surfer_move_horizontal_none()
{
   surfer_velocity.x = 0;
   return;
}

void MindDive::render_tunnel()
{
   tunnel_mesh.render();
   return;
}

void MindDive::render_stopwatch()
{
   AllegroFlare::Elements::Stopwatch stopwatch(font_bin, &timer);
   stopwatch.render();
   return;
}

void MindDive::render_surfer()
{
   if (!(al_is_primitives_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "MindDive" << "::" << "render_surfer" << ": error: " << "guard \"al_is_primitives_addon_initialized()\" not met";
      throw std::runtime_error(error_message.str());
   }
   al_draw_filled_circle(surfer.x, surfer.y, 10, ALLEGRO_COLOR{1, 1, 1, 1});
   AllegroFlare::draw_crosshair(surfer.x, surfer.y, ALLEGRO_COLOR{1, 0, 0, 1}, 20);
   return;
}

void MindDive::update()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "MindDive" << "::" << "update" << ": error: " << "guard \"initialized\" not met";
      throw std::runtime_error(error_message.str());
   }
   surfer.x += surfer_velocity.x;
   surfer.y += surfer_velocity.y;
   camera.position.x = surfer.x;
   camera.position.y = surfer.y;
   return;
}

void MindDive::render()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "MindDive" << "::" << "render" << ": error: " << "guard \"initialized\" not met";
      throw std::runtime_error(error_message.str());
   }
   camera.start_reverse_transform();
   render_tunnel();
   render_surfer();
   camera.restore_transform();

   render_stopwatch();
   return;
}


} // namespace MindDive
} // namespace Prototypes
} // namespace AllegroFlare


