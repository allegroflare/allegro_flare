#include <gtest/gtest.h>

#include <AllegroFlare/Testing/ErrorAssertions.hpp>
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
      float width = 1200;
      ALLEGRO_COLOR color{1, 0, 0, 1};
      al_draw_line(x-width/2, y, x+width/2, y, color, thickness);
      for (int i=0; i<=num_lines_out; i++)
      {
         al_draw_line(x-width/2, y-staff_line_distance*i, x+width/2, y-staff_line_distance*i, color, thickness);
         al_draw_line(x-width/2, y+staff_line_distance*i, x+width/2, y+staff_line_distance*i, color, thickness);
      }
   }
   void draw_staff_lines(float x, float y, float staff_line_distance = 20)
   {
      float thickness = staff_line_distance * 0.1;
      float width = 1200;
      ALLEGRO_COLOR color{1, 1, 1, 1};
      al_draw_line(x-width/2, y, x+width/2, y, color, thickness);
      for (int i=0; i<=2; i++)
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
   std::string expected_error_message = AllegroFlare::Logger::build_guard_error_message(
      "AllegroFlare::MusicNotation::Beam::render",
      "al_is_system_installed()"
   );
   EXPECT_THROW_WITH_MESSAGE(beam.render(), std::runtime_error, expected_error_message);
}


TEST_F(AllegroFlare_MusicNotation_BeamTest, render__without_primitives_addon_initialized__raises_an_error)
{
   al_init();
   AllegroFlare::MusicNotation::Beam beam;
   std::string expected_error_message = AllegroFlare::Logger::build_guard_error_message(
      "AllegroFlare::MusicNotation::Beam::render",
      "al_is_primitives_addon_initialized()"
   );
   EXPECT_THROW_WITH_MESSAGE(beam.render(), std::runtime_error, expected_error_message);
   al_uninstall_system();
}


TEST_F(AllegroFlare_MusicNotation_BeamTestWithAllegroRenderingFixture, CAPTURE__render__will_not_blow_up)
{
   AllegroFlare::MusicNotation::Beam beam;
   beam.set_staff_line_distance(20);

   beam.set_start_x(-100);
   beam.set_start_staff_pos(-2);
   beam.set_start_alignment(AllegroFlare::MusicNotation::Beam::Alignment::TOP);
   beam.set_end_x(100);
   beam.set_end_staff_pos(-2);
   beam.set_end_alignment(AllegroFlare::MusicNotation::Beam::Alignment::BOTTOM);

   AllegroFlare::Placement2D showcased_placement = build_centered_placement();
   showcased_placement.start_transform();
   draw_staff_guide_lines(0, 0, beam.get_staff_line_distance());
   beam.render();
   showcased_placement.restore_transform();

   al_flip_display();
}


TEST_F(AllegroFlare_MusicNotation_BeamTestWithAllegroRenderingFixture,
   CAPTURE__render__looks_normal_when_multiple_beams_are_rendered)
{
   using AllegroFlare::MusicNotation::Beam;

   AllegroFlare::MusicNotation::Beam beam1(20, -100, -2, Beam::Alignment::TOP, 100, -2, Beam::Alignment::BOTTOM);
   AllegroFlare::MusicNotation::Beam beam2(20, -100, -1, Beam::Alignment::MIDDLE, 100, 0, Beam::Alignment::MIDDLE);

   AllegroFlare::Placement2D showcased_placement = build_centered_placement();
   showcased_placement.start_transform();
   draw_staff_guide_lines(0, 0, beam1.get_staff_line_distance());
   beam1.render();
   beam2.render();
   showcased_placement.restore_transform();

   al_flip_display();
}


TEST_F(AllegroFlare_MusicNotation_BeamTestWithAllegroRenderingFixture,
   CAPTURE__render__with_secondary_beams__renders_as_expected)
{
   using AllegroFlare::MusicNotation::Beam;

   AllegroFlare::MusicNotation::Beam beam1(20, -300, -4, Beam::Alignment::BOTTOM, -100, -5, Beam::Alignment::BOTTOM);
   beam1.set_secondary_beams({
      { 1, 0.0, 0.5 },
      { 1, 0.9, 1.0 },
      { 2, 0.4, 0.5 },
   });
   AllegroFlare::MusicNotation::Beam beam2(20, 100, 2, Beam::Alignment::TOP, 400, 1, Beam::Alignment::BOTTOM);

   AllegroFlare::Placement2D showcased_placement = build_centered_placement();
   showcased_placement.start_transform();
   draw_staff_lines(0, 0, beam1.get_staff_line_distance());

   beam1.render();
   beam2.render();

   showcased_placement.restore_transform();

   al_flip_display();
   sleep_for(1);
}


