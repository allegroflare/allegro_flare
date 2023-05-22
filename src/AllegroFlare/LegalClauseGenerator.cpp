

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


std::string LegalClauseGenerator::generate_company_non_endorcement_disclaimer()
{
   std::string company_name = "CLUBCATT";
   std::stringstream in_fragment;
   in_fragment << "in these credits ";
   std::vector<std::string> referenced_software_company_names = { "Adobe Photoshop", "Google Docs", "ChatGPT" };
   std::stringstream referenced_software_company_names_as_in_fragment;
   return "Any company names, brand names, and/or trademarks listed " + in_fragment.str() + "are the sole property "
          "of their respective "
          "owners and are in no way associated with " + company_name + ". Their appearance in this list does not "
          "constitute an endorsement by either party. The inclusion of software names " +
          referenced_software_company_names_as_in_fragment.str() +
          "and their respective versions is solely for informational purposes and does not imply any partnership, "
          "sponsorship, or endorsement by the software providers. All rights to these software belong to their "
          "respective copyright holders.";
          //ClubCatt acknowledges and respects the intellectual property rights of others.
}


} // namespace AllegroFlare


