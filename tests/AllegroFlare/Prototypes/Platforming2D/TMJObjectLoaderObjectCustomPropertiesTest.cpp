
#include <gtest/gtest.h>

#include <AllegroFlare/Prototypes/Platforming2D/TMJObjectLoaderObjectCustomProperties.hpp>


TEST(AllegroFlare_Prototypes_Platforming2D_TMJObjectLoaderObjectCustomPropertiesTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Prototypes::Platforming2D::TMJObjectLoaderObjectCustomProperties custom_properties;
}


TEST(AllegroFlare_Prototypes_Platforming2D_TMJObjectLoaderObjectCustomPropertiesTest,
   will_store_objects_of_a_string_type)
{
   AllegroFlare::Prototypes::Platforming2D::TMJObjectLoaderObjectCustomProperties custom_properties;

   custom_properties.add("my_property", "foo");

   EXPECT_EQ(true, custom_properties.exists("my_property"));
   //EXPECT_EQ("string", custom_properties.get_type("my_property"));
   //EXPECT_EQ(true, custom_properties.is_string("my_property"));
   //EXPECT_EQ("foo", custom_properties.get_string("my_property"));
}


