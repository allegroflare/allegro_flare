
#include <gtest/gtest.h>


#define ASSERT_THROW_WITH_MESSAGE(code, raised_exception_type, raised_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { EXPECT_EQ(err.what(), std::string( raised_exception_message )); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }



#define ALLEGRO_UNSTABLE


#include <allegro5/allegro.h>
#include <AllegroFlare/Camera3D.hpp>
#include <AllegroFlare/Model3D.hpp>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_color.h>


class AllegroFlare_Camera3DTest : public ::testing::Test
{
protected:
   ALLEGRO_DISPLAY *display;

   AllegroFlare_Camera3DTest()
      : display(nullptr)
   {
   }

   virtual void SetUp() override
   {
      ASSERT_EQ(false, al_is_system_installed());
      ASSERT_EQ(true, al_init());

      al_set_new_display_flags(ALLEGRO_OPENGL | ALLEGRO_PROGRAMMABLE_PIPELINE);
      ASSERT_EQ(ALLEGRO_OPENGL, al_get_new_display_flags() & ALLEGRO_OPENGL);
      ASSERT_EQ(ALLEGRO_PROGRAMMABLE_PIPELINE, al_get_new_display_flags() & ALLEGRO_PROGRAMMABLE_PIPELINE);
      ALLEGRO_DISPLAY *display = al_create_display(800, 600);
      ASSERT_NE(nullptr, display);
   }

   virtual void TearDown() override
   {
      if (display) al_destroy_display(display);
      al_uninstall_system();
   }
};


TEST_F(AllegroFlare_Camera3DTest, can_be_created_without_blowing_up)
{
   AllegroFlare::vec3d position(0, 0, 0);
   AllegroFlare::vec3d view_vector(0, 0, 1);
   AllegroFlare::vec3d up_vector(0, 1, 0);

   AllegroFlare::Camera3D camera(position, view_vector, up_vector);
   SUCCEED();
}


TEST_F(AllegroFlare_Camera3DTest, clear_screen_and_start_transform_on_current_bitmap__with_reasonable_argument_works)
{
   AllegroFlare::vec3d position(0, 0, 0);
   AllegroFlare::vec3d view_vector(0, 0, 1);
   AllegroFlare::vec3d up_vector(0, 1, 0);

   AllegroFlare::Camera3D camera(position, view_vector, up_vector);
   camera.clear_screen_and_start_transform_on_current_bitmap();

   ALLEGRO_DISPLAY *current_display = al_get_current_display();

   al_init_image_addon();
   al_save_bitmap("tmp/hello_world.png", al_get_backbuffer(current_display));

   al_flip_display();

   SUCCEED();
}


TEST_F(AllegroFlare_Camera3DTest, with_stepback__renders_the_expected_output)
{
   AllegroFlare::vec3d position(0, 0, -5);
   AllegroFlare::vec3d view_vector(0, 0, 1);
   AllegroFlare::vec3d up_vector(0, 1, 0);

   AllegroFlare::Camera3D camera(position, view_vector, up_vector);
   camera.clear_screen_and_start_transform_on_current_bitmap();

   ALLEGRO_DISPLAY *current_display = al_get_current_display();

   al_init_image_addon();
   al_save_bitmap("tmp/hello_world.png", al_get_backbuffer(current_display));

   al_draw_filled_rectangle(-0.1, -0.1, 0.1, 0.1, al_color_name("white"));

   al_flip_display();

   SUCCEED();
}


TEST_F(AllegroFlare_Camera3DTest, with_stepback__renders_the_expected_output_2)
{
   AllegroFlare::vec3d position(0, 0, -4);
   AllegroFlare::vec3d view_vector(0, 0, 1);
   AllegroFlare::vec3d up_vector(0, 1, 0);

   AllegroFlare::Camera3D camera(position, view_vector, up_vector);
   camera.clear_screen_and_start_transform_on_current_bitmap();

   ALLEGRO_DISPLAY *current_display = al_get_current_display();

   al_init_image_addon();
   al_save_bitmap("tmp/hello_world.png", al_get_backbuffer(current_display));

   float x, y = 0;
   al_draw_filled_rectangle(-0.1+x, -0.1+y, 0.1+x, 0.1+y, al_color_name("white"));

   x = 1; y = 1;
   al_draw_filled_rectangle(-0.1+x, -0.1+y, 0.1+x, 0.1+y, al_color_name("yellow"));

   x = -2; y = -1;
   al_draw_filled_rectangle(-0.1+x, -0.1+y, 0.1+x, 0.1+y, al_color_name("orange"));

   al_flip_display();
   sleep(3);

   SUCCEED();
}


