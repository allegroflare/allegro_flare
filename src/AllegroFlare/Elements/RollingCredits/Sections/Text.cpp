

#include <AllegroFlare/Elements/RollingCredits/Sections/Text.hpp>




namespace AllegroFlare
{
namespace Elements
{
namespace RollingCredits
{
namespace Sections
{


Text::Text(std::string text, std::string alignment)
   : AllegroFlare::Elements::RollingCredits::Sections::Base(AllegroFlare::Elements::RollingCredits::Sections::Text::TYPE)
   , text(text)
   , alignment(alignment)
{
}


Text::~Text()
{
}


std::string Text::get_text() const
{
   return text;
}


std::string Text::get_alignment() const
{
   return alignment;
}




} // namespace Sections
} // namespace RollingCredits
} // namespace Elements
} // namespace AllegroFlare


