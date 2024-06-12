

#include <AllegroFlare/MotionFX/Sparkles2.hpp>

#include <AllegroFlare/Interpolators.hpp>
#include <AllegroFlare/Placement2D.hpp>
#include <AllegroFlare/Timeline/Actors/Actor2D.hpp>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>


namespace AllegroFlare
{
namespace MotionFX
{


Sparkles2::Sparkles2(AllegroFlare::BitmapBin* bitmap_bin, float x, float y, float time, float scale)
   : bitmap_bin(bitmap_bin)
   , x(x)
   , y(y)
   , time(time)
   , scale(scale)
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


void Sparkles2::set_time(float time)
{
   this->time = time;
}


void Sparkles2::set_scale(float scale)
{
   this->scale = scale;
}


float Sparkles2::get_x() const
{
   return x;
}


float Sparkles2::get_y() const
{
   return y;
}


float Sparkles2::get_time() const
{
   return time;
}


float Sparkles2::get_scale() const
{
   return scale;
}


void Sparkles2::initialize()
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::MotionFX::Sparkles2::initialize]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::MotionFX::Sparkles2::initialize]: error: guard \"(!initialized)\" not met");
   }
   // create the actor
   std::string star_bitmap_filename = "star-b.png";
   Timeline::Actors::Base *main_star_actor =
      new Timeline::Actors::Actor2D("foo", star_bitmap_filename, obtain_star_bitmap());
   std::vector<Timeline::Actors::Base*> friend_stars = {
      new Timeline::Actors::Actor2D("foo", star_bitmap_filename, obtain_star_bitmap()),
      new Timeline::Actors::Actor2D("foo", star_bitmap_filename, obtain_star_bitmap()),
      new Timeline::Actors::Actor2D("foo", star_bitmap_filename, obtain_star_bitmap()),
      new Timeline::Actors::Actor2D("foo", star_bitmap_filename, obtain_star_bitmap()),
      new Timeline::Actors::Actor2D("foo", star_bitmap_filename, obtain_star_bitmap()),
   };

   std::vector<Timeline::Actors::Base*> all_actors = { main_star_actor };
   all_actors.insert(all_actors.end(), friend_stars.begin(), friend_stars.end());

   // add the actors to the manager
   actor_manager.set_actors(all_actors);

   // main star
   // [time_sec] [param] [value] [!interpoltor]
   std::vector<std::string> script_lines = {
      "0.0 rotation 4.0 linear",
      "2.0 rotation 0.0 tripple_fast_in",

      "0.0 opacity 0.0 linear",
      "0.4 opacity 1.0 linear",
      "1.9 opacity 1.0 linear",
      "2.2 opacity 0.0 fast_out",

      "0.0 scale_x 0 linear",
      "0.0 scale_y 0 linear",
      "0.1 scale_x 0 linear",
      "0.1 scale_y 0 linear",
      "0.7 scale_x 1.2 bounce_out",
      "0.7 scale_y 1.2 bounce_out",

      //"0 color_r 0. linear",
      //"0 color_g 0.84 linear",
      //"0 color_b 0.0 linear",

      "0 color_r 0.91 linear",
      "0 color_g 0.875 linear",
      "0 color_b 0.537 linear",
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
      "0.3 opacity 1.0 linear",

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
      error_message << "[AllegroFlare::MotionFX::Sparkles2::render]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::MotionFX::Sparkles2::render]: error: guard \"al_is_system_installed()\" not met");
   }
   if (!(al_is_font_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::MotionFX::Sparkles2::render]: error: guard \"al_is_font_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::MotionFX::Sparkles2::render]: error: guard \"al_is_font_addon_initialized()\" not met");
   }
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::MotionFX::Sparkles2::render]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::MotionFX::Sparkles2::render]: error: guard \"initialized\" not met");
   }
   Placement2D place(x, y, 0, 0);
   place.scale.x = scale;
   place.scale.y = scale;
   place.start_transform();
   actor_manager.render(time);
   place.restore_transform();
   return;
}

ALLEGRO_BITMAP* Sparkles2::obtain_star_bitmap()
{
   if (!(bitmap_bin))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::MotionFX::Sparkles2::obtain_star_bitmap]: error: guard \"bitmap_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::MotionFX::Sparkles2::obtain_star_bitmap]: error: guard \"bitmap_bin\" not met");
   }
   return bitmap_bin->auto_get("star-b.png");
}


} // namespace MotionFX
} // namespace AllegroFlare


