
#include <gtest/gtest.h>


#define ASSERT_THROW_WITH_MESSAGE(code, raised_exception_type, raised_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { EXPECT_EQ(err.what(), std::string( raised_exception_message )); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }


#define ALLEGRO_UNSTABLE


#include <allegro5/allegro.h>
#include <AllegroFlare/Shader.hpp>



const std::string VERTEX_SHADER_SOURCE = R"DELIM(
attribute vec4 al_pos;
attribute vec4 al_color;
attribute vec2 al_texcoord;
uniform mat4 al_projview_matrix;
varying vec4 varying_color;
varying vec2 varying_texcoord;

void main()
{
   varying_color = al_color;
   varying_texcoord = al_texcoord;
   gl_Position = al_projview_matrix * al_pos;
}
)DELIM";



const std::string FRAGMENT_SHADER_SOURCE = R"DELIM(
uniform sampler2D al_tex;
uniform float tint_intensity;
uniform vec3 tint;
varying vec4 varying_color;
varying vec2 varying_texcoord;

void main()
{
   vec4 tmp = texture2D(al_tex, varying_texcoord);
   float inverse_tint_intensity = 1.0 - tint_intensity;
   tmp.r = (tmp.r * inverse_tint_intensity + tint.r * tint_intensity) * tmp.a;
   tmp.g = (tmp.g * inverse_tint_intensity + tint.g * tint_intensity) * tmp.a;
   tmp.b = (tmp.b * inverse_tint_intensity + tint.b * tint_intensity) * tmp.a;
   tmp.a = tmp.a;
   gl_FragColor = tmp;
}
)DELIM";



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


TEST_F(AllegroFlare_ShaderTest, initialize__creates_the_shader)
{
   AllegroFlare::Shader shader(VERTEX_SHADER_SOURCE, FRAGMENT_SHADER_SOURCE);
   shader.initialize();
   SUCCEED();
}


TEST_F(AllegroFlare_ShaderTest, initialize__with_invalid_vertex_code_raises_an_exception)
{
   std::string invalid_vertex_source_code = R"DELIM(
      attribute vec4 al_color;
      attribute vec4 al_pos;
      varying vec4 varying_color;
      void main()
      {
         varying_color = al_color;
         gl_Position = al_projview_matrix * al_pos;
      }
   )DELIM";

   AllegroFlare::Shader shader(invalid_vertex_source_code, FRAGMENT_SHADER_SOURCE);
   std::string expected_error_message = "There was an error attaching the VERTEX shader source code:\nERROR: 0:8: Use of undeclared identifier 'al_projview_matrix'\n";
   ASSERT_THROW_WITH_MESSAGE(shader.initialize(), std::runtime_error, expected_error_message);
}


