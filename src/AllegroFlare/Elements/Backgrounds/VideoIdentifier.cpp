

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
   return;
}


} // namespace Backgrounds
} // namespace Elements
} // namespace AllegroFlare


