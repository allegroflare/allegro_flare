

#include <AllegroFlare/Elements/RollingCredits/Sections/StandardColumn.hpp>



namespace AllegroFlare
{
namespace Elements
{
namespace RollingCredits
{
namespace Sections
{


StandardColumn::StandardColumn(std::vector<std::tuple<std::string, std::string>> elements)
   : AllegroFlare::Elements::RollingCredits::Sections::Base("StandardColumn")
   , elements(elements)
{
}


StandardColumn::~StandardColumn()
{
}


void StandardColumn::set_elements(std::vector<std::tuple<std::string, std::string>> elements)
{
   this->elements = elements;
}


std::vector<std::tuple<std::string, std::string>> StandardColumn::get_elements()
{
   return elements;
}


} // namespace Sections
} // namespace RollingCredits
} // namespace Elements
} // namespace AllegroFlare


