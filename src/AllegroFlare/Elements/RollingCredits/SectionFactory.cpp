

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

std::vector<AllegroFlare::Elements::RollingCredits::Sections::Text*> SectionFactory::create_standard_disclaimers_text(std::string text)
{
   auto &ALIGN_CENTER = AllegroFlare::Elements::RollingCredits::Sections::Text::ALIGN_CENTER;

   std::string disclaimer_1 = AllegroFlare::LegalClauseGenerator::generate_persons_resemblance_disclaimer();
   std::string disclaimer_2 = AllegroFlare::LegalClauseGenerator::generate_views_and_opinions_disclaimer();
   std::string disclaimer_3 = AllegroFlare::LegalClauseGenerator::generate_company_non_endorcement_disclaimer();
   std::string disclaimer_4 = AllegroFlare::LegalClauseGenerator::generate_no_mistreatment_of_animals_disclaimer();

   // TODO: include this disclaimer (replace FONT):
   //DISCLAIMER
   //THE FONT SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO ANY WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT OF COPYRIGHT, PATENT, TRADEMARK, OR OTHER RIGHT. IN NO EVENT SHALL THE COPYRIGHT HOLDER BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, INCLUDING ANY GENERAL, SPECIAL, INDIRECT, INCIDENTAL, OR CONSEQUENTIAL DAMAGES, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF THE USE OR INABILITY TO USE THE FONT SOFTWARE OR FROM OTHER DEALINGS IN THE FONT SOFTWARE.


   return std::vector<AllegroFlare::Elements::RollingCredits::Sections::Text*>{
      new AllegroFlare::Elements::RollingCredits::Sections::Text(disclaimer_1, ALIGN_CENTER),
      new AllegroFlare::Elements::RollingCredits::Sections::Text(disclaimer_2, ALIGN_CENTER),
      new AllegroFlare::Elements::RollingCredits::Sections::Text(disclaimer_3, ALIGN_CENTER),
      new AllegroFlare::Elements::RollingCredits::Sections::Text(disclaimer_4, ALIGN_CENTER),
   };
}


} // namespace RollingCredits
} // namespace Elements
} // namespace AllegroFlare


