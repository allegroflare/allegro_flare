

#include <AllegroFlare/Elements/RollingCredits/Sections/ColumnWithLabels.hpp>



namespace AllegroFlare
{
namespace Elements
{
namespace RollingCredits
{
namespace Sections
{


ColumnWithLabels::ColumnWithLabels(std::vector<std::tuple<std::string, std::string>> elements)
   : AllegroFlare::Elements::RollingCredits::Sections::Base("StandardColumn")
   , elements(elements)
{
}


ColumnWithLabels::~ColumnWithLabels()
{
}


void ColumnWithLabels::set_elements(std::vector<std::tuple<std::string, std::string>> elements)
{
   this->elements = elements;
}


std::vector<std::tuple<std::string, std::string>> ColumnWithLabels::get_elements()
{
   return elements;
}


} // namespace Sections
} // namespace RollingCredits
} // namespace Elements
} // namespace AllegroFlare


