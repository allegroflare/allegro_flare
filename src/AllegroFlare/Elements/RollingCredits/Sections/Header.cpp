

#include <AllegroFlare/Elements/RollingCredits/Sections/Header.hpp>




namespace AllegroFlare
{
namespace Elements
{
namespace RollingCredits
{
namespace Sections
{


Header::Header(std::string text)
   : AllegroFlare::Elements::RollingCredits::Sections::Base("Header")
   , text(text)
{
}


Header::~Header()
{
}


void Header::set_text(std::string text)
{
   this->text = text;
}


std::string Header::get_text() const
{
   return text;
}




} // namespace Sections
} // namespace RollingCredits
} // namespace Elements
} // namespace AllegroFlare


