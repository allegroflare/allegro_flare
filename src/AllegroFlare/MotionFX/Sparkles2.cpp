

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
   Timeline::Actor *main_star_actor = new Timeline::Actor2D("foo", obtain_star_bitmap());
   std::vector<Timeline::Actor*> friend_stars = {
      new Timeline::Actor2D("foo", obtain_star_bitmap()),
      new Timeline::Actor2D("foo", obtain_star_bitmap()),
      new Timeline::Actor2D("foo", obtain_star_bitmap()),
      new Timeline::Actor2D("foo", obtain_star_bitmap()),
      new Timeline::Actor2D("foo", obtain_star_bitmap()),
   };

   std::vector<Timeline::Actor*> all_actors = { main_star_actor };
   all_actors.insert(all_actors.end(), friend_stars.begin(), friend_stars.end());

   // add the actors to the manager
   actor_manager.set_actors(all_actors);

   // main star
   // [time_sec] [param] [value] [!interpoltor]
   std::vector<std::string> script_lines = {
      "0.0 rotation 4.0 linear",
      "2.0 rotation 0.0 tripple_fast_in",
      "0.0 opacity 0.0 linear",
      "0.2 opacity 1.0 linear",
      "0.0 scale_x 0 linear",
      "0.0 scale_y 0 linear",
      "0.7 scale_x 1.2 bounce_out",
      "0.7 scale_y 1.2 bounce_out",

      //"0 color_r 0. linear",
      //"0 color_g 0.84 linear",
      //"0 color_b 0.0 linear",

      "0 color_r 0.91 linear",
      "0 color_g 0.875 linear",
      "0 color_b 0.537 linear",

      // fade out
      "1.9 opacity 1.0 linear",
      "2.2 opacity 0.0 fast_out",
   };
   main_star_actor->load_script(script_lines);

   // friend stars
   int count = 0;
   for (auto &friend_star : friend_stars)
   {
      float rotation_steps = (3.1415 * 2) / friend_stars.size();
      friend_star->load_script(build_friend_star_script_lines(rotation_steps * count));
      count++;
   }

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

std::vector<std::string> Sparkles2::build_friend_star_script_lines(float rotation)
{
   std::stringstream rotation_start_line;
      rotation_start_line << "0.0 rotation " << rotation + -4.0 << " linear";
   std::stringstream rotation_end_line;
      rotation_end_line << "3.0 rotation " << rotation << " tripple_fast_in";

   std::vector<std::string> result = {
      "0.0 align_x 0 linear",
      "0.2 align_x 0 linear",
      "1.0 align_x 2.3 tripple_fast_in",

      rotation_start_line.str(),
      rotation_end_line.str(),

      "0.0 opacity 0.0 linear",
      "0.2 opacity 1.0 linear",

      "0.0 scale_x 0 linear",
      "0.0 scale_y 0 linear",
      "0.3 scale_x 0.5 double_fast_in",
      "0.3 scale_y 0.5 double_fast_in",

      "0 color_r 1.0 linear",
      "0 color_g 0.84 linear",
      "0 color_b 1.0 linear",

      // fade out
      "1.2 scale_x 0.5 double_slow_out",
      "1.2 scale_y 0.5 double_slow_out",
      "1.8 scale_x 0.55 double_slow_in",
      "1.8 scale_y 0.55 double_slow_in",

      "1.5 opacity 1.0 linear",
      "1.8 opacity 0.0 linear",
   };
   return result;
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
   return bitmap_bin->auto_get("star-b.png");
}
} // namespace MotionFX
} // namespace AllegroFlare


