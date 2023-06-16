
#include <gtest/gtest.h>

#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>
#include <AllegroFlare/GraphicsPipelines/DynamicEntityPipeline/ShadowDepthMapRenderer.hpp>
#include <AllegroFlare/GraphicsPipelines/DynamicEntityPipeline/EntityFactory.hpp>


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
   shadow_depth_map_renderer.setup_backbuffer_from_display(al_get_current_display()); // TODO: switch this to primary
                                                                                      // display from framework
   shadow_depth_map_renderer.setup_result_surface_bitmap();
   shadow_depth_map_renderer.init_shader();

   shadow_depth_map_renderer.render();

   // Shutdown our system
   shadow_depth_map_renderer.destroy();
}


TEST_F(AllegroFlare_GraphicsPipelines_DynamicEntityPipeline_ShadowDepthMapRendererTestWithAllegroRenderingFixtureTest,
   render__with_objects_in_the_scene__will_render_a_shadow_depth_map_as_expected)
{
   AllegroFlare::GraphicsPipelines::DynamicEntityPipeline::EntityPool entity_pool;
   AllegroFlare::GraphicsPipelines::DynamicEntityPipeline::ShadowDepthMapRenderer shadow_depth_map_renderer;

   // Setup our classes
   shadow_depth_map_renderer.set_entity_pool(&entity_pool);
   shadow_depth_map_renderer.setup_backbuffer_from_display(al_get_current_display()); // TODO: switch this to primary
                                                                                      // display from framework
   shadow_depth_map_renderer.setup_result_surface_bitmap();
   shadow_depth_map_renderer.init_shader();

   // Add some entities to our scene (Keep in mind for now only StaticModel3D entities are rendered)
   AllegroFlare::GraphicsPipelines::DynamicEntityPipeline::EntityFactory entity_factory;
   entity_factory.set_model_bin(&get_framework_model_bin);


   // Render the scene
   shadow_depth_map_renderer.render();

   // Shutdown our system
   shadow_depth_map_renderer.destroy();
}



