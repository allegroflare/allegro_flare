
#include <gtest/gtest.h>

#include <AllegroFlare/Testing/Comparison/AllegroFlare/ALLEGRO_VERTEX_WITH_TWO_UVS_AND_NORMAL.hpp>


TEST(AllegroFlare_Testing_Comparison_AllegroFlare_ALLEGRO_VERTEX_WITH_TWO_UVS_AND_NORMALTest,
   PrintTo__with_an_AllegroFlare_ALLEGRO_VERTEX_WITH_TWO_UVS_AND_NORMAL__will_output_as_expected)
{
   std::stringstream ss;
   AllegroFlare::ALLEGRO_VERTEX_WITH_TWO_UVS_AND_NORMAL object; // = {0.1, 0.2};
   object.x = 1.0;
   object.y = 8.4;
   object.z = 20.6;
   object.u1 = 1.0;
   object.v1 = 8.4;
   object.u2 = 0.125;
   object.v2 = 0.625;
   object.color = ALLEGRO_COLOR{0.125, 0.6, 0.8, 1.0};
   object.nx = 0.2;
   object.ny = 0.4;
   object.nz = 0.6;

   PrintTo(object, &ss);

   std::string expected_output = "ALLEGRO_VERTEX_WITH_TWO_UVS_AND_NORMAL(x:1, y:8.4, z:20.6, u1:1, v1:8.4, "
                                                            "u2:0.125, v2:0.625, "
                                                            "ALLEGRO_COLOR{0.125, 0.6, 0.8, 1}, "
                                                            "nx:0.2, ny:0.4, nz:0.6, )";
   std::string actual_output = ss.str();
   EXPECT_EQ(expected_output, actual_output);
}


TEST(AllegroFlare_Testing_Comparison_AllegroFlare_ALLEGRO_VERTEX_WITH_TWO_UVS_AND_NORMALTest,
   equality_operator__works_with_google_test_EXPECT_statement)
{
   AllegroFlare::ALLEGRO_VERTEX_WITH_TWO_UVS_AND_NORMAL object{
         1, 2, 3, 4, 5, 6, 7, ALLEGRO_COLOR{8, 9, 10, 11}, 12, 13, 14
      };
   AllegroFlare::ALLEGRO_VERTEX_WITH_TWO_UVS_AND_NORMAL other_object{
         1, 2, 3, 4, 5, 6, 7, ALLEGRO_COLOR{8, 9, 10, 11}, 12, 13, 14
      };

   EXPECT_EQ(object, other_object);
}


TEST(AllegroFlare_Testing_Comparison_AllegroFlare_ALLEGRO_VERTEX_WITH_TWO_UVS_AND_NORMALTest,
   inequality_operator__when_operating_on_an_inequality__works_with_google_test_EXPECT_statement)
{
   AllegroFlare::ALLEGRO_VERTEX_WITH_TWO_UVS_AND_NORMAL object{
         1, 2, 3, 4, 5, 6, 7, ALLEGRO_COLOR{8, 9, 10, 11}, 12, 13, 14
      };
   AllegroFlare::ALLEGRO_VERTEX_WITH_TWO_UVS_AND_NORMAL other_object;

   EXPECT_NE(object, other_object);
}


