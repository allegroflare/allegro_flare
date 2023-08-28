
#include <gtest/gtest.h>

#include <AllegroFlare/MusicNotation/MusicNotation.hpp>

#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>


class AllegroFlare_MusicNotation_MusicNotationTest : public ::testing::Test {};
class AllegroFlare_MusicNotation_MusicNotationTextWithAllegroRenderingFixture :
   public AllegroFlare::Testing::WithAllegroRenderingFixture
{};


TEST_F(AllegroFlare_MusicNotation_MusicNotationTest, can_be_created_without_blowing_up)
{
   AllegroFlare::MusicNotation::MusicNotation music_notation;
}


TEST_F(AllegroFlare_MusicNotation_MusicNotationTextWithAllegroRenderingFixture, can_be_created_without_blowing_up)
{
   AllegroFlare::MusicNotation::MusicNotation music_notation;
   //music_notation.draw(0, 0, "abcd");
   //al_flip_display();
   //sleep(1);
}


