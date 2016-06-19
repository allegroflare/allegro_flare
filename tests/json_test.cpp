

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE JSON
#include <boost/test/unit_test.hpp>




#include <allegro_flare/json.h>

#include <fstream>




BOOST_AUTO_TEST_CASE(decodes_a_string_value)
{
   BOOST_CHECK_EQUAL("Alex", json_string("\"Alex\"").stringValue());
   BOOST_CHECK_EQUAL("Toby", json_string("\"Toby\"").stringValue());
   BOOST_CHECK_EQUAL("Matthew", json_string("\"Matthew\"").stringValue());
   BOOST_CHECK_EQUAL("Mark", json_string("\"Mark\"").stringValue());
}




BOOST_AUTO_TEST_CASE(decodes_an_integer_value)
{
   BOOST_CHECK_EQUAL(1293, json_int("1293").intValue());
   BOOST_CHECK_EQUAL(42, json_int("42").intValue());
   BOOST_CHECK_EQUAL(1024768, json_int("1024768").intValue());
}




BOOST_AUTO_TEST_CASE(decodes_a_float_value)
{
   BOOST_CHECK_CLOSE(3.14, json_float("3.14").floatValue(), 0.00001);
   BOOST_CHECK_CLOSE(13E-13, json_float("13E-13").floatValue(), 0.00001);
   BOOST_CHECK_CLOSE(123456.789, json_float("123456.789").floatValue(), 0.00001);
}




BOOST_AUTO_TEST_CASE(decodes_a_boolean_value)
{
   BOOST_CHECK_EQUAL(false, json_bool("false").boolValue());
   BOOST_CHECK_EQUAL(true, json_bool("true").boolValue());
}




BOOST_AUTO_TEST_CASE(decodes_an_array_value)
{
   JSON::Array a = json_array("[8, 16, 42, 98]");
   BOOST_CHECK_EQUAL(4, a.values.size());

   int decoded_value = 0;
   decoded_value = json_int(a.values[0]->toString()).intValue();
   BOOST_CHECK_EQUAL(8, decoded_value);

   decoded_value = json_int(a.values[1]->toString()).intValue();
   BOOST_CHECK_EQUAL(16, decoded_value);

   decoded_value = json_int(a.values[2]->toString()).intValue();
   BOOST_CHECK_EQUAL(42, decoded_value);

   decoded_value = json_int(a.values[3]->toString()).intValue();
   BOOST_CHECK_EQUAL(98, decoded_value);
}




BOOST_AUTO_TEST_CASE(decodes_a_JSON_object)
{
   JSON::Object o = json_object("{\"width\": 900, \"height\": 600, \"name\": \"George\"}");

   BOOST_CHECK_EQUAL(3, o.values.size());

   int decoded_int = json_int(o.values["width"]->toString()).intValue();
   BOOST_CHECK_EQUAL(900, decoded_int);

   decoded_int = json_int(o.values["height"]->toString()).intValue();
   BOOST_CHECK_EQUAL(600, decoded_int);

   std::string decoded_string = json_string(o.values["name"]->toString()).stringValue();
   BOOST_CHECK_EQUAL("George", decoded_string);
}




BOOST_AUTO_TEST_CASE(knows_if_a_key_exists_in_a_JSON_object)
{
   JSON::Object o = json_object("{\"width\": 900, \"height\": 600, \"name\": \"George\"}");

   BOOST_CHECK_EQUAL(true, o.exists("width"));
   BOOST_CHECK_EQUAL(true, o.exists("height"));
   BOOST_CHECK_EQUAL(true, o.exists("name"));
   BOOST_CHECK_EQUAL(false, o.exists("foo"));
   BOOST_CHECK_EQUAL(false, o.exists("bar"));
}




BOOST_AUTO_TEST_CASE(decodes_a_complex_JSON_object)
{
}




BOOST_AUTO_TEST_CASE(decodes_a_null_value)
{
}




BOOST_AUTO_TEST_CASE(will_throw_an_error_when_JSON_does_not_parse)
{
}




