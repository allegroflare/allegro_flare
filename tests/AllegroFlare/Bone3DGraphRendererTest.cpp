
#include <gtest/gtest.h>

#define ASSERT_THROW_WITH_MESSAGE(code, raised_exception_type, expected_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { EXPECT_EQ(std::string(expected_exception_message), err.what()); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }

#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>

class AllegroFlare_Bone3DGraphRendererTest : public ::testing::Test
{};

class AllegroFlare_Bone3DGraphRendererTestWithAllegroRenderingFixture :
   public AllegroFlare::Testing::WithAllegroRenderingFixture
{};


#include <AllegroFlare/Bone3DGraphRenderer.hpp>


TEST_F(AllegroFlare_Bone3DGraphRendererTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Bone3DGraphRenderer bone_graph_renderer;
}


TEST_F(AllegroFlare_Bone3DGraphRendererTest, render__without_allegro_initialized__raises_an_error)
{
   AllegroFlare::Bone3DGraphRenderer bone_graph_renderer;
   std::string expected_error_message =
      "Bone3DGraphRenderer::render: error: guard \"al_is_system_installed()\" not met";
   ASSERT_THROW_WITH_MESSAGE(bone_graph_renderer.render(), std::runtime_error, expected_error_message);
}


TEST_F(AllegroFlare_Bone3DGraphRendererTestWithAllegroRenderingFixture, render__without_a_root_bone__raises_an_error)
{
   AllegroFlare::Bone3DGraphRenderer bone_graph_renderer;
   std::string expected_error_message =
      "Bone3DGraphRenderer::render: error: guard \"root_bone\" not met";
   ASSERT_THROW_WITH_MESSAGE(bone_graph_renderer.render(), std::runtime_error, expected_error_message);
}


TEST_F(AllegroFlare_Bone3DGraphRendererTestWithAllegroRenderingFixture, CAPTURE__render__will_not_blow_up)
{
   // TODO
   AllegroFlare::Bone3D *root_bone = new AllegroFlare::Bone3D;
   root_bone->position.x = 0;
   root_bone->position.y = 0;
   //root_bone->rotation.z = 0.1f;
      AllegroFlare::Bone3D *child_bone = new AllegroFlare::Bone3D;
      child_bone->position.x = 100;
      child_bone->position.y = 0;
      child_bone->rotation.z = 0.1f;
         AllegroFlare::Bone3D *child_bone2 = new AllegroFlare::Bone3D;
         child_bone2->position.x = 0;
         child_bone2->position.y = 250;
      child_bone->add_child(child_bone2);
   root_bone->add_child(child_bone);

   AllegroFlare::Bone3DGraphRenderer bone_graph_renderer(&get_font_bin_ref(), root_bone);
   bone_graph_renderer.render();

   AllegroFlare::Placement3D centered_placement; // NOTE: this should be a projection on the display
   centered_placement.position.x = 1920/2;
   centered_placement.position.y = 1080/2;

   float num_seconds= 0.2;
   for (unsigned i=0; i<60*num_seconds; i++)
   {
      al_clear_to_color(ALLEGRO_COLOR{0, 0, 0, 0});

      centered_placement.start_transform();
      bone_graph_renderer.render();
      centered_placement.restore_transform();

      root_bone->rotation.z += 0.001;
      child_bone->rotation.z -= 0.0018;
      
      al_flip_display();
   }
}


