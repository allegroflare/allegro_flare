

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE BalsamiqLayoutLoader
#include <boost/test/unit_test.hpp>




#include <allegro_flare/framework.h>

#include <fstream>
#include <allegro_flare/gui/layout_loaders/balsamiq_layout_loader.h>




#define TEST_FILENAME "data/tests/layouts/balsamiq_layout.json"




struct Fixture
{
   Fixture()
   {
      // Some Widgets require features in the Framework
      // such as images, fonts, etc.
      Framework::initialize();
   }
   ~Fixture()
   {
      Framework::destruct();
   }
};




BOOST_AUTO_TEST_CASE(necessairy_test_file_exists)
{
   std::ifstream ifile(TEST_FILENAME);
   BOOST_CHECK_EQUAL(true, (bool)ifile);
}




BOOST_AUTO_TEST_CASE(returns_false_when_loading_a_file_that_does_not_exist)
{
   BalsamiqLayoutLoader loader;
   BOOST_CHECK_EQUAL(false, loader.load_file(nullptr, "DNE.json"));
}




BOOST_FIXTURE_TEST_CASE(loads_a_json_file_to_a_UIWidget, Fixture)
{
   BalsamiqLayoutLoader loader;
   UIWidget *root = new UIWidget(nullptr, "Root", nullptr);
   loader.load_file(root, TEST_FILENAME);

   BOOST_CHECK_EQUAL(4, root->get_family().get_num_descendants());
}




