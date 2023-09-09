
#include <gtest/gtest.h>

#include <AllegroFlare/MusicNotation/RomanNumeralAnalysisSymbolRenderer.hpp>
#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>


class AllegroFlare_MusicNotation_RomanNumeralAnalysisSymbolRendererTest : public ::testing::Test {};
class AllegroFlare_MusicNotation_RomanNumeralAnalysisSymbolRendererTestWithAllegroRenderingFixture
   : public AllegroFlare::Testing::WithAllegroRenderingFixture
{};


TEST_F(AllegroFlare_MusicNotation_RomanNumeralAnalysisSymbolRendererTest, can_be_created_without_blowing_up)
{
   AllegroFlare::MusicNotation::RomanNumeralAnalysisSymbolRenderer roman_numeral_analysis_symbol_renderer;
}


TEST_F(AllegroFlare_MusicNotation_RomanNumeralAnalysisSymbolRendererTestWithAllegroRenderingFixture,
   render__will_not_blow_up)
{
   AllegroFlare::MusicNotation::RomanNumeralAnalysisSymbol symbol;
   AllegroFlare::MusicNotation::RomanNumeralAnalysisSymbolRenderer roman_numeral_analysis_symbol_renderer(
      &get_font_bin_ref(),
      &symbol
   );

   roman_numeral_analysis_symbol_renderer.render();

   al_flip_display();
   al_rest(1);
}


