
#include <gtest/gtest.h>

#include <AllegroFlare/Testing/ErrorAssertions.hpp>
#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>


#include <AllegroFlare/Elements/RollingCredits/SectionRenderers/Text.hpp>
#include <AllegroFlare/Elements/RollingCredits/Sections/Text.hpp>

class AllegroFlare_Elements_RollingCredits_SectionRenderers_TextTest : public ::testing::Test
{};

class AllegroFlare_Elements_RollingCredits_SectionRenderers_TextTestWithAllegroRenderingFixture
   : public AllegroFlare::Testing::WithAllegroRenderingFixture
{};




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
   EXPECT_THROW_WITH_MESSAGE(text_section_renderer.render(), std::runtime_error, expected_error_message);
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
   text_section_renderer.set_x(1920/2);
   text_section_renderer.set_y(1080/2);
   text_section_renderer.render();
   al_flip_display();
   al_rest(1);
}


TEST_F(AllegroFlare_Elements_RollingCredits_SectionRenderers_TextTestWithAllegroRenderingFixture,
   CAPTURE__render__will_respect_a_centered_alignment)
{
   // TODO: finish this test
   std::string text = "This game is a work of fiction. Any resemblance to actual persons, living or dead, "
      "or events is purely coincidental.";
   AllegroFlare::Elements::RollingCredits::SectionRenderers::Text text_section_renderer(
      &get_font_bin_ref(),
      text,
      AllegroFlare::Elements::RollingCredits::Sections::Text::ALIGN_CENTER
   );
   text_section_renderer.set_x(1920/2);
   text_section_renderer.set_y(1080/2);
   text_section_renderer.render();
   al_flip_display();
   al_rest(1);
}


TEST_F(AllegroFlare_Elements_RollingCredits_SectionRenderers_TextTestWithAllegroRenderingFixture,
   CAPTURE__render__with_an_invalid_alignment__will_throw_an_error)
{
   // TODO: finish this test
   AllegroFlare::Elements::RollingCredits::SectionRenderers::Text text_section_renderer(
      &get_font_bin_ref(),
      "foobar",
      "this-is-an-invalid-alignment"
   );
   text_section_renderer.render();
}


TEST_F(AllegroFlare_Elements_RollingCredits_SectionRenderers_TextTestWithAllegroRenderingFixture,
   render__will_return_the_height_of_the_section)
{
   // TODO
}


