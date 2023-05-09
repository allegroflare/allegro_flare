

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


ClubCattLogo::ClubCattLogo(AllegroFlare::BitmapBin* bitmap_bin, AllegroFlare::ModelBin* model_bin)
   : AllegroFlare::Elements::StoryboardPages::Base(AllegroFlare::Elements::StoryboardPages::ClubCattLogo::TYPE)
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


AllegroFlare::BitmapBin* ClubCattLogo::get_bitmap_bin() const
{
   return bitmap_bin;
}


AllegroFlare::ModelBin* ClubCattLogo::get_model_bin() const
{
   return model_bin;
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
   set_finished(false);
   clubcatt_logo.set_bitmap_bin(bitmap_bin);
   clubcatt_logo.set_model_bin(model_bin);
   clubcatt_logo.initialize();
   initialized = true;
}

void ClubCattLogo::start()
{
   // TODO: Start the animation
   return;
}

void ClubCattLogo::update()
{
   float time_now = al_get_time();
   clubcatt_logo.update(time_now);
   if (!get_finished() && clubcatt_logo.get_finished()) set_finished(true);
   return;
}

void ClubCattLogo::render()
{
   float time_now = al_get_time();
   clubcatt_logo.draw(time_now);
   return;
}

void ClubCattLogo::advance()
{
   // Will not do
   return;
}


} // namespace StoryboardPages
} // namespace Elements
} // namespace AllegroFlare


