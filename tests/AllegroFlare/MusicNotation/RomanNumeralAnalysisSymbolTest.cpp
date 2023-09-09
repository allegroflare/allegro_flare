
#include <gtest/gtest.h>

#include <AllegroFlare/MusicNotation/RomanNumeralAnalysisSymbol.hpp>


TEST(AllegroFlare_MusicNotation_RomanNumeralAnalysisSymbolTest, can_be_created_without_blowing_up)
{
   AllegroFlare::MusicNotation::RomanNumeralAnalysisSymbol roman_numeral_analysis_symbol;
}


TEST(AllegroFlare_MusicNotation_RomanNumeralAnalysisSymbolTest, run__returns_the_expected_response)
{
   AllegroFlare::MusicNotation::RomanNumeralAnalysisSymbol roman_numeral_analysis_symbol;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, roman_numeral_analysis_symbol.run());
}


