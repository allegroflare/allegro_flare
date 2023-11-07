
#include <gtest/gtest.h>

#include <AllegroFlare/Elements/DialogBoxes/Intertitle.hpp>


TEST(AllegroFlare_Elements_DialogBoxes_IntertitleTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Elements::DialogBoxes::Intertitle intertitle;
}


TEST(AllegroFlare_Elements_DialogBoxes_IntertitleTest, TYPE__has_the_expected_value)
{
   EXPECT_STREQ(
     "AllegroFlare/Elements/DialogBoxes/Intertitle",
     AllegroFlare::Elements::DialogBoxes::Intertitle::TYPE
   );
}


TEST(AllegroFlare_Elements_DialogBoxes_IntertitleTest, type__has_the_expected_value_matching_TYPE)
{
   AllegroFlare::Elements::DialogBoxes::Intertitle intertitle;
   EXPECT_EQ(AllegroFlare::Elements::DialogBoxes::Intertitle::TYPE, intertitle.get_type());
}


// TODO: Add tests

/*
TEST_F(AllegroFlare_Elements_DialogBoxRenderers_IntertitleTestWithAllegroRenderingFixture,
   start__will_set_the_number_of_revealed_characters_to_zero)
{
   std::string text = "Hello DialogBoxRenderers::IntertitleRenderer!";
   AllegroFlare::Elements::DialogBoxRenderers::IntertitleRenderer storyboard(&get_font_bin_ref(), text);

   storyboard.reveal_all_characters();
   EXPECT_EQ(true, storyboard.all_characters_are_revealed());
   storyboard.start();
   EXPECT_EQ(false, storyboard.all_characters_are_revealed());

}


TEST_F(AllegroFlare_Elements_DialogBoxRenderers_IntertitleTestWithAllegroRenderingFixture,
   start__will_set_finished_to_false)
{
   std::string text = "Hello DialogBoxRenderers::IntertitleRenderer!";
   AllegroFlare::Elements::DialogBoxRenderers::IntertitleRenderer storyboard(&get_font_bin_ref(), text);

   EXPECT_EQ(true, storyboard.get_finished());
   storyboard.start();
   EXPECT_EQ(false, storyboard.get_finished());
}


TEST_F(AllegroFlare_Elements_DialogBoxRenderers_IntertitleTestWithAllegroRenderingFixture,
   update__after_all_characters_have_been_revealed__and_before_wait_duration_after_all_characters_are_revealed_has_\
passed__will_not_set_finished_to_true)
{
   std::string text = "Hello DialogBoxRenderers::IntertitleRenderer!";
   AllegroFlare::Elements::DialogBoxRenderers::IntertitleRenderer storyboard(&get_font_bin_ref(), text);

   storyboard.start(); // TODO: Inject time
   storyboard.reveal_all_characters();
   EXPECT_EQ(false, storyboard.get_finished());
   storyboard.update(); // TODO: Inject time
   EXPECT_EQ(false, storyboard.get_finished());
}


TEST_F(AllegroFlare_Elements_DialogBoxRenderers_IntertitleTestWithAllegroRenderingFixture,
   update__after_all_characters_have_been_revealed__and_after_wait_duration_after_all_characters_are_revealed_has_\
passed__will_set_finished_to_true)
{
   std::string text = "Hello DialogBoxRenderers::IntertitleRenderer!";
   AllegroFlare::Elements::DialogBoxRenderers::IntertitleRenderer storyboard(&get_font_bin_ref(), text);

   storyboard.start(); // TODO: Inject time
   storyboard.reveal_all_characters();
   EXPECT_EQ(false, storyboard.get_finished());
   al_rest(3.1); // TODO: Replace this wait with injected time and a configurable wait duration
   storyboard.update(); // TODO: Inject time
   EXPECT_EQ(true, storyboard.get_finished());
}


TEST_F(AllegroFlare_Elements_DialogBoxRenderers_IntertitleTestWithAllegroRenderingFixture,
   reveal_all_characters__will_reveal_all_the_characters_on_the_current_page)
{
   std::string text = "This are characters that need to be revealed one-by-one.";
   AllegroFlare::Elements::DialogBoxRenderers::IntertitleRenderer storyboard(&get_font_bin_ref(), text);

   EXPECT_EQ(false, storyboard.all_characters_are_revealed());
   storyboard.reveal_all_characters();
   EXPECT_EQ(true, storyboard.all_characters_are_revealed());
}


TEST_F(AllegroFlare_Elements_DialogBoxRenderers_IntertitleTestWithAllegroRenderingFixture,
   reveal_all_characters__will_not_automatically_set_the_page_to_finished)
{
   std::string text = "This are characters that need to be revealed one-by-one.";
   AllegroFlare::Elements::DialogBoxRenderers::IntertitleRenderer storyboard(&get_font_bin_ref(), text);

   storyboard.start();
   storyboard.reveal_all_characters();
   EXPECT_EQ(false, storyboard.get_finished());
}


TEST_F(AllegroFlare_Elements_DialogBoxRenderers_IntertitleTestWithAllegroRenderingFixture,
   advance__when_all_characters_have_been_revealed__will_set_finished_to_true)
{
   std::string text = "Hello DialogBoxRenderers::IntertitleRenderer!";
   AllegroFlare::Elements::DialogBoxRenderers::IntertitleRenderer storyboard(&get_font_bin_ref(), text);

   storyboard.start();
   storyboard.reveal_all_characters();
   EXPECT_EQ(false, storyboard.get_finished());
   storyboard.advance();
   EXPECT_EQ(true, storyboard.get_finished());
}


TEST_F(AllegroFlare_Elements_DialogBoxRenderers_IntertitleTestWithAllegroRenderingFixture,
   advance__when_not_all_characters_have_been_revealed__will_reveal_all_the_characters)
{
   std::string text = "In this test, there is some text.";
   AllegroFlare::Elements::DialogBoxRenderers::IntertitleRenderer storyboard(&get_font_bin_ref(), text);

   storyboard.start();
   storyboard.advance();
   EXPECT_EQ(true, storyboard.all_characters_are_revealed());
}


TEST_F(AllegroFlare_Elements_DialogBoxRenderers_IntertitleTestWithAllegroRenderingFixture,
   advance__when_not_all_characters_have_been_revealed__will_not_set_finished_to_true)
{
   std::string text = "In this test, there is some text.";
   AllegroFlare::Elements::DialogBoxRenderers::IntertitleRenderer storyboard(&get_font_bin_ref(), text);

   storyboard.start();
   storyboard.advance();
   EXPECT_EQ(false, storyboard.get_finished());
}
*/



