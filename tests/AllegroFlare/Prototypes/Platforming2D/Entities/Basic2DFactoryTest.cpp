
#include <gtest/gtest.h>

#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>

#include <AllegroFlare/Prototypes/Platforming2D/Entities/Basic2DFactory.hpp>

class AllegroFlare_Prototypes_Platforming2D_Entities_Basic2DFactoryTest : public ::testing::Test {};
class AllegroFlare_Prototypes_Platforming2D_Entities_Basic2DFactoryWithAllegroRenderingFixtureTest
   : public AllegroFlare::Testing::WithAllegroRenderingFixture {};

#define TEST_FIXTURE_BITMAP_FOLDER "/Users/markoates/Repos/allegro_flare/tests/fixtures/bitmaps"

#include <AllegroFlare/Prototypes/Platforming2D/EntityFlagNames.hpp>



TEST(AllegroFlare_Prototypes_Platforming2D_Entities_Basic2DFactoryTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Prototypes::Platforming2D::Entities::Basic2DFactory basic2dfactory;
}


TEST_F(AllegroFlare_Prototypes_Platforming2D_Entities_Basic2DFactoryWithAllegroRenderingFixtureTest,
   create_from_bitmap_filename__returns_a_basic2d_entity_with_the_expected_bitmap_and_size_and_bitmap_alignment_strategy)
{
   using namespace AllegroFlare::Prototypes::Platforming2D::EntityFlagNames;

   AllegroFlare::BitmapBin &bitmap_bin = get_bitmap_bin_ref();
   bitmap_bin.set_full_path(TEST_FIXTURE_BITMAP_FOLDER);

   AllegroFlare::Prototypes::Platforming2D::Entities::Basic2DFactory basic2d_factory(&get_bitmap_bin_ref());
   AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D *created_entity =
      basic2d_factory.create_from_bitmap_filename("map_a", "test-sprite-128.png", "bottom_centered");

   AllegroFlare::vec2d expected_dimentions = {128, 128};
   AllegroFlare::vec2d actual_dimentions = created_entity->get_place_ref().size;

   ASSERT_NE(nullptr, created_entity->get_bitmap());
   ASSERT_EQ("bottom_centered", created_entity->get_bitmap_alignment_strategy());
   ASSERT_EQ(expected_dimentions, actual_dimentions);
   ASSERT_EQ(true, created_entity->exists(ON_MAP_NAME, "map_a"));

   delete created_entity;
}


