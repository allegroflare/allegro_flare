

#include <AllegroFlare/Elements/Backgrounds/VideoIdentifier.hpp>

#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Elements
{
namespace Backgrounds
{


VideoIdentifier::VideoIdentifier(AllegroFlare::VideoBin* video_bin, std::string video_identifier)
   : AllegroFlare::Elements::Backgrounds::Base(AllegroFlare::Elements::Backgrounds::VideoIdentifier::TYPE)
   , video_bin(video_bin)
   , video_identifier(video_identifier)
   , surface_width(1920)
   , surface_height(1080)
   , video_is_playing(false)
{
}


VideoIdentifier::~VideoIdentifier()
{
}


void VideoIdentifier::set_surface_width(int surface_width)
{
   this->surface_width = surface_width;
}


void VideoIdentifier::set_surface_height(int surface_height)
{
   this->surface_height = surface_height;
}


int VideoIdentifier::get_surface_width() const
{
   return surface_width;
}


int VideoIdentifier::get_surface_height() const
{
   return surface_height;
}


void VideoIdentifier::activate()
{
   if (!(video_bin))
   {
      std::stringstream error_message;
      error_message << "[VideoIdentifier::activate]: error: guard \"video_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("VideoIdentifier::activate: error: guard \"video_bin\" not met");
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

void VideoIdentifier::deactivate()
{
   if (!(video_bin))
   {
      std::stringstream error_message;
      error_message << "[VideoIdentifier::deactivate]: error: guard \"video_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("VideoIdentifier::deactivate: error: guard \"video_bin\" not met");
   }
   ALLEGRO_VIDEO *video = obtain_video();
   if (video) al_set_video_playing(video, false);
   return;
}

void VideoIdentifier::render()
{
   if (!(video_bin))
   {
      std::stringstream error_message;
      error_message << "[VideoIdentifier::render]: error: guard \"video_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("VideoIdentifier::render: error: guard \"video_bin\" not met");
   }
   if (!video_is_playing) return;

   ALLEGRO_VIDEO *video = obtain_video();
   if (!video) return;

   bool video_is_playing = al_is_video_playing(video); // I think there is a bug here
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

ALLEGRO_VIDEO* VideoIdentifier::obtain_video()
{
   if (!(video_bin))
   {
      std::stringstream error_message;
      error_message << "[VideoIdentifier::obtain_video]: error: guard \"video_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("VideoIdentifier::obtain_video: error: guard \"video_bin\" not met");
   }
   return video_bin->auto_get(video_identifier);
}


} // namespace Backgrounds
} // namespace Elements
} // namespace AllegroFlare


