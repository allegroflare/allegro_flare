

#include <AllegroFlare/LegalClauseGenerator.hpp>

#include <sstream>


namespace AllegroFlare
{


LegalClauseGenerator::LegalClauseGenerator()
{
}


LegalClauseGenerator::~LegalClauseGenerator()
{
}


std::string LegalClauseGenerator::generate_persons_resemblance_disclaimer()
{
   return "This is a work of fiction. Any resemblance to actual persons, living or dead, or events is purely "
      "coincidental.";
}

std::string LegalClauseGenerator::generate_views_and_opinions_disclaimer()
{
   return "The views and opinions expressed in this media do not necessarily reflect the views and opinions of "
      "the developers or the production company.";
}

std::string LegalClauseGenerator::generate_no_mistreatment_of_animals_disclaimer()
{
   // NOTE: This statement is an alternative to this trademarked phrase: "No animals were harmed.":
   // see: https://www.dvm360.com/view/movies-misuse-no-animals-were-harmed-disclaimer
   return "During the production of this game, no animals were suject to injury, indignity, or mistreatment of "
      "any kind.";
}

std::string LegalClauseGenerator::generate_as_is_without_warranty_disclaimer(bool in_upcase)
{
   std::string disclaimer = "THIS SOFTWARE IS PROVIDED 'AS-IS', WITHOUT ANY EXPRESS OR IMPLIED WARRANTY. IN NO "
      "EVENT WILL THE AUTHORS BE HELD LIABLE FOR ANY DAMAGES ARISING FROM THE USE OF THIS SOFTWARE.";
   return (in_upcase) ? upcase(disclaimer) : disclaimer;
}

std::string LegalClauseGenerator::generate_as_is_without_warranty_for_use_disclaimer()
{
   return "THIS SOFTWARE IS PROVIDED \"AS IS\", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING "
      "BUT NOT LIMITED TO ANY WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT "
      "OF COPYRIGHT, PATENT, TRADEMARK, OR OTHER RIGHT. IN NO EVENT SHALL THE COPYRIGHT HOLDER BE LIABLE FOR ANY "
      "CLAIM, DAMAGES OR OTHER LIABILITY, INCLUDING ANY GENERAL, SPECIAL, INDIRECT, INCIDENTAL, OR CONSEQUENTIAL "
      "DAMAGES, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF THE USE OR INABILITY TO "
      "USE THE SOFTWARE OR FROM OTHER DEALINGS IN THE SOFTWARE.";
}

std::string LegalClauseGenerator::generate_company_non_endorcement_disclaimer(std::string company_name, std::vector<std::string> referenced_software_company_names)
{
   std::stringstream in_fragment;
   in_fragment << "in these credits ";
   std::stringstream referenced_software_company_names_as_in_fragment;

   bool has_referenced_software_company_names = (!referenced_software_company_names.empty());

   if (has_referenced_software_company_names)
   {
      referenced_software_company_names_as_in_fragment << "as in but no limited to "
         << join(referenced_software_company_names) << " ";
   }

   return "Any company names, brand names, and/or trademarks listed " + in_fragment.str() + "are the sole property "
          "of their respective "
          "owners and are in no way associated with " + company_name + ". Their appearance in this list does not "
          "constitute an endorsement by either party. The inclusion of software names " +
          referenced_software_company_names_as_in_fragment.str() +
          "and their respective versions is solely for informational purposes and does not imply any partnership, "
          "sponsorship, or endorsement of the software providers by either party. All rights to these software "
          "belong to their respective copyright holders.";
}

std::string LegalClauseGenerator::join(std::vector<std::string> tokens, std::string delimiter, bool use_and)
{
   std::stringstream result;
   int size = tokens.size();

   for (int i = 0; i < size; ++i)
   {
      if (i > 0)
      {
         result << delimiter;
         if (use_and && i == size - 1)
         {
            result << "and ";
         }
      }
      result << tokens[i];
   }

   return result.str();
}

std::string LegalClauseGenerator::upcase(std::string text)
{
   std::string result;
   for (char& c : text)
   {
      result += std::toupper(c);
   }
   return result;
}


} // namespace AllegroFlare


