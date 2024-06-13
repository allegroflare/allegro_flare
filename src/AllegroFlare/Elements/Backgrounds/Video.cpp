

#include <AllegroFlare/Elements/Backgrounds/Video.hpp>

#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Elements
{
namespace Backgrounds
{


Video::Video(AllegroFlare::VideoBin* video_bin, std::string video_identifier)
   : AllegroFlare::Elements::Backgrounds::Base(AllegroFlare::Elements::Backgrounds::Video::TYPE)
   , video_bin(video_bin)
   , video_identifier(video_identifier)
   , surface_width(1920)
   , surface_height(1080)
   , video_is_playing(false)
   , initialized(false)
{
}


Video::~Video()
{
}


void Video::set_surface_width(int surface_width)
{
   this->surface_width = surface_width;
}


void Video::set_surface_height(int surface_height)
{
   this->surface_height = surface_height;
}


AllegroFlare::VideoBin* Video::get_video_bin() const
{
   return video_bin;
}


std::string Video::get_video_identifier() const
{
   return video_identifier;
}


int Video::get_surface_width() const
{
   return surface_width;
}


int Video::get_surface_height() const
{
   return surface_height;
}


void Video::set_video_bin(AllegroFlare::VideoBin* video_bin)
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::Backgrounds::Video::set_video_bin]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::Backgrounds::Video::set_video_bin]: error: guard \"(!initialized)\" not met");
   }
   this->video_bin = video_bin;
   return;
}

void Video::set_video_identifier(std::string video_identifier)
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::Backgrounds::Video::set_video_identifier]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::Backgrounds::Video::set_video_identifier]: error: guard \"(!initialized)\" not met");
   }
   this->video_identifier = video_identifier;
   return;
}

void Video::initialize()
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::Backgrounds::Video::initialize]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::Backgrounds::Video::initialize]: error: guard \"(!initialized)\" not met");
   }
   if (!(video_bin))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::Backgrounds::Video::initialize]: error: guard \"video_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::Backgrounds::Video::initialize]: error: guard \"video_bin\" not met");
   }
   initialized = true;
   return;
}

void Video::activate()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::Backgrounds::Video::activate]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::Backgrounds::Video::activate]: error: guard \"initialized\" not met");
   }
   ALLEGRO_VIDEO *video = obtain_video();
   if (video)
   {
      al_start_video(video, al_get_default_mixer());
      video_is_playing = true;
      std::cout << "video FPS: " << al_get_video_fps(video) << std::endl;
      std::cout << "video audio rate: " << al_get_video_audio_rate(video) << std::endl;
   }
   return;
}

void Video::deactivate()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::Backgrounds::Video::deactivate]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::Backgrounds::Video::deactivate]: error: guard \"initialized\" not met");
   }
   ALLEGRO_VIDEO *video = obtain_video();
   if (video) al_set_video_playing(video, false);
   return;
}

void Video::render()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::Backgrounds::Video::render]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::Backgrounds::Video::render]: error: guard \"initialized\" not met");
   }
   if (!video_is_playing) return;

   ALLEGRO_VIDEO *video = obtain_video();
   if (!video) return;

   bool video_is_playing = al_is_video_playing(video); // I think there is a bug here. See documentation section.
   if (!video_is_playing) return;

   ALLEGRO_BITMAP* frame = al_get_video_frame(video);
   if (!frame) return;

   std::string fit_style = VIDEO_FIT_STRATEGY_STRETCH_TO_FIT;
   if (fit_style == VIDEO_FIT_STRATEGY_STRETCH_TO_FIT)
   {
      float scale_x = surface_width / al_get_video_scaled_width(video);
      float scale_y = surface_height / al_get_video_scaled_height(video);
      float sw = al_get_bitmap_width(frame);
      float sh = al_get_bitmap_height(frame);
      float dw = scale_x * al_get_video_scaled_width(video);
      float dh = scale_y * al_get_video_scaled_height(video);
      al_draw_scaled_bitmap(frame, 0, 0, sw, sh, 0, 0, dw, dh, 0);
   }
   return;
}

ALLEGRO_VIDEO* Video::obtain_video()
{
   if (!(video_bin))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::Backgrounds::Video::obtain_video]: error: guard \"video_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::Backgrounds::Video::obtain_video]: error: guard \"video_bin\" not met");
   }
   return video_bin->auto_get(video_identifier);
}


} // namespace Backgrounds
} // namespace Elements
} // namespace AllegroFlare


