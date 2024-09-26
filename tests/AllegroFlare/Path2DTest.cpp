
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
   ALLEGRO_FONT *font = get_any_font();

   AllegroFlare::Path2D path_2d, path_2d_as_line, path_2d_as_loop;

   float cx = 1920/2;
   float cy = 1080/2;

   path_2d.add_point(cx-400, cy-10);
   path_2d.add_point(cx-0, cy-220);
   path_2d.add_point(cx+380, cy+20);
   path_2d.add_point(cx-50, cy+180);

   path_2d_as_line = path_2d;
   path_2d_as_line.move(-500, 0);
   path_2d_as_line.draw(true, false, false, true, ALLEGRO_COLOR{0.1, 0.45, 0.38, 1.0}, 1.0);
   path_2d_as_line.soften();
   path_2d_as_line.draw(true, false, false, true, ALLEGRO_COLOR{0.18, 0.65, 0.52, 1.0}, 2.0);
   path_2d_as_line.soften();
   path_2d_as_line.draw(true, false, false, true, ALLEGRO_COLOR{0.72, 1.0, 0.71, 1.0}, 3.0);

   // TODO: Add impl for "as_loop=true"
   path_2d_as_loop = path_2d;
   path_2d_as_loop.move(500, 0);
   path_2d_as_loop.draw(true, false, false, true, ALLEGRO_COLOR{0.1, 0.45, 0.38, 1.0}, 1.0);
   path_2d_as_loop.soften(true);
   path_2d_as_loop.draw(true, false, false, true, ALLEGRO_COLOR{0.18, 0.65, 0.52, 1.0}, 2.0);
   path_2d_as_loop.soften(true);
   path_2d_as_loop.draw(true, false, false, true, ALLEGRO_COLOR{0.72, 1.0, 0.71, 1.0}, 3.0);

   ALLEGRO_COLOR text_color = ALLEGRO_COLOR{0.6, 0.6, 0.5, 1.0};
   al_draw_text(font, text_color, cx-500, cy-300, ALLEGRO_ALIGN_CENTER, "soften()");
   al_draw_text(font, text_color, cx+500, cy-300, ALLEGRO_ALIGN_CENTER, "soften(as_loop=true)");

   al_flip_display();
   al_rest(1);
}


TEST_F(AllegroFlare_Path2DTestWithAllegroRenderingFixture,
   FOCUS__CAPTURE__ILLUSTRATION__soften__will_introduce_interpolated_points_to_the_path_for_a_smoother_path)
{
   ALLEGRO_FONT *font = get_any_font();

   AllegroFlare::Path2D path_2d, path_2d_as_line, path_2d_as_loop;
   float spacing_x = 600;
   float spacing_y = 500;

   float cx = 1920/2;
   float cy = 1080/2;

   path_2d.add_point(cx-300, cy-10);
   path_2d.add_point(cx-0, cy-120);
   path_2d.add_point(cx+280, cy+20);
   path_2d.add_point(cx-50, cy+100);

   ALLEGRO_COLOR color = ALLEGRO_COLOR{0.72, 1.0, 0.71, 1.0};
   ALLEGRO_COLOR previous_color = ALLEGRO_COLOR{0.1, 0.45, 0.38, 1.0};
      //ALLEGRO_COLOR{0.1, 0.45, 0.38, 1.0}

   path_2d_as_line = path_2d;
   path_2d_as_line.move(-spacing_x, -spacing_y/2);
   path_2d_as_line.draw(true, false, false, true, color, 3.0);
   path_2d_as_line.move(spacing_x, 0);
   path_2d_as_line.draw(true, false, false, true, previous_color, 2.0);
   path_2d_as_line.soften();
   path_2d_as_line.draw(true, false, false, true, color, 3.0);
   path_2d_as_line.move(spacing_x, 0);
   path_2d_as_line.draw(true, false, false, true, previous_color, 2.0);
   path_2d_as_line.soften();
   path_2d_as_line.draw(true, false, false, true, color, 3.0);

   // TODO: Add impl for "as_loop=true"
   path_2d_as_loop = path_2d;
   path_2d_as_loop.move(-spacing_x, spacing_y/2);
   path_2d_as_loop.draw(true, false, false, true, ALLEGRO_COLOR{0.1, 0.45, 0.38, 1.0}, 1.0);
   path_2d_as_loop.move(spacing_x, 0);
   path_2d_as_loop.draw(true, false, false, true, ALLEGRO_COLOR{0.1, 0.45, 0.38, 1.0}, 1.0);
   path_2d_as_loop.soften(true);
   path_2d_as_loop.draw(true, false, false, true, ALLEGRO_COLOR{0.18, 0.65, 0.52, 1.0}, 2.0);
   path_2d_as_loop.move(spacing_x, 0);
   path_2d_as_loop.draw(true, false, false, true, ALLEGRO_COLOR{0.18, 0.65, 0.52, 1.0}, 2.0);
   path_2d_as_loop.soften(true);
   path_2d_as_loop.draw(true, false, false, true, ALLEGRO_COLOR{0.72, 1.0, 0.71, 1.0}, 3.0);

   ALLEGRO_COLOR text_color = ALLEGRO_COLOR{0.6, 0.6, 0.5, 1.0};
   al_draw_text(font, text_color, cx-800, cy-spacing_y/2-180, ALLEGRO_ALIGN_LEFT, "showing 2 passes of soften()");
   al_draw_text(font, text_color, cx-800, cy+spacing_y/2-180, ALLEGRO_ALIGN_LEFT, "showing 2 passes of soften(as_loop=true)");

   al_flip_display();
   al_rest(1);
}


