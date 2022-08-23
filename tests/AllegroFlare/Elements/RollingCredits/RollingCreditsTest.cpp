
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
   calculate_height__will_return_the_height_of_the_entire_credits)
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

   float calculated_height = rolling_credits.calculate_height();
   float surface_center = rolling_credits.get_surface_width() / 2;

   EXPECT_EQ(176, calculated_height);

   // TODO: destroy sections
}


TEST_F(AllegroFlare_Elements_RollingCredits_RollingCreditsTestWithAllegroRenderingFixture,
   CAPTURE__calculate_height__will_match_the_height_of_the_entire_credits)
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

   float calculated_height = rolling_credits.calculate_height();
   float surface_center = rolling_credits.get_surface_width() / 2;

   // render the test capture
   clear();
   rolling_credits.render();
   draw_horizontal_crosshair(surface_center, calculated_height);

   al_flip_display();
   sleep_for(1);

   // TODO: destroy sections
}


TEST_F(AllegroFlare_Elements_RollingCredits_RollingCreditsTestWithAllegroRenderingFixture,
   CAPTURE__render__will_offset_vertically_by_the_y_offset)
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

   int passes = 60 * 2;
   float surface_center = rolling_credits.get_surface_width() / 2;
   for (int pass=0; pass<passes; pass++)
   {
      clear();

      float y_offset = pass * 3.0f;

      draw_horizontal_crosshair(surface_center, y_offset);
      rolling_credits.set_y_offset(y_offset);

      rolling_credits.render();
      
      al_flip_display();
      //sleep_for_frame();
   }

   // TODO: destroy sections
}


