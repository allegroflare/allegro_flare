
#include <gtest/gtest.h>

#include <AllegroFlare/Elements/FUI/PanningGrid.hpp>
#include <AllegroFlare/ColorKit.hpp>
#include <allegro5/allegro_color.h>

#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>
class AllegroFlare_Elements_FUI_PanningGridTest : public ::testing::Test {};
class AllegroFlare_Elements_FUI_PanningGridTestWithAllegroRenderingFixture
    : public AllegroFlare::Testing::WithAllegroRenderingFixture
{};


TEST_F(AllegroFlare_Elements_FUI_PanningGridTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Elements::FUI::PanningGrid panning_grid;
}


TEST_F(AllegroFlare_Elements_FUI_PanningGridTestWithAllegroRenderingFixture,
   CAPTURE__render__will_not_blow_up)
{
   AllegroFlare::Elements::FUI::PanningGrid panning_grid;
   panning_grid.set_font_bin(&get_font_bin_ref());
   panning_grid.initialize();

   clear();
   panning_grid.render();
   al_flip_display();
}


TEST_F(AllegroFlare_Elements_FUI_PanningGridTestWithAllegroRenderingFixture,
   CAPTURE__draw_l_bracket__will_render_as_expected)
{
   AllegroFlare::Elements::FUI::PanningGrid panning_grid;
   panning_grid.set_font_bin(&get_font_bin_ref());
   panning_grid.initialize();

   clear();
   panning_grid.draw_l_bracket();
   al_flip_display();
}


TEST_F(AllegroFlare_Elements_FUI_PanningGridTestWithAllegroRenderingFixture,
   CAPTURE__draw_3d_dimensional_grid__will_render_as_expected)
{
   AllegroFlare::Elements::FUI::PanningGrid panning_grid;
   panning_grid.set_font_bin(&get_font_bin_ref());
   panning_grid.initialize();

   clear();
   panning_grid.draw_3d_dimensional_grid();
   al_flip_display();
}


TEST_F(AllegroFlare_Elements_FUI_PanningGridTestWithAllegroRenderingFixture,
   CAPTURE__draw_2d_grid__will_render_as_expected)
{
   AllegroFlare::Elements::FUI::PanningGrid panning_grid;
   panning_grid.set_font_bin(&get_font_bin_ref());
   panning_grid.initialize();

   clear();
   panning_grid.draw_2d_grid();
   al_flip_display();
}


TEST_F(AllegroFlare_Elements_FUI_PanningGridTestWithAllegroRenderingFixture,
   CAPTURE__draw_vertical_ruler__will_render_as_expected)
{
   AllegroFlare::Elements::FUI::PanningGrid panning_grid;
   panning_grid.set_font_bin(&get_font_bin_ref());
   panning_grid.initialize();

   float spacing = 160;
   float x = 600;
   float y = 100;
   float align_x = 1.0f;
   float align_y = 0.5f;

   clear();
   // Draw the major tick lines
   panning_grid.draw_vertical_ruler(x, y,               9.0f, 4.0f, spacing, 6, align_x, 0.5f, al_color_html("b8e8e8"));
   // Draw the minor tick lines
   panning_grid.draw_vertical_ruler(x, y + spacing/3,   5.0f, 2.0f, spacing, 5, align_x, 0.5f, al_color_html("577685"));
   panning_grid.draw_vertical_ruler(x, y + spacing/3*2, 5.0f, 2.0f, spacing, 5, align_x, 0.5f, al_color_html("577685"));

   draw_vertical_crosshair(x, 1080/2);
   al_flip_display();
}


TEST_F(AllegroFlare_Elements_FUI_PanningGridTestWithAllegroRenderingFixture,
   CAPTURE__draw_cross__will_render_as_expected)
{
   AllegroFlare::Elements::FUI::PanningGrid panning_grid;
   panning_grid.set_font_bin(&get_font_bin_ref());
   panning_grid.initialize();

   float x = 1920/2;
   float y = 1080/2;

   clear();
   panning_grid.draw_cross(x, y, 30.0f, 0.5f, 0.5f, al_color_html("b8e8e8"));
   draw_crosshair(x, y);
   al_flip_display();
}


