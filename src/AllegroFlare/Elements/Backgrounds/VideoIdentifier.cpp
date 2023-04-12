

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
   if (video) al_start_video(video, nullptr);
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
   // TODO: obtain the frame and render the image
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


