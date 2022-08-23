
#include <gtest/gtest.h>

#define ASSERT_THROW_WITH_MESSAGE(code, raised_exception_type, expected_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { ASSERT_EQ(std::string(expected_exception_message), err.what()); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }

#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>


class AllegroFlare_Elements_RollingCredits_SectionRenderers_ColumnWithLabelsTest : public ::testing::Test
{};

class AllegroFlare_Elements_RollingCredits_SectionRenderers_ColumnWithLabelsTestWithAllegroRenderingFixture
   : public AllegroFlare::Testing::WithAllegroRenderingFixture
{};


#include <AllegroFlare/Elements/RollingCredits/SectionRenderers/ColumnWithLabels.hpp>


TEST_F(AllegroFlare_Elements_RollingCredits_SectionRenderers_ColumnWithLabelsTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Elements::RollingCredits::SectionRenderers::ColumnWithLabels column_with_labels_section_renderer;
}


TEST_F(AllegroFlare_Elements_RollingCredits_SectionRenderers_ColumnWithLabelsTest,
   render__without_allegro_initialized__raises_an_error)
{
   AllegroFlare::Elements::RollingCredits::SectionRenderers::ColumnWithLabels column_with_labels_section_renderer;
   std::string expected_error_message =
      "ColumnWithLabels::render: error: guard \"al_is_system_installed()\" not met";
   ASSERT_THROW_WITH_MESSAGE(column_with_labels_section_renderer.render(), std::runtime_error, expected_error_message);
}


TEST_F(AllegroFlare_Elements_RollingCredits_SectionRenderers_ColumnWithLabelsTestWithAllegroRenderingFixture,
   render__will_not_blow_up)
{
   AllegroFlare::Elements::RollingCredits::SectionRenderers::ColumnWithLabels column_with_labels_section_renderer(
      &get_font_bin_ref()
   );
   column_with_labels_section_renderer.render();
}


TEST_F(AllegroFlare_Elements_RollingCredits_SectionRenderers_ColumnWithLabelsTestWithAllegroRenderingFixture,
   CAPTURE__render__will_render_as_expected)
{
   AllegroFlare::Elements::RollingCredits::SectionRenderers::ColumnWithLabels column_with_labels_section_renderer(
      &get_font_bin_ref(), {}, 1920/2, 1080/2
   );
   column_with_labels_section_renderer.set_elements({
      { "Producer", "Robyn Kendall" },
      { "Production Design", "Tayyibah Samuels" },
      { "Music", "Ryker Odling" },
      { "Sound Design", "Aiza Rivera" },
      { "Lead Programming", "Annaliese Bauer" },
      { "Programming", "Anya Schofield" },
      { "Motion Design", "Ellenor Cote" },
      { "Element Design", "Katy Swanson" },
      { "Marketing Manager", "Melina Kelly" },
      { "Set Design", "Abby Burton" },
   });

   column_with_labels_section_renderer.render();
   al_flip_display();
}


TEST_F(AllegroFlare_Elements_RollingCredits_SectionRenderers_ColumnWithLabelsTestWithAllegroRenderingFixture,
   render__will_return_the_height_of_the_section)
{
   // TODO
}


