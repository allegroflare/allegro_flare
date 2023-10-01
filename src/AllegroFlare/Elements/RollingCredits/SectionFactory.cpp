

#include <AllegroFlare/Elements/RollingCredits/SectionFactory.hpp>

#include <AllegroFlare/LegalClauseGenerator.hpp>


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

AllegroFlare::Elements::RollingCredits::Sections::Text* SectionFactory::create_text(std::string text, std::string alignment)
{
   AllegroFlare::Elements::RollingCredits::Sections::Text* section =
     new AllegroFlare::Elements::RollingCredits::Sections::Text(text, alignment);
   return section;
}

std::vector<AllegroFlare::Elements::RollingCredits::Sections::LegalText*> SectionFactory::create_standard_disclaimers_text(std::string company_name, std::vector<std::string> non_endorced_software_and_software_company_names)
{
   auto &ALIGN_CENTER = AllegroFlare::Elements::RollingCredits::Sections::LegalText::ALIGN_CENTER;

   std::string disclaimer_1 = AllegroFlare::LegalClauseGenerator::generate_persons_resemblance_disclaimer();
   std::string disclaimer_2 = AllegroFlare::LegalClauseGenerator::generate_views_and_opinions_disclaimer();
   std::string disclaimer_3 = AllegroFlare::LegalClauseGenerator::generate_company_non_endorcement_disclaimer(
         company_name,
         non_endorced_software_and_software_company_names
      );
   std::string disclaimer_4 = AllegroFlare::LegalClauseGenerator::generate_no_mistreatment_of_animals_disclaimer();
   std::string disclaimer_5 = AllegroFlare::LegalClauseGenerator::generate_as_is_without_warranty_disclaimer();

   return std::vector<AllegroFlare::Elements::RollingCredits::Sections::LegalText*>{
      new AllegroFlare::Elements::RollingCredits::Sections::LegalText(disclaimer_1, ALIGN_CENTER),
      new AllegroFlare::Elements::RollingCredits::Sections::LegalText(disclaimer_2, ALIGN_CENTER),
      new AllegroFlare::Elements::RollingCredits::Sections::LegalText(disclaimer_3, ALIGN_CENTER),
      new AllegroFlare::Elements::RollingCredits::Sections::LegalText(disclaimer_4, ALIGN_CENTER),
      new AllegroFlare::Elements::RollingCredits::Sections::LegalText(disclaimer_5, ALIGN_CENTER),
   };
}


} // namespace RollingCredits
} // namespace Elements
} // namespace AllegroFlare


