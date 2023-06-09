
#include <gtest/gtest.h>

#include <AllegroFlare/GraphicsPipelines/DynamicEntityPipeline/Entities/StaticMultitextureModel3D.hpp>



TEST(AllegroFlare_GraphicsPipelines_DynamicEntityPipeline_Entities_StaticMultitextureModel3DTest,
   can_be_created_without_blowing_up)
{
   AllegroFlare::GraphicsPipelines::DynamicEntityPipeline::Entities::StaticMultitextureModel3D
      static_multitexture_model3d;
}


TEST(AllegroFlare_GraphicsPipelines_DynamicEntityPipeline_Entities_StaticMultitextureModel3DTest,
   TYPE__has_the_expected_value)
{
   EXPECT_STREQ(
     "AllegroFlare/GraphicsPipelines/DynamicEntityPipeline/Entities/StaticMultitextureModel3D",
     AllegroFlare::GraphicsPipelines::DynamicEntityPipeline::Entities::StaticMultitextureModel3D::TYPE
   );
}


TEST(AllegroFlare_GraphicsPipelines_DynamicEntityPipeline_Entities_StaticMultitextureModel3DTest,
   type__has_the_expected_value_matching_TYPE)
{
   AllegroFlare::GraphicsPipelines::DynamicEntityPipeline::Entities::StaticMultitextureModel3D
      static_multitexture_model3d;
   EXPECT_EQ(
      AllegroFlare::GraphicsPipelines::DynamicEntityPipeline::Entities::StaticMultitextureModel3D::TYPE,
      static_multitexture_model3d.get_type()
   );
}


