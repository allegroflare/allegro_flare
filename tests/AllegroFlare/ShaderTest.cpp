
#include <gtest/gtest.h>


#define ASSERT_THROW_WITH_MESSAGE(code, raised_exception_type, raised_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { EXPECT_EQ(err.what(), std::string( raised_exception_message )); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }


#define ALLEGRO_UNSTABLE


#include <allegro5/allegro.h>
#include <AllegroFlare/Shader.hpp>


class AllegroFlare_ShaderTest : public ::testing::Test
{
protected:
   ALLEGRO_DISPLAY *display;

   AllegroFlare_ShaderTest()
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


TEST_F(AllegroFlare_ShaderTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Shader shader;
   SUCCEED();
}


TEST_F(AllegroFlare_ShaderTest, initialize__with_source_files_that_are_not_present_raises_an_exception)
{
   AllegroFlare::Shader shader(
         "vertex_shader_file_that_does_not_exist.shader",
         "fragment_shader_file_that_does_not_exist.shader"
      );

   std::string expected_error_message = "There was an error attaching the VERTEX shader source from file:\n\"vertex_shader_file_that_does_not_exist.shader\"\nFailed to open vertex_shader_file_that_does_not_exist.shader\n";
   ASSERT_THROW_WITH_MESSAGE(shader.initialize(), std::runtime_error, expected_error_message);
}


TEST_F(AllegroFlare_ShaderTest, initialize__creates_the_shader)
{
   std::string path = "/Users/markoates/Repos/allegro_flare/";

   AllegroFlare::Shader shader(
         path + "bin/tests/AllegroFlare/data/shaders/" + "flat_color_shader.vertex.glsl",
         path + "bin/tests/AllegroFlare/data/shaders/" + "flat_color_shader.fragment.glsl"
      );

   shader.initialize();

   SUCCEED();
}


