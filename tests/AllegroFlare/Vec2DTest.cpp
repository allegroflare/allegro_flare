

#include <gtest/gtest.h>

#include <AllegroFlare/Vec2D.hpp>


TEST(AllegroFlare_Vec2DTest, when_constructed_from_a_float_pair__will_work_as_expected)
{
   std::pair<float, float> float_pair = { 0.125f, 8.5f };
   AllegroFlare::Vec2D vec = float_pair; // Construction

   EXPECT_EQ(vec.x, 0.125f);
   EXPECT_EQ(vec.y, 8.5f);
}


TEST(AllegroFlare_Vec2DTest, when_constructed_from_a_braced_set_of_floats__will_work_as_expected)
{
   AllegroFlare::Vec2D vec = { 0.125f, 8.5f };
   EXPECT_EQ(vec.x, 0.125f);
   EXPECT_EQ(vec.y, 8.5f);
}


TEST(AllegroFlare_Vec2DTest, when_the_assignment_operator_is_used_from_a_float_pair__will_work_as_expected)
{
   std::pair<float, float> float_pair = { 0.125f, 8.5f };
   AllegroFlare::Vec2D vec;

   vec = float_pair; // Assignment

   EXPECT_EQ(vec.x, 0.125f);
   EXPECT_EQ(vec.y, 8.5f);
}


TEST(AllegroFlare_Vec2DTest, when_the_assignment_operator_is_used_from_a_braced_set_of_floats__will_work_as_expected)
{
   AllegroFlare::Vec2D vec;
   vec = { 0.125f, 8.5f }; // Assignment

   EXPECT_EQ(vec.x, 0.125f);
   EXPECT_EQ(vec.y, 8.5f);
}


TEST(AllegroFlare_Vec2DTest, when_plus_equals_operator_is_used_with_a_float_pair__will_add_components_correctly)
{
    AllegroFlare::Vec2D vec(5.0f, 10.0f);
    std::pair<float, float> operand_pair = {1.5f, -2.5f};

    vec += operand_pair;

    EXPECT_EQ(vec.x, 6.5f);   // 5.0 + 1.5
    EXPECT_EQ(vec.y, 7.5f);   // 10.0 + (-2.5)
}


TEST(AllegroFlare_Vec2DTest, when_minus_equals_operator_is_used_with_a_float_pair__will_subtract_components_correctly)
{
    AllegroFlare::Vec2D vec(10.0f, 20.0f);
    std::pair<float, float> operand_pair = {3.0f, -5.0f};

    vec -= operand_pair;

    EXPECT_EQ(vec.x, 7.0f);   // 10.0 - 3.0
    EXPECT_EQ(vec.y, 25.0f);  // 20.0 - (-5.0)
}


TEST(AllegroFlare_Vec2DTest,
   when_multiply_equals_operator_is_used_with_a_float_pair__will_multiply_components_correctly)
{
    AllegroFlare::Vec2D vec(4.0f, -5.0f);
    std::pair<float, float> operand_pair = {2.5f, 2.0f};

    vec *= operand_pair;

    EXPECT_EQ(vec.x, 10.0f);  // 4.0 * 2.5
    EXPECT_EQ(vec.y, -10.0f); // -5.0 * 2.0
}


TEST(AllegroFlare_Vec2DTest,
   when_multiply_equals_operator_is_used_with_a_float_pair_containing_zero__will_result_in_zeroed_components)
{
    AllegroFlare::Vec2D vec1(10.0f, 20.0f);
    std::pair<float, float> pair1 = {0.0f, 2.0f};
    vec1 *= pair1;
    EXPECT_EQ(vec1.x, 0.0f);   // 10.0 * 0.0
    EXPECT_EQ(vec1.y, 40.0f);  // 20.0 * 2.0

    AllegroFlare::Vec2D vec2(10.0f, 20.0f);
    std::pair<float, float> pair2 = {3.0f, 0.0f};
    vec2 *= pair2;
    EXPECT_EQ(vec2.x, 30.0f);  // 10.0 * 3.0
    EXPECT_EQ(vec2.y, 0.0f);   // 20.0 * 0.0

    AllegroFlare::Vec2D vec3(10.0f, 20.0f);
    std::pair<float, float> pair3 = {0.0f, 0.0f};
    vec3 *= pair3;
    EXPECT_EQ(vec3.x, 0.0f);   // 10.0 * 0.0
    EXPECT_EQ(vec3.y, 0.0f);   // 20.0 * 0.0
}


TEST(AllegroFlare_Vec2DTest,
   when_divide_equals_operator_is_used_with_a_float_pair__will_divide_components_correctly)
{
    AllegroFlare::Vec2D vec(10.0f, -20.0f);
    std::pair<float, float> operand_pair = {2.0f, 4.0f}; // Using non-zero divisors

    vec /= operand_pair;

    EXPECT_EQ(vec.x, 5.0f);   // 10.0 / 2.0
    EXPECT_EQ(vec.y, -5.0f);  // -20.0 / 4.0
}


TEST(AllegroFlare_Vec2DTest,
   compound_assignment_operators_with_float_pair_when_returning_reference__will_allow_chaining_and_update_correctly)
{
    AllegroFlare::Vec2D vec_plus(1.0f, 2.0f);
    std::pair<float, float> p1 = {2.0f, 3.0f};
    std::pair<float, float> p2 = {0.5f, 1.5f};

    (vec_plus += p1) += p2; // (1+2)+0.5, (2+3)+1.5
    EXPECT_EQ(vec_plus.x, 3.5f);
    EXPECT_EQ(vec_plus.y, 6.5f);

    AllegroFlare::Vec2D vec_minus(10.0f, 20.0f);
    (vec_minus -= p1) -= p2; // (10-2)-0.5, (20-3)-1.5
    EXPECT_EQ(vec_minus.x, 7.5f);
    EXPECT_EQ(vec_minus.y, 15.5f);

    AllegroFlare::Vec2D vec_multiply(2.0f, 4.0f);
    // p1 = {2.0f, 3.0f}, p2 = {0.5f, 1.5f}
    (vec_multiply *= p1) *= p2; // (2*2)*0.5, (4*3)*1.5
    EXPECT_EQ(vec_multiply.x, 2.0f);    // 4.0 * 0.5
    EXPECT_EQ(vec_multiply.y, 18.0f);   // 12.0 * 1.5

    AllegroFlare::Vec2D vec_divide(20.0f, 60.0f);
    // p1 = {2.0f, 3.0f}, p2 = {0.5f, 1.5f} -> for division, p2 values might lead to large numbers if used as divisor of divisor
    // Let's use p1 for both divisions, or a new pair with simple values
    std::pair<float, float> p_div = {2.0f, 5.0f};
    (vec_divide /= p1) /= p_div; // (20/2)/2, (60/3)/5
    EXPECT_EQ(vec_divide.x, 5.0f);    // 10.0 / 2.0
    EXPECT_EQ(vec_divide.y, 4.0f);    // 20.0 / 5.0
}



