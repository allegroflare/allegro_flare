

#define BOOST_TEST_MODULE AttributesTestModule
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>


#include <allegro_flare/attributes.h>


BOOST_AUTO_TEST_CASE(unknown_attributes_do_not_exist)
{
   Attributes attributes;
   BOOST_CHECK(attributes.exists("hello") == false);
}

BOOST_AUTO_TEST_CASE(attributes_can_be_created)
{
   Attributes attributes;
   attributes.set("hello");
   BOOST_CHECK(attributes.exists("hello"));
}

BOOST_AUTO_TEST_CASE(created_key_value_pairs_exist)
{
   Attributes attributes;
   attributes.set("size", "large");
   BOOST_CHECK_EQUAL(attributes.exists("size", "large"), true);
}

BOOST_AUTO_TEST_CASE(unknown_key_value_pairs_do_not_exist)
{
   Attributes attributes;
   attributes.set("size", "large");
   BOOST_CHECK_EQUAL(attributes.exists("size", "small"), false);
}

BOOST_AUTO_TEST_CASE(attribute_values_can_be_retrieved)
{
   Attributes attributes;
   attributes.set("name", "Alex");
   BOOST_CHECK_EQUAL(attributes.get("name"), "Alex");
}

BOOST_AUTO_TEST_CASE(attributes_can_be_counted)
{
   Attributes attributes;
   attributes.set("name", "Alex");
   BOOST_CHECK_EQUAL(attributes.num_attributes(), 1);
   attributes.set("color", "green");
   BOOST_CHECK_EQUAL(attributes.num_attributes(), 2);
   attributes.set("animal", "alligator");
   BOOST_CHECK_EQUAL(attributes.num_attributes(), 3);
}

BOOST_AUTO_TEST_CASE(attribute_values_can_be_changed)
{
   Attributes attributes;
   attributes.set("name", "Alex");
   attributes.set("name", "Beary");
   BOOST_CHECK_EQUAL(attributes.get("name"), "Beary");
}

BOOST_AUTO_TEST_CASE(attributes_can_be_removed)
{
   Attributes attributes;
   attributes.set("os", "OSX");
   attributes.remove("os");
   BOOST_CHECK_EQUAL(attributes.num_attributes(), 0);
}

BOOST_AUTO_TEST_CASE(attributes_matching_key_value_can_be_removed)
{
   Attributes attributes;
   attributes.set("os", "Windows");
   attributes.remove("os", "Windows");
   BOOST_CHECK_EQUAL(attributes.num_attributes(), 0);
}

BOOST_AUTO_TEST_CASE(attributes_can_be_set_with_standard_datatypes)
{
   Attributes attributes;

   attributes.set("name", "Mark");
   BOOST_CHECK_EQUAL(attributes.get("name"), "Mark");

   attributes.set("father", std::string("Tony"));
   BOOST_CHECK_EQUAL(attributes.get("father"), "Tony");

   attributes.set("answer", 42);
   BOOST_CHECK_EQUAL(attributes.get("answer"), "42");

   attributes.set("pi", 3.14f);
   BOOST_CHECK_EQUAL(attributes.get("pi"), "3.14");

   attributes.set("tau", 6.28);
   BOOST_CHECK_EQUAL(attributes.get("tau"), "6.28");

   attributes.set("happy", true);
   BOOST_CHECK_EQUAL(attributes.get("happy"), "true");

   attributes.set("caffinated", false);
   BOOST_CHECK_EQUAL(attributes.get("caffinated"), "false");
}

BOOST_AUTO_TEST_CASE(attributes_can_be_retrieved_as_standard_datatypes)
{
   Attributes attributes;

   attributes.set("value", "128");
   BOOST_CHECK_EQUAL(attributes.get_as_int("value"), 128);

   attributes.set("phi", "1.618");
   BOOST_CHECK_CLOSE(attributes.get_as_float("phi"), 1.618, 0.00001);

   attributes.set("flavor", "sweet");
   BOOST_CHECK_EQUAL(attributes.get_as_string("flavor"), std::string("sweet"));

   attributes.set("should_do_laundry", "true");
   BOOST_CHECK_EQUAL(attributes.get_as_bool("should_do_laundry"), true);

   attributes.set("doing_laundry_now", "false");
   BOOST_CHECK_EQUAL(attributes.get_as_bool("doing_laundry_now"), false);
}

