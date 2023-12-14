
#include <gtest/gtest.h>

#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>
#include <AllegroFlare/GraphicsPipelines/DynamicEntityPipeline/ShadowDepthMapRenderer.hpp>
#include <AllegroFlare/GraphicsPipelines/DynamicEntityPipeline/EntityFactory.hpp>
#include <AllegroFlare/Testing/TestNameInference.hpp>


class AllegroFlare_GraphicsPipelines_DynamicEntityPipeline_ShadowDepthMapRendererTest : public ::testing::Test {};
class AllegroFlare_GraphicsPipelines_DynamicEntityPipeline_ShadowDepthMapRendererTestWithAllegroRenderingFixtureTest :
   public AllegroFlare::Testing::WithAllegroRenderingFixture
{};


TEST_F(AllegroFlare_GraphicsPipelines_DynamicEntityPipeline_ShadowDepthMapRendererTest,
   can_be_created_without_blowing_up)
{
   AllegroFlare::GraphicsPipelines::DynamicEntityPipeline::ShadowDepthMapRenderer shadow_depth_map_renderer;
}


TEST_F(AllegroFlare_GraphicsPipelines_DynamicEntityPipeline_ShadowDepthMapRendererTestWithAllegroRenderingFixtureTest,
   render__does_not_blow_up)
{
   AllegroFlare::GraphicsPipelines::DynamicEntityPipeline::EntityPool entity_pool;
   AllegroFlare::GraphicsPipelines::DynamicEntityPipeline::ShadowDepthMapRenderer shadow_depth_map_renderer;

   // Setup our classes
   shadow_depth_map_renderer.set_entity_pool(&entity_pool);
   //shadow_depth_map_renderer.setup_backbuffer_from_display(al_get_current_display()); // TODO: switch this to primary
                                                                                      // display from framework
   shadow_depth_map_renderer.setup_result_surface_bitmap(1920, 1080);
   //shadow_depth_map_renderer.setup_result_surface_bitmap();
   shadow_depth_map_renderer.init_camera_defaults();
   shadow_depth_map_renderer.init_shader();

   shadow_depth_map_renderer.render();

   // Shutdown our system
   shadow_depth_map_renderer.destroy();
}


TEST_F(AllegroFlare_GraphicsPipelines_DynamicEntityPipeline_ShadowDepthMapRendererTestWithAllegroRenderingFixtureTest,
   render__with_objects_in_the_scene__will_render_a_shadow_depth_map_as_expected)
{
   AllegroFlare::ModelBin model_bin;
   model_bin.set_full_path(get_fixtures_path() + "models");
   AllegroFlare::GraphicsPipelines::DynamicEntityPipeline::EntityPool entity_pool;
   AllegroFlare::GraphicsPipelines::DynamicEntityPipeline::ShadowDepthMapRenderer shadow_depth_map_renderer;

   // Setup our classes
   shadow_depth_map_renderer.set_entity_pool(&entity_pool);
   //shadow_depth_map_renderer.setup_backbuffer_from_display(get_display());
   shadow_depth_map_renderer.setup_result_surface_bitmap(1920, 1080);
   //shadow_depth_map_renderer.setup_result_surface_bitmap();
   shadow_depth_map_renderer.init_camera_defaults();
   shadow_depth_map_renderer.init_shader();

   // Setup our EntityFactory
   AllegroFlare::GraphicsPipelines::DynamicEntityPipeline::EntityFactory entity_factory;
   entity_factory.set_model_bin(&model_bin);
   entity_factory.set_bitmap_bin(&get_bitmap_bin_ref()); // TODO: Only make this dependency required if it is used

   // Add some entities to our scene (Keep in mind for now only StaticModel3D entities are rendered)
   auto entity = entity_factory.create_static_model_3d("rounded_unit_cube-01.obj");
   //entity_pool.add(entity);
   entity_pool.add({
      entity_factory.create_static_model_3d("rounded_unit_cube-01.obj", "none", { 0, 0, 0 }),
      entity_factory.create_static_model_3d("rounded_unit_cube-01.obj", "none", { 5, 0, 0 }),
      entity_factory.create_static_model_3d("rounded_unit_cube-01.obj", "none", { 0, 5, 0 }),
      entity_factory.create_static_model_3d("rounded_unit_cube-01.obj", "none", { -5, 0, 5 }),
   });

   // Render the scene
   shadow_depth_map_renderer.render();

   // Grab the result and save to test snapshots
   // NOTE: Scene is facing a far cube, orthographic projection, tilted slightly up.  Appears as a grey rounded object
   std::string snapshot_filename = AllegroFlare::Testing::TestNameInference::build_test_snapshot_full_filename();
   ALLEGRO_BITMAP *rendered_shadow_depth_map_result = shadow_depth_map_renderer.get_result_surface_bitmap();
   al_save_bitmap(snapshot_filename.c_str(), rendered_shadow_depth_map_result);

   // Shutdown our system
   shadow_depth_map_renderer.destroy();
}


