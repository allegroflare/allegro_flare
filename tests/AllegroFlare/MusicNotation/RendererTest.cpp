
#include <gtest/gtest.h>

#include <AllegroFlare/MusicNotation/Renderer.hpp>


TEST(AllegroFlare_MusicNotation_RendererTest, can_be_created_without_blowing_up)
{
   AllegroFlare::MusicNotation::Renderer renderer;
}


TEST(AllegroFlare_MusicNotation_RendererTest, run__returns_the_expected_response)
{
   AllegroFlare::MusicNotation::Renderer renderer;
   std::string expected_string = "Hello World!";
   EXPECT_EQ(expected_string, renderer.run());
}

