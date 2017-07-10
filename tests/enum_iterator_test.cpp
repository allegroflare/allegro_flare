

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE EnumIteratorTest
#include <boost/test/unit_test.hpp>



#include <allegro_flare/enum_iterator.h>



BOOST_AUTO_TEST_CASE(iteratesOverEnumValues)
{
   enum foo
   {
      one = 2,
      two = 6,
      three = 8,
   };

   typedef EnumIterator<foo, foo::one, foo::three> fooIterator;

   std::stringstream ss;

   for (foo i : fooIterator())
   {
      ss << i;
   }

   std::string expected_output = "2345678";
   std::string returned_output = ss.str();

   BOOST_CHECK_EQUAL(expected_output, returned_output);
}



