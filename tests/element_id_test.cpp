

#define BOOST_TEST_MODULE ElementID
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>


#include <allegro_flare/element_id.h>


BOOST_AUTO_TEST_CASE(has_a_first_element_with_id_1)
{
   ElementID element1 = ElementID(NULL);
   ElementID element2 = ElementID(NULL);
   BOOST_CHECK_EQUAL(element1.get_id(), 1);
   BOOST_CHECK_EQUAL(element2.get_id(), 2);
}


BOOST_AUTO_TEST_CASE(returns_its_root)
{
   ElementID root = ElementID(NULL);
      ElementID *child_1 = new ElementID(&root);
         ElementID *child_1_A = new ElementID(child_1);
         ElementID *child_1_B = new ElementID(child_1);
      ElementID *child_2 = new ElementID(&root);
         ElementID *child_2_A = new ElementID(child_2);
         ElementID *child_2_B = new ElementID(child_2);
            ElementID *child_2_B_1 = new ElementID(child_2_B);
         ElementID *child_2_C = new ElementID(child_2);

   BOOST_CHECK_EQUAL(&root, child_1->get_root());
      BOOST_CHECK_EQUAL(&root, child_1_A->get_root());
      BOOST_CHECK_EQUAL(&root, child_1_B->get_root());
   BOOST_CHECK_EQUAL(&root, child_2->get_root());
      BOOST_CHECK_EQUAL(&root, child_2_A->get_root());
      BOOST_CHECK_EQUAL(&root, child_2_B->get_root());
         BOOST_CHECK_EQUAL(&root, child_2_B_1->get_root());
      BOOST_CHECK_EQUAL(&root, child_2_C->get_root());
}


BOOST_AUTO_TEST_CASE(returns_NULL_without_a_root)
{
   ElementID root = ElementID(NULL);
   BOOST_CHECK_EQUAL((void *)0, root.get_root());
}


BOOST_AUTO_TEST_CASE(returns_the_first_child_with_a_matching_attribute)
{
   ElementID root = ElementID(NULL);

   ElementID *child_1 = new ElementID(&root);
   child_1->set("name", "Samuel");
   ElementID *child_2 = new ElementID(&root);
   child_2->set("name", "Joey");

   BOOST_CHECK_EQUAL(child_1, root.find_first("name"));
}


BOOST_AUTO_TEST_CASE(finds_the_first_child_with_a_matching_attribute_and_value)
{
   ElementID root = ElementID(NULL);

   ElementID *child_1 = new ElementID(&root);
   child_1->set("name", "Samuel");
   ElementID *child_2 = new ElementID(&root);
   child_2->set("name", "Joey");

   BOOST_CHECK_EQUAL(child_2, root.find_first("name", "Joey"));
}


BOOST_AUTO_TEST_CASE(returns_NULL_when_a_child_with_matching_attributes_is_not_found)
{
   ElementID root = ElementID(NULL);

   ElementID *child = new ElementID(&root);
   child->set("name", "Joey");

   BOOST_CHECK_EQUAL((void*)(0), root.find_first("DNE"));
   BOOST_CHECK_EQUAL((void*)(0), root.find_first("DNE", "not found"));
}


BOOST_AUTO_TEST_CASE(finds_the_first_descendant_with_a_matching_attribute)
{
   ElementID root = ElementID(NULL);

   ElementID *child_1 = new ElementID(&root);
   child_1->set("color", "green");
      ElementID *child_1_A = new ElementID(child_1);
      child_1_A->set("color", "orange");
         ElementID *child_1_A_1 = new ElementID(child_1_A);
         child_1_A_1->set("color", "green");
         ElementID *child_1_A_2 = new ElementID(child_1_A);
         child_1_A_2->set("size", "medium");
         ElementID *child_1_A_3 = new ElementID(child_1_A);
         child_1_A_3->set("color", "pink");
      ElementID *child_1_B = new ElementID(child_1);
      child_1_B->set("name", "Samuel");
         ElementID *child_1_B_1 = new ElementID(child_1_B);
         child_1_B_1->set("size", "large");

   ElementID *child_2 = new ElementID(&root);
   child_2->set("name", "Emmanuelle");
      ElementID *child_2_A = new ElementID(child_2);
      child_2_A->set("color", "green");
      ElementID *child_2_B = new ElementID(child_2);
      child_2_B->set("power", "42");

   BOOST_CHECK_EQUAL(child_1, root.find_first_descendant("color"));
   BOOST_CHECK_EQUAL(child_1_A_2, root.find_first_descendant("size"));
   BOOST_CHECK_EQUAL(child_1_B, root.find_first_descendant("name"));
   BOOST_CHECK_EQUAL(child_2_B, root.find_first_descendant("power"));
}


