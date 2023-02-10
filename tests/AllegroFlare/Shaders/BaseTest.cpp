
#include <gtest/gtest.h>

#include <AllegroFlare/Shaders/Base.hpp>
#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>
#include <allegro5/allegro_primitives.h>
#include <AllegroFlare/Color.hpp>


class AllegroFlare_Shaders_BaseTest : public ::testing::Test {};
class AllegroFlare_Shaders_BaseWithAllegroRenderingFixtureTest
   : public AllegroFlare::Testing::WithAllegroRenderingFixture
{
};


class ShadersBaseTestClass : public AllegroFlare::Shaders::Base
{
public:
   ShadersBaseTestClass(std::string vertex_source_code="", std::string fragment_source_code="")
      : AllegroFlare::Shaders::Base("ShadersBaseTestClass", vertex_source_code, fragment_source_code)
   {}
};


TEST_F(AllegroFlare_Shaders_BaseTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Shaders::Base base;
}


TEST_F(AllegroFlare_Shaders_BaseTest, TYPE__has_the_expected_value)
{
   AllegroFlare::Shaders::Base base;
   EXPECT_EQ("AllegroFlare/Shaders/Base", base.get_type());
}


TEST_F(AllegroFlare_Shaders_BaseTest, type__has_the_expected_value_matching_TYPE)
{
   AllegroFlare::Shaders::Base base;
   EXPECT_EQ(AllegroFlare::Shaders::Base::TYPE, base.get_type());
}


TEST_F(AllegroFlare_Shaders_BaseTest, derived_classes_will_have_the_expected_type)
{
   ShadersBaseTestClass test_class;
   EXPECT_EQ("ShadersBaseTestClass", test_class.get_type());
}


TEST_F(AllegroFlare_Shaders_BaseTest, hotload__before_initialization__will_throw_an_error)
{
   // TODO
}


TEST_F(AllegroFlare_Shaders_BaseWithAllegroRenderingFixtureTest, hotload__will_not_blow_up)
{
   ShadersBaseTestClass test_class(
      al_get_default_shader_source(ALLEGRO_SHADER_GLSL, ALLEGRO_VERTEX_SHADER),
      al_get_default_shader_source(ALLEGRO_SHADER_GLSL, ALLEGRO_PIXEL_SHADER)
   );
   test_class.initialize();

   std::string hotloaded_vertex_source =
      "attribute vec4 vPosition;  \n"
      "void main()                \n"
      "{                          \n"
      "  gl_Position = vPosition; \n"
      "}                          \n";

   std::string hotloaded_fragment_source =
      "void main()                                \n"
      "{                                          \n"
      "  gl_FragColor = vec4(0.0, 0.4, 0.6, 1.0); \n"
      "}                                          \n";

   test_class.hotload(hotloaded_vertex_source, hotloaded_fragment_source);
}


TEST_F(AllegroFlare_Shaders_BaseWithAllegroRenderingFixtureTest,
   VISUAL__hotload__will_reload_the_shader_source_code_with_new_code_and_rebuild_the_shader)
{
static const std::string hotloaded_vertex_source = R"DELIM(
attribute vec4 al_pos;
attribute vec4 al_color;
attribute vec2 al_texcoord;
uniform mat4 al_projview_matrix;
uniform bool al_use_tex_matrix;
uniform mat4 al_tex_matrix;
varying vec4 varying_color;
varying vec2 varying_texcoord;
void main()
{
 varying_color = al_color;
 if (al_use_tex_matrix) {
   vec4 uv = al_tex_matrix * vec4(al_texcoord, 0, 1);
   varying_texcoord = vec2(uv.x, uv.y);
 }
 else
   varying_texcoord = al_texcoord;
 gl_Position = al_projview_matrix * al_pos;
}
)DELIM";


static const std::string hotloaded_fragment_source = R"DELIM(
#ifdef GL_ES
precision lowp float;
#endif
uniform sampler2D al_tex;
uniform bool al_use_tex;
uniform bool al_alpha_test;
uniform int al_alpha_func;
uniform float al_alpha_test_val;
varying vec4 varying_color;
varying vec2 varying_texcoord;

bool alpha_test_func(float x, int op, float compare);

void main()
{
  vec4 c;
  if (al_use_tex)
    c = varying_color * texture2D(al_tex, varying_texcoord);
  else
    c = varying_color;
  if (!al_alpha_test || alpha_test_func(c.a, al_alpha_func, al_alpha_test_val))
    //gl_FragColor = c;   // For the purposes of the test, this is the original line
    gl_FragColor = c * c; // For the purposes of the test, this is the changed line
  else
    discard;
}

bool alpha_test_func(float x, int op, float compare)
{
  if (op == 0) return false;
  else if (op == 1) return true;
  else if (op == 2) return x < compare;
  else if (op == 3) return x == compare;
  else if (op == 4) return x <= compare;
  else if (op == 5) return x > compare;
  else if (op == 6) return x != compare;
  else if (op == 7) return x >= compare;
  return false;
}
)DELIM";


   ALLEGRO_BITMAP *toy_train_image = get_bitmap_bin_ref().auto_get("toy-train-02.png");

   ShadersBaseTestClass test_class(
      al_get_default_shader_source(ALLEGRO_SHADER_GLSL, ALLEGRO_VERTEX_SHADER),
      al_get_default_shader_source(ALLEGRO_SHADER_GLSL, ALLEGRO_PIXEL_SHADER)
   );

   // Initialize our shader
   test_class.initialize();

   // draw some "scene"
   al_clear_to_color(AllegroFlare::Color::Eigengrau);
   al_draw_bitmap(
      toy_train_image,
      1920/2-al_get_bitmap_width(toy_train_image)/2,
      1080/2-al_get_bitmap_height(toy_train_image)/2,
      0
   );
   al_flip_display();
   al_rest(2);

   // Hotload our new shader source
   test_class.hotload(hotloaded_vertex_source, hotloaded_fragment_source);
   test_class.activate();

   al_clear_to_color(AllegroFlare::Color::Eigengrau);
   al_draw_bitmap(
      toy_train_image,
      1920/2-al_get_bitmap_width(toy_train_image)/2,
      1080/2-al_get_bitmap_height(toy_train_image)/2,
      0
   );
   al_flip_display();
   al_rest(2);
}


