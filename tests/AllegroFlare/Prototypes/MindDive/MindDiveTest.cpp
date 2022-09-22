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


TEST_F(AllegroFlare_Prototypes_MindDive_MindDiveTestWithAllegroRenderingFixture,
   INTERACTIVE__render__will_work_as_expected)
{
   AllegroFlare::Prototypes::MindDive::MindDive mind_dive(&get_bitmap_bin_ref());
   mind_dive.initialize();

   clear();

   mind_dive.update();
   mind_dive.render();

   al_flip_display();
   sleep_for(1);
}


