
#include <gtest/gtest.h>

#include <AllegroFlare/LegalClauseGenerator.hpp>


TEST(AllegroFlare_LegalClauseGeneratorTest, can_be_created_without_blowing_up)
{
   AllegroFlare::LegalClauseGenerator legal_clause_generator;
}


TEST(AllegroFlare_LegalClauseGeneratorTest,
   generate_company_non_endorcement_disclaimer__will_generate_the_expected_text)
{
   AllegroFlare::LegalClauseGenerator legal_clause_generator;
   std::string company_name = "SlowPoke Software";
   std::vector<std::string> referenced_software_company_names = { 
      "MeowsterEdit",
      "Gator Graphicshop",
      "FerretFoto",
   };

   std::string expected_disclaimer = "Any company names, brand names, and/or trademarks listed in these credits are "
      "the sole property of their respective owners and are in no way associated with SlowPoke Software. Their "
      "appearance in this list does not constitute an endorsement by either party. The inclusion of software names as "
      "in but no limited to MeowsterEdit, Gator Graphicshop, FerretFoto and their respective versions is solely for "
      "informational purposes and does not imply any partnership, sponsorship, or endorsement by the software "
      "providers by either party. All rights to these software belong to their respective copyright holders.";

   std::string actual_disclaimer = legal_clause_generator.generate_company_non_endorcement_disclaimer(
      company_name,
      referenced_software_company_names
   );

   EXPECT_EQ(expected_disclaimer, actual_disclaimer);
}


TEST(AllegroFlare_LegalClauseGeneratorTest,
   generate_company_non_endorcement_disclaimer__with_an_empty_list_of_referenced_software_company_names__will_output_\
the_expected_text)
{
   // TODO
}


