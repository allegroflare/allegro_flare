

#include <AllegroFlare/Elements/RollingCredits/Sections/LegalText.hpp>




namespace AllegroFlare
{
namespace Elements
{
namespace RollingCredits
{
namespace Sections
{


LegalText::LegalText(std::string text, std::string alignment)
   : AllegroFlare::Elements::RollingCredits::Sections::Base(AllegroFlare::Elements::RollingCredits::Sections::LegalText::TYPE)
   , text(text)
   , alignment(alignment)
{
}


LegalText::~LegalText()
{
}


std::string LegalText::get_text() const
{
   return text;
}


std::string LegalText::get_alignment() const
{
   return alignment;
}




} // namespace Sections
} // namespace RollingCredits
} // namespace Elements
} // namespace AllegroFlare


