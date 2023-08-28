
#include <gtest/gtest.h>

#include <AllegroFlare/MusicNotation/MusicNotation.hpp>

#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>
#include <AllegroFlare/DrawingInterfaces/Allegro5.hpp>


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
   AllegroFlare::DrawingInterfaces::Allegro5 drawing_interface;
   AllegroFlare::MusicNotation::MusicNotation music_notation(&drawing_interface, &get_font_bin_ref());

   std::string music_notation_content_string = " & ^    -6=,e75'q1| -1.,-2 er 4]";
   music_notation.draw(1920/2, 1080/2, music_notation_content_string);

   al_flip_display();
   sleep(1);
}