BOOST_AUTO_TEST_CASE(custom_datatypes_can_be_created)
{
   // TODO
   // test saving/loading of files
}

BOOST_AUTO_TEST_CASE(attributes_can_be_set_using_custom_datatypes)
{
   // TODO
   // test saving/loading of files
}

BOOST_AUTO_TEST_CASE(attributes_can_be_retrieved_as_a_custom_datatype)
{
   // TODO
   // test saving/loading of files
}

BOOST_AUTO_TEST_CASE(attributes_can_be_saved_and_loaded_from_files)
{
   // TODO
   // test saving/loading of files
}

BOOST_AUTO_TEST_CASE(a_copy_of_the_key_value_pairs_can_be_retrieved)
{
   Attributes attributes;

   attributes.set("name", "Alex");
   attributes.set("color", "green");
   attributes.set("height", 16);

   std::map<std::string, std::string> values = attributes.get_copy();

   std::map<std::string, std::string> expected;
   expected["name"] = "Alex";
   expected["color"] = "green";
   expected["height"] = "16";

   BOOST_REQUIRE_EQUAL(values.size(), expected.size());

   // p.s. I'm not a fan of this technique
   auto itv=values.begin();
   auto ite=expected.begin();
   while (itv != values.end())
   {
      BOOST_CHECK_EQUAL(itv->first, ite->first);
      BOOST_CHECK_EQUAL(itv->second, ite->second);
      itv++;
      ite++;
   }
}

BOOST_AUTO_TEST_CASE(binding_will_create_an_attribute_if_it_did_not_exist_previously)
{
   int temperature = -40;
   Attributes attributes;
   attributes.bind("temperature", &temperature);
   BOOST_CHECK_EQUAL(attributes.exists("temperature"), true);
}

BOOST_AUTO_TEST_CASE(an_attribute_identifies_as_unbound_when_not_bounded)
{
   Attributes attributes;
   attributes.set("size", "32");
   BOOST_CHECK_EQUAL(attributes.is_bound("size"), false);
}

BOOST_AUTO_TEST_CASE(an_attribute_identifies_as_bounded_when_bouneded)
{
   int size = 256;
   Attributes attributes;
   attributes.bind("size", &size);
   BOOST_CHECK_EQUAL(attributes.is_bound("size"), true);
}

BOOST_AUTO_TEST_CASE(an_attribute_is_set_to_the_value_of_the_variable_when_bound)
{
   Attributes attributes;
   attributes.set("temperature", 72);
   int temperature = -40;
   attributes.bind("temperature", &temperature);
   BOOST_CHECK_EQUAL(attributes.is_synced("temperature"), true);
}

BOOST_AUTO_TEST_CASE(an_attribute_is_not_synced_if_the_variable_is_modified)
{
   Attributes attributes;
   int temperature = -40;
   attributes.bind("temperature", &temperature);
   temperature = 72;
   BOOST_CHECK_EQUAL(attributes.is_unsynced("temperature"), true);
}

BOOST_AUTO_TEST_CASE(a_bound_attribute_will_pull_when_retrieved)
{
   Attributes attributes;
   int kilometers = 1000;
   attributes.bind("kilometers", &kilometers);
   kilometers = 42;
   BOOST_CHECK_EQUAL(attributes.get("kilometers"), "42");
}

BOOST_AUTO_TEST_CASE(a_bound_attribute_will_push_to_the_bound_variable_when_set)
{
   Attributes attributes;
   int kilometers = 1000;
   attributes.bind("kilometers", &kilometers);
   attributes.set("kilometers", "120");
   BOOST_CHECK_EQUAL(kilometers, 120);
}

BOOST_AUTO_TEST_CASE(a_bound_attribute_will_push_when_set_to_all_datatypes)
{
   // TODO
}






