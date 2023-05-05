
#include <gtest/gtest.h>

#include <AllegroFlare/Shaders/Multitexture.hpp>

#include <AllegroFlare/Camera3D.hpp>
#include <AllegroFlare/MultitextureModel3D.hpp>
#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>
// TODO: improve this:
#if defined(_WIN32) || defined(_WIN64)
      static std::string TEST_FIXTURE_FOLDER = "/msys64/home/Mark/Repos/allegro_flare/bin/data/";
      static std::string PROPER_TEST_FIXTURE_FOLDER = "/msys64/home/Mark/Repos/allegro_flare/tests/fixtures/";
#else
      static std::string TEST_FIXTURE_FOLDER = "/Users/markoates/Repos/allegro_flare/bin/data/";
      static std::string PROPER_TEST_FIXTURE_FOLDER = "/Users/markoates/Repos/allegro_flare/tests/fixtures/";
#endif


class AllegroFlare_Shaders_MultitextureTest : public ::testing::Test {};

class AllegroFlare_Shaders_MultitextureTestWithSetup : public AllegroFlare::Testing::WithAllegroRenderingFixture
{
public:
   AllegroFlare::Camera3D camera;
   AllegroFlare::MultitextureModel3D subject;
   ALLEGRO_BITMAP *texture_a;
   bool subject_loaded;

   AllegroFlare_Shaders_MultitextureTestWithSetup()
      : camera()
      , subject()
      , texture_a(nullptr)
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
         std::string texture_a_filename="simple_scene-01-ao-01.jpg"
      )
   {
      std::string fixtures_path = get_fixtures_path();
      subject.load_obj_file(
         fixtures_path + base_obj_filename,
         fixtures_path + uv2_obj_filename
      );
      texture_a = get_bitmap_bin_ref()[texture_a_filename];
      subject_loaded = true;
   }

   void examine_subject(float number_of_seconds=1.0f)
   {
      if (!subject_loaded) throw std::runtime_error("no subject loaded");

      camera.stepout = {0, 1.0, 4};  // step back from the origin
      camera.tilt = 0.13;            // look up(-)/down(+)

      int loops = (int)(number_of_seconds * 60.0f);
      for (int i=0; i<loops; i++)
      {
         // update
         camera.spin += 0.001;

         // setup the render surface
         al_clear_depth_buffer(1);
         al_clear_to_color(ALLEGRO_COLOR{0.1, 0.105, 0.12, 1.0});
         camera.setup_projection_on(get_display_backbuffer());

         // setup our subject texture
         subject.texture = texture_a;

         // render our subject
         subject.draw();

         // flip the display
         al_flip_display();
      }
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


TEST_F(AllegroFlare_Shaders_MultitextureTestWithSetup, when_active__will_render_model_as_expected)
{
   // TODO
   load_subject();
   examine_subject(6.0);
}


