
#include <gtest/gtest.h>

#include <AllegroFlare/Path2D.hpp>
#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>


class AllegroFlare_Path2DTest: public ::testing::Test {};
class AllegroFlare_Path2DTestWithAllegroRenderingFixture : public AllegroFlare::Testing::WithAllegroRenderingFixture {};


TEST_F(AllegroFlare_Path2DTest, can_be_crated_without_blowing_up)
{
   AllegroFlare::Path2D path_2d;
}


TEST_F(AllegroFlare_Path2DTestWithAllegroRenderingFixture, CAPTURE__render__will_render_a_line)
{
   AllegroFlare::Path2D path_2d;
   float cx = 1920/2;
   float cy = 1080/2;
   path_2d.add_point(cx-400, cy-10);
   path_2d.add_point(cx-0, cy-220);
   path_2d.add_point(cx+380, cy+20);
   path_2d.add_point(cx-50, cy+180);

   path_2d.draw(true, false, false, true, ALLEGRO_COLOR{0.1, 0.45, 0.36, 1.0});

   al_flip_display();
}


TEST_F(AllegroFlare_Path2DTestWithAllegroRenderingFixture, CAPTURE__soften__will_make_the_path_smoother)
{
   AllegroFlare::Path2D path_2d;
   float cx = 1920/2;
   float cy = 1080/2;
   path_2d.add_point(cx-400, cy-10);
   path_2d.add_point(cx-0, cy-220);
   path_2d.add_point(cx+380, cy+20);
   path_2d.add_point(cx-50, cy+180);

   path_2d.draw(true, false, false, true, ALLEGRO_COLOR{0.1, 0.45, 0.38, 1.0}, 1.0);
   path_2d.soften();
   path_2d.draw(true, false, false, true, ALLEGRO_COLOR{0.18, 0.65, 0.52, 1.0}, 2.0);
   path_2d.soften();
   path_2d.draw(true, false, false, true, ALLEGRO_COLOR{0.72, 1.0, 0.71, 1.0}, 3.0);
   al_flip_display();

   al_rest(1);
}


