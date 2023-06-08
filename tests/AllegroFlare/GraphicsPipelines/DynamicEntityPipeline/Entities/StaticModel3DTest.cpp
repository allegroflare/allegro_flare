
#include <gtest/gtest.h>

#include <AllegroFlare/GraphicsPipelines/DynamicEntityPipeline/Entities/StaticModel3D.hpp>


TEST(AllegroFlare_GraphicsPipelines_DynamicEntityPipeline_Entities_StaticModel3DTest, can_be_created_without_blowing_up)
{
   AllegroFlare::GraphicsPipelines::DynamicEntityPipeline::Entities::StaticModel3D static_model3d;
}


TEST(AllegroFlare_GraphicsPipelines_DynamicEntityPipeline_Entities_StaticModel3DTest, TYPE__has_the_expected_value)
{
   EXPECT_STREQ(
     "AllegroFlare/GraphicsPipelines/DynamicEntityPipeline/Entities/StaticModel3D",
     AllegroFlare::GraphicsPipelines::DynamicEntityPipeline::Entities::StaticModel3D::TYPE
   );
}


TEST(AllegroFlare_GraphicsPipelines_DynamicEntityPipeline_Entities_StaticModel3DTest, type__has_the_expected_value_matching_TYPE)
{
   AllegroFlare::GraphicsPipelines::DynamicEntityPipeline::Entities::StaticModel3D static_model3d;
   EXPECT_EQ(AllegroFlare::GraphicsPipelines::DynamicEntityPipeline::Entities::StaticModel3D::TYPE, static_model3d.get_type());
}


