
#include <gtest/gtest.h>


#define ASSERT_THROW_WITH_MESSAGE(code, raised_exception_type, raised_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { EXPECT_EQ(err.what(), std::string( raised_exception_message )); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }



#define ALLEGRO_UNSTABLE


#include <allegro5/allegro.h>
#include <AllegroFlare/Camera3D.hpp>


TEST(AllegroFlare_Camera3DTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Camera3D camera;
}


