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


TEST_F(AllegroFlare_RulersTestWithAllegroRenderingFixture, CAPTURE__draw_horizontal_ruler__will_not_blow_up)
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


