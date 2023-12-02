
#include <gtest/gtest.h>
#include <AllegroFlare/Testing/ErrorAssertions.hpp>
#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>

#include <AllegroFlare/Elements/RollingCredits/SectionRenderers/Multicolumn.hpp>


class AllegroFlare_Elements_RollingCredits_SectionRenderers_MulticolumnTest : public ::testing::Test
{};

class AllegroFlare_Elements_RollingCredits_SectionRenderers_MulticolumnTestWithAllegroRenderingFixture
   : public AllegroFlare::Testing::WithAllegroRenderingFixture
{};


TEST_F(AllegroFlare_Elements_RollingCredits_SectionRenderers_MulticolumnTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Elements::RollingCredits::SectionRenderers::Multicolumn column_with_labels_section_renderer;
}


TEST_F(AllegroFlare_Elements_RollingCredits_SectionRenderers_MulticolumnTest,
   TYPE__has_the_expected_value)
{
   EXPECT_STREQ(
     "AllegroFlare/Elements/RollingCredits/SectionRenderers/Multicolumn",
     AllegroFlare::Elements::RollingCredits::SectionRenderers::Multicolumn::TYPE
   );
}


TEST_F(AllegroFlare_Elements_RollingCredits_SectionRenderers_MulticolumnTest,
   type__has_the_expected_value_matching_TYPE)
{
   AllegroFlare::Elements::RollingCredits::SectionRenderers::Multicolumn multicolumn;
   EXPECT_EQ(AllegroFlare::Elements::RollingCredits::SectionRenderers::Multicolumn::TYPE, multicolumn.get_type());
}


TEST_F(AllegroFlare_Elements_RollingCredits_SectionRenderers_MulticolumnTest,
   render__without_allegro_initialized__raises_an_error)
{
   AllegroFlare::Elements::RollingCredits::SectionRenderers::Multicolumn column_with_labels_section_renderer;
   std::string expected_error_message =
      "Multicolumn::render: error: guard \"al_is_system_installed()\" not met";
   ASSERT_THROW_WITH_MESSAGE(column_with_labels_section_renderer.render(), std::runtime_error, expected_error_message);
}


TEST_F(AllegroFlare_Elements_RollingCredits_SectionRenderers_MulticolumnTestWithAllegroRenderingFixture,
   render__will_not_blow_up)
{
   AllegroFlare::Elements::RollingCredits::SectionRenderers::Multicolumn column_with_labels_section_renderer(
      &get_font_bin_ref()
   );
   column_with_labels_section_renderer.render();
}


TEST_F(AllegroFlare_Elements_RollingCredits_SectionRenderers_MulticolumnTestWithAllegroRenderingFixture,
   CAPTURE__render__will_render_as_expected)
{
   AllegroFlare::Elements::RollingCredits::SectionRenderers::Multicolumn column_with_labels_section_renderer(
      &get_font_bin_ref(), {}, 1920/2, 1080/2, 1920-600
   );
   column_with_labels_section_renderer.set_elements({
      {
         { "Robyn Kendall" },
         { "Tayyibah Samuels" },
         { "Ryker Odling" },
      },
      {
         { "Aiza Rivera" },
         { "Annaliese Bauer" },
         { "Anya Schofield" },
         { "Ellenor Cote" },
      },
      {
         { "Katy Swanson" },
         { "Melina Kelly" },
         { "Abby Burton" },
      },
   });

   column_with_labels_section_renderer.render();
   al_flip_display();
}


TEST_F(AllegroFlare_Elements_RollingCredits_SectionRenderers_MulticolumnTestWithAllegroRenderingFixture,
   CAPTURE__render__with_more_columns_in_the_elements_and_centered_elements__will_render_as_expected)
{
   AllegroFlare::Elements::RollingCredits::SectionRenderers::Multicolumn column_with_labels_section_renderer(
      &get_font_bin_ref(), {}, 1920/2, 1080/2, 1920-600
   );
   column_with_labels_section_renderer.set_elements({
      {
         { "Robyn Kendall" },
         { "Tayyibah Samuels" },
         { "Ryker Odling" },
         { "Yuki Nakamura" },
         { "Aiza Rivera" },
      },
      {
         { "Annaliese Bauer" },
         { "Anya Schofield" },
         { "Ellenor Cote" },
         { "Emily Davis" },
      },
      {
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
   });
   column_with_labels_section_renderer.set_element_alignment("centered");

   column_with_labels_section_renderer.render();
   al_flip_display();
}


TEST_F(AllegroFlare_Elements_RollingCredits_SectionRenderers_MulticolumnTestWithAllegroRenderingFixture,
   render__will_return_the_height_of_the_section)
{
   AllegroFlare::Elements::RollingCredits::SectionRenderers::Multicolumn column_with_labels_section_renderer(
      &get_font_bin_ref(), {}, 1920/2, 1080/2, 1920-600
   );
   column_with_labels_section_renderer.set_elements({
      {
         { "Robyn Kendall" },
         { "Tayyibah Samuels" },
         { "Ryker Odling" },
      },
      {
         { "Aiza Rivera" },
         { "Annaliese Bauer" },
         { "Anya Schofield" },
         { "Ellenor Cote" },
      },
      {
         { "Katy Swanson" },
         { "Melina Kelly" },
         { "Abby Burton" },
      },
   });

   float expected_height = 144;
   float actual_height = column_with_labels_section_renderer.render(true);
   EXPECT_FLOAT_EQ(expected_height, actual_height);
}


// TODO: Add test that nothing is rendered when render(true) is called


