#include <gtest/gtest.h>

#include <AllegroFlare/Testing/ErrorAssertions.hpp>
#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>
#include <AllegroFlare/TextFormatter/Basic.hpp>
#include <allegro5/allegro_primitives.h> // for al_is_primitives_addon_initialized();


class AllegroFlare_TextFormatter_BasicTest : public ::testing::Test {};
class AllegroFlare_TextFormatter_BasicTestWithAllegroRenderingFixture
   : public AllegroFlare::Testing::WithAllegroRenderingFixture
{};



TEST_F(AllegroFlare_TextFormatter_BasicTest, can_be_created_without_blowing_up)
{
   AllegroFlare::TextFormatter::Basic basic;
}


TEST_F(AllegroFlare_TextFormatter_BasicTest, render__without_allegro_initialized__raises_an_error)
{
   AllegroFlare::TextFormatter::Basic basic;
   EXPECT_THROW_GUARD_ERROR(basic.render(), "AllegroFlare::TextFormatter::Basic::render", "al_is_system_installed()");
}


TEST_F(AllegroFlare_TextFormatter_BasicTestWithAllegroRenderingFixture, CAPTURE__render__will_not_blow_up)
{
   AllegroFlare::TextFormatter::Basic basic(&get_font_bin_ref());
   basic.render();
   al_flip_display();
}


TEST_F(AllegroFlare_TextFormatter_BasicTest, parse_into_chunks__will_generate_the_expected_chunks)
{
   std::string raw_text_source = "This is some (color=green)dialog text(color=normal) that will fill this box.";

   std::vector<std::pair<bool, std::string>> expected_chunks = {
      { false, "This is some " },
      { true, "color=green" },
      { false, "dialog text" },
      { true, "color=normal" },
      { false, " that will fill this box." },
   };
   std::vector<std::pair<bool, std::string>> actual_chunks =
      AllegroFlare::TextFormatter::Basic::parse_into_chunks(raw_text_source);

   EXPECT_EQ(expected_chunks, actual_chunks);
}


TEST_F(AllegroFlare_TextFormatter_BasicTestWithAllegroRenderingFixture, CAPTURE__calculate_line_breaks__will_\
return_a_list_of_character_indexes_where_line_breaks_should_occur)
{
   //std::string raw_text_source = "This is some (color=green)dialog text(color=normal) that will fill this box.";
   std::string raw_text_source = "This is some dialog text that will fill this box.";

   std::set<int> expected_line_break_indices = { 13, 25, 40, 50 };
   AllegroFlare::TextFormatter::Basic basic(&get_font_bin_ref());
   std::set<int> actual_line_break_indices = basic.calculate_line_breaks(raw_text_source);

   EXPECT_EQ(expected_line_break_indices, actual_line_break_indices);

   // Draw the normal multiline for reference:
   clear();
   ALLEGRO_FONT *font = get_font_bin_ref().auto_get("Inter-Medium.ttf -52");
   al_draw_multiline_text(
      font,
      ALLEGRO_COLOR{1, 1, 1, 1},
      100,
      100,
      300,
      al_get_font_line_height(font),
      ALLEGRO_ALIGN_LEFT,
      raw_text_source.c_str()
   );
   al_flip_display();
   al_rest(1);
}


TEST_F(AllegroFlare_TextFormatter_BasicTestWithAllegroRenderingFixture, CAPTURE__render__will_\
render_formatted_text_with_the_expected_line_breaks)
{
   std::string raw_text_source = "This is some dialog text that will fill this box.";
   AllegroFlare::TextFormatter::Basic basic(&get_font_bin_ref());
   basic.set_text(raw_text_source);

   clear();
   basic.render();
   al_flip_display();
   al_rest(1);
}


