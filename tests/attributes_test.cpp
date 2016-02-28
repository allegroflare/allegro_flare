

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

