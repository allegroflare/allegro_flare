
#include <gtest/gtest.h>

#include <AllegroFlare/Testing/ErrorAssertions.hpp>
#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>


class AllegroFlare_Elements_RollingCredits_SectionRenderers_HeaderTest : public ::testing::Test
{};

class AllegroFlare_Elements_RollingCredits_SectionRenderers_HeaderTestWithAllegroRenderingFixture
   : public AllegroFlare::Testing::WithAllegroRenderingFixture
{};


#include <AllegroFlare/Elements/RollingCredits/SectionRenderers/Header.hpp>


TEST_F(AllegroFlare_Elements_RollingCredits_SectionRenderers_HeaderTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Elements::RollingCredits::SectionRenderers::Header header_section_renderer;
}


TEST_F(AllegroFlare_Elements_RollingCredits_SectionRenderers_HeaderTest,
   render__without_allegro_initialized__raises_an_error)
{
   AllegroFlare::Elements::RollingCredits::SectionRenderers::Header header_section_renderer;
   EXPECT_THROW_GUARD_ERROR(
      header_section_renderer.render(),
      "AllegroFlare::Elements::RollingCredits::SectionRenderers::Header::render",
      "al_is_system_installed()"
   );
}


TEST_F(AllegroFlare_Elements_RollingCredits_SectionRenderers_HeaderTestWithAllegroRenderingFixture,
   render__will_not_blow_up)
{
   AllegroFlare::Elements::RollingCredits::SectionRenderers::Header header_section_renderer(&get_font_bin_ref());
   header_section_renderer.render();
   SUCCEED();
}


TEST_F(AllegroFlare_Elements_RollingCredits_SectionRenderers_HeaderTestWithAllegroRenderingFixture,
   CAPTURE__render__will_appear_as_expected)
{
   // TODO: Move subject to center of screen and add positioning crosshairs
   AllegroFlare::Elements::RollingCredits::SectionRenderers::Header header_section_renderer(&get_font_bin_ref());
   header_section_renderer.render();
   al_flip_display();
   SUCCEED();
}


