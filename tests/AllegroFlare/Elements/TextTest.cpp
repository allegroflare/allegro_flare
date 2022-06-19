
#include <gtest/gtest.h>

#define ASSERT_THROW_WITH_MESSAGE(code, raised_exception_type, expected_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { ASSERT_EQ(std::string(expected_exception_message), err.what()); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }

#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>


class AllegroFlare_Elements_TextTest : public ::testing::Test
{};

class AllegroFlare_Elements_TextTestWithAllegroRenderingFixture
   : public AllegroFlare::Testing::WithAllegroRenderingFixture
{};


#include <AllegroFlare/Elements/Text.hpp>


TEST_F(AllegroFlare_Elements_TextTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Elements::Text text;
}


TEST_F(AllegroFlare_Elements_TextTest, render__without_allegro_initialized__raises_an_error)
{
   AllegroFlare::Elements::Text text;
   std::string expected_error_message = "Text::render: error: guard \"al_is_system_installed()\" not met";
   ASSERT_THROW_WITH_MESSAGE(text.render(), std::runtime_error, expected_error_message);
}


TEST_F(AllegroFlare_Elements_TextTestWithAllegroRenderingFixture,
   render__without_a_font_bin__will_throw_an_error)
{
   AllegroFlare::Elements::Text text;
   std::string expected_error_message = "Text::obtain_font: error: guard \"font_bin\" not met";
   ASSERT_THROW_WITH_MESSAGE(text.render(), std::runtime_error, expected_error_message);
}


TEST_F(AllegroFlare_Elements_TextTestWithAllegroRenderingFixture,
   render__will_draw_the_text_to_the_screen)
{
   AllegroFlare::FontBin &font_bin = get_font_bin_ref();
   AllegroFlare::Elements::Text text(&font_bin);
   text.render();
   al_flip_display();
   sleep(1);
   SUCCEED();
}


TEST_F(AllegroFlare_Elements_TextTestWithAllegroRenderingFixture,
   fit_placement_width_and_height_to_text__will_set_the_placement_width_and_height_to_the_dimentions_of_the_text)
{
   AllegroFlare::FontBin &font_bin = get_font_bin_ref();
   AllegroFlare::Elements::Text text(&font_bin);
   text.fit_placement_width_and_height_to_text();

   EXPECT_EQ(186, text.get_placement().size.x);
   EXPECT_EQ(48, text.get_placement().size.y);
}


