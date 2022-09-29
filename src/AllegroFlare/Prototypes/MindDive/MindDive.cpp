

#include <AllegroFlare/Prototypes/MindDive/MindDive.hpp>

#include <AllegroFlare/Color.hpp>
#include <AllegroFlare/Placement3D.hpp>
#include <AllegroFlare/Prototypes/MindDive/TunnelMeshFactory.hpp>
#include <AllegroFlare/Prototypes/MindDive/TunnelMeshSurferCollisionResolver.hpp>
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
   , surfer_position({0, 0, 0})
   , surfer_velocity({0, 0, 0})
   , timer()
   , camera()
   , hud({})
   , state(STATE_WAITING_START)
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
   AllegroFlare::Prototypes::MindDive::TunnelMeshFactory factory(bitmap_bin);
   //current_tunnel_mesh = factory.create_classic_random();
   current_tunnel_mesh = factory.create_random_with_walls();

   hud.set_font_bin(font_bin);
   hud.set_timer(&timer);
   hud.initialize();

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
   surfer_position.x = current_tunnel_mesh->infer_real_width() * 0.5
                     - current_tunnel_mesh->obtain_tile_width() * 0.5;
   surfer_position.z = current_tunnel_mesh->infer_real_height()
                     - current_tunnel_mesh->obtain_tile_height() * 0.5;

   surfer_velocity = AllegroFlare::Vec3D(0, 0, 0);

   camera.stepout = AllegroFlare::Vec3D(0, 2, 5);
   state = STATE_WAITING_START;

   hud.show_ready_slate();
   //camera.tilt = 0.4;
   //camera.zoom = 2.1;
   //camera.spin += 0.01f;

   reset_timer();
   return;
}

void MindDive::start_racing()
{
   if (state != STATE_WAITING_START) return;
   state = STATE_RACING;
   start_timer();
   hud.clear_slate();
   return;
}

void MindDive::surfer_move_right()
{
   if (state == STATE_WAITING_START) start_racing();
   surfer_velocity.x = 3;
   return;
}

void MindDive::surfer_move_left()
{
   if (state == STATE_WAITING_START) start_racing();
   surfer_velocity.x = -3;
   return;
}

void MindDive::surfer_accelerate()
{
   if (state == STATE_WAITING_START) start_racing();
   surfer_velocity.z = -20;
   return;
}

void MindDive::surfer_reverse()
{
   if (state == STATE_WAITING_START) start_racing();
   surfer_velocity.z = 2;
   return;
}

void MindDive::surfer_stop()
{
   if (state == STATE_WAITING_START) start_racing();
   surfer_velocity.z = 0;
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

void MindDive::render_hud()
{
   hud.render();
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
   draw_crosshair(surfer_position, AllegroFlare::Color::Yellow, 0.75);
   //al_draw_filled_circle(surfer_position.x, surfer_position.z, 0.25, ALLEGRO_COLOR{1, 1, 1, 1});
   return;
}

void MindDive::evaluate_surfer_past_goal()
{
   if (state != STATE_RACING) return;

   if (surfer_position.z <= 0)
   {
      timer.pause();
      state = STATE_WON;
      surfer_velocity.x = 0.0f;
      surfer_velocity.z = 0.0f;
      hud.show_win_slate();
   }

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
   AllegroFlare::Prototypes::MindDive::TunnelMeshSurferCollisionResolver collision_resolver(
      current_tunnel_mesh,
      &surfer_position,
      &surfer_velocity
   );
   collision_resolver.resolve();

   camera.position = surfer_position;

   evaluate_surfer_past_goal();

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
   camera.setup_projection_on(al_get_backbuffer(al_get_current_display()));

   //glCullFace(GL_BACK);  // requiring opengl should evnetually be fazed out
   //glDisable(GL_CULL_FACE);

   //camera.start_reverse_transform();
   //AllegroFlare::Placement3D place;
   //place.start_transform();
   render_tunnel();
   render_surfer();
   //place.restore_transform();
   //camera.restore_transform();

   render_hud();
   return;
}


} // namespace MindDive
} // namespace Prototypes
} // namespace AllegroFlare


