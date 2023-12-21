
#include <gtest/gtest.h>

#include <AllegroFlare/Model3D.hpp>
#include <AllegroFlare/Camera3D.hpp>

#include <AllegroFlare/Testing/ErrorAssertions.hpp>
#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>
#include <AllegroFlare/Testing/Comparison/AllegroFlare/ALLEGRO_VERTEX_WITH_NORMAL.hpp>


// TODO: improve this:
#if defined(_WIN32) || defined(_WIN64)
      static std::string TEST_FIXTURE_MODEL_FOLDER = "/msys64/home/Mark/Repos/allegro_flare/bin/data/models/";
      static std::string PROPER_TEST_FIXTURE_MODEL_FOLDER = "/msys64/home/Mark/Repos/allegro_flare/tests/fixtures/models/";
#else
      static std::string TEST_FIXTURE_MODEL_FOLDER = "/Users/markoates/Repos/allegro_flare/bin/data/models/";
      static std::string PROPER_TEST_FIXTURE_MODEL_FOLDER = "/Users/markoates/Repos/allegro_flare/tests/fixtures/models/";
#endif



static AllegroFlare::ALLEGRO_VERTEX_WITH_NORMAL build_vertex(
      float x,
      float y,
      float z,
      float u,
      float v,
      ALLEGRO_COLOR color,
      float nx,
      float ny,
      float nz
   )
{
   return AllegroFlare::ALLEGRO_VERTEX_WITH_NORMAL{x, y, z, u, v, color, nx, ny, nz};
}


class AllegroFlare_Model3DTest : public ::testing::Test {};
class AllegroFlare_Model3DWithAllegroRenderingFixtureTest : public AllegroFlare::Testing::WithAllegroRenderingFixture
{
public:
   AllegroFlare::Camera3D camera;
   AllegroFlare::Model3D subject;

   virtual void SetUp() override
   {
      AllegroFlare::Testing::WithAllegroRenderingFixture::SetUp();
      subject.initialize();
   }

   void load_subject(std::string filename=TEST_FIXTURE_MODEL_FOLDER + "coin_ring-01.obj")
   {
      subject.load_obj_file(filename.c_str());
   }

   void examine_subject(float number_of_seconds=1.0f)
   {
      camera.stepout = {0, 0, 4};  // step back from the origin
      camera.tilt = 0.35;          // look down slightly

      int loops = (int)(number_of_seconds * 60.0f);
      for (int i=0; i<loops; i++)
      {
         // update
         camera.spin += 0.01;

         // draw
         al_clear_depth_buffer(1);
         al_clear_to_color(ALLEGRO_COLOR{0.1, 0.105, 0.12, 1.0});
         camera.setup_projection_on(get_display_backbuffer());
         subject.draw();
         al_flip_display();
      }
   }
};



TEST_F(AllegroFlare_Model3DTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Model3D model_3d;
}


TEST_F(AllegroFlare_Model3DTest,
   initialize__will_work_as_expected)
{
   al_init();
   al_init_primitives_addon();
   ALLEGRO_DISPLAY *display = al_create_display(1920, 1080);

   AllegroFlare::Model3D model_3d;
   model_3d.initialize();

   al_destroy_display(display);
   al_uninstall_system();
}


TEST_F(AllegroFlare_Model3DWithAllegroRenderingFixtureTest, VISUAL__draw__will_draw_the_subject)
{
   load_subject();
   examine_subject(2);
}


TEST_F(AllegroFlare_Model3DWithAllegroRenderingFixtureTest,
   inspect_status__will_output_information_about_the_model_in_its_current_state)
{
   load_subject();

   testing::internal::CaptureStdout();
   subject.inspect_status();
   std::string actual_cout = testing::internal::GetCapturedStdout();

   std::string expected_cout =
       "-             model:\n"
       "       num_vertices: 1440\n"
       "  has_vertex_buffer: false\n"
       "  num_named_objects: 1\n"
       "      named_objects:\n"
       "                     - named_object:\n"
       "                         identifier: \"Torus\"\n"
       "                        num_indexes: 1440\n";

   ASSERT_EQ(expected_cout, actual_cout);
}


TEST_F(AllegroFlare_Model3DWithAllegroRenderingFixtureTest,
   flatten_single_named_object__will_remove_named_objects_if_there_is_one_present)
{
   load_subject();
   subject.flatten_single_named_object();

   testing::internal::CaptureStdout();
   subject.inspect_status();
   std::string actual_cout = testing::internal::GetCapturedStdout();

   std::string expected_cout =
       "-             model:\n"
       "       num_vertices: 1440\n"
       "  has_vertex_buffer: false\n"
       "  num_named_objects: 0\n";

   ASSERT_EQ(expected_cout, actual_cout);
}


TEST_F(AllegroFlare_Model3DWithAllegroRenderingFixtureTest,
   append__when_either_object_has_named_objects__will_throw_an_error)
{
   // TODO
}


