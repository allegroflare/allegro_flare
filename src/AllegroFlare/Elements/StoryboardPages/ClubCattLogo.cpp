

#include <AllegroFlare/Elements/StoryboardPages/ClubCattLogo.hpp>

#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Elements
{
namespace StoryboardPages
{


ClubCattLogo::ClubCattLogo(AllegroFlare::RenderSurfaces::Base* render_surface, AllegroFlare::BitmapBin* bitmap_bin, AllegroFlare::ModelBin* model_bin)
   : AllegroFlare::Elements::StoryboardPages::Base(AllegroFlare::Elements::StoryboardPages::ClubCattLogo::TYPE)
   , render_surface(render_surface)
   , bitmap_bin(bitmap_bin)
   , model_bin(model_bin)
   , clubcatt_logo()
   , initialized(false)
{
}


ClubCattLogo::~ClubCattLogo()
{
}


void ClubCattLogo::set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin)
{
   this->bitmap_bin = bitmap_bin;
}


void ClubCattLogo::set_model_bin(AllegroFlare::ModelBin* model_bin)
{
   this->model_bin = model_bin;
}


AllegroFlare::RenderSurfaces::Base* ClubCattLogo::get_render_surface() const
{
   return render_surface;
}


AllegroFlare::BitmapBin* ClubCattLogo::get_bitmap_bin() const
{
   return bitmap_bin;
}


AllegroFlare::ModelBin* ClubCattLogo::get_model_bin() const
{
   return model_bin;
}


void ClubCattLogo::set_render_surface(AllegroFlare::RenderSurfaces::Base* render_surface)
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[ClubCattLogo::set_render_surface]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("ClubCattLogo::set_render_surface: error: guard \"(!initialized)\" not met");
   }
   this->render_surface = render_surface;
   return;
}

void ClubCattLogo::initialize()
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[ClubCattLogo::initialize]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("ClubCattLogo::initialize: error: guard \"(!initialized)\" not met");
   }
   if (!(bitmap_bin))
   {
      std::stringstream error_message;
      error_message << "[ClubCattLogo::initialize]: error: guard \"bitmap_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("ClubCattLogo::initialize: error: guard \"bitmap_bin\" not met");
   }
   if (!(model_bin))
   {
      std::stringstream error_message;
      error_message << "[ClubCattLogo::initialize]: error: guard \"model_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("ClubCattLogo::initialize: error: guard \"model_bin\" not met");
   }
   if (!(render_surface))
   {
      std::stringstream error_message;
      error_message << "[ClubCattLogo::initialize]: error: guard \"render_surface\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("ClubCattLogo::initialize: error: guard \"render_surface\" not met");
   }
   set_finished(false);
   clubcatt_logo.set_render_surface(render_surface);
   clubcatt_logo.set_bitmap_bin(bitmap_bin);
   clubcatt_logo.set_model_bin(model_bin);
   clubcatt_logo.initialize();
   initialized = true;
}

void ClubCattLogo::disable_clearing_background_color()
{
   // TODO: Test this
   clubcatt_logo.set_clear_background_to_color(false);
   return;
}

void ClubCattLogo::start()
{
   float time_now = al_get_time();
   clubcatt_logo.play(time_now);
   return;
}

void ClubCattLogo::update()
{
   float time_now = al_get_time();
   clubcatt_logo.update(time_now);
   if (!get_finished() && clubcatt_logo.get_finished())
   {
      // TODO: Conside where destroy should occur (considering this may need to be looped during a game's demo mode)
      set_finished(true);
   }
   return;
}

void ClubCattLogo::render()
{
   if (clubcatt_logo.get_destroyed()) return;

   float time_now = al_get_time();
   clubcatt_logo.draw(time_now);
   return;
}

void ClubCattLogo::advance()
{
   // No advancing on this storyboard page
   return;
}


} // namespace StoryboardPages
} // namespace Elements
} // namespace AllegroFlare


