

#define BOOST_TEST_MODULE AttributesTestModule
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>


#include <allegro_flare/element_id.h>


BOOST_AUTO_TEST_CASE(id_can_be_set_and_retrieved)
{
   ElementIDManager manager;
   ElementID element(&manager);

   element.set_id("foo");
   BOOST_CHECK(element.get_id() == "foo");

   element.set_id("bar");
   BOOST_CHECK(element.get_id() == "bar");
}



