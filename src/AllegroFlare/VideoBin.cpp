

#include <AllegroFlare/VideoBin.hpp>

#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{


VideoBin::VideoBin()
   : AllegroFlare::Bin<std::string, ALLEGRO_VIDEO*>("VideoBin")
{
}


VideoBin::~VideoBin()
{
}


bool VideoBin::validate()
{
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::VideoBin::validate]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::VideoBin::validate]: error: guard \"al_is_system_installed()\" not met");
   }
   if (!(al_is_video_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::VideoBin::validate]: error: guard \"al_is_video_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::VideoBin::validate]: error: guard \"al_is_video_addon_initialized()\" not met");
   }
   return true;
}

ALLEGRO_VIDEO* VideoBin::load_data(std::string identifier)
{
   validate();
   return al_open_video(identifier.c_str());
}

void VideoBin::destroy_data(ALLEGRO_VIDEO* video)
{
   return al_close_video(video);
}


} // namespace AllegroFlare


