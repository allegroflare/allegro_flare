

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
          "sponsorship, or endorsement by the software providers by either party. All rights to these software "
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


} // namespace AllegroFlare


