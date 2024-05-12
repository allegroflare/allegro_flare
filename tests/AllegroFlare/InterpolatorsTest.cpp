#include <gtest/gtest.h>

#include <AllegroFlare/Interpolators.hpp>


TEST(AllegroFlareInterpolatorsTest, has_a_namespace_alias_of_Interpolators)
{
   EXPECT_EQ(1.0f, AllegroFlare::Interpolators::linear(1.0f));
}


