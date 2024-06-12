
#include <gtest/gtest.h>

#include <Tileo/Shaders/MeshWithNormals.hpp>
#include <AllegroFlare/Testing/ErrorAssertions.hpp>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_color.h>
#include <AllegroFlare/Placement2D.hpp>
#include <AllegroFlare/BitmapBin.hpp>


#if defined(_WIN32) || defined(_WIN64)
#define TEST_FIXTURES_PATH "/msys64/home/Mark/Repos/allegro_flare/tests/fixtures/"
#define TEST_FIXTURE_TEST_RUN_SNAPSHOTS_FOLDER "/msys64/home/Mark/Repos/allegro_flare/tmp/test_snapshots/"
#else
#define TEST_FIXTURES_PATH "/Users/markoates/Repos/allegro_flare/tests/fixtures/"
#define TEST_FIXTURE_TEST_RUN_SNAPSHOTS_FOLDER "/Users/markoates/Repos/allegro_flare/tmp/test_snapshots/"
#endif


class Tileo_Shaders_MeshWithNormalsTest : public ::testing::Test
{
protected:
   ALLEGRO_DISPLAY *display;

   Tileo_Shaders_MeshWithNormalsTest()
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
      if (al_get_current_display()) al_destroy_display(al_get_current_display());
      al_uninstall_system();
   }

   ALLEGRO_DISPLAY *get_display()
   {
      return display;
   }
};


TEST_F(Tileo_Shaders_MeshWithNormalsTest, can_be_created_without_blowing_up)
{
   Tileo::Shaders::MeshWithNormals flat_color_shader;
   SUCCEED();
}


TEST_F(Tileo_Shaders_MeshWithNormalsTest, activate__before_being_initialized_raises_an_exception)
{
   Tileo::Shaders::MeshWithNormals flat_color_shader;
   std::string expected_error_message = AllegroFlare::Logger::build_guard_error_message(
      "Tileo::Shaders::MeshWithNormals::activate",
      "initialized"
   );
   EXPECT_THROW_WITH_MESSAGE(flat_color_shader.activate(), std::runtime_error, expected_error_message);
}


TEST_F(Tileo_Shaders_MeshWithNormalsTest, initialize__works_without_blowing_up)
{
   Tileo::Shaders::MeshWithNormals flat_color_shader;
   flat_color_shader.initialize();
   SUCCEED();
}


TEST_F(Tileo_Shaders_MeshWithNormalsTest, activate__works_without_blowing_up)
{
   Tileo::Shaders::MeshWithNormals flat_color_shader;

   flat_color_shader.initialize();
   flat_color_shader.activate();
}


TEST_F(Tileo_Shaders_MeshWithNormalsTest, when_active__renders_the_image_with_the_flat_color)
{
   Tileo::Shaders::MeshWithNormals flat_color_shader;
   AllegroFlare::BitmapBin bitmap_bin;
   bitmap_bin.set_full_path(TEST_FIXTURES_PATH);

   flat_color_shader.initialize();
   flat_color_shader.activate();

   al_init_image_addon();

   ALLEGRO_BITMAP *test_image = bitmap_bin.auto_get("bitmaps/billboarding_tester_sprite.png");

   ALLEGRO_COLOR color = al_color_name("red");

   flat_color_shader.set_flat_color(color);
   flat_color_shader.set_light_direction({1.0f, 1.0f, 0.0f}); // not needed for this demo

   ALLEGRO_DISPLAY *current_display = al_get_current_display();
   ASSERT_NE(nullptr, current_display);

   AllegroFlare::Placement2D place(
         al_get_display_width(current_display)/2,
         al_get_display_height(current_display)/2,
         al_get_bitmap_width(test_image),
         al_get_bitmap_height(test_image));
   place.scale = AllegroFlare::vec2d(4, 4);
   place.start_transform();
   al_draw_bitmap(test_image, 0, 0, 0);
   place.restore_transform();

   ALLEGRO_COLOR expected_color = color;
   ALLEGRO_COLOR actual_color = al_get_pixel(
         al_get_backbuffer(current_display),
         al_get_display_width(current_display)/2,
         al_get_display_height(current_display)/2
      );

   //ASSERT_EQ(color.r, actual_color.r);
   //ASSERT_EQ(color.g, actual_color.g);
   //ASSERT_EQ(color.b, actual_color.b);
   //ASSERT_EQ(color.a, actual_color.a);

   //al_flip_display();


   // TODO: improve this test snapshot naming inference
   std::string output_image_full_filename =
      TEST_FIXTURE_TEST_RUN_SNAPSHOTS_FOLDER "Tileo_Shaders_MeshWithNormalsTest_when_active__renders_"
      "the_image_with_the_flat_color.png";
   ASSERT_EQ(true, al_save_bitmap(output_image_full_filename.c_str(), al_get_backbuffer(current_display)));
}


