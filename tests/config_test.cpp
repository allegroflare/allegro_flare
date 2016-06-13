

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE Config
#include <boost/test/unit_test.hpp>




#include <allegro_flare/config.h>

#include <fstream>




#define TEST_FILENAME "data/tests/config.cfg"




BOOST_AUTO_TEST_CASE(necessairy_test_file_exists)
{
   std::ifstream ifile(TEST_FILENAME);
   BOOST_CHECK_EQUAL(true, (bool)ifile);
}




BOOST_AUTO_TEST_CASE(retrieves_if_the_config_key_exists_in_the_global_space)
{
   Config config = Config(TEST_FILENAME);

   BOOST_CHECK_EQUAL(true, config.has_value("", "name"));
   BOOST_CHECK_EQUAL(true, config.has_value("", "width"));
   BOOST_CHECK_EQUAL(true, config.has_value("", "height"));
   BOOST_CHECK_EQUAL(true, config.has_value("", "pi"));
   BOOST_CHECK_EQUAL(false, config.has_value("", "foo"));
   BOOST_CHECK_EQUAL(false, config.has_value("", "bar"));
   BOOST_CHECK_EQUAL(false, config.has_value("", "baz"));
}




BOOST_AUTO_TEST_CASE(retrieves_a_string_value)
{
   Config config = Config(TEST_FILENAME);

   BOOST_CHECK_EQUAL("Jordan", config.get_value_str("", "name"));
}




BOOST_AUTO_TEST_CASE(retrieves_an_int_value)
{
   Config config = Config(TEST_FILENAME);

   BOOST_CHECK_EQUAL(1080, config.get_value_int("", "width"));
   BOOST_CHECK_EQUAL(320, config.get_value_int("", "height"));
}




BOOST_AUTO_TEST_CASE(retrieves_a_float_value_within_a_margin_of_error)
{
   Config config = Config(TEST_FILENAME);

   BOOST_CHECK_CLOSE(3.14, config.get_value_float("", "pi"), 0.00001);
}




BOOST_AUTO_TEST_CASE(returns_a_default_value_if_a_section_and_key_does_not_exist)
{
   Config config = Config(TEST_FILENAME);

   BOOST_CHECK_EQUAL("Beary", config.get_or_default_str("", "hero", "Beary"));
   BOOST_CHECK_EQUAL(42, config.get_or_default_int("", "speed", 42));
   BOOST_CHECK_CLOSE(6.28, config.get_or_default_float("", "tau", 6.28), 0.00001);
}




