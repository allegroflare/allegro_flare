
#include <gtest/gtest.h>

#include <AllegroFlare/MusicNotation/MusicNotation.hpp>

#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>
#include <AllegroFlare/DrawingInterfaces/Allegro5.hpp>
#include <AllegroFlare/Testing/ErrorAssertions.hpp>


class AllegroFlare_MusicNotation_MusicNotationTest : public ::testing::Test {};
class AllegroFlare_MusicNotation_MusicNotationTextWithAllegroRenderingFixture :
   public AllegroFlare::Testing::WithAllegroRenderingFixture
{};


TEST_F(AllegroFlare_MusicNotation_MusicNotationTest, can_be_created_without_blowing_up)
{
   AllegroFlare::MusicNotation::MusicNotation music_notation;
}


TEST_F(AllegroFlare_MusicNotation_MusicNotationTextWithAllegroRenderingFixture,
   draw__when_an_expected_closing_brace_is_not_present__throws_an_error)
{
   AllegroFlare::DrawingInterfaces::Allegro5 drawing_interface;
   AllegroFlare::MusicNotation::MusicNotation music_notation(&drawing_interface, &get_font_bin_ref());
   std::string music_notation_content_string = "{missing_closing_brace";

   EXPECT_THROW_WITH_MESSAGE(
      music_notation.draw(0, 0, music_notation_content_string),
      std::runtime_error,
      "[MusicNotation::draw]: error: music string parse error: expected closing curly brace '}' not found"
   );
}


TEST_F(AllegroFlare_MusicNotation_MusicNotationTextWithAllegroRenderingFixture,
   draw__when_an_expected_closing_parenthesis_is_not_present__throws_an_error)
{
   AllegroFlare::DrawingInterfaces::Allegro5 drawing_interface;
   AllegroFlare::MusicNotation::MusicNotation music_notation(&drawing_interface, &get_font_bin_ref());
   std::string music_notation_content_string = "(missing_closing_parenthesis";

   EXPECT_THROW_WITH_MESSAGE(
      music_notation.draw(0, 0, music_notation_content_string),
      std::runtime_error,
      "[MusicNotation::draw]: error: music string parse error: expected closing parenthesis ')' not found"
   );
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
   //sleep(1);
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
   CAPTURE__setting_a_color_within_the_content_will_work_as_expected)
{
   AllegroFlare::DrawingInterfaces::Allegro5 drawing_interface;
   AllegroFlare::MusicNotation::MusicNotation music_notation(&drawing_interface, &get_font_bin_ref());

   std::string music_notation_content_string = "{color=orange} & ^    -6=,e75'q1| {color=springgreen}-1.{color=orange},-2 er 4]";
   music_notation.draw(1920/2, 1080/2, music_notation_content_string);

   al_flip_display();
   //sleep(1);
}