TEST_F(AllegroFlare_Elements_FUI_PanningGridTestWithAllegroRenderingFixture,
   CAPTURE__draw_tall_cross__will_render_as_expected)
{
   // TODO: Revise "draw_tall_cross" arguments for clarity and practical application
   AllegroFlare::Elements::FUI::PanningGrid panning_grid;
   panning_grid.set_font_bin(&get_font_bin_ref());
   panning_grid.initialize();

   float x = 1920/2;
   float y = 1080/2;

   clear();
   float spacing = 160;
   panning_grid.draw_tall_cross(x, y, 10.0f, spacing, 6, 0.5f, 0.5f, al_color_html("b8e8e8"));
   draw_crosshair(x, y);
   al_flip_display();
}


TEST_F(AllegroFlare_Elements_FUI_PanningGridTestWithAllegroRenderingFixture,
   CAPTURE__build_tall_cross_segments__will_build_the_expected_vertices)
{
   // TODO: Revise "draw_tall_cross" arguments for clarity and practical application
   AllegroFlare::Elements::FUI::PanningGrid panning_grid;
   panning_grid.set_font_bin(&get_font_bin_ref());
   panning_grid.initialize();

   float x = 1920/2;
   float y = 1080/2;
   float t = 4.0f;
   float l = 80.0f;
   float ax = 0.5f;
   float ay = 0.5f;
   float spacing_x = 400;
   float spacing_y = 180;
   std::vector<ALLEGRO_VERTEX> segments;
   ALLEGRO_COLOR color = al_color_html("b8e8e8");

   clear();

   // Draw row of example crosses in the top row

   // Cross on the left (has top, right, left segments)
   segments = panning_grid.build_tall_cross_segments(
         x-spacing_x, y-spacing_y, t, l, ax, ay, true, true, false, true, false, color
      );
   al_draw_prim(&segments[0], NULL, NULL, 0, segments.size(), ALLEGRO_PRIM_TRIANGLE_LIST);
   draw_crosshair(x-spacing_x, y-spacing_y);

   // Cross in the middle (has bottom, left, middle segments)
   segments = panning_grid.build_tall_cross_segments(
         x, y-spacing_y, t, l, ax, ay, false, false, true, true, true, color
      );
   al_draw_prim(&segments[0], NULL, NULL, 0, segments.size(), ALLEGRO_PRIM_TRIANGLE_LIST);
   draw_crosshair(x, y-spacing_y);

   // Cross on the right (has bottom, middle segments)
   segments = panning_grid.build_tall_cross_segments(
         x+spacing_x, y-spacing_y, t, l, ax, ay, false, false, true, false, true, color
      );
   al_draw_prim(&segments[0], NULL, NULL, 0, segments.size(), ALLEGRO_PRIM_TRIANGLE_LIST);
   draw_crosshair(x+spacing_x, y-spacing_y);

   // Draw row of example crosses in the bottom row

   // Cross on the left (has left, bottom)
   segments = panning_grid.build_tall_cross_segments(
         x-spacing_x, y+spacing_y, 20.0, l, ax, ay, false, false, true, true, false, color
      );
   al_draw_prim(&segments[0], NULL, NULL, 0, segments.size(), ALLEGRO_PRIM_TRIANGLE_LIST);
   draw_crosshair(x-spacing_x, y+spacing_y);

   // Cross in the middle (has middle segment only)
   segments = panning_grid.build_tall_cross_segments(
         x, y+spacing_y, t, l, ax, ay, false, false, false, false, true, color
      );
   al_draw_prim(&segments[0], NULL, NULL, 0, segments.size(), ALLEGRO_PRIM_TRIANGLE_LIST);
   draw_crosshair(x, y+spacing_y);

   // Cross on the right (has bottom, middle segments)
   segments = panning_grid.build_tall_cross_segments(
         x+spacing_x, y+spacing_y, 16.0f, 8.0f, ax, ay, true, true, false, false, true, color
      );
   al_draw_prim(&segments[0], NULL, NULL, 0, segments.size(), ALLEGRO_PRIM_TRIANGLE_LIST);
   draw_crosshair(x+spacing_x, y+spacing_y);

   al_flip_display();
}