TEST_F(AllegroFlare_GraphicsPipelines_DynamicEntityPipeline_ShadowDepthMapRendererTestWithAllegroRenderingFixtureTest,
   VISUAL__render__with_moving_light_will_translate_as_expected)
{
   AllegroFlare::ModelBin model_bin;
   model_bin.set_full_path(get_fixtures_path() + "models");
   AllegroFlare::GraphicsPipelines::DynamicEntityPipeline::EntityPool entity_pool;
   AllegroFlare::GraphicsPipelines::DynamicEntityPipeline::ShadowDepthMapRenderer shadow_depth_map_renderer;
   AllegroFlare::Camera3D &light = shadow_depth_map_renderer.get_casting_light_ref();

   // Setup our classes
   shadow_depth_map_renderer.set_entity_pool(&entity_pool);
   //shadow_depth_map_renderer.setup_backbuffer_from_display(get_display());
   shadow_depth_map_renderer.setup_result_surface_bitmap(1920, 1080);
   //shadow_depth_map_renderer.setup_result_surface_bitmap();
   shadow_depth_map_renderer.init_camera_defaults();
   shadow_depth_map_renderer.init_shader();

   // Setup our EntityFactory
   AllegroFlare::GraphicsPipelines::DynamicEntityPipeline::EntityFactory entity_factory;
   entity_factory.set_model_bin(&model_bin);
   entity_factory.set_bitmap_bin(&get_bitmap_bin_ref()); // TODO: Only make this dependency required if it is used

   // Add some entities to our scene (Keep in mind for now only StaticModel3D entities are rendered)
   auto entity = entity_factory.create_static_model_3d("rounded_unit_cube-01.obj");
   //entity_pool.add(entity);
   entity_pool.add({
      entity_factory.create_static_model_3d("rounded_unit_cube-01.obj", "none", { 0, 0, 0 }),
      entity_factory.create_static_model_3d("rounded_unit_cube-01.obj", "none", { 5, 0, 0 }),
      entity_factory.create_static_model_3d("rounded_unit_cube-01.obj", "none", { 0, 5, 0 }),
      entity_factory.create_static_model_3d("rounded_unit_cube-01.obj", "none", { -5, 0, 5 }),
      entity_factory.create_static_model_3d("coin_ring-01.obj",         "none", { 5, -5, -5 }),
      entity_factory.create_static_model_3d("coin_ring-01.obj",         "none", { -5, -5, 0 }),
      entity_factory.create_static_model_3d("coin_ring-01.obj",         "none", { -5, 0, -5 }),
      entity_factory.create_static_model_3d("flat_stage-01.obj",        "none", { 0, 0, 0 }),
      entity_factory.create_static_model_3d("simple_scene-01.obj",      "none", { 0, 0, 0 }),
   });

   for (int i=0; i<500; i++)
   {
      // Do some movements of the light
      light.spin += 0.005f;

      // Render the scene
      // Render the depth map pass to our buffer
      shadow_depth_map_renderer.render();

      // Render the depth map pass to the screen for us to see
      al_clear_depth_buffer(1);
      //al_set_render_state(ALLEGRO_DEPTH_TEST, 1);
      //al_set_render_state(ALLEGRO_WRITE_MASK, ALLEGRO_MASK_RGBA);
      al_draw_bitmap(shadow_depth_map_renderer.get_result_surface_bitmap(), 0, 0, 0);
      
      al_flip_display();
   }

   std::string snapshot_filename = AllegroFlare::Testing::TestNameInference::build_test_snapshot_full_filename();
   ALLEGRO_BITMAP *rendered_shadow_depth_map_result = shadow_depth_map_renderer.get_result_surface_bitmap();
   al_save_bitmap(snapshot_filename.c_str(), rendered_shadow_depth_map_result);

   // Shutdown our system
   shadow_depth_map_renderer.destroy();
}



