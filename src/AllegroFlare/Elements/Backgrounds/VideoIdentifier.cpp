

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
{
}


VideoIdentifier::~VideoIdentifier()
{
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
   // Should this logic be in the "show" function instead?
   ALLEGRO_VIDEO *video = obtain_video();
   if (video) al_start_video(video, al_get_default_mixer());
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
   ALLEGRO_VIDEO *video = obtain_video();
   if (!video) return;

   bool video_is_playing = al_is_video_playing(video);
   if (!video_is_playing) return;

   //ALLEGRO_BITMAP* frame = al_get_video_frame(video);
   //if (!frame) return;

   //float scale = 1.0;
   //float sw = al_get_bitmap_width(frame);
   //float sh = al_get_bitmap_height(frame);
   //float dw = scale * al_get_video_scaled_width(video);
   //float dh = scale * al_get_video_scaled_height(video);
   //al_draw_scaled_bitmap(frame, 0, 0, sw, sh, 0, 0, dw, dh, 0);
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


