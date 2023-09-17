
#include <gtest/gtest.h>

#include <AllegroFlare/Testing/Comparison/AllegroFlare/MusicNotation/Parser/PitchToken.hpp>


TEST(AllegroFlare_Testing_Comparison_AllegroFlare_MusicNotation_Parser_PitchTokenTest,
   PrintTo__with_an_AllegroFlare_PitchToken__will_output_as_expected)
{
   std::stringstream ss;
   AllegroFlare::MusicNotation::Parser::PitchToken object;

   PrintTo(object, &ss);

   std::string expected_output = "PitchToken(staff_position: 0, accidental: 0, accidental_natural: 0, )";
   std::string actual_output = ss.str();
   EXPECT_EQ(expected_output, actual_output);
}


TEST(AllegroFlare_Testing_Comparison_AllegroFlare_MusicNotation_Parser_PitchTokenTest,
   equality_operator__works_with_google_test_EXPECT_statement)
{
   AllegroFlare::MusicNotation::Parser::PitchToken object;
   AllegroFlare::MusicNotation::Parser::PitchToken other_object;

   EXPECT_EQ(object, other_object);
}


