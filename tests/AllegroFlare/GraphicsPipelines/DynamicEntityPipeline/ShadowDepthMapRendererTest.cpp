
#include <gtest/gtest.h>

#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>
#include <AllegroFlare/GraphicsPipelines/DynamicEntityPipeline/ShadowDepthMapRenderer.hpp>


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
   shadow_depth_map_renderer.init_shader();

   shadow_depth_map_renderer.render();

   // Shutdown our system
   shadow_depth_map_renderer.destroy();
}