TEST_F(AllegroFlare_Model3DWithAllegroRenderingFixtureTest,
   append__if_the_object_has_an_active_vertex_buffer__will_destroy_the_vertex_buffer_and_output_a_warning_message)
{
   // TODO
}


TEST_F(AllegroFlare_Model3DWithAllegroRenderingFixtureTest,
   VISUAL__append__will_append_vertices_from_another_model)
{
   load_subject();
   AllegroFlare::Model3D model_to_append;
   model_to_append.initialize();
   std::string model_filename_to_merge = TEST_FIXTURE_MODEL_FOLDER + "archway-01.obj";
   model_to_append.load_obj_file(model_filename_to_merge.c_str());

   subject.flatten_single_named_object();
   model_to_append.flatten_single_named_object();

   testing::internal::CaptureStdout();
   subject.append(model_to_append);
   std::string actual_cout = testing::internal::GetCapturedStdout();
   std::string expected_cout = ""; // Expecting no output warnings

   EXPECT_EQ(expected_cout, actual_cout);

   examine_subject(1);
}


TEST_F(AllegroFlare_Model3DWithAllegroRenderingFixtureTest,
   extract_named_object_vertices__when_a_named_object_does_not_exist_with_that_name__throws_an_error)
{
   load_subject(PROPER_TEST_FIXTURE_MODEL_FOLDER + "named_objects-02.obj");
   EXPECT_EQ(3, subject.named_objects.size());

   EXPECT_THROW_WITH_MESSAGE(
      subject.extract_named_object_vertices("a-named-object-that-does-not-exist"),
      std::runtime_error,
      "[AllegroFlare::Model3D::extract_named_object_vertices] error: Looking for named_object named "
         "\"a-named-object-that-does-not-exist\" but it does not exist."
   );
}


TEST_F(AllegroFlare_Model3DWithAllegroRenderingFixtureTest,
   count_num_named_objects_with_name__will_return_the_number_of_named_objects_that_match_the_name)
{
   load_subject(PROPER_TEST_FIXTURE_MODEL_FOLDER + "level_with_multiple_named_objects_with_the_same_name.obj");
   int actual_count = subject.count_num_named_objects_with_name("mushroom");
   EXPECT_EQ(3, actual_count);
}


TEST_F(AllegroFlare_Model3DWithAllegroRenderingFixtureTest,
   remove_named_objects__will_remove_all_instances_of_named_objects_that_have_the_name)
{
   load_subject(PROPER_TEST_FIXTURE_MODEL_FOLDER + "level_with_multiple_named_objects_with_the_same_name.obj");
   ASSERT_EQ(3, subject.count_num_named_objects_with_name("mushroom"));
   subject.remove_named_objects("mushroom");
   EXPECT_EQ(0, subject.count_num_named_objects_with_name("mushroom"));
}


