

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE ElementID
#include <boost/test/unit_test.hpp>


#include <allegro_flare/element_id.h>
#include <ctime>



struct Fixture
{
   ElementID root;
      ElementID *child_1;
         ElementID *child_1_A;
         ElementID *child_1_B;
      ElementID *child_2;
         ElementID *child_2_A;
            ElementID *child_2_A_1;
         ElementID *child_2_B;
      ElementID *child_3;

   Fixture()
      : root(NULL)
      , child_1(new ElementID(&root))
      , child_1_A(new ElementID(child_1))
      , child_1_B(new ElementID(child_1))
      , child_2(new ElementID(&root))
      , child_2_A(new ElementID(child_2))
      , child_2_A_1(new ElementID(child_2_A))
      , child_2_B(new ElementID(child_2))
      , child_3(new ElementID(&root))
   {}
};




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




BOOST_AUTO_TEST_CASE(returns_its_number_of_children)
{
   ElementID root = ElementID(NULL);
   BOOST_CHECK_EQUAL(0, root.num_children());
   new ElementID(&root);
   BOOST_CHECK_EQUAL(1, root.num_children());
   new ElementID(&root);
   BOOST_CHECK_EQUAL(2, root.num_children());
}




BOOST_AUTO_TEST_CASE(returns_true_if_it_has_children_otherwise_false)
{
   ElementID root = ElementID(NULL);

   BOOST_CHECK_EQUAL(false, root.has_children());

   new ElementID(&root);
   BOOST_CHECK_EQUAL(true, root.has_children());

   delete root.get_nth_child(0);
   BOOST_CHECK_EQUAL(false, root.has_children());
}




BOOST_AUTO_TEST_CASE(knows_if_it_has_a_parent)
{
   ElementID root = ElementID(nullptr);
   ElementID child = ElementID(&root);

   BOOST_CHECK_EQUAL(false, root.has_parent());
   BOOST_CHECK_EQUAL(true, child.has_parent());
}




BOOST_AUTO_TEST_CASE(returns_its_parent)
{
   ElementID root = ElementID(nullptr);
   ElementID child_1 = ElementID(&root);
   ElementID child_1A = ElementID(&child_1);

   BOOST_CHECK_EQUAL(&root, child_1.get_parent());
   BOOST_CHECK_EQUAL(&child_1, child_1A.get_parent());
}




BOOST_AUTO_TEST_CASE(returns_nullptr_if_it_does_not_have_a_parent)
{
   ElementID root = ElementID(nullptr);

   BOOST_CHECK_EQUAL((ElementID *)(nullptr), root.get_parent());
}




BOOST_AUTO_TEST_CASE(can_reassign_its_parent)
{
   ElementID *child = new ElementID(nullptr);
   ElementID new_parent = ElementID(nullptr);

   child->reassign_parent(&new_parent);

   BOOST_CHECK_EQUAL(&new_parent, child->get_parent());
}




BOOST_AUTO_TEST_CASE(can_not_reassign_itself_as_parent)
{
   // to be implemented
   BOOST_CHECK_EQUAL(false, true);
}




BOOST_AUTO_TEST_CASE(can_not_reassign_parentage_to_a_parent_that_a_descendant)
{
   // to be implemented
   BOOST_CHECK_EQUAL(false, true);
}




BOOST_AUTO_TEST_CASE(its_newly_assigned_parent_has_the_child)
{
   ElementID *child = new ElementID(nullptr);
   ElementID new_parent = ElementID(nullptr);

   child->reassign_parent(&new_parent);

   BOOST_CHECK_EQUAL(true, new_parent.is_child(child));
}




BOOST_AUTO_TEST_CASE(its_previously_assigned_parent_no_longer_has_the_child)
{
   ElementID original_parent = ElementID(nullptr);
   ElementID *child = new ElementID(&original_parent);
   ElementID new_parent = ElementID(nullptr);

   BOOST_CHECK_EQUAL(true, original_parent.is_child(child));

   child->reassign_parent(&new_parent);

   BOOST_CHECK_EQUAL(false, original_parent.is_child(child));
}




BOOST_AUTO_TEST_CASE(parent_removes_child_when_child_is_deleted__test_1)
{
   ElementID root = ElementID(NULL);
   ElementID *child_1 = new ElementID(&root);
   ElementID *child_2 = new ElementID(&root);

   BOOST_CHECK_EQUAL(2, root.num_children());

   delete child_1;
   BOOST_CHECK_EQUAL(1, root.num_children());

   delete child_2;
   BOOST_CHECK_EQUAL(0, root.num_children());
}




