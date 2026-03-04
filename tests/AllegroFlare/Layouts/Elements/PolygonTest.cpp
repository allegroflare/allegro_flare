
#include <gtest/gtest.h>

#include <AllegroFlare/Layouts/Elements/Polygon.hpp>
#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>



class AllegroFlare_Layouts_Elements_PolygonTestWithAllegroRenderingFixture
   : public AllegroFlare::Testing::WithAllegroRenderingFixture
{};


TEST(AllegroFlare_Layouts_Elements_PolygonTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Layouts::Elements::Polygon polygon;
}


TEST_F(AllegroFlare_Layouts_Elements_PolygonTestWithAllegroRenderingFixture, CAPTURE__can_be_created_without_blowing_up)
{
   AllegroFlare::Layouts::Elements::Polygon polygon;

   // Weird drop shape, supposed to be a "heart". Nice job, ChatGPT.
   std::vector<AllegroFlare::Vec2D> points =
   {
      { 0.50f, 0.95f }, // top cleft

      { 0.68f, 0.92f },
      { 0.82f, 0.82f },
      { 0.92f, 0.68f },
      { 0.96f, 0.52f },
      { 0.90f, 0.38f },
      { 0.78f, 0.26f },
      { 0.64f, 0.14f },

      { 0.50f, 0.00f }, // bottom tip

      { 0.36f, 0.14f },
      { 0.22f, 0.26f },
      { 0.10f, 0.38f },
      { 0.04f, 0.52f },
      { 0.08f, 0.68f },
      { 0.18f, 0.82f },
      { 0.32f, 0.92f }
   };
   for (auto &point : points)
   {
      point.x *= 600;
      point.y *= 600;
   }


   polygon.polygon = points;

   std::vector<ALLEGRO_VERTEX> triangulated_polygon = polygon.build_triangulated_polygon();

   clear();

   ALLEGRO_BITMAP *texture = get_bitmap_bin_ref()["cat_for_color_testing.jpg"];

   al_draw_prim(&triangulated_polygon[0], nullptr, texture, 0, triangulated_polygon.size(), ALLEGRO_PRIM_TRIANGLE_FAN);

   al_flip_display();
   al_rest(1);
}


