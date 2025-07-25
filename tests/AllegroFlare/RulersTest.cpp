#include <gtest/gtest.h>

#include <AllegroFlare/Testing/ErrorAssertions.hpp>
#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>
#include <AllegroFlare/Rulers.hpp>
#include <allegro5/allegro_primitives.h> // for al_is_primitives_addon_initialized();
#include <allegro5/allegro_color.h> // for al_color_html();


class AllegroFlare_RulersTest : public ::testing::Test {};
class AllegroFlare_RulersTestWithAllegroRenderingFixture
   : public AllegroFlare::Testing::WithAllegroRenderingFixture
{};



TEST_F(AllegroFlare_RulersTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Rulers rulers;
}


TEST_F(AllegroFlare_RulersTestWithAllegroRenderingFixture, CAPTURE__draw_vertical_ruler__will_not_blow_up)
{
   AllegroFlare::Placement2D subject_placement = build_centered_placement();
   AllegroFlare::Rulers rulers(&get_font_bin_ref());

   clear();
   subject_placement.start_transform();
   rulers.draw_vertical_ruler(0, 0, 30.0, 4.0, 160.0, 5, 0.0, 0.0, al_color_html("b8e8e8"));
   subject_placement.restore_transform();

   al_flip_display();
   sleep_for(1);
}


TEST_F(AllegroFlare_RulersTestWithAllegroRenderingFixture, CAPTURE__draw_horizontal_ruler__will_render_as_expected)
{
   AllegroFlare::Placement2D subject_placement = build_centered_placement();
   AllegroFlare::Rulers rulers(&get_font_bin_ref());

   clear();
   subject_placement.start_transform();
   rulers.draw_horizontal_ruler(0, 0, 4.0, 30.0, 160.0, 5, 0.0, 0.0, al_color_html("b8e8e8"));
   rulers.draw_horizontal_ruler_numbers(0, -4, 3, 1, 160.0, 5, 0.5, 1.0, al_color_html("b8e8e8"));
   subject_placement.restore_transform();

   al_flip_display();
   sleep_for(1);
}


TEST_F(AllegroFlare_RulersTestWithAllegroRenderingFixture,
   CAPTURE__draw_2d_grid_2__will_render_as_expected)
{
   AllegroFlare::Rulers rulers(&get_font_bin_ref());

   clear();
   rulers.draw_hd_layout_grid();

   al_flip_display();
   sleep_for(1);
}


TEST_F(AllegroFlare_RulersTestWithAllegroRenderingFixture,
   FOCUS__CAPTURE__draw_hd_layout_grid__will_render_a_grid_of_dotted_lines)
{
   AllegroFlare::Rulers rulers(&get_font_bin_ref());

   clear();
   rulers.draw_hd_layout_grid(
      1920/2,
      1080/2,
      12,                                  // num_sections_x
      8,                                   // num_sections_y
      al_color_html("667788"),            // color
      2.0f,                                // line_thickness
      15.0f,                               // dot_spacing
      5.0f                                 // dot_length
   );

   al_flip_display();
   sleep_for(1);
}