TEST_F(AllegroFlare_TextFormatter_BasicTestWithAllegroRenderingFixture, FOCUS__CAPTURE__render__with_formatting_tags__\
will_render_formatted_text_with_the_expected_line_breaks)
{
   std::string raw_text_source =
      "Lorem ipsum dolor sit amet, (em)consectetur adipiscing(/em) elit. Donec fringilla arcu "
      "nec magna mattis cursus. Maecenas (em)non justo urna(/em). Vivamus eu augue tristique, "
      "pharetra enim ut, sollicitudin quam. Aenean ut purus at enim elementum rhoncus. "
      "In a finibus sapien. Donec mattis laoreet luctus. Aliquam eu accumsan sapien, at "
      "congue massa. Phasellus consequat sapien ac scelerisque finibus. Curabitur "
      "hendrerit, diam eget faucibus rhoncus, ante nulla mattis lorem, vitae semper "
      "sapien sem sit amet ex. (em)Donec sit(/em) amet dolor libero. Vestibulum ante ipsum "
      "primis in faucibus orci luctus et ultrices posuere cubilia curae; Nunc dignissim "
      "aliquam luctus. Sed varius odio a neque ultrices, ac pretium ligula aliquam. "
      "Proin neque arcu, gravida et nisi non, ullamcorper fringilla ligula. Duis "
      "laoreet sollicitudin nunc, eu ornare diam consequat ac. Duis dapibus tellus ac "
      "mauris bibendum finibus.";

   AllegroFlare::TextFormatter::Basic basic(&get_font_bin_ref());
   float box_max_width = 1920/3*2;
   basic.set_text(raw_text_source);
   basic.set_x(1920/2 - box_max_width/2);
   basic.set_y(1080/6);
   basic.set_max_text_box_width(box_max_width);
   basic.set_font_size(28);

   int num_revealed_characters = 0;
   for (int i=0; i<300; i++)
   {
      clear();
      basic.set_num_revealed_characters(i);
      basic.render();
      al_flip_display();
   }

   al_rest(1);
}


/*
TEST(AllegroFlare_Elements_DialogBoxes_InterparsableTest, parse_into_chunks__when_only_an_operational_chunk_is_\
present__will_parse_only_a_single_operational_chunk)
{
   std::string raw_text_source = "(character_sprite=happy)";

   std::vector<std::pair<bool, std::string>> expected_chunks = {
      { true, "character_sprite=happy" },
   };
   std::vector<std::pair<bool, std::string>> actual_chunks =
      AllegroFlare::Elements::DialogBoxes::Interparsable::parse_into_chunks(raw_text_source);

   EXPECT_EQ(expected_chunks, actual_chunks);
}


TEST(AllegroFlare_Elements_DialogBoxes_InterparsableTest, collate_raw_text_source__will_return_text_that_has_\
operational_chunks_removed)
{
   std::string raw_text_source = "This is (color=green)dialog text(color=normal) that that has operational chunks.";

   std::string expected_processed_text = "This is dialog text that that has operational chunks.";
   std::string actual_processed_text = 
      AllegroFlare::Elements::DialogBoxes::Interparsable::collate_printable_text_only(raw_text_source);

   EXPECT_EQ(expected_processed_text, actual_processed_text);
}


TEST(AllegroFlare_Elements_DialogBoxes_InterparsableTest, parse_into_chunks__with_an_uneven_number_of_parens__will_\
throw_an_error)
{
   std::string raw_text_source = "This is some text ( that has a missing) closing (paren.";

   EXPECT_THROW_WITH_MESSAGE(
      AllegroFlare::Elements::DialogBoxes::Interparsable::parse_into_chunks(raw_text_source),
      std::runtime_error,
      "[AllegroFlare::Elements::DialogBoxes::Interparsable::parse_into_chunks]: error: Unmatched opening parenthesis "
         "found in text \"This is some text ( that has a missing) closing (paren.\""
   );
}


TEST(AllegroFlare_Elements_DialogBoxes_InterparsableTest, parse_into_chunks__when_nested_parens_are_present__will_\
throw_an_error)
{
   std::string raw_text_source = "This is some text ( that has nested ( parens ) ).";

   EXPECT_THROW_WITH_MESSAGE(
      AllegroFlare::Elements::DialogBoxes::Interparsable::parse_into_chunks(raw_text_source),
      std::runtime_error,
      "[AllegroFlare::Elements::DialogBoxes::Interparsable::parse_into_chunks]: error: Nested parentheses were "
         "found in the text \"This is some text ( that has nested ( parens ) ).\". Nested parens are not supported."
   );
}


TEST(AllegroFlare_Elements_DialogBoxes_InterparsableTest, parse_into_chunks__when_a_closing_paren_is_present_before_\
an_opening_paren__will_throw_an_error)
{
   std::string raw_text_source = "This is some text ) that has incorrect ( parens ) ).";

   EXPECT_THROW_WITH_MESSAGE(
      AllegroFlare::Elements::DialogBoxes::Interparsable::parse_into_chunks(raw_text_source),
      std::runtime_error,
      "[AllegroFlare::Elements::DialogBoxes::Interparsable::parse_into_chunks]: error: There was an open paren that "
         "does not have a matching closing paren in the text \"This is some text ) that has incorrect ( parens ) ).\""
   );
}
*/


