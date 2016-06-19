

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE BalsamiqLayoutLoader
#include <boost/test/unit_test.hpp>




#include <allegro_flare/framework.h>

#include <fstream>
#include <allegro_flare/gui/layout_loaders/balsamiq_layout_loader.h>








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




