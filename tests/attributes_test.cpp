

#define BOOST_TEST_MODULE AttributesTestModule
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>


#include <allegro_flare/attributes.h>


BOOST_AUTO_TEST_CASE(UnknownAttributesDoNotExist)
{
   Attributes attributes;
   BOOST_CHECK(attributes.exists("hello") == false);
}

BOOST_AUTO_TEST_CASE(AttributesCanBeCreated)
{
   Attributes attributes;
   attributes.set("hello");
   BOOST_CHECK(attributes.exists("hello"));
}


