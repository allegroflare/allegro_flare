

#include <AllegroFlare/Elements/RollingCredits/Sections/Multicolumn.hpp>




namespace AllegroFlare
{
namespace Elements
{
namespace RollingCredits
{
namespace Sections
{


Multicolumn::Multicolumn(std::vector<std::vector<std::string>> elements)
   : AllegroFlare::Elements::RollingCredits::Sections::Base(AllegroFlare::Elements::RollingCredits::Sections::Multicolumn::TYPE)
   , elements(elements)
{
}


Multicolumn::~Multicolumn()
{
}


std::vector<std::vector<std::string>> Multicolumn::get_elements() const
{
   return elements;
}




} // namespace Sections
} // namespace RollingCredits
} // namespace Elements
} // namespace AllegroFlare


