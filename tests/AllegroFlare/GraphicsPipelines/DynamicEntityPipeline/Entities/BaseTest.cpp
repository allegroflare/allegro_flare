
#include <gtest/gtest.h>

#include <AllegroFlare/GraphicsPipelines/DynamicEntityPipeline/Entities/Base.hpp>


class EntitiesBaseTestClass : public AllegroFlare::GraphicsPipelines::DynamicEntityPipeline::Entities::Base
{
public:
   EntitiesBaseTestClass()
      : AllegroFlare::GraphicsPipelines::DynamicEntityPipeline::Entities::Base("EntitiesBaseTestClass")
   {}
};


TEST(AllegroFlare_GraphicsPipelines_DynamicEntityPipeline_Entities_BaseTest, can_be_created_without_blowing_up)
{
   AllegroFlare::GraphicsPipelines::DynamicEntityPipeline::Entities::Base base;
}


TEST(AllegroFlare_GraphicsPipelines_DynamicEntityPipeline_Entities_BaseTest, TYPE__has_the_expected_value)
{
   EXPECT_STREQ(
     "AllegroFlare/GraphicsPipelines/DynamicEntityPipeline/Entities/Base",
     AllegroFlare::GraphicsPipelines::DynamicEntityPipeline::Entities::Base::TYPE
   );
}


TEST(AllegroFlare_GraphicsPipelines_DynamicEntityPipeline_Entities_BaseTest, type__has_the_expected_value_matching_TYPE)
{
   AllegroFlare::GraphicsPipelines::DynamicEntityPipeline::Entities::Base base;
   EXPECT_EQ(AllegroFlare::GraphicsPipelines::DynamicEntityPipeline::Entities::Base::TYPE, base.get_type());
}


TEST(AllegroFlare_GraphicsPipelines_DynamicEntityPipeline_Entities_BaseTest, derived_classes_will_have_the_expected_type)
{
   EntitiesBaseTestClass test_class;
   EXPECT_EQ("EntitiesBaseTestClass", test_class.get_type());
}