TEST_F(AllegroFlare_Elements_FUI_PanningGridTestWithAllegroRenderingFixture,
   CAPTURE__build_grid__will_render_as_expected)
{
   AllegroFlare::Elements::FUI::PanningGrid panning_grid;
   panning_grid.set_font_bin(&get_font_bin_ref());
   panning_grid.initialize();

   float x = 1920/2;
   float y = 1080/2;

   clear();
   float spacing = 90;
   float extensions = 60;
   // TODO: Work out what to do when grid is 0 rows, 0 columns, currently it's missing the top "tick"
   std::vector<ALLEGRO_VERTEX> vertices=
      panning_grid.build_grid(x, y, 2.0f, spacing, extensions, 6, 3, 0.5f, 0.5f, al_color_html("b8e8e8"));
   al_draw_prim(&vertices[0], NULL, NULL, 0, vertices.size(), ALLEGRO_PRIM_TRIANGLE_LIST);
   draw_crosshair(x, y);
   al_flip_display();
}


TEST_F(AllegroFlare_Elements_FUI_PanningGridTestWithAllegroRenderingFixture,
   CAPTURE__build_bracket__will_render_as_expected)
{
   AllegroFlare::Elements::FUI::PanningGrid panning_grid;
   panning_grid.set_font_bin(&get_font_bin_ref());
   panning_grid.initialize();

   float w = 1920/4;
   float h = 1080/3;
   float x = 1920/2 - w/2;
   float y = 1080/2 - h/2;
   float t = 20.0f;
   float l = 40.0f;
   float align_x = 0.5f;
   float align_y = 0.5f;

   clear();
   float spacing = 90;
   float extensions = 60;
   // TODO: Work out what to do when grid is 0 rows, 0 columns, currently it's missing the top "tick"
   std::vector<ALLEGRO_VERTEX> vertices=
      panning_grid.build_bracket(x, y, w, h, t, l, align_x, align_y, 10.0f, 10.0f, al_color_html("b8e8e8"));
   al_draw_prim(&vertices[0], NULL, NULL, 0, vertices.size(), ALLEGRO_PRIM_TRIANGLE_LIST);
   draw_rectangle(x, y, w, h);
   al_flip_display();
}


TEST_F(AllegroFlare_Elements_FUI_PanningGridTestWithAllegroRenderingFixture,
   build_number__will_output_the_expected_string_representation_of_the_number)
{
   EXPECT_EQ("3 2 1", AllegroFlare::Elements::FUI::PanningGrid::build_number(321));
   // Note the replacement of "0" with the letter "O". This is specific use for the Orbitron font, which has a slash
   // through the "0" and does not look as nice on visuals.
   EXPECT_EQ("4 O O", AllegroFlare::Elements::FUI::PanningGrid::build_number(400));
}


TEST_F(AllegroFlare_Elements_FUI_PanningGridTestWithAllegroRenderingFixture,
   CAPTURE__draw_number__will_render_the_number_as_expected)
{
   float x = 1920/2;
   float y = 1080/2 - 200;
   float y_spacing = 100;
   int i=0;

   AllegroFlare::Elements::FUI::PanningGrid panning_grid;
   panning_grid.set_font_bin(&get_font_bin_ref());
   panning_grid.initialize();

   draw_crosshair(x, y+y_spacing*i);
   panning_grid.draw_number(x, y+y_spacing*i++, 137,   5, 0.0f, 0.0f, al_color_html("b8e8e8"));

   draw_crosshair(x, y+y_spacing*i);
   panning_grid.draw_number(x, y+y_spacing*i++, 137,  -1, 0.5f, 0.5f, al_color_html("b8e8e8"));

   draw_crosshair(x, y+y_spacing*i);
   panning_grid.draw_number(x, y+y_spacing*i++, 54321, 3, 1.0f, 1.0f, al_color_html("b8e8e8"));

   al_flip_display();
}


