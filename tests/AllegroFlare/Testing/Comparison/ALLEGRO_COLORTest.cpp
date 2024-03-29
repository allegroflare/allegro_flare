
#include <gtest/gtest.h>

#include <AllegroFlare/Testing/Comparison/ALLEGRO_COLOR.hpp>


TEST(AllegroFlare_Testing_Comparison_ALLEGRO_COLORTest, PrintTo__with_an_ALLEGRO_COLOR__will_output_as_expected)
{
   std::stringstream ss;
   ALLEGRO_COLOR color = ALLEGRO_COLOR{0.2, 0.3, 0.4, 0.5};

   PrintTo(color, &ss);

   std::string expected_output = "ALLEGRO_COLOR{0.2, 0.3, 0.4, 0.5}";
   std::string actual_output = ss.str();
   EXPECT_EQ(expected_output, actual_output);
}


TEST(AllegroFlare_Testing_Comparison_ALLEGRO_COLORTest,
   equality_operator__works_with_google_test_EXPECT_statement)
{
   ALLEGRO_COLOR vec{1, 1, 1, 1};
   ALLEGRO_COLOR other_vec{1, 1, 1, 1};

   EXPECT_EQ(vec, other_vec);
}


TEST(AllegroFlare_Testing_Comparison_ALLEGRO_COLORTest,
   inequality_operator__works_with_google_test_EXPECT_statement)
{
   ALLEGRO_COLOR vec{0, 1, 1, 1};
   ALLEGRO_COLOR other_vec{1, 1, 1, 1};

   EXPECT_NE(vec, other_vec);
}


