

#include <AllegroFlare/Prototypes/MindDive/MindDive.hpp>

#include <AllegroFlare/Elements/Stopwatch.hpp>
#include <AllegroFlare/Placement3D.hpp>
#include <AllegroFlare/Prototypes/MindDive/TunnelMeshFactory.hpp>
#include <AllegroFlare/Useful.hpp>
#include <allegro5/allegro_opengl.h>
#include <cmath>
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
   , current_tunnel_mesh()
   , surfer({0, 0})
   , surfer_velocity({0, 0})
   , timer()
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


AllegroFlare::Prototypes::MindDive::TunnelMesh* &MindDive::get_current_tunnel_mesh_ref()
{
   return current_tunnel_mesh;
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
   //camera.size.x = 1920;
   //camera.size.y = 1080;
   //camera.set_zoom(2.0f);
   AllegroFlare::Prototypes::MindDive::TunnelMeshFactory factory(bitmap_bin);

   current_tunnel_mesh = factory.create_classic_random();
   //AllegroFlare::Prototypes::MindDive::TunnelMeshFactory

   //tunnel_mesh.set_bitmap_bin(bitmap_bin);
   //tunnel_mesh.initialize();

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

void MindDive::reset()
{
   //surfer.x = current_tunnel_mesh->infer_real_width() / 2;
   //surfer.y = current_tunnel_mesh->infer_real_height() - current_tunnel_mesh->obtain_tile_height() / 2;
   surfer_velocity.x = 0;
   surfer_velocity.y = 0;
   reset_timer();
   start_timer();

   //camera.stepout = 10;
   //camera.tilt = 0.2;
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
   surfer_velocity.y = -6;
   return;
}

void MindDive::surfer_reverse()
{
   surfer_velocity.y = 2;
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
   current_tunnel_mesh->render();
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
   al_draw_filled_circle(surfer.x, surfer.y, 0.25, ALLEGRO_COLOR{1, 1, 1, 1});
   //AllegroFlare::draw_crosshair(surfer.x, surfer.y, ALLEGRO_COLOR{1, 0, 0, 1}, 20);
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
   surfer.x += surfer_velocity.x * 0.01;
   surfer.y += surfer_velocity.y * 0.01;
   //camera.position.x = surfer.x;
   //camera.position.y = surfer.y;
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
   //al_clear_depth_buffer(1);
   //camera.position.x = surfer.x;
   //camera.position.y = surfer.y;
   //camera.position.z = sin(al_get_time()) * 5;
   //camera.tilt = 3.14 / 2 + 0.4;  //al_get_time() * 0.5; // tilt the camera, looking down slightly at the target
   camera.stepout = AllegroFlare::Vec3D(0, 0, 10);
   camera.tilt = 0.4;  //al_get_time() * 0.5; // tilt the camera, looking down slightly at the target
   //camera.spin = 0.5f;
   camera.setup_projection_on(al_get_backbuffer(al_get_current_display()));
   //camera.zoom = 2.1;
   //camera.spin += 0.01f;

   //glCullFace(GL_BACK);  // requiring opengl should evnetually be fazed out
   //glDisable(GL_CULL_FACE);

   //camera.start_reverse_transform();
   AllegroFlare::Placement3D place;
   //place.size.x = tunnel_mesh.infer_real_width();
   //place.size.y = tunnel_mesh.infer_real_height();
   //place.scale.x = 0.95; //1.0 / 32.0f;
   //place.scale.y = 0.95; //1.0 / 32.0f;
   //place.scale.z = 0.95; //1.0 / 32.0f;
   //place.rotation.y = al_get_time(); //1.0 / 32.0f;
   //place.rotation.x = al_get_time() * 0.25;
   //place.rotation.x = -0.05;
   place.start_transform();
   render_tunnel();
   render_surfer();
   place.restore_transform();
   //camera.restore_transform();

   //render_stopwatch();
   return;
}


} // namespace MindDive
} // namespace Prototypes
} // namespace AllegroFlare


