
#include <gtest/gtest.h>

#include <AllegroFlare/GraphicsPipelines/DynamicEntityPipeline/ShadowDepthMapRenderer.hpp>


TEST(AllegroFlare_GraphicsPipelines_DynamicEntityPipeline_ShadowDepthMapRendererTest, can_be_created_without_blowing_up)
{
   AllegroFlare::GraphicsPipelines::DynamicEntityPipeline::ShadowDepthMapRenderer shadow_depth_map_renderer;
}


TEST(AllegroFlare_GraphicsPipelines_DynamicEntityPipeline_ShadowDepthMapRendererTest, render__does_not_blow_up)
{
   AllegroFlare::GraphicsPipelines::DynamicEntityPipeline::ShadowDepthMapRenderer shadow_depth_map_renderer;
   shadow_depth_map_renderer.render();
}


