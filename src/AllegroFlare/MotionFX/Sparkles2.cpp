

#include <AllegroFlare/MotionFX/Sparkles2.hpp>
#include <AllegroFlare/Timeline/Actor2D.hpp>
#include <AllegroFlare/Interpolators.hpp>
#include <vector>
#include <string>
#include <stdexcept>
#include <sstream>
#include <stdexcept>
#include <sstream>
#include <AllegroFlare/Placement2D.hpp>
#include <stdexcept>
#include <sstream>
#include <stdexcept>
#include <sstream>


namespace AllegroFlare
{
namespace MotionFX
{


Sparkles2::Sparkles2(AllegroFlare::BitmapBin* bitmap_bin, float x, float y)
   : bitmap_bin(bitmap_bin)
   , x(x)
   , y(y)
   , actor_manager({})
   , initialized(false)
{
}


Sparkles2::~Sparkles2()
{
}


void Sparkles2::set_x(float x)
{
   this->x = x;
}


void Sparkles2::set_y(float y)
{
   this->y = y;
}


float Sparkles2::get_x()
{
   return x;
}


float Sparkles2::get_y()
{
   return y;
}


void Sparkles2::initialize()
{
   if (!((!initialized)))
      {
         std::stringstream error_message;
         error_message << "Sparkles2" << "::" << "initialize" << ": error: " << "guard \"(!initialized)\" not met";
         throw std::runtime_error(error_message.str());
      }
   // create the actor
   Timeline::Actor2D *actor = new Timeline::Actor2D("foo", obtain_star_bitmap());

   // add the actors to the manager
   actor_manager.set_actors({
      actor
   });

   // one way
   ///AllegroFlare::Timeline::Track *actor_rotation_track = actor->get_param_by_id("rotation");
   //actor_rotation_track->add_keyframe(1.0, 2.0, interpolator::linear);
   //actor_rotation_track->add_keyframe(2.0, -2.0, interpolator::fast_in);


   // another way
   // [time_sec] [param] [value] [!interpoltor]
   std::vector<std::string> script_lines = {
      "0.0 rotation -4.0 linear",
      "2.0 rotation 0.0 tripple_fast_in",
      "0.0 opacity 0.0 linear",
      "0.2 opacity 1.0 linear",
      "0.0 scale_x 0 linear",
      "0.0 scale_y 0 linear",
      "0.7 scale_x 1.2 bounce_out",
      "0.7 scale_y 1.2 bounce_out",
   };
   actor->load_script(script_lines);

   initialized = true;
   return;
}

void Sparkles2::update()
{
   if (!(al_is_system_installed()))
      {
         std::stringstream error_message;
         error_message << "Sparkles2" << "::" << "update" << ": error: " << "guard \"al_is_system_installed()\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (!(al_is_font_addon_initialized()))
      {
         std::stringstream error_message;
         error_message << "Sparkles2" << "::" << "update" << ": error: " << "guard \"al_is_font_addon_initialized()\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (!(initialized))
      {
         std::stringstream error_message;
         error_message << "Sparkles2" << "::" << "update" << ": error: " << "guard \"initialized\" not met";
         throw std::runtime_error(error_message.str());
      }
   return;
}

void Sparkles2::render()
{
   if (!(al_is_system_installed()))
      {
         std::stringstream error_message;
         error_message << "Sparkles2" << "::" << "render" << ": error: " << "guard \"al_is_system_installed()\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (!(al_is_font_addon_initialized()))
      {
         std::stringstream error_message;
         error_message << "Sparkles2" << "::" << "render" << ": error: " << "guard \"al_is_font_addon_initialized()\" not met";
         throw std::runtime_error(error_message.str());
      }
   if (!(initialized))
      {
         std::stringstream error_message;
         error_message << "Sparkles2" << "::" << "render" << ": error: " << "guard \"initialized\" not met";
         throw std::runtime_error(error_message.str());
      }
   Placement2D place(x, y, 0, 0);
   place.scale.x = 0.5;
   place.scale.y = 0.5;
   place.start_transform();
   actor_manager.render(al_get_time());
   place.restore_transform();
   return;
}

ALLEGRO_BITMAP* Sparkles2::obtain_star_bitmap()
{
   if (!(bitmap_bin))
      {
         std::stringstream error_message;
         error_message << "Sparkles2" << "::" << "obtain_star_bitmap" << ": error: " << "guard \"bitmap_bin\" not met";
         throw std::runtime_error(error_message.str());
      }
   return bitmap_bin->auto_get("star-a.png");
}
} // namespace MotionFX
} // namespace AllegroFlare


