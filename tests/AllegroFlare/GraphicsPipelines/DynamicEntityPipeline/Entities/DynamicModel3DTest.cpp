
#include <gtest/gtest.h>

#include <AllegroFlare/GraphicsPipelines/DynamicEntityPipeline/Entities/DynamicModel3D.hpp>


TEST(AllegroFlare_GraphicsPipelines_DynamicEntityPipeline_Entities_DynamicModel3DTest, can_be_created_without_blowing_up)
{
   AllegroFlare::GraphicsPipelines::DynamicEntityPipeline::Entities::DynamicModel3D dynamic_model3d;
}


TEST(AllegroFlare_GraphicsPipelines_DynamicEntityPipeline_Entities_DynamicModel3DTest, TYPE__has_the_expected_value)
{
   EXPECT_STREQ(
     "AllegroFlare/GraphicsPipelines/DynamicEntityPipeline/Entities/DynamicModel3D",
     AllegroFlare::GraphicsPipelines::DynamicEntityPipeline::Entities::DynamicModel3D::TYPE
   );
}


TEST(AllegroFlare_GraphicsPipelines_DynamicEntityPipeline_Entities_DynamicModel3DTest, type__has_the_expected_value_matching_TYPE)
{
   AllegroFlare::GraphicsPipelines::DynamicEntityPipeline::Entities::DynamicModel3D dynamic_model3d;
   EXPECT_EQ(AllegroFlare::GraphicsPipelines::DynamicEntityPipeline::Entities::DynamicModel3D::TYPE, dynamic_model3d.get_type());
}