TEST_F(AllegroFlare_Elements_FUI_PanningGridTestWithAllegroRenderingFixture,
   CAPTURE__draw_vertical_ruler_numbers__will_render_as_expected)
{
   AllegroFlare::Elements::FUI::PanningGrid panning_grid;
   panning_grid.set_font_bin(&get_font_bin_ref());
   panning_grid.initialize();

   float spacing = 160;
   float x = 600;
   float y = 160;
   float align_x = 1.0f;
   float align_y = 0.5f;

   clear();
   // Draw an example vertical ruler on the left
   panning_grid.draw_vertical_ruler_numbers(x, y, 0, 1, spacing, 6, align_x, align_y, al_color_html("b8e8e8"));
   draw_vertical_crosshair(x, 1080/2);

   // Draw an example vertical ruler on the right side
   x += 600;
   spacing = 124;
   panning_grid.draw_vertical_ruler_numbers(x, y, 3, 3, spacing, 7, align_x, align_y, al_color_html("b8e8e8"));
   draw_crosshair(x, y);
   draw_crosshair(x, y+spacing*1);
   draw_crosshair(x, y+spacing*2);
   al_flip_display();
}


TEST_F(AllegroFlare_Elements_FUI_PanningGridTestWithAllegroRenderingFixture,
   CAPTURE__build_rectangle_frame_segments__will_render_as_expected)
{
   AllegroFlare::Elements::FUI::PanningGrid panning_grid;
   panning_grid.set_font_bin(&get_font_bin_ref());
   panning_grid.initialize();

   float spacing_x = 580;
   float spacing_y = 200;
   float width = 400;
   float height = 260;
   float thickness = 12.0f;
   float x = 1920/2 - width/2;
   float y = 1080/2 - height/2;
   ALLEGRO_COLOR color = al_color_html("b8e8e8");
   color = AllegroFlare::ColorKit::fade(color, 0.4);
   bool t = true;

   clear();

   std::vector<ALLEGRO_VERTEX> vertices;

   // Top row examples

   // Draw an example rectangle on the left
   vertices = panning_grid.build_rectangle_frame_segments(
         x-spacing_x, y-spacing_y, width, height, thickness, 0.5f, 0.5f, t, t, t, t, t, t, t, t, color
      );
   al_draw_prim(&vertices[0], NULL, NULL, 0, vertices.size(), ALLEGRO_PRIM_TRIANGLE_LIST);
   draw_rectangle(x-spacing_x, y-spacing_y, width, height);

   // Draw an example rectangle in the center
   vertices = panning_grid.build_rectangle_frame_segments(
         x, y-spacing_y, width, height, thickness, 1.0f, 1.0f, t, t, t, t, t, t, t, t, color
      );
   al_draw_prim(&vertices[0], NULL, NULL, 0, vertices.size(), ALLEGRO_PRIM_TRIANGLE_LIST);
   draw_rectangle(x, y-spacing_y, width, height);

   // Draw an example rectangle on the right
   vertices = panning_grid.build_rectangle_frame_segments(
         x+spacing_x, y-spacing_y, width, height, thickness, 0.0f, 0.0f, t, t, t, t, t, t, t, t, color
      );
   al_draw_prim(&vertices[0], NULL, NULL, 0, vertices.size(), ALLEGRO_PRIM_TRIANGLE_LIST);
   draw_rectangle(x+spacing_x, y-spacing_y, width, height);

   // Bottom row examples

   // Draw an example rectangle on the left
   vertices = panning_grid.build_rectangle_frame_segments(
         x-spacing_x, y+spacing_y, width, height, 20, 2.5f, 1.5f, t, t, t, t, t, t, t, t, color);
   al_draw_prim(&vertices[0], NULL, NULL, 0, vertices.size(), ALLEGRO_PRIM_TRIANGLE_LIST);
   draw_rectangle(x-spacing_x, y+spacing_y, width, height);

   // Draw an example rectangle in the center
   vertices = panning_grid.build_rectangle_frame_segments(
         x, y+spacing_y, width, height, 18, 0.0f, -1.5f, t, t, t, t, t, t, t, t, color
      );
   al_draw_prim(&vertices[0], NULL, NULL, 0, vertices.size(), ALLEGRO_PRIM_TRIANGLE_LIST);
   draw_rectangle(x, y+spacing_y, width, height);

   // Draw an example rectangle on the right
   vertices = panning_grid.build_rectangle_frame_segments(
         x+spacing_x, y+spacing_y, width, height, 40, -1.0f, -0.5f, t, t, t, t, t, t, t, t, color
      );
   al_draw_prim(&vertices[0], NULL, NULL, 0, vertices.size(), ALLEGRO_PRIM_TRIANGLE_LIST);
   draw_rectangle(x+spacing_x, y+spacing_y, width, height);

   al_flip_display();
}


