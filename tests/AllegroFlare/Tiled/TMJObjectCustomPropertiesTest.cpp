
#include <gtest/gtest.h>

#include <AllegroFlare/Tiled/TMJObjectCustomProperties.hpp>
#include <AllegroFlare/Testing/ErrorAssertions.hpp>


TEST(AllegroFlare_Tiled_TMJObjectCustomPropertiesTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Tiled::TMJObjectCustomProperties custom_properties;
}


TEST(AllegroFlare_Tiled_TMJObjectCustomPropertiesTest,
   will_store_objects_of_a_string_type)
{
   AllegroFlare::Tiled::TMJObjectCustomProperties custom_properties;

   custom_properties.add_string("my_property", "foo");
   EXPECT_EQ(true, custom_properties.exists("my_property"));
   EXPECT_EQ("string", custom_properties.get_type("my_property"));
   EXPECT_EQ(true, custom_properties.is_string("my_property"));
   EXPECT_EQ("foo", custom_properties.get_string("my_property"));
}


TEST(AllegroFlare_Tiled_TMJObjectCustomPropertiesTest,
   will_store_objects_of_a_int_type)
{
   AllegroFlare::Tiled::TMJObjectCustomProperties custom_properties;

   custom_properties.add_int("my_property", 42);
   EXPECT_EQ(true, custom_properties.exists("my_property"));
   EXPECT_EQ("int", custom_properties.get_type("my_property"));
   EXPECT_EQ(true, custom_properties.is_int("my_property"));
   EXPECT_EQ(42, custom_properties.get_int("my_property"));
}


TEST(AllegroFlare_Tiled_TMJObjectCustomPropertiesTest,
   will_store_objects_of_a_float_type)
{
   AllegroFlare::Tiled::TMJObjectCustomProperties custom_properties;

   custom_properties.add_float("my_property", 4.125f);
   EXPECT_EQ(true, custom_properties.exists("my_property"));
   EXPECT_EQ("float", custom_properties.get_type("my_property"));
   EXPECT_EQ(true, custom_properties.is_float("my_property"));
   EXPECT_EQ(4.125, custom_properties.get_float("my_property"));
}


TEST(AllegroFlare_Tiled_TMJObjectCustomPropertiesTest,
   will_store_objects_of_a_bool_type)
{
   AllegroFlare::Tiled::TMJObjectCustomProperties custom_properties;

   custom_properties.add_bool("my_property", true);
   EXPECT_EQ(true, custom_properties.exists("my_property"));
   EXPECT_EQ("bool", custom_properties.get_type("my_property"));
   EXPECT_EQ(true, custom_properties.is_bool("my_property"));
   EXPECT_EQ(true, custom_properties.get_bool("my_property"));
}


TEST(AllegroFlare_Tiled_TMJObjectCustomPropertiesTest,
   empty__when_there_are_no_custom_properties__will_return_true)
{
   AllegroFlare::Tiled::TMJObjectCustomProperties custom_properties;
   EXPECT_EQ(true, custom_properties.empty());
}


TEST(AllegroFlare_Tiled_TMJObjectCustomPropertiesTest,
   empty__when_any_custom_properties_are_present__will_return_false)
{
   AllegroFlare::Tiled::TMJObjectCustomProperties custom_properties;

   custom_properties.add_bool("my_property", true);
   EXPECT_EQ(false, custom_properties.empty());
   custom_properties.clear();

   custom_properties.add_int("my_property", 123);
   EXPECT_EQ(false, custom_properties.empty());
   custom_properties.clear();

   custom_properties.add_float("my_property", 3.14f);
   EXPECT_EQ(false, custom_properties.empty());
   custom_properties.clear();

   custom_properties.add_string("my_property", "My custom string value");
   EXPECT_EQ(false, custom_properties.empty());
   custom_properties.clear();
}


TEST(AllegroFlare_Tiled_TMJObjectCustomPropertiesTest,
   get_functions__when_the_key_does_not_exist__throws_an_error)
{
   AllegroFlare::Tiled::TMJObjectCustomProperties custom_properties;

   EXPECT_THROW_WITH_MESSAGE(
      custom_properties.get_int("key-that-does-not-exist"),
      std::runtime_error,
      "[AllegroFlare::Tiled::TMJObjectCustomProperties::get_int]: error: The key \"key-that-does-not-exist\" does "
         "not exist."
   );
   EXPECT_THROW_WITH_MESSAGE(
      custom_properties.get_string("key-that-does-not-exist"),
      std::runtime_error,
      "[AllegroFlare::Tiled::TMJObjectCustomProperties::get_string]: error: The key \"key-that-does-not-exist\" does "
         "not exist."
   );
   EXPECT_THROW_WITH_MESSAGE(
      custom_properties.get_float("key-that-does-not-exist"),
      std::runtime_error,
      "[AllegroFlare::Tiled::TMJObjectCustomProperties::get_float]: error: The key \"key-that-does-not-exist\" does "
         "not exist."
   );
   EXPECT_THROW_WITH_MESSAGE(
      custom_properties.get_bool("key-that-does-not-exist"),
      std::runtime_error,
      "[AllegroFlare::Tiled::TMJObjectCustomProperties::get_bool]: error: The key \"key-that-does-not-exist\" does "
         "not exist."
   );
}

	
TEST(AllegroFlare_Tiled_TMJObjectCustomPropertiesTest,
   add_functions__when_the_key_already_exists__throws_an_error)
{
   AllegroFlare::Tiled::TMJObjectCustomProperties custom_properties;

   custom_properties.add_int("my_key");

   EXPECT_THROW_WITH_MESSAGE(
      custom_properties.add_int("my_key"),
      std::runtime_error,
      "[AllegroFlare::Tiled::TMJObjectCustomProperties::add_int]: error: The key \"my_key\" already exists."
   );
   EXPECT_THROW_WITH_MESSAGE(
      custom_properties.add_string("my_key"),
      std::runtime_error,
      "[AllegroFlare::Tiled::TMJObjectCustomProperties::add_string]: error: The key \"my_key\" already exists."
   );
   EXPECT_THROW_WITH_MESSAGE(
      custom_properties.add_bool("my_key"),
      std::runtime_error,
      "[AllegroFlare::Tiled::TMJObjectCustomProperties::add_bool]: error: The key \"my_key\" already exists."
   );
   EXPECT_THROW_WITH_MESSAGE(
      custom_properties.add_float("my_key"),
      std::runtime_error,
      "[AllegroFlare::Tiled::TMJObjectCustomProperties::add_float]: error: The key \"my_key\" already exists."
   );
}
	
	
