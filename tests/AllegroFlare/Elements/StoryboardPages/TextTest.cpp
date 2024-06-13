
#include <gtest/gtest.h>

#include <AllegroFlare/Testing/ErrorAssertions.hpp>
#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>


class AllegroFlare_Elements_StoryboardPages_TextTest : public ::testing::Test
{};

class AllegroFlare_Elements_StoryboardPages_TextTestWithAllegroRenderingFixture
   : public AllegroFlare::Testing::WithAllegroRenderingFixture
{};


#include <AllegroFlare/Elements/StoryboardPages/Text.hpp>


TEST_F(AllegroFlare_Elements_StoryboardPages_TextTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Elements::StoryboardPages::Text text;
}


TEST_F(AllegroFlare_Elements_StoryboardPages_TextTest, has_the_expected_type)
{
   AllegroFlare::Elements::StoryboardPages::Text text;
   EXPECT_EQ("Text", text.get_type());
}


TEST_F(AllegroFlare_Elements_StoryboardPages_TextTest, render__without_allegro_initialized__raises_an_error)
{
   AllegroFlare::Elements::StoryboardPages::Text text;
   EXPECT_THROW_GUARD_ERROR(
      text.render(),
      "AllegroFlare::Elements::StoryboardPages::Text::render",
      "al_is_system_installed()"
   );
}


TEST_F(AllegroFlare_Elements_StoryboardPages_TextTestWithAllegroRenderingFixture, render__will_not_blow_up)
{
   AllegroFlare::Elements::StoryboardPages::Text text(&get_font_bin_ref());
   text.render();
   SUCCEED();
}


TEST_F(AllegroFlare_Elements_StoryboardPages_TextTestWithAllegroRenderingFixture,
   CAPTURE__render__will_show_the_text)
{
   std::string text_to_show = "Hello StoryboardPages/Text!";
   AllegroFlare::Elements::StoryboardPages::Text text(&get_font_bin_ref(), text_to_show);
   text.render();
   al_flip_display();
   SUCCEED();
}


