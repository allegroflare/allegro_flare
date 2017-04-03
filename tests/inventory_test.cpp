

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Inventory
#include <boost/test/unit_test.hpp>




#include <allegro_flare/inventory.h>




enum item_enums
{
   ITEM_1,
   ITEM_2,
   ITEM_3,
};




BOOST_AUTO_TEST_CASE(adds_and_counts_items_in_inventory)
{
   Inventory inventory = Inventory();
   BOOST_CHECK_EQUAL(0, inventory.get_item_count(ITEM_1));
   inventory.add_item(ITEM_1);
   BOOST_CHECK_EQUAL(1, inventory.get_item_count(ITEM_1));
   inventory.add_item(ITEM_1);
   BOOST_CHECK_EQUAL(2, inventory.get_item_count(ITEM_1));
}




BOOST_AUTO_TEST_CASE(removes_items_from_inventory)
{
   Inventory inventory = Inventory();
   inventory.add_item(ITEM_2);
   inventory.add_item(ITEM_2);
   BOOST_CHECK_EQUAL(2, inventory.get_item_count(ITEM_2));
   inventory.remove_item(ITEM_2);
   BOOST_CHECK_EQUAL(1, inventory.get_item_count(ITEM_2));
}




BOOST_AUTO_TEST_CASE(itentifies_if_an_item_exists_in_inventory)
{
   Inventory inventory = Inventory();
   inventory.add_item(ITEM_1);
   inventory.add_item(ITEM_2);

   BOOST_CHECK_EQUAL(true, inventory.get_item_count(ITEM_1));
   BOOST_CHECK_EQUAL(true, inventory.get_item_count(ITEM_2));
   BOOST_CHECK_EQUAL(false, inventory.get_item_count(ITEM_3));
}




