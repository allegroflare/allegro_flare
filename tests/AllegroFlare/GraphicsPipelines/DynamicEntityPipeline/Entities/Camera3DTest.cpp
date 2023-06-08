
#include <gtest/gtest.h>

#include <AllegroFlare/GraphicsPipelines/DynamicEntityPipeline/Entities/Camera3D.hpp>


TEST(AllegroFlare_GraphicsPipelines_DynamicEntityPipeline_Entities_Camera3DTest, can_be_created_without_blowing_up)
{
   AllegroFlare::GraphicsPipelines::DynamicEntityPipeline::Entities::Camera3D camera3d;
}


TEST(AllegroFlare_GraphicsPipelines_DynamicEntityPipeline_Entities_Camera3DTest, TYPE__has_the_expected_value)
{
   EXPECT_STREQ(
     "AllegroFlare/GraphicsPipelines/DynamicEntityPipeline/Entities/Camera3D",
     AllegroFlare::GraphicsPipelines::DynamicEntityPipeline::Entities::Camera3D::TYPE
   );
}


TEST(AllegroFlare_GraphicsPipelines_DynamicEntityPipeline_Entities_Camera3DTest, type__has_the_expected_value_matching_TYPE)
{
   AllegroFlare::GraphicsPipelines::DynamicEntityPipeline::Entities::Camera3D camera3d;
   EXPECT_EQ(AllegroFlare::GraphicsPipelines::DynamicEntityPipeline::Entities::Camera3D::TYPE, camera3d.get_type());
}


