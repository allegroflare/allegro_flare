
#include <gtest/gtest.h>

#define ASSERT_THROW_WITH_MESSAGE(code, raised_exception_type, expected_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { ASSERT_EQ(std::string(expected_exception_message), err.what()); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }

#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>


class AllegroFlare_Elements_RollingCredits_SectionRenderers_TextTest : public ::testing::Test
{};

class AllegroFlare_Elements_RollingCredits_SectionRenderers_TextTestWithAllegroRenderingFixture
   : public AllegroFlare::Testing::WithAllegroRenderingFixture
{};


#include <AllegroFlare/Elements/RollingCredits/SectionRenderers/Text.hpp>



TEST_F(AllegroFlare_Elements_RollingCredits_SectionRenderers_TextTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Elements::RollingCredits::SectionRenderers::Text text;
}


TEST_F(AllegroFlare_Elements_RollingCredits_SectionRenderers_TextTest, TYPE__has_the_expected_value)
{
   AllegroFlare::Elements::RollingCredits::SectionRenderers::Text text;
   EXPECT_EQ("SectionRenderers/Text", text.get_type());
}


TEST_F(AllegroFlare_Elements_RollingCredits_SectionRenderers_TextTest, type__has_the_expected_value_matching_TYPE)
{
   AllegroFlare::Elements::RollingCredits::SectionRenderers::Text text;
   EXPECT_EQ(AllegroFlare::Elements::RollingCredits::SectionRenderers::Text::TYPE, text.get_type());
}


TEST_F(AllegroFlare_Elements_RollingCredits_SectionRenderers_TextTest,
   render__without_allegro_initialized__raises_an_error)
{
   AllegroFlare::Elements::RollingCredits::SectionRenderers::Text text_section_renderer;
   std::string expected_error_message =
      "Text::render: error: guard \"al_is_system_installed()\" not met";
   ASSERT_THROW_WITH_MESSAGE(text_section_renderer.render(), std::runtime_error, expected_error_message);
}


TEST_F(AllegroFlare_Elements_RollingCredits_SectionRenderers_TextTestWithAllegroRenderingFixture,
   render__will_not_blow_up)
{
   AllegroFlare::Elements::RollingCredits::SectionRenderers::Text text_section_renderer(&get_font_bin_ref());
   text_section_renderer.render();
   SUCCEED();
}


TEST_F(AllegroFlare_Elements_RollingCredits_SectionRenderers_TextTestWithAllegroRenderingFixture,
   CAPTURE__render__will_render_the_text_as_expected)
{
   std::string text = "This game is a work of fiction. Any resemblance to actual persons, living or dead, "
      "or events is purely coincidental.";
   AllegroFlare::Elements::RollingCredits::SectionRenderers::Text text_section_renderer(
      &get_font_bin_ref(),
      text
   );
   text_section_renderer.render();
   al_flip_display();
   al_rest(1);
}


