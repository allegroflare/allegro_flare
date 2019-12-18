
#include <gtest/gtest.h>


#define ASSERT_THROW_WITH_MESSAGE(code, raised_exception_type, raised_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { EXPECT_EQ(err.what(), std::string( raised_exception_message )); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }



#define ALLEGRO_UNSTABLE


#include <allegro5/allegro.h>
#include <AllegroFlare/Camera3D.hpp>
#include <AllegroFlare/Model3D.hpp>
#include <AllegroFlare/Useful.hpp> // for TAU
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_color.h>
#include <cmath> // for std::abs


bool basically_equal(const ALLEGRO_COLOR &col1, const ALLEGRO_COLOR &col2, float threshold=0.0001f)
{
   if (std::abs(col1.a - col2.a) > threshold) return false;
   if (std::abs(col1.g - col2.g) > threshold) return false;
   if (std::abs(col1.b - col2.b) > threshold) return false;
   if (std::abs(col1.r - col2.r) > threshold) return false;
   return true;
}


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

   void draw_targets()
   {
      float x = 0;
      float y = 0;
      al_draw_filled_rectangle(-0.1+x, -0.1+y, 0.1+x, 0.1+y, al_color_name("white"));

      x = 5;
      y = 0;
      al_draw_filled_rectangle(-0.1+x, -0.1+y, 0.1+x, 0.1+y, al_color_name("yellow"));

      x = -5;
      y = 0;
      al_draw_filled_rectangle(-0.1+x, -0.1+y, 0.1+x, 0.1+y, al_color_name("orange"));
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
   AllegroFlare::vec3d position(0, 0, -5);
   AllegroFlare::vec3d view_vector(0, 0, 1);
   AllegroFlare::vec3d up_vector(0, 1, 0);
   float stepback_rotation = 0.0;
   float stepback_pitch = 0.0;

   ALLEGRO_DISPLAY *display = al_get_current_display();
   ALLEGRO_BITMAP *rendering_surface = al_get_backbuffer(display);
   ASSERT_NE(nullptr, rendering_surface);

   ALLEGRO_BITMAP *backbuffer_sub_bitmap = al_create_sub_bitmap(al_get_backbuffer(display), 0, 0, al_get_display_width(display), al_get_display_height(display));
   ASSERT_NE(nullptr, backbuffer_sub_bitmap);

   float screen_center_x = al_get_bitmap_width(rendering_surface)/2;
   float screen_center_y = al_get_bitmap_height(rendering_surface)/2;

   int total_passes = 260;
   for (int i=0; i<total_passes; i++)
   {
      float pass = (float) i / total_passes;
      AllegroFlare::Camera3D camera(position, view_vector, up_vector);
      //stepback_rotation += 0.01;
      //stepback_pitch += 0.01;
      camera.stepback_rotation.y = pass * AllegroFlare::TAU / 8;//stepback_rotation;
      camera.stepback_pitch = 0;///stepback_pitch;
      camera.clear_screen_and_start_transform_on_current_bitmap();

      draw_targets();

      al_set_target_bitmap(backbuffer_sub_bitmap);
      al_draw_rectangle(screen_center_x - 10, screen_center_y - 5, screen_center_x + 10, screen_center_y + 5, al_color_name("yellow"), 3.0);

      al_flip_display();
   }

   ALLEGRO_COLOR expected_color = al_color_name("orange");
   ALLEGRO_COLOR actual_color = al_get_pixel(rendering_surface, screen_center_x, screen_center_y);
   ASSERT_EQ(true, basically_equal(expected_color, actual_color));


   for (int i=0; i<total_passes; i++)
   {
      float pass = (float) i / total_passes;
      AllegroFlare::Camera3D camera(position, view_vector, up_vector);
      //stepback_rotation += 0.01;
      //stepback_pitch += 0.01;
      camera.stepback_rotation.y = pass * AllegroFlare::TAU / 8;//stepback_rotation;
      camera.stepback_pitch = 0;///stepback_pitch;
      camera.clear_screen_and_start_transform_on_current_bitmap();

      draw_targets();

      al_flip_display();
   }

   ALLEGRO_DISPLAY *current_display = al_get_current_display();
   al_init_image_addon();
   al_save_bitmap("tmp/hello_world.png", al_get_backbuffer(current_display));

   sleep(1);

   SUCCEED();
}