BOOST_AUTO_TEST_CASE(parent_removes_child_when_child_is_deleted__test_2)
{
   ElementID root = ElementID(NULL);
   std::vector<ElementID *> children(100, nullptr);
   for (auto &c : children) c = new ElementID(&root);

   std::srand(unsigned(std::time(0)));
   std::random_shuffle(children.begin(), children.end());

   for (unsigned i=0; i<children.size(); i++)
   {
      delete children[i];

      int expected_num_children = children.size() - i - 1;
      BOOST_CHECK_EQUAL(expected_num_children, root.num_children());
   }
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




BOOST_FIXTURE_TEST_CASE(returns_an_nth_descendant, Fixture)
{
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




BOOST_FIXTURE_TEST_CASE(returns_NULL_when_an_nth_descendant_does_not_exist, Fixture)
{
   BOOST_CHECK_EQUAL((void *)0, root.get_nth_descendant(-1));
   BOOST_CHECK_EQUAL((void *)0, root.get_nth_descendant(root.num_descendants()));

   BOOST_CHECK_EQUAL((void *)0, child_1->get_nth_descendant(2));

   BOOST_CHECK_EQUAL((void *)0, child_1_A->get_nth_descendant(0));

   BOOST_CHECK_EQUAL((void *)0, child_2->get_nth_descendant(3));
   BOOST_CHECK_EQUAL((void *)0, child_2_A->get_nth_descendant(1));
}




BOOST_FIXTURE_TEST_CASE(returns_a_flat_list_of_descendants, Fixture)
{
   std::vector<ElementID *> expected = {
      child_1, child_1_A, child_1_B, child_2, child_2_A, child_2_A_1, child_2_B, child_3
   };

   std::vector<ElementID *> list_of_descendants = root.get_flat_list_of_descendants();

   BOOST_CHECK_EQUAL_COLLECTIONS(expected.begin(), expected.end(),
      list_of_descendants.begin(), list_of_descendants.end());
}




BOOST_FIXTURE_TEST_CASE(returns_an_index_of_a_child_element, Fixture)
{
   BOOST_CHECK_EQUAL(0, root.get_index_of_child(child_1));
   BOOST_CHECK_EQUAL(1, root.get_index_of_child(child_2));

   BOOST_CHECK_EQUAL(0, child_1->get_index_of_child(child_1_A));
   BOOST_CHECK_EQUAL(1, child_1->get_index_of_child(child_1_B));

   BOOST_CHECK_EQUAL(0, child_2->get_index_of_child(child_2_A));
   BOOST_CHECK_EQUAL(1, child_2->get_index_of_child(child_2_B));

   BOOST_CHECK_EQUAL(0, child_2_A->get_index_of_child(child_2_A_1));
}


BOOST_FIXTURE_TEST_CASE(returns_negative_1_if_an_index_is_not_present_for_an_element, Fixture)
{
   BOOST_CHECK_EQUAL(-1, root.get_index_of_child(child_1_A));
   BOOST_CHECK_EQUAL(-1, root.get_index_of_child(child_2_A));
   BOOST_CHECK_EQUAL(-1, root.get_index_of_child(child_2_A_1));

   BOOST_CHECK_EQUAL(-1, child_1->get_index_of_child(child_2));
   BOOST_CHECK_EQUAL(-1, child_1->get_index_of_child(child_2_A_1));
   BOOST_CHECK_EQUAL(-1, child_1->get_index_of_child(&root));

   BOOST_CHECK_EQUAL(-1, child_2->get_index_of_child(child_1));
   BOOST_CHECK_EQUAL(-1, child_2->get_index_of_child(child_1_A));
   BOOST_CHECK_EQUAL(-1, child_2->get_index_of_child(child_1_B));
}




BOOST_FIXTURE_TEST_CASE(returns_an_nth_child, Fixture)
{
   BOOST_CHECK_EQUAL(child_1, root.get_nth_child(0));
   BOOST_CHECK_EQUAL(child_2, root.get_nth_child(1));

   BOOST_CHECK_EQUAL(child_1_A, child_1->get_nth_child(0));
   BOOST_CHECK_EQUAL(child_1_B, child_1->get_nth_child(1));

   BOOST_CHECK_EQUAL(child_2_A, child_2->get_nth_child(0));
   BOOST_CHECK_EQUAL(child_2_B, child_2->get_nth_child(1));

   BOOST_CHECK_EQUAL(child_2_A_1, child_2_A->get_nth_child(0));
}




BOOST_AUTO_TEST_CASE(returns_a_random_child)
{
   ElementID root(NULL);
   ElementID *child_1 = new ElementID(&root);
   ElementID *child_2 = new ElementID(&root);
   ElementID *child_3 = new ElementID(&root);

   int child_1_picks = 0;
   int child_2_picks = 0;
   int child_3_picks = 0;

   const int TOTAL_TRIES = 200;
   int min_expected_picks = TOTAL_TRIES/6;

   for (unsigned i=0; i<TOTAL_TRIES; i++)
   {
      ElementID *picked_element = root.get_random_child();
      if (picked_element == child_1) child_1_picks++;
      else if (picked_element == child_2) child_2_picks++;
      else if (picked_element == child_3) child_3_picks++;
   }

   int total_picks = child_1_picks + child_2_picks + child_3_picks;

   BOOST_CHECK_EQUAL(TOTAL_TRIES, total_picks);

   BOOST_CHECK(child_1_picks > min_expected_picks);
   BOOST_CHECK(child_2_picks > min_expected_picks);
   BOOST_CHECK(child_3_picks > min_expected_picks);
}




BOOST_FIXTURE_TEST_CASE(returns_its_next_sibling, Fixture)
{
   BOOST_CHECK_EQUAL(child_2, child_1->get_next_sibling());
   BOOST_CHECK_EQUAL(child_1_B, child_1_A->get_next_sibling());
   BOOST_CHECK_EQUAL(child_2_B, child_2_A->get_next_sibling());
}




BOOST_FIXTURE_TEST_CASE(can_bring_its_child_to_the_front, Fixture)
{
   root.bring_child_to_front(child_2);

   BOOST_CHECK_EQUAL(child_2, root.get_children().front());

   root.bring_child_to_front(child_3);

   BOOST_CHECK_EQUAL(child_3, root.get_children().front());
}




BOOST_FIXTURE_TEST_CASE(can_send_its_child_to_the_back, Fixture)
{
   root.send_child_to_back(child_1);

   BOOST_CHECK_EQUAL(child_1, root.get_children().back());

   root.send_child_to_back(child_2);

   BOOST_CHECK_EQUAL(child_2, root.get_children().back());
}




BOOST_FIXTURE_TEST_CASE(does_not_bring_child_to_front_if_the_element_is_not_a_child, Fixture)
{
   std::vector<ElementID *> expected_root_children = {child_1, child_2, child_3};
   ElementID *not_a_child_of_root = child_1_A;

   root.bring_child_to_front(not_a_child_of_root);

   std::vector<ElementID *> returned_root_children = root.get_children();

   BOOST_CHECK_EQUAL_COLLECTIONS(expected_root_children.begin(), expected_root_children.end(),
         returned_root_children.begin(), returned_root_children.end());
}




BOOST_FIXTURE_TEST_CASE(does_not_send_child_to_back_if_the_element_is_not_a_child, Fixture)
{
   std::vector<ElementID *> expected_root_children = {child_1, child_2, child_3};
   ElementID *not_a_child_of_root = child_1_A;

   root.send_child_to_back(not_a_child_of_root);

   std::vector<ElementID *> returned_root_children = root.get_children();

   BOOST_CHECK_EQUAL_COLLECTIONS(expected_root_children.begin(), expected_root_children.end(),
         returned_root_children.begin(), returned_root_children.end());
}




BOOST_FIXTURE_TEST_CASE(returns_its_previous_sibling, Fixture)
{
   BOOST_CHECK_EQUAL(child_1, child_2->get_previous_sibling());
   BOOST_CHECK_EQUAL(child_1_A, child_1_B->get_previous_sibling());
   BOOST_CHECK_EQUAL(child_2_A, child_2_B->get_previous_sibling());
}




BOOST_FIXTURE_TEST_CASE(returns_NULL_when_a_next_or_previous_sibling_does_not_exist, Fixture)
{
   BOOST_CHECK_EQUAL((void *)0, root.get_next_sibling());
   BOOST_CHECK_EQUAL((void *)0, root.get_previous_sibling());
}




BOOST_FIXTURE_TEST_CASE(can_identify_if_an_element_is_a_child, Fixture)
{
   BOOST_CHECK_EQUAL(true, root.is_child(child_1));
   BOOST_CHECK_EQUAL(true, root.is_child(child_2));
   BOOST_CHECK_EQUAL(false, root.is_child(child_1_A));
   BOOST_CHECK_EQUAL(true, child_1->is_child(child_1_B));
   BOOST_CHECK_EQUAL(false, child_1->is_child(child_2_B));
}




BOOST_FIXTURE_TEST_CASE(can_identify_if_an_element_is_a_descendant, Fixture)
{
   BOOST_CHECK_EQUAL(true, root.is_descendant(child_1));
   BOOST_CHECK_EQUAL(true, root.is_descendant(child_1_B));
   BOOST_CHECK_EQUAL(true, root.is_descendant(child_2));
   BOOST_CHECK_EQUAL(true, root.is_descendant(child_2_A_1));
   BOOST_CHECK_EQUAL(true, root.is_descendant(child_2_B));

   BOOST_CHECK_EQUAL(true, child_2->is_descendant(child_2_A));
   BOOST_CHECK_EQUAL(true, child_2->is_descendant(child_2_A_1));

   BOOST_CHECK_EQUAL(true, child_2_A->is_descendant(child_2_A_1));
}




BOOST_FIXTURE_TEST_CASE(can_identify_if_an_element_is_not_a_descendant, Fixture)
{
   BOOST_CHECK_EQUAL(false, root.is_descendant(&root));
   BOOST_CHECK_EQUAL(false, root.is_descendant(nullptr));

   BOOST_CHECK_EQUAL(false, child_1->is_descendant(&root));
   BOOST_CHECK_EQUAL(false, child_1->is_descendant(nullptr));
   BOOST_CHECK_EQUAL(false, child_1->is_descendant(child_1));
   BOOST_CHECK_EQUAL(false, child_1->is_descendant(child_2));
   BOOST_CHECK_EQUAL(false, child_1->is_descendant(child_2_A));
   BOOST_CHECK_EQUAL(false, child_1->is_descendant(child_2_A_1));
   BOOST_CHECK_EQUAL(false, child_1->is_descendant(child_2_B));

   BOOST_CHECK_EQUAL(false, child_2->is_descendant(&root));
   BOOST_CHECK_EQUAL(false, child_2->is_descendant(nullptr));
   BOOST_CHECK_EQUAL(false, child_2->is_descendant(child_2));
   BOOST_CHECK_EQUAL(false, child_2->is_descendant(child_1));
   BOOST_CHECK_EQUAL(false, child_2->is_descendant(child_1_A));
   BOOST_CHECK_EQUAL(false, child_2->is_descendant(child_1_B));
}




BOOST_FIXTURE_TEST_CASE(returns_a_list_of_children, Fixture)
{
   std::vector<ElementID *> expected_root_children = {child_1, child_2, child_3};
   std::vector<ElementID *> expected_child_1_children = {child_1_A, child_1_B};
   std::vector<ElementID *> expected_child_2_children = {child_2_A, child_2_B};
   std::vector<ElementID *> expected_child_2_A_children = {child_2_A_1};

   std::vector<ElementID *> returned_root_children = root.get_children();
   std::vector<ElementID *> returned_child_1_children = child_1->get_children();
   std::vector<ElementID *> returned_child_2_children = child_2->get_children();
   std::vector<ElementID *> returned_child_2_A_children = child_2_A->get_children();

   BOOST_CHECK_EQUAL_COLLECTIONS(expected_root_children.begin(), expected_root_children.end(),
         returned_root_children.begin(), returned_root_children.end());
   BOOST_CHECK_EQUAL_COLLECTIONS(expected_child_1_children.begin(), expected_child_1_children.end(),
         returned_child_1_children.begin(), returned_child_1_children.end());
   BOOST_CHECK_EQUAL_COLLECTIONS(expected_child_2_children.begin(), expected_child_2_children.end(),
         returned_child_2_children.begin(), returned_child_2_children.end());
   BOOST_CHECK_EQUAL_COLLECTIONS(expected_child_2_A_children.begin(), expected_child_2_A_children.end(),
         returned_child_2_A_children.begin(), returned_child_2_A_children.end());
}




