
#include <gtest/gtest.h>

#include <AllegroFlare/LegalClauseGenerator.hpp>


TEST(AllegroFlare_LegalClauseGeneratorTest, can_be_created_without_blowing_up)
{
   AllegroFlare::LegalClauseGenerator legal_clause_generator;
}


TEST(AllegroFlare_LegalClauseGeneratorTest, run__returns_the_expected_response)
{
   AllegroFlare::LegalClauseGenerator legal_clause_generator;
   std::string expected_disclaimer = "Hello World!";
   EXPECT_EQ(expected_disclaimer, legal_clause_generator.generate_company_non_endorcement_disclaimer());
}


