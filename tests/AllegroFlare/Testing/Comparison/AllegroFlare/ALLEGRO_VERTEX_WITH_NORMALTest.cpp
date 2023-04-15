
#include <gtest/gtest.h>

#include <AllegroFlare/Testing/Comparison/AllegroFlare/ALLEGRO_VERTEX_WITH_NORMAL.hpp>


TEST(AllegroFlare_Testing_Comparison_AllegroFlare_ALLEGRO_VERTEX_WITH_NORMALTest,
   PrintTo__with_an_AllegroFlare_ALLEGRO_VERTEX_WITH_NORMAL__will_output_as_expected)
{
   std::stringstream ss;
   AllegroFlare::ALLEGRO_VERTEX_WITH_NORMAL object; // = {0.1, 0.2};
   object.x = 1.0;
   object.y = 8.4;
   object.z = 20.6;
   object.u = 1.0;
   object.v = 8.4;
   object.nx = 0.2;
   object.ny = 0.4;
   object.nz = 0.6;

   PrintTo(object, &ss);

   std::string expected_output = "ALLEGRO_VERTEX_WITH_NORMAL(x:1, y:8.4, z:20.6, u:1, v:8.4, "
                                                            "nx:0.2, ny:0.4, nz:0.6, )";
   std::string actual_output = ss.str();
   EXPECT_EQ(expected_output, actual_output);
}


//TEST(AllegroFlare_Testing_Comparison_AllegroFlare_ALLEGRO_VERTEX_WITH_NORMALTest,
   //equality_operator__works_with_google_test_EXPECT_statement)
//{
   //AllegroFlare::ALLEGRO_VERTEX_WITH_NORMAL object;
   //AllegroFlare::ALLEGRO_VERTEX_WITH_NORMAL other_object;

   //EXPECT_EQ(object, other_object);
//}


