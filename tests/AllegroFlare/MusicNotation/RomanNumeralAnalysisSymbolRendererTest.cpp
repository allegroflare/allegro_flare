
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
}


TEST_F(AllegroFlare_MusicNotation_RomanNumeralAnalysisSymbolRendererTestWithAllegroRenderingFixture,
   CAPTURE__render__will_appear_as_expected)
{
   AllegroFlare::Placement2D showcased_placement = build_centered_placement();
   AllegroFlare::MusicNotation::RomanNumeralAnalysisSymbol symbol;
   AllegroFlare::MusicNotation::RomanNumeralAnalysisSymbolRenderer roman_numeral_analysis_symbol_renderer(
      &get_font_bin_ref(),
      &symbol
   );

   // Render the subject
   showcased_placement.start_transform();
   roman_numeral_analysis_symbol_renderer.render();
   showcased_placement.restore_transform();

   al_flip_display();
   al_rest(1);
}