TEST_F(AllegroFlare_Elements_FUI_PanningGridTestWithAllegroRenderingFixture,
   CAPTURE__build_rectangle_frame_segments__with_select_segments__will_render_as_expected)
{
   AllegroFlare::Elements::FUI::PanningGrid panning_grid;
   panning_grid.set_font_bin(&get_font_bin_ref());
   panning_grid.initialize();

   float spacing_x = 580;
   float spacing_y = 200;
   float width = 400;
   float height = 260;
   float thickness = 12.0f;
   float x = 1920/2 - width/2;
   float y = 1080/2 - height/2;
   ALLEGRO_COLOR color = al_color_html("b8e8e8");
   color = AllegroFlare::ColorKit::fade(color, 0.9);
   bool t = true;
   bool f = false;

   clear();

   std::vector<ALLEGRO_VERTEX> vertices;

   // Top row examples

   // Draw an example rectangle on the left
   vertices = panning_grid.build_rectangle_frame_segments(
         x-spacing_x, y-spacing_y, width, height, thickness, 0.5f, 0.5f, t, f, t, f, t, f, t, f, color
      );
   al_draw_prim(&vertices[0], NULL, NULL, 0, vertices.size(), ALLEGRO_PRIM_TRIANGLE_LIST);
   draw_rectangle(x-spacing_x, y-spacing_y, width, height);

   // Draw an example rectangle in the center
   vertices = panning_grid.build_rectangle_frame_segments(
         x, y-spacing_y, width, height, thickness, 1.0f, 1.0f, f, t, f, t, f, t, f, t, color
      );
   al_draw_prim(&vertices[0], NULL, NULL, 0, vertices.size(), ALLEGRO_PRIM_TRIANGLE_LIST);
   draw_rectangle(x, y-spacing_y, width, height);

   // Draw an example rectangle on the right
   vertices = panning_grid.build_rectangle_frame_segments(
         x+spacing_x, y-spacing_y, width, height, thickness, 0.0f, 0.0f, t, t, t, t, t, t, t, t, color
      );
   al_draw_prim(&vertices[0], NULL, NULL, 0, vertices.size(), ALLEGRO_PRIM_TRIANGLE_LIST);
   draw_rectangle(x+spacing_x, y-spacing_y, width, height);

   // Bottom row examples

   // Draw an example rectangle on the left
   width = 200;
   height = 300;
   x = 1920/2 - width/2;
   y = 1080/2 - height/2;
   vertices = panning_grid.build_rectangle_frame_segments(
         x-spacing_x, y+spacing_y, width, height, thickness, 0.0f, 0.0f, t, t, f, t, t, t, f, t, color);
   al_draw_prim(&vertices[0], NULL, NULL, 0, vertices.size(), ALLEGRO_PRIM_TRIANGLE_LIST);
   draw_rectangle(x-spacing_x, y+spacing_y, width, height);

   // Draw an example rectangle in the center
   thickness = 30;
   vertices = panning_grid.build_rectangle_frame_segments(
         x, y+spacing_y, width, height, thickness, 0.5f, 0.5f, f, f, t, t, f, f, t, t, color
      );
   al_draw_prim(&vertices[0], NULL, NULL, 0, vertices.size(), ALLEGRO_PRIM_TRIANGLE_LIST);
   draw_rectangle(x, y+spacing_y, width, height);

   // Draw an example rectangle on the right
   vertices = panning_grid.build_rectangle_frame_segments(
         x+spacing_x, y+spacing_y, width, height, thickness, 1.0f, 1.0f, f, t, f, t, f, t, t, t, color
      );
   al_draw_prim(&vertices[0], NULL, NULL, 0, vertices.size(), ALLEGRO_PRIM_TRIANGLE_LIST);
   draw_rectangle(x+spacing_x, y+spacing_y, width, height);

   al_flip_display();
}


