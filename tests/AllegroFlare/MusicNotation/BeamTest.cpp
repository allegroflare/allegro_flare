#include <gtest/gtest.h>

#define EXPECT_THROW_WITH_MESSAGE(code, raised_exception_type, expected_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { EXPECT_EQ(std::string(expected_exception_message), err.what()); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }

#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>
#include <allegro5/allegro_primitives.h>


class AllegroFlare_MusicNotation_BeamTest : public ::testing::Test {};
class AllegroFlare_MusicNotation_BeamTestWithAllegroRenderingFixture
   : public AllegroFlare::Testing::WithAllegroRenderingFixture
{
public:
   void draw_staff_guide_lines(float x, float y, float staff_line_distance = 20, int num_lines_out=2)
   {
      float thickness = 1.0;
      float width = 400;
      ALLEGRO_COLOR color{1, 0, 0, 1};
      al_draw_line(x-width/2, y, x+width/2, y, color, thickness);
      for (int i=0; i<=num_lines_out; i++)
      {
         al_draw_line(x-width/2, y-staff_line_distance*i, x+width/2, y-staff_line_distance*i, color, thickness);
         al_draw_line(x-width/2, y+staff_line_distance*i, x+width/2, y+staff_line_distance*i, color, thickness);
      }
   }
};


#include <AllegroFlare/MusicNotation/Beam.hpp>
#include <allegro5/allegro_primitives.h> // for al_is_primitives_addon_initialized();


TEST_F(AllegroFlare_MusicNotation_BeamTest, can_be_created_without_blowing_up)
{
   AllegroFlare::MusicNotation::Beam beam;
}


TEST_F(AllegroFlare_MusicNotation_BeamTest, render__without_allegro_initialized__raises_an_error)
{
   AllegroFlare::MusicNotation::Beam beam;
   std::string expected_error_message =
      "Beam::render: error: guard \"al_is_system_installed()\" not met";
   EXPECT_THROW_WITH_MESSAGE(beam.render(), std::runtime_error, expected_error_message);
}


TEST_F(AllegroFlare_MusicNotation_BeamTest, render__without_primitives_addon_initialized__raises_an_error)
{
   al_init();
   AllegroFlare::MusicNotation::Beam beam;
   std::string expected_error_message =
      "Beam::render: error: guard \"al_is_primitives_addon_initialized()\" not met";
   EXPECT_THROW_WITH_MESSAGE(beam.render(), std::runtime_error, expected_error_message);
   al_uninstall_system();
}


TEST_F(AllegroFlare_MusicNotation_BeamTestWithAllegroRenderingFixture, CAPTURE__render__will_not_blow_up)
{
   AllegroFlare::MusicNotation::Beam beam;
   beam.set_staff_line_distance(20);
   beam.set_start_alignment(AllegroFlare::MusicNotation::Beam::Alignment::TOP);
   beam.set_end_alignment(AllegroFlare::MusicNotation::Beam::Alignment::BOTTOM);

   AllegroFlare::Placement2D showcased_placement = build_centered_placement();
   showcased_placement.start_transform();
   draw_staff_guide_lines(0, 0);
   beam.render();
   showcased_placement.restore_transform();

   al_flip_display();
   sleep_for(1);
}


