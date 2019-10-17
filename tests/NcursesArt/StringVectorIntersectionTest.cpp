
#include <gtest/gtest.h>

#include <NcursesArt/StringVectorIntersection.hpp>

TEST(StringVectorIntersectionTest, intersection__returns_the_intersection)
{
   std::vector<std::string> v1 = { "a", "b", "c", "d", "e", "f" };
   std::vector<std::string> v2 = { "a", "c", "j", "k", "f" };

   NcursesArt::StringVectorIntersection intersector(v1, v2);

   std::vector<std::string> expected_intersection = { "a", "c", "f" };
   std::vector<std::string> actual_intersection = intersector.intersection();

   EXPECT_EQ(expected_intersection, actual_intersection);
}

TEST(StringVectorIntersectionTest, intersection__returns_the_intersection_regardless_of_ordering_of_either_set)
{
   std::vector<std::string> v1 = { "f", "b", "c", "d", "a", "e" };
   std::vector<std::string> v2 = { "c", "a", "j", "k", "f" };

   NcursesArt::StringVectorIntersection intersector(v1, v2);

   std::vector<std::string> expected_intersection = { "a", "c", "f" };
   std::vector<std::string> actual_intersection = intersector.intersection();

   EXPECT_EQ(expected_intersection, actual_intersection);
}


