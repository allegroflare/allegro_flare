

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Clipboard
#include <boost/test/unit_test.hpp>




#include <allegro_flare/clipboard.h>




using namespace allegro_flare;




BOOST_AUTO_TEST_CASE(can_get_and_set_a_string)
{
   std::string testing_text_A = "This is some content for the clipboard";
   Clipboard::set(testing_text_A);
   BOOST_CHECK_EQUAL(testing_text_A, Clipboard::get());

   std::string testing_text_B = "Contents of the clipboard can be changed";
   Clipboard::set(testing_text_B);
   BOOST_CHECK_EQUAL(testing_text_B, Clipboard::get());
}




