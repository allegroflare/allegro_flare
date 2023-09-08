
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
   AllegroFlare::MusicNotation::TieRenderer tie_renderer;
   //std::string expected_string = "Hello World!";
   tie_renderer.render();
   al_flip_display();
}


