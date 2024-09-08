
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

   path_2d.draw(true, false, false, true, ALLEGRO_COLOR{0.2, 0.9, 0.76, 1.0});

   al_flip_display();

   al_rest(1);
}