TEST_F(AllegroFlare_Model3DWithAllegroRenderingFixtureTest,
   extract_named_object_vertices__will_return_vertices_of_the_named_object)
{
   load_subject(PROPER_TEST_FIXTURE_MODEL_FOLDER + "named_objects-02.obj");
   EXPECT_EQ(3, subject.named_objects.size());

   ALLEGRO_COLOR c{1, 1, 1, 1};
   std::vector<AllegroFlare::ALLEGRO_VERTEX_WITH_NORMAL> expected_vertices = {
      build_vertex(-3, 2, -22, 0.625, 0.5,  c, 0,  1,  0),
      build_vertex(-5, 2, -22, 0.875, 0.5,  c, 0,  1,  0),
      build_vertex(-5, 2, -20, 0.875, 0.25, c, 0,  1,  0),
      build_vertex(-5, 2, -20, 0.875, 0.25, c, 0,  1,  0),
      build_vertex(-3, 2, -20, 0.625, 0.25, c, 0,  1,  0),
      build_vertex(-3, 2, -22, 0.625, 0.5,  c, 0,  1,  0),

      build_vertex(-3, 0, -20, 0.375, 0.25, c, 0,  0,  1),
      build_vertex(-3, 2, -20, 0.625, 0.25, c, 0,  0,  1),
      build_vertex(-5, 2, -20, 0.625, 0,    c, 0,  0,  1),
      build_vertex(-5, 2, -20, 0.625, 0,    c, 0,  0,  1),
      build_vertex(-5, 0, -20, 0.375, 0,    c, 0,  0,  1),
      build_vertex(-3, 0, -20, 0.375, 0.25, c, 0,  0,  1),

      build_vertex(-5, 0, -20, 0.375, 1,    c, -1, 0,  0),
      build_vertex(-5, 2, -20, 0.625, 1,    c, -1, 0,  0),
      build_vertex(-5, 2, -22, 0.625, 0.75, c, -1, 0,  0),
      build_vertex(-5, 2, -22, 0.625, 0.75, c, -1, 0,  0),
      build_vertex(-5, 0, -22, 0.375, 0.75, c, -1, 0,  0),
      build_vertex(-5, 0, -20, 0.375, 1,    c, -1, 0,  0),

      build_vertex(-5, 0, -22, 0.125, 0.5,  c, 0,  -1, 0),
      build_vertex(-3, 0, -22, 0.375, 0.5,  c, 0,  -1, 0),
      build_vertex(-3, 0, -20, 0.375, 0.25, c, 0,  -1, 0),
      build_vertex(-3, 0, -20, 0.375, 0.25, c, 0,  -1, 0),
      build_vertex(-5, 0, -20, 0.125, 0.25, c, 0,  -1, 0),
      build_vertex(-5, 0, -22, 0.125, 0.5,  c, 0,  -1, 0),

      build_vertex(-3, 0, -22, 0.375, 0.5,  c, 1,  0,  0),
      build_vertex(-3, 2, -22, 0.625, 0.5,  c, 1,  0,  0),
      build_vertex(-3, 2, -20, 0.625, 0.25, c, 1,  0,  0),
      build_vertex(-3, 2, -20, 0.625, 0.25, c, 1,  0,  0),
      build_vertex(-3, 0, -20, 0.375, 0.25, c, 1,  0,  0),
      build_vertex(-3, 0, -22, 0.375, 0.5,  c, 1,  0,  0),

      build_vertex(-5, 0, -22, 0.375, 0.75, c, 0, 0, -1),
      build_vertex(-5, 2, -22, 0.625, 0.75, c, 0, 0, -1),
      build_vertex(-3, 2, -22, 0.625, 0.5,  c, 0, 0, -1),
      build_vertex(-3, 2, -22, 0.625, 0.5,  c, 0, 0, -1),
      build_vertex(-3, 0, -22, 0.375, 0.5,  c, 0, 0, -1),
      build_vertex(-5, 0, -22, 0.375, 0.75, c, 0, 0, -1),
   };
   std::vector<AllegroFlare::ALLEGRO_VERTEX_WITH_NORMAL> actual_vertices =
      subject.extract_named_object_vertices("Cube");

   //expected_vertices.erase(expected_vertices.begin(), expected_vertices.begin() + 32);
   //actual_vertices.erase(actual_vertices.begin(), actual_vertices.begin() + 32);

   //for (int i=0; i<3; i++)
   //{
      //expected_vertices.pop_back();
      //actual_vertices.pop_back();
   //}

   EXPECT_EQ(36, actual_vertices.size()); // NOTE: 32 vertices in a cube (which is what this object is in this test)
   EXPECT_EQ(expected_vertices, actual_vertices);
}


TEST_F(AllegroFlare_Model3DWithAllegroRenderingFixtureTest,
   DISABLED__promote_to_vertex_buffer__when_there_are_one_or_more_named_objects__will_throw_an_error)
{
   // TODO
}


TEST_F(AllegroFlare_Model3DWithAllegroRenderingFixtureTest,
   promote_to_vertex_buffer__will_be_reflected_in_inspect_status)
{
   load_subject();
   subject.flatten_single_named_object();
   subject.promote_to_vertex_buffer();

   testing::internal::CaptureStdout();
   subject.inspect_status();
   std::string actual_cout = testing::internal::GetCapturedStdout();

   std::string expected_cout =
       "-             model:\n"
       "       num_vertices: 1440\n"
       "  has_vertex_buffer: true\n" // <-- expected modified line
       "  num_named_objects: 0\n";

   ASSERT_EQ(expected_cout, actual_cout);
}


TEST_F(AllegroFlare_Model3DWithAllegroRenderingFixtureTest,
   promote_to_vertext_buffer__will_not_produce_any_warnings)
{
   load_subject();
   subject.flatten_single_named_object();

   testing::internal::CaptureStdout();
   subject.promote_to_vertex_buffer();
   std::string actual_cout = testing::internal::GetCapturedStdout();
   std::string expected_cout = ""; // Expecting no output warnings

   EXPECT_EQ(expected_cout, actual_cout);
}


TEST_F(AllegroFlare_Model3DWithAllegroRenderingFixtureTest,
   VISUAL__draw__when_the_model_has_been_promoted_to_a_vertex_buffer__will_render_as_expected)
{
   load_subject();
   AllegroFlare::Model3D model_to_append;
   model_to_append.initialize();
   std::string model_filename_to_merge = TEST_FIXTURE_MODEL_FOLDER + "archway-01.obj";
   model_to_append.load_obj_file(model_filename_to_merge.c_str());

   testing::internal::CaptureStdout();

   // 1. flatten any named objects on the models to be merged (appended)
   subject.flatten_single_named_object();
   model_to_append.flatten_single_named_object();

   // 2. append other model
   subject.append(model_to_append);

   // 3. promote to vertex buffer
   subject.promote_to_vertex_buffer();

   std::string actual_cout = testing::internal::GetCapturedStdout();
   std::string expected_cout = ""; // Expecting no output warnings
   EXPECT_EQ(expected_cout, actual_cout);

   examine_subject(1);
}


