

#include <gtest/gtest.h>

#include <AllegroFlare/ElementID.hpp>



#include <ctime>
#include <random> // for rng and shuffle



using namespace AllegroFlare;



class AllegroFlare_ElementIDTestWithFixture : public ::testing::Test
{
protected:
   ElementID root;
      ElementID *child_1;
         ElementID *child_1_A;
         ElementID *child_1_B;
      ElementID *child_2;
         ElementID *child_2_A;
            ElementID *child_2_A_1;
         ElementID *child_2_B;
      ElementID *child_3;

   AllegroFlare_ElementIDTestWithFixture()
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



TEST(AllegroFlare_ElementIDTest, get_next_unique_id__will_return_the_next_unique_id)
{
   // NOTE: This cannot be tested because the unique ids are static
}



TEST(AllegroFlare_ElementIDTest, get_id__will_return_unique_ids_for_each_element_that_is_created)
{
   int next_unique_id = ElementID::get_next_unique_id();
   int next_expected_id = next_unique_id;

   ElementID element1 = ElementID(NULL);
   ASSERT_EQ(element1.get_id(), next_expected_id);

   next_expected_id++;

   ElementID element2 = ElementID(NULL);
   ASSERT_EQ(element2.get_id(), next_expected_id);

   next_expected_id++;

   ElementID element3 = ElementID(NULL);
   ASSERT_EQ(element3.get_id(), next_expected_id);
}



TEST(AllegroFlare_ElementIDTest, reset_next_unique_id_counter__will_cause_element_ids_to_restart_at_1)
{
   ElementID::__reset_next_unique_id_counter(); // this is used because the next_unique_id counter is

   ElementID element1 = ElementID(NULL);
   ElementID element2 = ElementID(NULL);
   ASSERT_EQ(element1.get_id(), 1);
   ASSERT_EQ(element2.get_id(), 2);
}



TEST(AllegroFlare_ElementIDTest, returns_its_root)
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

   ASSERT_EQ(&root, child_1->get_root());
      ASSERT_EQ(&root, child_1_A->get_root());
      ASSERT_EQ(&root, child_1_B->get_root());
   ASSERT_EQ(&root, child_2->get_root());
      ASSERT_EQ(&root, child_2_A->get_root());
      ASSERT_EQ(&root, child_2_B->get_root());
         ASSERT_EQ(&root, child_2_B_1->get_root());
      ASSERT_EQ(&root, child_2_C->get_root());
}




TEST(AllegroFlare_ElementIDTest, returns_NULL_without_a_root)
{
   ElementID root = ElementID(NULL);
   ASSERT_EQ((void *)0, root.get_root());
}




TEST(AllegroFlare_ElementIDTest, returns_its_number_of_children)
{
   ElementID root = ElementID(NULL);
   ASSERT_EQ(0, root.num_children());
   new ElementID(&root);
   ASSERT_EQ(1, root.num_children());
   new ElementID(&root);
   ASSERT_EQ(2, root.num_children());
}




TEST(AllegroFlare_ElementIDTest, returns_true_if_it_has_children_otherwise_false)
{
   ElementID root = ElementID(NULL);

   ASSERT_EQ(false, root.has_children());

   new ElementID(&root);
   ASSERT_EQ(true, root.has_children());

   delete root.get_nth_child(0);
   ASSERT_EQ(false, root.has_children());
}




TEST(AllegroFlare_ElementIDTest, knows_if_it_has_a_parent)
{
   ElementID root = ElementID(nullptr);
   ElementID child = ElementID(&root);

   ASSERT_EQ(false, root.has_parent());
   ASSERT_EQ(true, child.has_parent());
}




TEST(AllegroFlare_ElementIDTest, returns_its_parent)
{
   ElementID root = ElementID(nullptr);
   ElementID child_1 = ElementID(&root);
   ElementID child_1A = ElementID(&child_1);

   ASSERT_EQ(&root, child_1.get_parent());
   ASSERT_EQ(&child_1, child_1A.get_parent());
}




TEST(AllegroFlare_ElementIDTest, returns_nullptr_if_it_does_not_have_a_parent)
{
   ElementID root = ElementID(nullptr);

   ASSERT_EQ((ElementID *)(nullptr), root.get_parent());
}




TEST(AllegroFlare_ElementIDTest, can_reassign_its_parent)
{
   ElementID *child = new ElementID(nullptr);
   ElementID new_parent = ElementID(nullptr);

   child->reassign_parent(&new_parent);

   ASSERT_EQ(&new_parent, child->get_parent());
}




TEST(DISABLED_AllegroFlare_ElementIDTest, can_not_reassign_itself_as_parent)
{
   // to be implemented
   ASSERT_EQ(false, true);
}




TEST(DISABLED_AllegroFlare_ElementIDTest, can_not_reassign_parentage_to_a_parent_that_a_descendant)
{
   // to be implemented
   ASSERT_EQ(false, true);
}




TEST(AllegroFlare_ElementIDTest, its_newly_assigned_parent_has_the_child)
{
   ElementID *child = new ElementID(nullptr);
   ElementID new_parent = ElementID(nullptr);

   child->reassign_parent(&new_parent);

   ASSERT_EQ(true, new_parent.is_child(child));
}




