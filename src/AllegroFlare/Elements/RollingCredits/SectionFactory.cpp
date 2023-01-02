

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


AllegroFlare::Elements::RollingCredits::Sections::ColumnWithLabels* SectionFactory::create_column_with_labels(std::vector<std::tuple<std::string, std::string>> elements)
{
   AllegroFlare::Elements::RollingCredits::Sections::ColumnWithLabels* section =
     new AllegroFlare::Elements::RollingCredits::Sections::ColumnWithLabels(elements);
   return section;
}

AllegroFlare::Elements::RollingCredits::Sections::Header* SectionFactory::create_header(std::string text)
{
   AllegroFlare::Elements::RollingCredits::Sections::Header* section =
     new AllegroFlare::Elements::RollingCredits::Sections::Header(text);
   return section;
}

AllegroFlare::Elements::RollingCredits::Sections::Text* SectionFactory::create_text(std::string text)
{
   AllegroFlare::Elements::RollingCredits::Sections::Text* section =
     new AllegroFlare::Elements::RollingCredits::Sections::Text(text);
   return section;
}

std::vector<AllegroFlare::Elements::RollingCredits::Sections::Text*> SectionFactory::create_standard_disclaimers_text(std::string text)
{
   std::string disclaimer_1 = "This is a work of fiction. Any resemblance to actual persons, living or dead, "
      "or events is purely coincidental.";
   std::string disclaimer_2 = "The views and opinions expressed in this media do not necessarily reflect the "
      "views and opinions of the developers or the production company.";
   // NOTE: This statement is an alternative to this trademarked phrase: "No animals were harmed.":
   // see: https://www.dvm360.com/view/movies-misuse-no-animals-were-harmed-disclaimer
   std::string disclaimer_3 = "During the production of this game, no animals were suject to injury, indignity, "
      "or mistreatment of any kind.";


   return std::vector<AllegroFlare::Elements::RollingCredits::Sections::Text*>{
      new AllegroFlare::Elements::RollingCredits::Sections::Text(disclaimer_1),
      new AllegroFlare::Elements::RollingCredits::Sections::Text(disclaimer_2),
      new AllegroFlare::Elements::RollingCredits::Sections::Text(disclaimer_3),
   };
}


} // namespace RollingCredits
} // namespace Elements
} // namespace AllegroFlare


