
#include <gtest/gtest.h>

#define EXPECT_THROW_WITH_MESSAGE(code, raised_exception_type, expected_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { EXPECT_EQ(std::string(expected_exception_message), err.what()); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }

#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>

#include <AllegroFlare/EventNames.hpp>


class AllegroFlare_Elements_AdvancingTextTest : public ::testing::Test
{};

class AllegroFlare_Elements_AdvancingTextTestWithAllegroRenderingFixture
   : public AllegroFlare::Testing::WithAllegroRenderingFixture
{};


#include <AllegroFlare/Elements/AdvancingText.hpp>


TEST_F(AllegroFlare_Elements_AdvancingTextTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Elements::AdvancingText advancing_text;
}


TEST_F(AllegroFlare_Elements_AdvancingTextTestWithAllegroRenderingFixture,
   start__will_set_the_number_of_revealed_characters_to_zero)
{
   std::string text = "Hello AdvancingText!";
   AllegroFlare::Elements::AdvancingText advancing_text(text);

   advancing_text.reveal_all_characters();
   EXPECT_EQ(true, advancing_text.get_all_characters_are_revealed());
   advancing_text.start();
   EXPECT_EQ(false, advancing_text.get_all_characters_are_revealed());

}


TEST_F(AllegroFlare_Elements_AdvancingTextTestWithAllegroRenderingFixture,
   start__will_set_all_characters_to_revealed_to_false)
{
   std::string text = "Hello AdvancingText!";
   AllegroFlare::Elements::AdvancingText advancing_text(text);

   advancing_text.reveal_all_characters();
   EXPECT_EQ(true, advancing_text.get_all_characters_are_revealed());
   advancing_text.start();
   EXPECT_EQ(false, advancing_text.get_all_characters_are_revealed());
}


TEST_F(AllegroFlare_Elements_AdvancingTextTestWithAllegroRenderingFixture,
   after_all_characters_have_been_revealed__will_set_all_characters_are_revealed_to_true)
{
   std::string text = "Hello AdvancingText!";
   AllegroFlare::Elements::AdvancingText advancing_text(text);

   advancing_text.start();
   advancing_text.reveal_all_characters();
   EXPECT_EQ(true, advancing_text.get_all_characters_are_revealed());
}


TEST_F(AllegroFlare_Elements_AdvancingTextTestWithAllegroRenderingFixture,
   reveal_all_characters__will_reveal_all_the_characters_on_the_current_page)
{
   std::string text = "This are characters that need to be revealed one-by-one.";
   AllegroFlare::Elements::AdvancingText advancing_text(text);

   EXPECT_EQ(false, advancing_text.get_all_characters_are_revealed());
   advancing_text.reveal_all_characters();
   EXPECT_EQ(true, advancing_text.get_all_characters_are_revealed());
}


// TODO: Add more tests that confirm the expected advancement of "revealed_characters_count" considering rate, etc


