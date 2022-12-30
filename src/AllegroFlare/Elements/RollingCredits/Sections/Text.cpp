

#include <AllegroFlare/Elements/RollingCredits/Sections/Text.hpp>




namespace AllegroFlare
{
namespace Elements
{
namespace RollingCredits
{
namespace Sections
{


Text::Text(std::string text)
   : AllegroFlare::Elements::RollingCredits::Sections::Base(AllegroFlare::Elements::RollingCredits::Sections::Text::TYPE)
   , text(text)
{
}


Text::~Text()
{
}


std::string Text::get_text() const
{
   return text;
}




} // namespace Sections
} // namespace RollingCredits
} // namespace Elements
} // namespace AllegroFlare


