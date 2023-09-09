
#include <gtest/gtest.h>

#include <AllegroFlare/MusicNotation/RomanNumeralAnalysisSymbol.hpp>


TEST(AllegroFlare_MusicNotation_RomanNumeralAnalysisSymbolTest, can_be_created_without_blowing_up)
{
   AllegroFlare::MusicNotation::RomanNumeralAnalysisSymbol roman_numeral_analysis_symbol;
}


TEST(AllegroFlare_MusicNotation_RomanNumeralAnalysisSymbolTest,
   calculate_all_chord_notes_chromatic__will_return_the_expected_notes)
{
   AllegroFlare::MusicNotation::RomanNumeralAnalysisSymbol roman_numeral_analysis_symbol;
   roman_numeral_analysis_symbol.set_scale_degree(4);
   roman_numeral_analysis_symbol.set_extensions({ {6, 0} });
   roman_numeral_analysis_symbol.set_chord_quality(
      AllegroFlare::MusicNotation::RomanNumeralAnalysisSymbol::ChordQuality::MINOR
   );

   std::vector<std::pair<int, int>> expected = { {0, 0}, {2, -1}, {4, 0}, {6, 0} };
   std::vector<std::pair<int, int>> actual =
      roman_numeral_analysis_symbol.calculate_root_position_figured_bass_notes_with_extensions();

   EXPECT_EQ(expected, actual);
}