BOOST_AUTO_TEST_CASE(finds_the_first_descendant_with_a_matching_attribute_and_value)
{
   ElementID root = ElementID(NULL);

   ElementID *child_1 = new ElementID(&root);
   child_1->set("color", "green");
      ElementID *child_1_A = new ElementID(child_1);
      child_1_A->set("color", "orange");
         ElementID *child_1_A_1 = new ElementID(child_1_A);
         child_1_A_1->set("color", "green");
         ElementID *child_1_A_2 = new ElementID(child_1_A);
         child_1_A_2->set("size", "medium");
         ElementID *child_1_A_3 = new ElementID(child_1_A);
         child_1_A_3->set("color", "pink");
      ElementID *child_1_B = new ElementID(child_1);
      child_1_B->set("name", "Samuel");
         ElementID *child_1_B_1 = new ElementID(child_1_B);
         child_1_B_1->set("size", "large");

   ElementID *child_2 = new ElementID(&root);
   child_2->set("name", "Emmanuelle");
      ElementID *child_2_A = new ElementID(child_2);
      child_2_A->set("color", "green");
      ElementID *child_2_B = new ElementID(child_2);
      child_2_B->set("power", "42");

   BOOST_CHECK_EQUAL(child_1, root.find_first_descendant("color", "green"));
   BOOST_CHECK_EQUAL(child_1_A, root.find_first_descendant("color", "orange"));
   BOOST_CHECK_EQUAL(child_1_A_2, root.find_first_descendant("size", "medium"));
   BOOST_CHECK_EQUAL(child_1_A_3, root.find_first_descendant("color", "pink"));
   BOOST_CHECK_EQUAL(child_1_B, root.find_first_descendant("name", "Samuel"));
   BOOST_CHECK_EQUAL(child_2, root.find_first_descendant("name", "Emmanuelle"));
   BOOST_CHECK_EQUAL(child_2_B, root.find_first_descendant("power", "42"));
}


BOOST_AUTO_TEST_CASE(returns_NULL_when_a_matching_descendant_does_not_exist)
{
   ElementID root = ElementID(NULL);

   BOOST_CHECK_EQUAL((void *)0, root.find_first_descendant("foo"));
   BOOST_CHECK_EQUAL((void *)0, root.find_first_descendant("foo", "bar"));
}


BOOST_AUTO_TEST_CASE(finds_children_with_a_matching_attribute)
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


BOOST_AUTO_TEST_CASE(finds_children_with_a_matching_attribute_and_value)
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


BOOST_AUTO_TEST_CASE(finds_all_descendants_matching_an_attribute)
{
   ElementID root = ElementID(NULL);

   ElementID *child_1 = new ElementID(&root);
   child_1->set("color", "green");
      ElementID *child_1_A = new ElementID(child_1);
      child_1_A->set("color", "orange");
         ElementID *child_1_A_1 = new ElementID(child_1_A);
         child_1_A_1->set("size", "large");
         child_1_A_1->set("color", "green");
         ElementID *child_1_A_2 = new ElementID(child_1_A);
         child_1_A_2->set("size", "medium");
         ElementID *child_1_A_3 = new ElementID(child_1_A);
         child_1_A_3->set("color", "green");
      ElementID *child_1_B = new ElementID(child_1);
      child_1_B->set("name", "Samuel");

   ElementID *child_2 = new ElementID(&root);
   child_2->set("name", "Emmanuelle");
      ElementID *child_2_A = new ElementID(child_2);
      child_2_A->set("color", "green");

   std::vector<ElementID *> results = root.find_all_descendants("color");

   BOOST_REQUIRE_EQUAL(5, results.size());

   BOOST_CHECK_EQUAL(child_1, results[0]);
   BOOST_CHECK_EQUAL(child_1_A, results[1]);
   BOOST_CHECK_EQUAL(child_1_A_1, results[2]);
   BOOST_CHECK_EQUAL(child_1_A_3, results[3]);
   BOOST_CHECK_EQUAL(child_2_A, results[4]);
}


BOOST_AUTO_TEST_CASE(finds_all_descendants_matching_an_attribute_and_value)
{
   ElementID root = ElementID(NULL);

   ElementID *child_1 = new ElementID(&root);
   child_1->set("color", "green");
      ElementID *child_1_A = new ElementID(child_1);
      child_1_A->set("color", "orange");
         ElementID *child_1_A_1 = new ElementID(child_1_A);
         child_1_A_1->set("size", "large");
         child_1_A_1->set("color", "green");
         ElementID *child_1_A_2 = new ElementID(child_1_A);
         child_1_A_2->set("size", "medium");
         ElementID *child_1_A_3 = new ElementID(child_1_A);
         child_1_A_3->set("color", "green");
      ElementID *child_1_B = new ElementID(child_1);
      child_1_B->set("name", "Samuel");

   ElementID *child_2 = new ElementID(&root);
   child_2->set("name", "Emmanuelle");
      ElementID *child_2_A = new ElementID(child_2);
      child_2_A->set("color", "green");

   std::vector<ElementID *> expected = {child_1, child_1_A_1, child_1_A_3, child_2_A};

   std::vector<ElementID *> results = root.find_all_descendants("color", "green");

   BOOST_CHECK_EQUAL_COLLECTIONS(expected.begin(), expected.end(), results.begin(), results.end());
}


