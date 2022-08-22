
#include <gtest/gtest.h>

#define ASSERT_THROW_WITH_MESSAGE(code, raised_exception_type, expected_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { ASSERT_EQ(std::string(expected_exception_message), err.what()); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }

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
   std::string expected_error_message =
      "Header::render: error: guard \"al_is_system_installed()\" not met";
   ASSERT_THROW_WITH_MESSAGE(header_section_renderer.render(), std::runtime_error, expected_error_message);
}


TEST_F(AllegroFlare_Elements_RollingCredits_SectionRenderers_HeaderTestWithAllegroRenderingFixture,
   render__will_not_blow_up)
{
   AllegroFlare::Elements::RollingCredits::SectionRenderers::Header header_section_renderer(&get_font_bin_ref());
   header_section_renderer.render();
   SUCCEED();
}


