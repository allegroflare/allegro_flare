
#include <gtest/gtest.h>

#include <AllegroFlare/Testing/Comparison/AllegroFlare/Tiled/TMJImageLayer.hpp>


TEST(AllegroFlare_Testing_Comparison_AllegroFlare_Tiled_TMJImageLayerTest,
   PrintTo__with_an_AllegroFlare_TMJImageLayer__will_output_as_expected)
{
   std::stringstream ss;
   AllegroFlare::Tiled::TMJImageLayer object;

   PrintTo(object, &ss);

   std::string expected_output = "TMJImageLayer{ id: 0, name: \"[unset-name]\", image_filename: "
      "\"[unset-image_filename]\", offset_x: 0, offset_y: 0, parallax_x: 0, parallax_y: 0, repeat_x: 0, "
      "repeat_y: 0, opacity: 0, tint_color_is_set: 0, tint_color: ALLEGRO_COLOR{1, 1, 1, 1} }";
   std::string actual_output = ss.str();
   EXPECT_EQ(expected_output, actual_output);
}


TEST(AllegroFlare_Testing_Comparison_AllegroFlare_Tiled_TMJImageLayerTest,
   equality_operator__works_with_google_test_EXPECT_EQ_statement)
{
   AllegroFlare::Tiled::TMJImageLayer object;
   AllegroFlare::Tiled::TMJImageLayer other_object;

   EXPECT_EQ(object, other_object);
}


TEST(AllegroFlare_Testing_Comparison_AllegroFlare_Tiled_TMJImageLayerTest,
   DISABLED__equality_operator__works_with_google_test_EXPECT_NE_statement)
{
   AllegroFlare::Tiled::TMJImageLayer object;
   AllegroFlare::Tiled::TMJImageLayer other_object;

   EXPECT_NE(object, other_object);
}


