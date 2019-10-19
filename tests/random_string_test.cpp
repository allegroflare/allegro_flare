

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE RANDOM_STRING
#include <boost/test/unit_test.hpp>




#include <AllegroFlare/Useful.hpp>




using namespace AllegroFlare;




BOOST_AUTO_TEST_CASE(only_returns_strings_with_the_expected_characters_and_length)
{
   std::string allowed_characters = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

   std::vector<std::string> errors;

   for (int i=0; i<30; i++)
   {
      int length = random_int(1, 100);
      std::string val = random_string(length);

      BOOST_CHECK_EQUAL(length, val.length());
      BOOST_CHECK_EQUAL(std::string::npos, val.find_first_not_of(allowed_characters));

   }
}




