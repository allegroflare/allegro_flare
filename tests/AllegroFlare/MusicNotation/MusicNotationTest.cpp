
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


TEST_F(AllegroFlare_MusicNotation_MusicNotationTextWithAllegroRenderingFixture,
   CAPTURE__renders_as_expected_with_a_simple_test_string)
{
   AllegroFlare::DrawingInterfaces::Allegro5 drawing_interface;
   AllegroFlare::MusicNotation::MusicNotation music_notation(&drawing_interface, &get_font_bin_ref());

   std::string music_notation_content_string = " & ^    -6=,e75'q1| -1.,-2 er 4]";
   music_notation.draw(1920/2, 1080/2, music_notation_content_string);

   al_flip_display();
   //sleep(1);
}


TEST_F(AllegroFlare_MusicNotation_MusicNotationTextWithAllegroRenderingFixture,
   CAPTURE__render__when_notes_have_dots__will_render_them_in_the_correct_place_on_the_staff)
{
   AllegroFlare::DrawingInterfaces::Allegro5 drawing_interface;
   AllegroFlare::MusicNotation::MusicNotation music_notation(&drawing_interface, &get_font_bin_ref(), 12);
   std::string music_notation_content_string;

   music_notation_content_string = "4.4..3.3..2.2..1.1..0.0..,1.1..2.2..3.3..4.4..";
   music_notation.draw(1920/2 - 850, 1080/2-100, music_notation_content_string);

   music_notation_content_string = "r4.4..3.3..2.2..1.1..0.0..,1.1..2.2..3.3..4.4..";
   music_notation.draw(1920/2 - 850, 1080/2+100, music_notation_content_string);

   al_flip_display();
   sleep(1);
}


TEST_F(AllegroFlare_MusicNotation_MusicNotationTextWithAllegroRenderingFixture,
   CAPTURE__setting_a_staff_color_will_work_as_expected)
{
   AllegroFlare::DrawingInterfaces::Allegro5 drawing_interface;
   AllegroFlare::MusicNotation::MusicNotation music_notation(&drawing_interface, &get_font_bin_ref());

   std::string music_notation_content_string = "{staff_color=orange} & ^    -6=,e75'q1| -1.,-2 er 4]";
   music_notation.draw(1920/2, 1080/2, music_notation_content_string);

   al_flip_display();
   //sleep(1);
}


TEST_F(AllegroFlare_MusicNotation_MusicNotationTextWithAllegroRenderingFixture,
   CAPTURE__renders_tied_notes_as_expected)
{
   AllegroFlare::DrawingInterfaces::Allegro5 drawing_interface;
   AllegroFlare::MusicNotation::MusicNotation music_notation(&drawing_interface, &get_font_bin_ref(), 20);

   std::string music_notation_content_string = " & ^    q~0q0";

   music_notation.draw(1920/2, 1080/2, music_notation_content_string);

   al_flip_display();
   //sleep(1);
}


