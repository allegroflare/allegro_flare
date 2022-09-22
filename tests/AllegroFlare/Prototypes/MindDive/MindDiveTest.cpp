#include <gtest/gtest.h>

#define EXPECT_THROW_WITH_MESSAGE(code, raised_exception_type, expected_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { EXPECT_EQ(std::string(expected_exception_message), err.what()); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }

#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>


class AllegroFlare_Prototypes_MindDive_MindDiveTest : public ::testing::Test {};
class AllegroFlare_Prototypes_MindDive_MindDiveTestWithAllegroRenderingFixture
   : public AllegroFlare::Testing::WithAllegroRenderingFixture
{};


#include <AllegroFlare/Prototypes/MindDive/MindDive.hpp>
#include <allegro5/allegro_primitives.h> // for al_is_primitives_addon_initialized();


TEST_F(AllegroFlare_Prototypes_MindDive_MindDiveTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Prototypes::MindDive::MindDive mind_dive;
}


TEST_F(AllegroFlare_Prototypes_MindDive_MindDiveTestWithAllegroRenderingFixture, render__will_work_as_expected)
{
   AllegroFlare::Prototypes::MindDive::MindDive mind_dive(&get_bitmap_bin_ref());
   mind_dive.initialize();

   AllegroFlare::Placement2D place = build_centered_placement(
      mind_dive.get_tunnel_mesh_ref().infer_real_width(),
      mind_dive.get_tunnel_mesh_ref().infer_real_height()
   );
   place.scale = {2.0, 2.0};

   clear();

   place.start_transform();
   mind_dive.render();
   place.restore_transform();

   al_flip_display();
   sleep_for(1);
}


