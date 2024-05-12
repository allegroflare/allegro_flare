#include <gtest/gtest.h>

#include <AllegroFlare/Interpolators.hpp>


TEST(AllegroFlareInterpolatorsTest, has_a_legacy_namespace_alias_of_interpolators)
{
   // TODO: Remove the alias and update downstream
   EXPECT_EQ(1.0f, AllegroFlare::Interpolators::linear(1.0f));
   EXPECT_EQ(1.0f, AllegroFlare::interpolator::linear(1.0f));
}


