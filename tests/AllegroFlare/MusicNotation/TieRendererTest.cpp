
#include <gtest/gtest.h>

#include <AllegroFlare/MusicNotation/TieRenderer.hpp>
#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>


class AllegroFlare_MusicNotation_TieRendererTest : public ::testing::Test {};
class AllegroFlare_MusicNotation_TieRendererTestWithAllegroRenderingFixture
   : public AllegroFlare::Testing::WithAllegroRenderingFixture
{};


TEST_F(AllegroFlare_MusicNotation_TieRendererTest, can_be_created_without_blowing_up)
{
   AllegroFlare::MusicNotation::TieRenderer tie_renderer;
}


TEST_F(AllegroFlare_MusicNotation_TieRendererTestWithAllegroRenderingFixture,
   CAPTURE__render__does_not_blow_up)
{
   AllegroFlare::Placement2D showcased_placement = build_centered_placement();
   AllegroFlare::MusicNotation::TieRenderer tie_renderer;

   // Render the subject
   showcased_placement.start_transform();
   tie_renderer.render();
   showcased_placement.restore_transform();

   al_flip_display();
}


