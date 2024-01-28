
#include <gtest/gtest.h>

#include <AllegroFlare/Prototypes/Platforming2D/EntityControlConnectors/Base.hpp>


class EntityControlConnectorsBaseTestClass : public AllegroFlare::Prototypes::Platforming2D::EntityControlConnectors::Base
{
public:
   EntityControlConnectorsBaseTestClass()
      : AllegroFlare::Prototypes::Platforming2D::EntityControlConnectors::Base("EntityControlConnectorsBaseTestClass")
   {}
};


TEST(AllegroFlare_Prototypes_Platforming2D_EntityControlConnectors_BaseTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Prototypes::Platforming2D::EntityControlConnectors::Base base;
}


TEST(AllegroFlare_Prototypes_Platforming2D_EntityControlConnectors_BaseTest, TYPE__has_the_expected_value)
{
   EXPECT_STREQ(
     "AllegroFlare/Prototypes/Platforming2D/EntityControlConnectors/Base",
     AllegroFlare::Prototypes::Platforming2D::EntityControlConnectors::Base::TYPE
   );
}


TEST(AllegroFlare_Prototypes_Platforming2D_EntityControlConnectors_BaseTest, type__has_the_expected_value_matching_TYPE)
{
   AllegroFlare::Prototypes::Platforming2D::EntityControlConnectors::Base base;
   EXPECT_EQ(AllegroFlare::Prototypes::Platforming2D::EntityControlConnectors::Base::TYPE, base.get_type());
}


TEST(AllegroFlare_Prototypes_Platforming2D_EntityControlConnectors_BaseTest, derived_classes_will_have_the_expected_type)
{
   EntityControlConnectorsBaseTestClass test_class;
   EXPECT_EQ("EntityControlConnectorsBaseTestClass", test_class.get_type());
}


