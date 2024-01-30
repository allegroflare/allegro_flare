
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

   custom_properties.add_string("my_property", "foo");
   EXPECT_EQ(true, custom_properties.exists("my_property"));
   EXPECT_EQ("string", custom_properties.get_type("my_property"));
   EXPECT_EQ(true, custom_properties.is_string("my_property"));
   EXPECT_EQ("foo", custom_properties.get_string("my_property"));
}


TEST(AllegroFlare_Prototypes_Platforming2D_TMJObjectLoaderObjectCustomPropertiesTest,
   will_store_objects_of_a_int_type)
{
   AllegroFlare::Prototypes::Platforming2D::TMJObjectLoaderObjectCustomProperties custom_properties;

   custom_properties.add_int("my_property", 42);
   EXPECT_EQ(true, custom_properties.exists("my_property"));
   EXPECT_EQ("int", custom_properties.get_type("my_property"));
   EXPECT_EQ(true, custom_properties.is_int("my_property"));
   EXPECT_EQ(42, custom_properties.get_int("my_property"));
}


TEST(AllegroFlare_Prototypes_Platforming2D_TMJObjectLoaderObjectCustomPropertiesTest,
   will_store_objects_of_a_float_type)
{
   AllegroFlare::Prototypes::Platforming2D::TMJObjectLoaderObjectCustomProperties custom_properties;

   custom_properties.add_float("my_property", 4.125f);
   EXPECT_EQ(true, custom_properties.exists("my_property"));
   EXPECT_EQ("float", custom_properties.get_type("my_property"));
   EXPECT_EQ(true, custom_properties.is_float("my_property"));
   EXPECT_EQ(4.125, custom_properties.get_float("my_property"));
}


TEST(AllegroFlare_Prototypes_Platforming2D_TMJObjectLoaderObjectCustomPropertiesTest,
   will_store_objects_of_a_bool_type)
{
   AllegroFlare::Prototypes::Platforming2D::TMJObjectLoaderObjectCustomProperties custom_properties;

   custom_properties.add_bool("my_property", true);
   EXPECT_EQ(true, custom_properties.exists("my_property"));
   EXPECT_EQ("bool", custom_properties.get_type("my_property"));
   EXPECT_EQ(true, custom_properties.is_bool("my_property"));
   EXPECT_EQ(true, custom_properties.get_bool("my_property"));
}


