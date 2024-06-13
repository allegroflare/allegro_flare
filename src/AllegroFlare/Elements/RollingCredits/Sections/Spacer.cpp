

#include <AllegroFlare/Elements/RollingCredits/Sections/Spacer.hpp>

#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Elements
{
namespace RollingCredits
{
namespace Sections
{


Spacer::Spacer(int height_px)
   : AllegroFlare::Elements::RollingCredits::Sections::Base(AllegroFlare::Elements::RollingCredits::Sections::Spacer::TYPE)
   , height_px(height_px)
{
}


Spacer::~Spacer()
{
}


int Spacer::get_height_px() const
{
   return height_px;
}


void Spacer::set_height_px(int height_px)
{
   if (!((height_px > 0)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Elements::RollingCredits::Sections::Spacer::set_height_px]: error: guard \"(height_px > 0)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Elements::RollingCredits::Sections::Spacer::set_height_px]: error: guard \"(height_px > 0)\" not met");
   }
   this->height_px = height_px;
   return;
}


} // namespace Sections
} // namespace RollingCredits
} // namespace Elements
} // namespace AllegroFlare


