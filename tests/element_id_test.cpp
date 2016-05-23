

#define BOOST_TEST_MODULE ElementID
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>


#include <allegro_flare/element_id.h>


BOOST_AUTO_TEST_CASE(first_element_created_had_id_1)
{
   ElementID element1 = ElementID(NULL);
   ElementID element2 = ElementID(NULL);
   BOOST_CHECK_EQUAL(element1.get_id(), 1);
   BOOST_CHECK_EQUAL(element2.get_id(), 2);
}


BOOST_AUTO_TEST_CASE(will_return_its_number_of_children)
{
   ElementID root = ElementID(NULL);
   BOOST_CHECK_EQUAL(root.num_children(), 0);

   ElementID *child_1 = new ElementID(&root);
   BOOST_CHECK_EQUAL(root.num_children(), 1);

   ElementID *child_2 = new ElementID(&root);
   BOOST_CHECK_EQUAL(root.num_children(), 2);

   ElementID *child_3 = new ElementID(&root);
   BOOST_CHECK_EQUAL(root.num_children(), 3);
}



