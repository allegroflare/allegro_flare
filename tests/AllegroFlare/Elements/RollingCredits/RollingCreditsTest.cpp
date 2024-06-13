
#include <gtest/gtest.h>

#include <AllegroFlare/Testing/ErrorAssertions.hpp>
#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>


#include <AllegroFlare/Elements/RollingCredits/Sections/Header.hpp>
#include <AllegroFlare/Elements/RollingCredits/Sections/ColumnWithLabels.hpp>
#include <AllegroFlare/Elements/RollingCredits/Sections/Text.hpp>
#include <AllegroFlare/Elements/RollingCredits/Sections/Multicolumn.hpp>


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
   EXPECT_THROW_GUARD_ERROR(
      rolling_credits.render(),
      "AllegroFlare::Elements::RollingCredits::RollingCredits::render",
      "al_is_system_installed()"
   );
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
      new AllegroFlare::Elements::RollingCredits::Sections::ColumnWithLabels(
         { std::pair<std::string, std::string>("Producer", "Mark Oates") }
      ),
   });

   rolling_credits.render();
   al_flip_display();
   //sleep_for(1);

   // TODO: destroy sections
}


TEST_F(AllegroFlare_Elements_RollingCredits_RollingCreditsTestWithAllegroRenderingFixture,
   CAPTURE__render__will_render_a_Multicolumn_section)
{
   //using namespace AllegroFlare::Elements::RollingCredits::Sections;

   AllegroFlare::Elements::RollingCredits::RollingCredits rolling_credits(&get_font_bin_ref());
   rolling_credits.set_sections({
      new AllegroFlare::Elements::RollingCredits::Sections::Multicolumn({
         {
            { "Robyn Kendall" },
            { "Tayyibah Samuels" },
            { "Ryker Odling" },
            { "Yuki Nakamura" },
         },
         {
            { "Annaliese Bauer" },
            { "Anya Schofield" },
            { "Ellenor Cote" },
            { "Emily Davis" },
            { "Aiza Rivera" },
         },
         {
            { "Kaito Tanaka" },
            { "Marcus Bennett" },
            { "Natalie Hayes" },
            { "Jordan Parker" },
            { "Morgan Reynolds" },
         },
         {
            { "Katy Swanson" },
            { "Melina Kelly" },
            { "Ryu Kim" },
            { "Abby Burton" },
         },
      }),
   });

   rolling_credits.render();
   al_flip_display();
   sleep_for(1);

   // TODO: destroy sections
}


#include <AllegroFlare/Elements/RollingCredits/SectionFactory.hpp>
TEST_F(AllegroFlare_Elements_RollingCredits_RollingCreditsTestWithAllegroRenderingFixture,
   CAPTURE__render__will_render_allegro_contributors_nicely)
{
   //TODO: Move this test somewhere else, in another class or something
   AllegroFlare::Elements::RollingCredits::SectionFactory section_factory;

   AllegroFlare::Elements::RollingCredits::RollingCredits rolling_credits(&get_font_bin_ref());
   rolling_credits.set_sections({
      new AllegroFlare::Elements::RollingCredits::Sections::Header("People who have contributed code to Allegro 5"),
      section_factory.create_allegro5_contributors_list(3)
   });

   rolling_credits.render();
   al_flip_display();
   sleep_for(1);

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
         std::pair<std::string, std::string>("Producer", "Turtle McShell"),
         std::pair<std::string, std::string>("Line Producer", "Zeebra Stripe"),
         std::pair<std::string, std::string>("Lead Programmer", "Selma Sloth"),
      }),
      new Text("No animals were harmed in the making of these credits."),
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
         std::pair<std::string, std::string>("Producer", "Turtle McShell"),
         std::pair<std::string, std::string>("Line Producer", "Zeebra Stripe"),
         std::pair<std::string, std::string>("Lead Programmer", "Selma Sloth"),
      }),
      new Text("No animals were harmed in the making of these credits."),
   });

   float calculated_height = rolling_credits.calculate_height();
   float surface_center = rolling_credits.get_surface_width() / 2;

   EXPECT_EQ(271, calculated_height);

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
         std::pair<std::string, std::string>("Producer", "Turtle McShell"),
         std::pair<std::string, std::string>("Line Producer", "Zeebra Stripe"),
         std::pair<std::string, std::string>("Lead Programmer", "Selma Sloth"),
      }),
      new Text("No animals were harmed in the making of these credits."),
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
         std::pair<std::string, std::string>("Producer", "Turtle McShell"),
         std::pair<std::string, std::string>("Line Producer", "Zeebra Stripe"),
         std::pair<std::string, std::string>("Lead Programmer", "Selma Sloth"),
      }),
      new Text("No animals were harmed in the making of these credits."),
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


