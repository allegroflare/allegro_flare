
#include <gtest/gtest.h>

#include <AllegroFlare/Testing/ErrorAssertions.hpp>
#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>


#include <AllegroFlare/Elements/RollingCredits/SectionRenderers/LegalText.hpp>
#include <AllegroFlare/Elements/RollingCredits/Sections/LegalText.hpp>

class AllegroFlare_Elements_RollingCredits_SectionRenderers_LegalTextTest : public ::testing::Test
{};

class AllegroFlare_Elements_RollingCredits_SectionRenderers_LegalTextTestWithAllegroRenderingFixture
   : public AllegroFlare::Testing::WithAllegroRenderingFixture
{};




TEST_F(AllegroFlare_Elements_RollingCredits_SectionRenderers_LegalTextTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Elements::RollingCredits::SectionRenderers::LegalText legal_text;
}


TEST_F(AllegroFlare_Elements_RollingCredits_SectionRenderers_LegalTextTest, TYPE__has_the_expected_value)
{
   AllegroFlare::Elements::RollingCredits::SectionRenderers::LegalText legal_text;
   EXPECT_EQ(
      "AllegroFlare/Elements/RollingCredits/SectionRenderers/LegalText",
      legal_text.get_type()
   );
}


TEST_F(AllegroFlare_Elements_RollingCredits_SectionRenderers_LegalTextTest, type__has_the_expected_value_matching_TYPE)
{
   AllegroFlare::Elements::RollingCredits::SectionRenderers::LegalText legal_text;
   EXPECT_EQ(AllegroFlare::Elements::RollingCredits::SectionRenderers::LegalText::TYPE, legal_text.get_type());
}


TEST_F(AllegroFlare_Elements_RollingCredits_SectionRenderers_LegalTextTest,
   render__without_allegro_initialized__raises_an_error)
{
   AllegroFlare::Elements::RollingCredits::SectionRenderers::LegalText legal_text_section_renderer;
   EXPECT_THROW_GUARD_ERROR(
      legal_text_section_renderer.render(),
      "AllegroFlare::Elements::RollingCredits::SectionRenderers::LegalText::render",
      "al_is_system_installed()"
   );
}


TEST_F(AllegroFlare_Elements_RollingCredits_SectionRenderers_LegalTextTestWithAllegroRenderingFixture,
   render__will_not_blow_up)
{
   AllegroFlare::Elements::RollingCredits::SectionRenderers::LegalText legal_text_section_renderer(&get_font_bin_ref());
   legal_text_section_renderer.render();
   SUCCEED();
}


TEST_F(AllegroFlare_Elements_RollingCredits_SectionRenderers_LegalTextTestWithAllegroRenderingFixture,
   CAPTURE__render__will_render_the_legal_text_as_expected)
{
   std::string legal_text = "This game is a work of fiction. Any resemblance to actual persons, living or dead, "
      "or events is purely coincidental.";
   AllegroFlare::Elements::RollingCredits::SectionRenderers::LegalText legal_text_section_renderer(
      &get_font_bin_ref(),
      legal_text
   );
   legal_text_section_renderer.set_x(1920/2);
   legal_text_section_renderer.set_y(1080/2);
   legal_text_section_renderer.render();
   al_flip_display();
   al_rest(1);
}


TEST_F(AllegroFlare_Elements_RollingCredits_SectionRenderers_LegalTextTestWithAllegroRenderingFixture,
   CAPTURE__render__will_respect_a_centered_alignment)
{
   // TODO: finish this test
   std::string legal_text = "This game is a work of fiction. Any resemblance to actual persons, living or dead, "
      "or events is purely coincidental.";
   AllegroFlare::Elements::RollingCredits::SectionRenderers::LegalText legal_text_section_renderer(
      &get_font_bin_ref(),
      legal_text,
      AllegroFlare::Elements::RollingCredits::Sections::LegalText::ALIGN_CENTER
   );
   legal_text_section_renderer.set_x(1920/2);
   legal_text_section_renderer.set_y(1080/2);
   legal_text_section_renderer.render();
   al_flip_display();
   al_rest(1);
}


TEST_F(AllegroFlare_Elements_RollingCredits_SectionRenderers_LegalTextTestWithAllegroRenderingFixture,
   CAPTURE__render__with_an_invalid_alignment__will_throw_an_error)
{
   // TODO: finish this test
   AllegroFlare::Elements::RollingCredits::SectionRenderers::LegalText legal_text_section_renderer(
      &get_font_bin_ref(),
      "foobar",
      "this-is-an-invalid-alignment"
   );
   legal_text_section_renderer.render();
}


TEST_F(AllegroFlare_Elements_RollingCredits_SectionRenderers_LegalTextTestWithAllegroRenderingFixture,
   render__will_return_the_height_of_the_section)
{
   // TODO
}


