

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




BOOST_AUTO_TEST_CASE(parses_an_empty_object_as_valid)
{
   JSON::Object o = json_object("{}");

   BOOST_CHECK_EQUAL(false, o.exists("foo"));
   BOOST_CHECK_EQUAL(false, o.exists("bar"));
   BOOST_CHECK_EQUAL(true, o.values.empty());
}




BOOST_AUTO_TEST_CASE(returns_its_value_as_a_string_representation)
{
   JSON::Value v = JSON::decode("\"This is my string\"");
   BOOST_CHECK_EQUAL("This is my string", v.as_string());
}




BOOST_AUTO_TEST_CASE(returns_its_value_as_a_JSON_object_representation)
{
   std::string obj_str = "{\"width\": 900, \"height\": 600, \"name\": \"George\"}";
   JSON::Object expected = json_object(obj_str);
   JSON::Value v = JSON::decode(obj_str);
   JSON::Object returned = v.as_object();

   //BOOST_CHECK_EQUAL(expected.value, returned.value);
   //BOOST_REQUIRE_EQUAL(expected.values.size(), returned.values.size());
   //for (unsigned i=0; i<expected.values.size(); i++)
      //BOOST_CHECK_EQUAL(expected.values[i].value, returned.values[i].value);
   //BOOST_CHECK_EQUAL(expected.toString(), returned.toString()); 
   //BOOST_CHECK_EQUAL(expected.(), returned.toString()); 
}




BOOST_AUTO_TEST_CASE(returns_its_value_as_an_array_representation)
{
}




BOOST_AUTO_TEST_CASE(returns_its_value_as_an_integer_representation)
{
   JSON::Value v = JSON::decode("\"1234567\"");
   BOOST_CHECK_EQUAL(1234567, v.as_integer());
}




BOOST_AUTO_TEST_CASE(returns_its_value_as_an_float_representation)
{
   JSON::Value v = JSON::decode("\"3.14\"");
   BOOST_CHECK_CLOSE(3.14f, v.as_float(), 0.0001);
}




BOOST_AUTO_TEST_CASE(returns_its_value_as_an_boolean_representation)
{
   JSON::Value v1 = JSON::decode("\"true\"");
   BOOST_CHECK_EQUAL(true, v1.as_bool());

   JSON::Value v2 = JSON::decode("\"false\"");
   BOOST_CHECK_EQUAL(false, v2.as_bool());
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




