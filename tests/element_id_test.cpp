

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


BOOST_AUTO_TEST_CASE(will_find_first_child_element_matching_attributes)
{
   ElementID root = ElementID(NULL);

   ElementID *child_1 = new ElementID(&root);
   child_1->set("name", "Samuel");
   ElementID *child_2 = new ElementID(&root);
   child_2->set("name", "Joey");

   BOOST_CHECK_EQUAL(child_1, root.find_first("name"));
}


BOOST_AUTO_TEST_CASE(will_find_first_child_element_matching_attribute_with_value)
{
   ElementID root = ElementID(NULL);

   ElementID *child_1 = new ElementID(&root);
   child_1->set("name", "Samuel");
   ElementID *child_2 = new ElementID(&root);
   child_2->set("name", "Joey");

   BOOST_CHECK_EQUAL(child_2, root.find_first("name", "Joey"));
}


BOOST_AUTO_TEST_CASE(will_return_NULL_when_the_requested_child_is_not_found)
{
   ElementID root = ElementID(NULL);

   ElementID *child = new ElementID(&root);
   child->set("name", "Joey");

   BOOST_CHECK_EQUAL((void*)(0), root.find_first("DNE"));
   BOOST_CHECK_EQUAL((void*)(0), root.find_first("DNE", "not found"));
}



BOOST_AUTO_TEST_CASE(will_find_children_with_a_matching_attribute)
{
   ElementID root = ElementID(NULL);

   ElementID *child_1 = new ElementID(&root);
   child_1->set("name", "Samuel");
   ElementID *child_2 = new ElementID(&root);
   child_2->set("value", "42");
   ElementID *child_3 = new ElementID(&root);
   child_3->set("name", "Joey");

   std::vector<ElementID *> results = root.find_all("name");

   BOOST_REQUIRE_EQUAL(2, results.size());
   BOOST_CHECK_EQUAL(child_1, results[0]);
   BOOST_CHECK_EQUAL(child_3, results[1]);
}


BOOST_AUTO_TEST_CASE(will_find_children_with_a_matching_attribute_and_value)
{
   ElementID root = ElementID(NULL);

   ElementID *child_1 = new ElementID(&root);
   child_1->set("name", "Samuel");
   ElementID *child_2 = new ElementID(&root);
   child_2->set("value", "42");
   ElementID *child_3 = new ElementID(&root);
   child_3->set("value", "128");
   ElementID *child_4 = new ElementID(&root);
   child_4->set("value", "42");

   std::vector<ElementID *> results = root.find_all("value", "42");

   BOOST_REQUIRE_EQUAL(2, results.size());
   BOOST_CHECK_EQUAL(child_2, results[0]);
   BOOST_CHECK_EQUAL(child_4, results[1]);
}

