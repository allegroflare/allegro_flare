

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE BalsamiqLayoutLoader
#include <boost/test/unit_test.hpp>




#include <allegro_flare/gui/layout_loaders/balsamiq_layout_loader.h>




BOOST_AUTO_TEST_CASE(is_not_currently_implemented)
{
   BalsamiqLayoutLoader loader;
   BOOST_CHECK_EQUAL((void *)0, loader.load_file("DNE.json"));
}




