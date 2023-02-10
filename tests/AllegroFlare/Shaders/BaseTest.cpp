
#include <gtest/gtest.h>

#include <AllegroFlare/Shaders/Base.hpp>
#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>


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


TEST_F(AllegroFlare_Shaders_BaseWithAllegroRenderingFixtureTest,
   hotload__will_reload_the_shader_source_code_with_new_code_and_rebuild_the_shader)
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
      "};                         \n";

   std::string hotloaded_fragment_source =
      "precision mediump float;                   \n"
      "void main()                                \n"
      "{                                          \n"
      "  gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0); \n"
      "}                                          \n";

   test_class.hotload(hotloaded_vertex_source, hotloaded_fragment_source);
}