TEST(AllegroFlare_ElementIDTest, its_previously_assigned_parent_no_longer_has_the_child)
{
   ElementID original_parent = ElementID(nullptr);
   ElementID *child = new ElementID(&original_parent);
   ElementID new_parent = ElementID(nullptr);

   ASSERT_EQ(true, original_parent.is_child(child));

   child->reassign_parent(&new_parent);

   ASSERT_EQ(false, original_parent.is_child(child));
}




TEST(AllegroFlare_ElementIDTest, parent_removes_child_when_child_is_deleted__test_1)
{
   ElementID root = ElementID(NULL);
   ElementID *child_1 = new ElementID(&root);
   ElementID *child_2 = new ElementID(&root);

   ASSERT_EQ(2, root.num_children());

   delete child_1;
   ASSERT_EQ(1, root.num_children());

   delete child_2;
   ASSERT_EQ(0, root.num_children());
}




TEST(AllegroFlare_ElementIDTest, parent_removes_child_when_child_is_deleted__test_2)
{
   ElementID root = ElementID(NULL);
   std::vector<ElementID *> children(100, nullptr);
   for (auto &c : children) c = new ElementID(&root);

   //std::srand(unsigned(std::time(0)));

   std::random_device rng;
   std::mt19937 urng(rng());
   std::shuffle(children.begin(), children.end(), urng);

   for (unsigned i=0; i<children.size(); i++)
   {
      delete children[i];

      int expected_num_children = children.size() - i - 1;
      ASSERT_EQ(expected_num_children, root.num_children());
   }
}




TEST(AllegroFlare_ElementIDTest, returns_the_first_child_with_a_matching_attribute)
{
   ElementID root = ElementID(NULL);

   ElementID *child_1 = new ElementID(&root);
   child_1->set("name", "Samuel");
   ElementID *child_2 = new ElementID(&root);
   child_2->set("name", "Joey");

   ASSERT_EQ(child_1, root.find_first("name"));
}




TEST(AllegroFlare_ElementIDTest, finds_the_first_child_with_a_matching_attribute_and_value)
{
   ElementID root = ElementID(NULL);

   ElementID *child_1 = new ElementID(&root);
   child_1->set("name", "Samuel");
   ElementID *child_2 = new ElementID(&root);
   child_2->set("name", "Joey");

   ASSERT_EQ(child_2, root.find_first("name", "Joey"));
}




TEST(AllegroFlare_ElementIDTest, returns_NULL_when_a_child_with_matching_attributes_is_not_found)
{
   ElementID root = ElementID(NULL);

   ElementID *child = new ElementID(&root);
   child->set("name", "Joey");

   ASSERT_EQ((void*)(0), root.find_first("DNE"));
   ASSERT_EQ((void*)(0), root.find_first("DNE", "not found"));
}




TEST(AllegroFlare_ElementIDTest, finds_the_first_descendant_with_a_matching_attribute)
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

   ASSERT_EQ(child_1, root.find_first_descendant("color"));
   ASSERT_EQ(child_1_A_2, root.find_first_descendant("size"));
   ASSERT_EQ(child_1_B, root.find_first_descendant("name"));
   ASSERT_EQ(child_2_B, root.find_first_descendant("power"));
}




TEST(AllegroFlare_ElementIDTest, finds_the_first_descendant_with_a_matching_attribute_and_value)
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

   ASSERT_EQ(child_1, root.find_first_descendant("color", "green"));
   ASSERT_EQ(child_1_A, root.find_first_descendant("color", "orange"));
   ASSERT_EQ(child_1_A_2, root.find_first_descendant("size", "medium"));
   ASSERT_EQ(child_1_A_3, root.find_first_descendant("color", "pink"));
   ASSERT_EQ(child_1_B, root.find_first_descendant("name", "Samuel"));
   ASSERT_EQ(child_2, root.find_first_descendant("name", "Emmanuelle"));
   ASSERT_EQ(child_2_B, root.find_first_descendant("power", "42"));
}




TEST(AllegroFlare_ElementIDTest, returns_NULL_when_a_matching_descendant_does_not_exist)
{
   ElementID root = ElementID(NULL);

   ASSERT_EQ((void *)0, root.find_first_descendant("foo"));
   ASSERT_EQ((void *)0, root.find_first_descendant("foo", "bar"));
}




TEST(AllegroFlare_ElementIDTest, finds_children_with_a_matching_attribute)
{
   ElementID root = ElementID(NULL);

   ElementID *child_1 = new ElementID(&root);
   child_1->set("name", "Samuel");
   ElementID *child_2 = new ElementID(&root);
   child_2->set("value", "42");
   ElementID *child_3 = new ElementID(&root);
   child_3->set("name", "Joey");

   std::vector<ElementID *> results = root.find_all("name");

   ASSERT_EQ(2, results.size());
   ASSERT_EQ(child_1, results[0]);
   ASSERT_EQ(child_3, results[1]);
}





