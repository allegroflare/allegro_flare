
#include <gtest/gtest.h>

#include <AllegroFlare/Shaders/Multitexture.hpp>

#include <AllegroFlare/Camera3D.hpp>
#include <AllegroFlare/MultitextureModel3D.hpp>
#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>


class AllegroFlare_Shaders_MultitextureTest : public ::testing::Test {};

class AllegroFlare_Shaders_MultitextureTestWithSetup : public AllegroFlare::Testing::WithAllegroRenderingFixture
{
public:
   AllegroFlare::Camera3D camera;
   AllegroFlare::MultitextureModel3D subject;
   ALLEGRO_BITMAP *texture_a;
   ALLEGRO_BITMAP *texture_b;
   bool subject_loaded;

   AllegroFlare_Shaders_MultitextureTestWithSetup()
      : camera()
      , subject()
      , texture_a(nullptr)
      , texture_b(nullptr)
      , subject_loaded(false)
   {}

   virtual void SetUp() override
   {
      AllegroFlare::Testing::WithAllegroRenderingFixture::SetUp();
      subject.initialize();
   }

   void load_subject(
         std::string base_obj_filename="models/simple_scene-01.obj",
         std::string uv2_obj_filename="models/simple_scene-01-ao-01.obj",
         std::string texture_a_filename="simple_scene-01-1024.jpg",
         std::string texture_b_filename="simple_scene-01-ao-01.jpg"
      )
   {
      std::string fixtures_path = get_fixtures_path();
      subject.load_obj_file(
         fixtures_path + base_obj_filename,
         fixtures_path + uv2_obj_filename
      );
      texture_a = get_bitmap_bin_ref()[texture_a_filename];
      texture_b = get_bitmap_bin_ref()[texture_b_filename];
      subject_loaded = true;
   }
};


TEST_F(AllegroFlare_Shaders_MultitextureTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Shaders::Multitexture multitexture;
}


TEST_F(AllegroFlare_Shaders_MultitextureTest, TYPE__has_the_expected_value)
{
   EXPECT_STREQ(
     "AllegroFlare/Shaders/Multitexture",
     AllegroFlare::Shaders::Multitexture::TYPE
   );
}


TEST_F(AllegroFlare_Shaders_MultitextureTest, type__has_the_expected_value_matching_TYPE)
{
   AllegroFlare::Shaders::Multitexture multitexture;
   EXPECT_EQ(AllegroFlare::Shaders::Multitexture::TYPE, multitexture.get_type());
}


TEST_F(AllegroFlare_Shaders_MultitextureTestWithSetup, initialize__will_not_blow_up)
{
   AllegroFlare::Shaders::Multitexture multitexture_shader;
   multitexture_shader.initialize();
}


TEST_F(AllegroFlare_Shaders_MultitextureTestWithSetup, when_active__will_render_model_as_expected)
{
   AllegroFlare::Shaders::Multitexture multitexture_shader;
   multitexture_shader.initialize();

   load_subject();

   camera.stepout = {0, 1.0, 4};  // step back from the origin
   camera.tilt = 0.13;            // look up(-)/down(+)
   camera.spin = 0.2;             // set a good start initial spin

   float number_of_seconds=60.0f;
   int loops = (int)(number_of_seconds * 3.0f);
   for (int i=0; i<loops; i++)
   {
      // update
      camera.spin += 0.001;

      // setup the render surface
      al_clear_depth_buffer(1);
      al_clear_to_color(ALLEGRO_COLOR{0.1, 0.105, 0.12, 1.0});
      camera.setup_projection_on(get_display_backbuffer());

      // Setup our subject texture
      //NOTE: At this time, the subject has no texture(s), e.g. "subject.texture = texture_a" here. Not until the
      // MultitextureModel3D has the textures on it.

      multitexture_shader.set_texture_a(texture_a);
      multitexture_shader.set_texture_b(texture_b);

      multitexture_shader.activate();

      // render our subject
      //NOTE: For this test, will not be using "subject.draw()". Instead we will be rendering manually, and setting
      // textures on the shader manually
      std::vector<AllegroFlare::ALLEGRO_VERTEX_WITH_TWO_UVS_AND_NORMAL> &vertices = subject.vertexes;
      al_draw_prim(&vertices[0], subject.vertex_declaration, texture_a, 0, vertices.size(), ALLEGRO_PRIM_TRIANGLE_LIST);

      multitexture_shader.deactivate();

      // flip the display
      al_flip_display();
   }
}