TEST_F(AllegroFlare_MusicNotation_MusicNotationTextWithAllegroRenderingFixture,
   CAPTURE__setting_the_staff_line_distance_between_renders__will_work_as_expected)
{
   std::string music_notation_content_string = " & ^    -6=,e75'q1| -1.,-2 er 4]";
   AllegroFlare::DrawingInterfaces::Allegro5 drawing_interface;
   AllegroFlare::MusicNotation::MusicNotation music_notation(&drawing_interface, &get_font_bin_ref());

   music_notation.draw(1920/2 - 500, 1080/2-400, music_notation_content_string);

   music_notation.set_staff_line_distance(30);
   music_notation.draw(1920/2 - 500, 1080/2-100, music_notation_content_string);

   music_notation.set_staff_line_distance(7);
   music_notation.draw(1920/2 - 500, 1080/2+300, music_notation_content_string);

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


TEST_F(AllegroFlare_MusicNotation_MusicNotationTextWithAllegroRenderingFixture,
   CAPTURE__on_rendering__will_return_the_width_of_the_rendered_string)
{
   AllegroFlare::DrawingInterfaces::Allegro5 drawing_interface;
   AllegroFlare::MusicNotation::MusicNotation music_notation(&drawing_interface, &get_font_bin_ref(), 20);

   std::string music_notation_content_string = " & ^    q~0q0|";

   float x = 1920/2 - 600;
   float x_cursor = 0;

   x_cursor += music_notation.draw(x+x_cursor, 1080/2, music_notation_content_string);
   x_cursor += music_notation.draw(x+x_cursor, 1080/2, music_notation_content_string);
   x_cursor += music_notation.draw(x+x_cursor, 1080/2, music_notation_content_string);

   al_flip_display();
   //sleep(1);
}


TEST_F(AllegroFlare_MusicNotation_MusicNotationTextWithAllegroRenderingFixture,
   CAPTURE__on_rendering__note_clusters__will_render_as_expected)
{
   AllegroFlare::DrawingInterfaces::Allegro5 drawing_interface;
   AllegroFlare::MusicNotation::MusicNotation music_notation(&drawing_interface, &get_font_bin_ref(), 20);

   std::string music_notation_content_string = " & ^        (0 2 4).   ,(0 2 5).   (-7 5 -3 '2 4).";

   music_notation.draw(1920/2-600, 1080/2, music_notation_content_string);

   al_flip_display();
   //sleep(1);
}


TEST_F(AllegroFlare_MusicNotation_MusicNotationTextWithAllegroRenderingFixture,
   CAPTURE__on_rendering__note_clusters__will_handle_octaves_as_expected)
{
   AllegroFlare::DrawingInterfaces::Allegro5 drawing_interface;
   AllegroFlare::MusicNotation::MusicNotation music_notation(&drawing_interface, &get_font_bin_ref(), 20);

   std::string music_notation_content_string = " & ^       (0 ,=4 -7 3 ,1 2 ''+6)..";

   music_notation.draw(1920/2-600, 1080/2, music_notation_content_string);

   al_flip_display();
   //sleep(1);
}


TEST_F(AllegroFlare_MusicNotation_MusicNotationTextWithAllegroRenderingFixture,
   CAPTURE__on_rendering__accidentals_on_note_clusters__will_stack_and_collapse_as_expected)
{
   AllegroFlare::DrawingInterfaces::Allegro5 drawing_interface;
   AllegroFlare::MusicNotation::MusicNotation music_notation(&drawing_interface, &get_font_bin_ref(), 20);

   std::string music_notation_content_string =
      "     (+0 +2 =5 +'0).   (+0 +2 =4 '+0).   (,6 '=1 +2 +4 6).   (,=3 +5 '=0 =2 3).   (,=1 +2 +4 =6 '=1).";

   music_notation.draw(1920/2-700, 1080/2, music_notation_content_string);

   al_flip_display();
   //sleep(1);
}


TEST_F(AllegroFlare_MusicNotation_MusicNotationTextWithAllegroRenderingFixture,
   CAPTURE__on_rendering__accidentals_will_appear_on_notes_as_expected)
{
   AllegroFlare::DrawingInterfaces::Allegro5 drawing_interface;
   AllegroFlare::MusicNotation::MusicNotation music_notation(&drawing_interface, &get_font_bin_ref(), 14);

   std::vector<std::string> notation_strings = {
      "  -0 -1 -2 -3 -4 -5 -6 '-0 -1 -2 -3 -4 -5 -6 -7",
      ",,  -0 -1 -2 -3 -4 -5 -6 '-0 -1 -2 -3 -4 -5 -6 -7",
      "  +0 +1 +2 +3 +4 +5 +6 '+0 +1 +2 +3 +4 +5 +6 +7",
      ",,  +0 +1 +2 +3 +4 +5 +6 '+0 +1 +2 +3 +4 +5 +6 +7",
      "  =0 =1 =2 =3 =4 =5 =6 '=0 =1 =2 =3 =4 =5 =6 =7",
      ",, =0 =1 =2 =3 =4 =5 =6 '=0 =1 =2 =3 =4 =5 =6 =7",
   };

   float x = 1920/2 - 600;
   float y = 1080/2 - 400;
   float spacing_y = 160;
   int count = 0;

   for (auto &notation_string : notation_strings)
   {
      music_notation.draw(x, y + spacing_y * count, notation_string);
      count++;
   }

   al_flip_display();
   //sleep(1);
}


