
#include <gtest/gtest.h>

#define ASSERT_THROW_WITH_MESSAGE(code, raised_exception_type, expected_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { ASSERT_EQ(std::string(expected_exception_message), err.what()); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }

#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>


#include <AllegroFlare/Elements/RollingCredits/Sections/Header.hpp>
#include <AllegroFlare/Elements/RollingCredits/Sections/ColumnWithLabels.hpp>


class AllegroFlare_Elements_RollingCredits_RollingCreditsTest : public ::testing::Test
{};

class AllegroFlare_Elements_RollingCredits_RollingCreditsTestWithAllegroRenderingFixture
   : public AllegroFlare::Testing::WithAllegroRenderingFixture
{};


#include <AllegroFlare/Elements/RollingCredits/RollingCredits.hpp>


TEST_F(AllegroFlare_Elements_RollingCredits_RollingCreditsTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Elements::RollingCredits::RollingCredits rolling_credits;
}


TEST_F(AllegroFlare_Elements_RollingCredits_RollingCreditsTest, render__without_allegro_initialized__raises_an_error)
{
   AllegroFlare::Elements::RollingCredits::RollingCredits rolling_credits;
   std::string expected_error_message =
      "RollingCredits::render: error: guard \"al_is_system_installed()\" not met";
   ASSERT_THROW_WITH_MESSAGE(rolling_credits.render(), std::runtime_error, expected_error_message);
}


TEST_F(AllegroFlare_Elements_RollingCredits_RollingCreditsTestWithAllegroRenderingFixture, render__will_not_blow_up)
{
   AllegroFlare::Elements::RollingCredits::RollingCredits rolling_credits;
   rolling_credits.render();
   SUCCEED();
}


TEST_F(AllegroFlare_Elements_RollingCredits_RollingCreditsTest, set_sections__will_set_the_sections)
{
   // TODO
}


TEST_F(AllegroFlare_Elements_RollingCredits_RollingCreditsTest, set_sections__will_reset_the_y_offset_to_0)
{
   // TODO
}


TEST_F(AllegroFlare_Elements_RollingCredits_RollingCreditsTestWithAllegroRenderingFixture,
   render__will_render_a_Header_section)
{
   //using namespace AllegroFlare::Elements::RollingCredits::Sections;

   AllegroFlare::Elements::RollingCredits::RollingCredits rolling_credits(&get_font_bin_ref());
   rolling_credits.set_sections({
      new AllegroFlare::Elements::RollingCredits::Sections::Header("This is the header text"),
   });

   rolling_credits.render();
   al_flip_display();
   //sleep_for(1);

   // TODO: destroy sections
}


TEST_F(AllegroFlare_Elements_RollingCredits_RollingCreditsTestWithAllegroRenderingFixture,
   render__will_render_a_ColumnWithLabels_section)
{
   //using namespace AllegroFlare::Elements::RollingCredits::Sections;

   AllegroFlare::Elements::RollingCredits::RollingCredits rolling_credits(&get_font_bin_ref());
   rolling_credits.set_sections({
      new AllegroFlare::Elements::RollingCredits::Sections::ColumnWithLabels({ { "Producer", "Mark Oates" } }),
   });

   rolling_credits.render();
   al_flip_display();
   //sleep_for(1);

   // TODO: destroy sections
}


TEST_F(AllegroFlare_Elements_RollingCredits_RollingCreditsTestWithAllegroRenderingFixture,
   CAPTURE__render__will_render_multiple_sections_with_a_divider)
{
   using namespace AllegroFlare::Elements::RollingCredits::Sections;

   AllegroFlare::Elements::RollingCredits::RollingCredits rolling_credits(&get_font_bin_ref());
   rolling_credits.set_sections({
      new Header("Section Header"),
      new ColumnWithLabels({
         { "Producer", "Turtle McShell" },
         { "Line Producer", "Zeebra Stripe" },
         { "Lead Programmer", "Selma Sloth" },
      }),
   });

   rolling_credits.render();
   al_flip_display();
   //sleep_for(1);

   // TODO: destroy sections
}


TEST_F(AllegroFlare_Elements_RollingCredits_RollingCreditsTestWithAllegroRenderingFixture,
   CAPTURE__render__will_return_the_height_of_the_entire_credits)
{
   using namespace AllegroFlare::Elements::RollingCredits::Sections;

   AllegroFlare::Elements::RollingCredits::RollingCredits rolling_credits(&get_font_bin_ref());
   rolling_credits.set_sections({
      new Header("Section Header"),
      new ColumnWithLabels({
         { "Producer", "Turtle McShell" },
         { "Line Producer", "Zeebra Stripe" },
         { "Lead Programmer", "Selma Sloth" },
      }),
   });

   float height = rolling_credits.render();
   float surface_center = rolling_credits.get_surface_width() / 2;
   draw_horizontal_crosshair(surface_center, height);

   al_flip_display();
   sleep_for(1);

   // TODO: destroy sections
}