BOOST_AUTO_TEST_CASE(gets_a_descendant_by_id)
{
   ElementID root = ElementID(NULL);
   ElementID *child_1 = new ElementID(&root);
      ElementID *child_1_A = new ElementID(child_1);
   ElementID *child_2 = new ElementID(&root);
      ElementID *child_2_A = new ElementID(child_2);
         ElementID *child_2_A_1 = new ElementID(child_2_A);
         ElementID *child_2_A_2 = new ElementID(child_2_A);
         ElementID *child_2_A_3 = new ElementID(child_2_A);
      ElementID *child_2_B = new ElementID(child_2);
         ElementID *child_2_B_1 = new ElementID(child_2_B);
   ElementID *child_3 = new ElementID(&root);
      ElementID *child_3_A = new ElementID(child_3);
      ElementID *child_3_B = new ElementID(child_3);


   BOOST_CHECK_EQUAL(child_1, root.find_descendant_by_id(child_1->get_id()));
   BOOST_CHECK_EQUAL(child_2, root.find_descendant_by_id(child_2->get_id()));
   BOOST_CHECK_EQUAL(child_2_A_2, root.find_descendant_by_id(child_2_A_2->get_id()));
   BOOST_CHECK_EQUAL(child_3_A, root.find_descendant_by_id(child_3_A->get_id()));
}


BOOST_AUTO_TEST_CASE(returns_an_nth_descendant)
{
   ElementID root = ElementID(NULL);

   ElementID *child_1 = new ElementID(&root);
      ElementID *child_1_A = new ElementID(child_1);
      ElementID *child_1_B = new ElementID(child_1);
   ElementID *child_2 = new ElementID(&root);
      ElementID *child_2_A = new ElementID(child_2);
         ElementID *child_2_A_1 = new ElementID(child_2_A);
      ElementID *child_2_B = new ElementID(child_2);

   BOOST_CHECK_EQUAL(child_1, root.get_nth_descendant(0));
   BOOST_CHECK_EQUAL(child_1_A, root.get_nth_descendant(1));
   BOOST_CHECK_EQUAL(child_1_B, root.get_nth_descendant(2));
   BOOST_CHECK_EQUAL(child_2, root.get_nth_descendant(3));
   BOOST_CHECK_EQUAL(child_2_A, root.get_nth_descendant(4));
   BOOST_CHECK_EQUAL(child_2_A_1, root.get_nth_descendant(5));
   BOOST_CHECK_EQUAL(child_2_B, root.get_nth_descendant(6));

   BOOST_CHECK_EQUAL(child_2_A, child_2->get_nth_descendant(0));
   BOOST_CHECK_EQUAL(child_2_A_1, child_2->get_nth_descendant(1));
   BOOST_CHECK_EQUAL(child_2_B, child_2->get_nth_descendant(2));
}


BOOST_AUTO_TEST_CASE(returns_NULL_when_an_nth_descendant_does_not_exist)
{
   ElementID root = ElementID(NULL);

   ElementID *child_1 = new ElementID(&root);
      ElementID *child_1_A = new ElementID(child_1);
      ElementID *child_1_B = new ElementID(child_1);
   ElementID *child_2 = new ElementID(&root);
      ElementID *child_2_A = new ElementID(child_2);
         ElementID *child_2_A_1 = new ElementID(child_2_A);
      ElementID *child_2_B = new ElementID(child_2);

   BOOST_CHECK_EQUAL((void *)0, root.get_nth_descendant(-1));
   BOOST_CHECK_EQUAL((void *)0, root.get_nth_descendant(7));

   BOOST_CHECK_EQUAL((void *)0, child_1->get_nth_descendant(2));

   BOOST_CHECK_EQUAL((void *)0, child_1_A->get_nth_descendant(0));

   BOOST_CHECK_EQUAL((void *)0, child_2->get_nth_descendant(3));
   BOOST_CHECK_EQUAL((void *)0, child_2_A->get_nth_descendant(1));
}


BOOST_AUTO_TEST_CASE(returns_a_flat_list_of_descendants)
{
   ElementID root = ElementID(NULL);

   ElementID *child_1 = new ElementID(&root);
      ElementID *child_1_A = new ElementID(child_1);
      ElementID *child_1_B = new ElementID(child_1);
   ElementID *child_2 = new ElementID(&root);
      ElementID *child_2_A = new ElementID(child_2);
         ElementID *child_2_A_1 = new ElementID(child_2_A);
      ElementID *child_2_B = new ElementID(child_2);

   std::vector<ElementID *> expected = {
      child_1, child_1_A, child_1_B, child_2, child_2_A, child_2_A_1, child_2_B
   };

   std::vector<ElementID *> list_of_descendants = root.get_flat_list_of_descendants();

   BOOST_CHECK_EQUAL_COLLECTIONS(expected.begin(), expected.end(),
      list_of_descendants.begin(), list_of_descendants.end());
}