TEST_F(AllegroFlare_Elements_FUI_PanningGridTestWithAllegroRenderingFixture,
   CAPTURE__build_tab__will_build_the_tab_as_expected)
{
   AllegroFlare::Elements::FUI::PanningGrid panning_grid;
   panning_grid.set_font_bin(&get_font_bin_ref());
   panning_grid.initialize();

   float spacing_x = 460;
   float spacing_y = 240;
   float offset_x = spacing_x * 0.25;
   float width = 180;
   float x = 1920/2;
   float y = 1080/2 - 52;
   float thickness = 16.0f;
   ALLEGRO_COLOR color = al_color_html("b8e8e8");
   color = AllegroFlare::ColorKit::fade(color, 0.9);
   float yy=0;
   float xx=0;

   clear();

   std::vector<ALLEGRO_VERTEX> vertices;


   // Examples showing "horizontal" tabs
   // First row of examples

   // Left example
   yy = y-spacing_y*1.5;
   xx = x-offset_x;
   vertices = panning_grid.build_tab(xx-spacing_x, yy, width, thickness, 1.0f, true, true, false, false, color);
   al_draw_prim(&vertices[0], NULL, NULL, 0, vertices.size(), ALLEGRO_PRIM_TRIANGLE_LIST);
   draw_crosshair(xx-spacing_x, yy);
   draw_crosshair_blue(xx-width-spacing_x, yy);

   // Center example
   vertices = panning_grid.build_tab(xx, yy, width, thickness, 0.5f, true, true, true, false, color);
   al_draw_prim(&vertices[0], NULL, NULL, 0, vertices.size(), ALLEGRO_PRIM_TRIANGLE_LIST);
   draw_crosshair(xx, yy);
   draw_crosshair_blue(xx-width*0.5, yy);
   draw_crosshair_blue(xx+width*0.5, yy);

   // Right example
   vertices = panning_grid.build_tab(xx+spacing_x, yy, width, thickness, 0.0f, true, false, true, false, color);
   al_draw_prim(&vertices[0], NULL, NULL, 0, vertices.size(), ALLEGRO_PRIM_TRIANGLE_LIST);
   draw_crosshair(xx+spacing_x, yy);
   draw_crosshair_blue(xx+width+spacing_x, yy);

   // Second row of examples

   // Left example
   yy = y-spacing_y*0.5;
   xx = x+offset_x;
   vertices = panning_grid.build_tab(xx-spacing_x, yy, width, thickness, 1.0f, false, true, false, false, color);
   al_draw_prim(&vertices[0], NULL, NULL, 0, vertices.size(), ALLEGRO_PRIM_TRIANGLE_LIST);
   draw_crosshair(xx-spacing_x, yy);
   draw_crosshair_blue(xx-width-spacing_x, yy);

   // Center example
   vertices = panning_grid.build_tab(xx, yy, width, thickness, 0.5f, false, true, true, false, color);
   al_draw_prim(&vertices[0], NULL, NULL, 0, vertices.size(), ALLEGRO_PRIM_TRIANGLE_LIST);
   draw_crosshair(xx, yy);
   draw_crosshair_blue(xx-width*0.5, yy);
   draw_crosshair_blue(xx+width*0.5, yy);

   // Right example
   vertices = panning_grid.build_tab(xx+spacing_x, yy, width, thickness, 0.0f, false, false, true, false, color);
   al_draw_prim(&vertices[0], NULL, NULL, 0, vertices.size(), ALLEGRO_PRIM_TRIANGLE_LIST);
   draw_crosshair(xx+spacing_x, yy);
   draw_crosshair_blue(xx+width+spacing_x, yy);


   // Examples showing "vertical" tabs
   // Top row of examples

   // Left example
   yy = y+spacing_y*0.5;
   xx = x-offset_x;
   vertices = panning_grid.build_tab(xx-spacing_x, yy, width, thickness, 1.0f, true, true, false, true, color);
   al_draw_prim(&vertices[0], NULL, NULL, 0, vertices.size(), ALLEGRO_PRIM_TRIANGLE_LIST);
   draw_crosshair(xx-spacing_x, yy);
   draw_crosshair_blue(xx-spacing_x, yy+width);

   // Center example
   vertices = panning_grid.build_tab(xx, yy, width, thickness, 0.5f, true, true, true, true, color);
   al_draw_prim(&vertices[0], NULL, NULL, 0, vertices.size(), ALLEGRO_PRIM_TRIANGLE_LIST);
   draw_crosshair(xx, yy);
   draw_crosshair_blue(xx, yy+width*0.5);
   draw_crosshair_blue(xx, yy-width*0.5);

   // Right example
   vertices = panning_grid.build_tab(xx+spacing_x, yy, width, thickness, 0.0f, true, false, true, true, color);
   al_draw_prim(&vertices[0], NULL, NULL, 0, vertices.size(), ALLEGRO_PRIM_TRIANGLE_LIST);
   draw_crosshair(xx+spacing_x, yy);
   draw_crosshair_blue(xx+spacing_x, yy-width);

   // Bottom row of examples

   // Left example
   yy = y+spacing_y*1.5;
   xx = x+offset_x;
   vertices = panning_grid.build_tab(xx-spacing_x, yy, width, thickness, 1.0f, false, true, false, true, color);
   al_draw_prim(&vertices[0], NULL, NULL, 0, vertices.size(), ALLEGRO_PRIM_TRIANGLE_LIST);
   draw_crosshair(xx-spacing_x, yy);
   draw_crosshair_blue(xx-spacing_x, yy+width);

   // Center example
   vertices = panning_grid.build_tab(xx, yy, width, thickness, 0.5f, false, true, true, true, color);
   al_draw_prim(&vertices[0], NULL, NULL, 0, vertices.size(), ALLEGRO_PRIM_TRIANGLE_LIST);
   draw_crosshair(xx, yy);
   draw_crosshair_blue(xx, yy+width*0.5);
   draw_crosshair_blue(xx, yy-width*0.5);

   // Right example
   vertices = panning_grid.build_tab(xx+spacing_x, yy, width, thickness, 0.0f, false, false, true, true, color);
   al_draw_prim(&vertices[0], NULL, NULL, 0, vertices.size(), ALLEGRO_PRIM_TRIANGLE_LIST);
   draw_crosshair(xx+spacing_x, yy);
   draw_crosshair_blue(xx+spacing_x, yy-width);

   al_flip_display();
}


