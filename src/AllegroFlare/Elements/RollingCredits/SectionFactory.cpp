

#include <AllegroFlare/Elements/RollingCredits/SectionFactory.hpp>



namespace AllegroFlare
{
namespace Elements
{
namespace RollingCredits
{


SectionFactory::SectionFactory()
{
}


SectionFactory::~SectionFactory()
{
}


AllegroFlare::Elements::RollingCredits::Sections::ColumnWithLabels SectionFactory::build_column_with_labels_section(std::vector<std::tuple<std::string, std::string>> sections)
{
   return AllegroFlare::Elements::RollingCredits::Sections::ColumnWithLabels(sections);
}

AllegroFlare::Elements::RollingCredits::Sections::Header SectionFactory::build_header_section(std::string text)
{
   return AllegroFlare::Elements::RollingCredits::Sections::Header(text);
}
} // namespace RollingCredits
} // namespace Elements
} // namespace AllegroFlare