TEST_F(AllegroFlare_Elements_FUI_PanningGridTestWithAllegroRenderingFixture,
   CAPTURE__build_window_frame__will_build_the_frame_as_expected)
{
   AllegroFlare::Elements::FUI::PanningGrid panning_grid;
   panning_grid.set_font_bin(&get_font_bin_ref());
   panning_grid.initialize();

   float width = 600;
   float height = 400;
   float x = 1920/2 - width/2;
   float y = 1080/2 - height/2;
   std::vector<ALLEGRO_VERTEX> vertices;
   ALLEGRO_COLOR color = al_color_html("b8e8e8");
   color = AllegroFlare::ColorKit::fade(color, 0.9);

   clear();

   vertices = panning_grid.build_window_frame(x, y, width, height, 1.0f, 1.0f, 0.0f, 0.0f, 2.0f, 120, 4.0f, color);
   al_draw_prim(&vertices[0], NULL, NULL, 0, vertices.size(), ALLEGRO_PRIM_TRIANGLE_LIST);
   al_draw_prim(&vertices[0], NULL, NULL, 0, vertices.size(), ALLEGRO_PRIM_TRIANGLE_LIST);
   draw_rectangle(x, y, width, height);

   al_flip_display();
}


TEST_F(AllegroFlare_Elements_FUI_PanningGridTestWithAllegroRenderingFixture,
   CAPTURE__build_bracketed_box__will_build_the_box_as_expected)
{
   AllegroFlare::Elements::FUI::PanningGrid panning_grid;
   panning_grid.set_font_bin(&get_font_bin_ref());
   panning_grid.initialize();

   float width = 80;
   float height = 80;
   float x = 1920/2 - width/2;
   float y = 1080/2 - height/2;
   float offset = 200;
   float thickness = 2.0f;
   std::vector<ALLEGRO_VERTEX> vertices;
   ALLEGRO_COLOR color = al_color_html("b8e8e8");
   ALLEGRO_COLOR box_color = AllegroFlare::ColorKit::fade(color, 0.2);
   ALLEGRO_COLOR bracket_color = AllegroFlare::ColorKit::fade(color, 0.35);

   clear();

   vertices = panning_grid.build_bracketed_box(
         x-offset, y, width, height, thickness, 0.0f, 0.0f, thickness, 16.0f, 16.0f, color, color
      );
   al_draw_prim(&vertices[0], NULL, NULL, 0, vertices.size(), ALLEGRO_PRIM_TRIANGLE_LIST);
   draw_rectangle(x-offset, y, width, height);

   vertices = panning_grid.build_bracketed_box(
         x+offset, y, width, height, thickness, 0.0f, 0.0f, thickness, 16.0f, 16.0f, box_color, bracket_color
      );
   al_draw_prim(&vertices[0], NULL, NULL, 0, vertices.size(), ALLEGRO_PRIM_TRIANGLE_LIST);

   al_flip_display();
}


TEST_F(AllegroFlare_Elements_FUI_PanningGridTestWithAllegroRenderingFixture,
   CAPTURE__draw_text__will_draw_the_text_as_expected)
{
   AllegroFlare::Elements::FUI::PanningGrid panning_grid;
   panning_grid.set_font_bin(&get_font_bin_ref());
   panning_grid.initialize();

   float x = 1920/2;
   float y = 1080/2;
   ALLEGRO_COLOR color = al_color_html("b8e8e8");

   clear();

   panning_grid.draw_text(x, y);

   al_flip_display();
}


TEST_F(AllegroFlare_Elements_FUI_PanningGridTestWithAllegroRenderingFixture,
   CAPTURE__draw_text__will_return_the_width_and_height_of_the_text)
{
   AllegroFlare::Elements::FUI::PanningGrid panning_grid;
   panning_grid.set_font_bin(&get_font_bin_ref());
   panning_grid.initialize();

   float x = 1920/2;
   float y = 1080/2;
   ALLEGRO_COLOR color = al_color_html("b8e8e8");

   clear();

   std::pair<float, float> dimensions = panning_grid.draw_text(x, y, "rotation mode");
   draw_rectangle(x, y, dimensions.first, dimensions.second);

   al_flip_display();
}


