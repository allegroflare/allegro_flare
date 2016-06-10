

#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE AttributesTestModule
#include <boost/test/unit_test.hpp>




#include <allegro_flare/attributes.h>

#include <fstream>
#include <sstream>
#include <unistd.h>




struct my_custom_datatype
{
public:
   float x;
   float y;

   static bool to_val_func(void *val, std::string str)
   {
      my_custom_datatype &f = *static_cast<my_custom_datatype *>(val);
      std::stringstream ss(str);
      ss >> f.x;
      ss >> f.y;
      return true;
   }

   static std::string to_str_func(void *val)
   {
      my_custom_datatype &f = *static_cast<my_custom_datatype *>(val);
      std::stringstream ss;
      ss << f.x << " " << f.y;
      return ss.str();
   }
};




BOOST_AUTO_TEST_CASE(unknown_attributes_do_not_exist)
{
   Attributes attributes;
   BOOST_CHECK(attributes.exists("hello") == false);
}




BOOST_AUTO_TEST_CASE(attributes_can_be_created)
{
   Attributes attributes;
   attributes.set("hello");
   BOOST_CHECK(attributes.exists("hello"));
}




BOOST_AUTO_TEST_CASE(created_key_value_pairs_exist)
{
   Attributes attributes;
   attributes.set("size", "large");
   BOOST_CHECK_EQUAL(attributes.exists("size", "large"), true);
}




BOOST_AUTO_TEST_CASE(unknown_key_value_pairs_do_not_exist)
{
   Attributes attributes;
   attributes.set("size", "large");
   BOOST_CHECK_EQUAL(attributes.exists("size", "small"), false);
}




BOOST_AUTO_TEST_CASE(attribute_values_can_be_retrieved)
{
   Attributes attributes;
   attributes.set("name", "Alex");
   BOOST_CHECK_EQUAL(attributes.get("name"), "Alex");
}




BOOST_AUTO_TEST_CASE(attributes_can_be_counted)
{
   Attributes attributes;
   attributes.set("name", "Alex");
   BOOST_CHECK_EQUAL(attributes.num_attributes(), 1);
   attributes.set("color", "green");
   BOOST_CHECK_EQUAL(attributes.num_attributes(), 2);
   attributes.set("animal", "alligator");
   BOOST_CHECK_EQUAL(attributes.num_attributes(), 3);
}




BOOST_AUTO_TEST_CASE(attribute_values_can_be_changed)
{
   Attributes attributes;
   attributes.set("name", "Alex");
   attributes.set("name", "Beary");
   BOOST_CHECK_EQUAL(attributes.get("name"), "Beary");
}




BOOST_AUTO_TEST_CASE(attributes_can_be_removed)
{
   Attributes attributes;
   attributes.set("os", "OSX");
   attributes.remove("os");
   BOOST_CHECK_EQUAL(attributes.num_attributes(), 0);
}




BOOST_AUTO_TEST_CASE(attributes_matching_key_value_can_be_removed)
{
   Attributes attributes;
   attributes.set("os", "Windows");
   attributes.remove("os", "Windows");
   BOOST_CHECK_EQUAL(attributes.num_attributes(), 0);
}




BOOST_AUTO_TEST_CASE(attributes_can_be_set_with_standard_datatypes)
{
   Attributes attributes;

   attributes.set("name", "Mark");
   BOOST_CHECK_EQUAL(attributes.get("name"), "Mark");

   attributes.set("father", std::string("Tony"));
   BOOST_CHECK_EQUAL(attributes.get("father"), "Tony");

   attributes.set("answer", 42);
   BOOST_CHECK_EQUAL(attributes.get("answer"), "42");

   attributes.set("pi", 3.14f);
   BOOST_CHECK_EQUAL(attributes.get("pi"), "3.14");

   attributes.set("tau", 6.28);
   BOOST_CHECK_EQUAL(attributes.get("tau"), "6.28");

   attributes.set("happy", true);
   BOOST_CHECK_EQUAL(attributes.get("happy"), "true");

   attributes.set("caffinated", false);
   BOOST_CHECK_EQUAL(attributes.get("caffinated"), "false");
}




BOOST_AUTO_TEST_CASE(attributes_can_be_retrieved_as_standard_datatypes)
{
   Attributes attributes;

   attributes.set("value", "128");
   BOOST_CHECK_EQUAL(attributes.get_as_int("value"), 128);

   attributes.set("phi", "1.618");
   BOOST_CHECK_CLOSE(attributes.get_as_float("phi"), 1.618, 0.00001);

   attributes.set("flavor", "sweet");
   BOOST_CHECK_EQUAL(attributes.get_as_string("flavor"), std::string("sweet"));

   attributes.set("should_do_laundry", "true");
   BOOST_CHECK_EQUAL(attributes.get_as_bool("should_do_laundry"), true);

   attributes.set("doing_laundry_now", "false");
   BOOST_CHECK_EQUAL(attributes.get_as_bool("doing_laundry_now"), false);
}




BOOST_AUTO_TEST_CASE(a_datatype_that_has_not_been_created_is_inknown)
{
   Attributes attributes;
   BOOST_CHECK_EQUAL(Attributes::datatype_is_known("my_custom_datatype"), false);
}




BOOST_AUTO_TEST_CASE(custom_datatypes_that_have_been_created_are_known)
{
   Attributes attributes;

   attributes.create_datatype_definition("my_custom_datatype",
         my_custom_datatype::to_val_func, my_custom_datatype::to_str_func);

   BOOST_CHECK_EQUAL(Attributes::datatype_is_known("my_custom_datatype"), true);
}




BOOST_AUTO_TEST_CASE(an_attribute_can_not_be_set_as_an_unknown_datatype)
{
   Attributes attributes;
   my_custom_datatype custom;
   BOOST_CHECK_EQUAL(attributes.set("key", "an_unknown_datatype", (void *)&custom), false);
}




BOOST_AUTO_TEST_CASE(a_variable_cannot_be_bound_to_a_datatype_that_does_not_exist)
{
   Attributes attributes;
   my_custom_datatype custom;
   BOOST_CHECK_EQUAL(attributes.bind("key", "an_unknown_datatype", &custom), false);
}




BOOST_AUTO_TEST_CASE(custom_datatypes_can_be_bound)
{
   Attributes attributes;
   my_custom_datatype custom;

   attributes.create_datatype_definition("my_custom_datatype",
         my_custom_datatype::to_val_func, my_custom_datatype::to_str_func);

   BOOST_CHECK_EQUAL(attributes.bind("foo", "my_custom_datatype", &custom), true);
}




BOOST_AUTO_TEST_CASE(attributes_can_be_set_using_custom_datatypes)
{
   Attributes attributes;
   my_custom_datatype my_2d_vector;
   my_2d_vector.x = 0.35;
   my_2d_vector.y = 0.01;

   attributes.create_datatype_definition("my_custom_datatype",
         my_custom_datatype::to_val_func, my_custom_datatype::to_str_func);

   attributes.set("position", "my_custom_datatype", (void *)&my_2d_vector);

   BOOST_CHECK_EQUAL(attributes.get("position"), "0.35 0.01");
}




BOOST_AUTO_TEST_CASE(a_custom_attribute_is_set_to_the_value_of_the_variable_when_bound)
{
   Attributes attributes;
   my_custom_datatype custom_var;

   custom_var.x = 0.876f;
   custom_var.y = 6.543f;

   // create custom datatype
   attributes.create_datatype_definition("my_custom_datatype",
         my_custom_datatype::to_val_func, my_custom_datatype::to_str_func);

   // bind it to an existing datatype with values
   attributes.bind("custom", "my_custom_datatype", &custom_var);

   BOOST_CHECK_EQUAL(attributes.is_synced("custom"), true);
}




BOOST_AUTO_TEST_CASE(attributes_can_be_retrieved_as_a_custom_datatype)
{
   Attributes attributes;
   my_custom_datatype my_2d_vector;

   attributes.create_datatype_definition("my_custom_datatype",
         my_custom_datatype::to_val_func, my_custom_datatype::to_str_func);

   attributes.set("position", "123.4 567.8");
   attributes.get_as_custom(&my_2d_vector, "my_custom_datatype", "position");

   BOOST_CHECK_CLOSE(my_2d_vector.x, 123.4f, 0.00001);
   BOOST_CHECK_CLOSE(my_2d_vector.y, 567.8f, 0.00001);
}




BOOST_AUTO_TEST_CASE(attributes_can_be_saved_to_a_file)
{
   std::string test_filename = "TEST_alex_attributes_1.txt";

   // remove the test file if it already exists

   if (access(test_filename.c_str(), F_OK) != -1)
      BOOST_REQUIRE_EQUAL(0, remove(test_filename.c_str()));

   // create and save our attributes

   Attributes attributes;

   attributes.set("name", "Alex");
   attributes.set("color", "green");
   attributes.set("height", "16");

   attributes.save(test_filename);

   // validate the file was created

   std::ifstream file(test_filename);
   BOOST_REQUIRE_EQUAL(file.fail(), false);

   // validate the contents of the file

   std::string expected_file_contents = "";
   expected_file_contents += "name: Alex\n";
   expected_file_contents += "color: green\n";
   expected_file_contents += "height: 16\n";

   file.open(test_filename);
   std::stringstream contents;
   contents << file.rdbuf();

   BOOST_CHECK_EQUAL(expected_file_contents, contents.str());

   file.close();

   // remove the test file if it already exists

   BOOST_REQUIRE_EQUAL(0, remove(test_filename.c_str()));
}




BOOST_AUTO_TEST_CASE(attributes_can_be_loaded_from_a_file)
{
   std::string test_filename = "TEST_alex_attributes_2.txt";

   // remove the test file if it already exists

   if (access(test_filename.c_str(), F_OK) != -1)
      BOOST_REQUIRE_EQUAL(0, remove(test_filename.c_str()));

   // create a faux file

   std::ofstream outfile(test_filename);
   outfile << "name: Alex\n";
   outfile << "color: green\n";
   outfile << "height: 16\n";
   outfile.close();

   BOOST_REQUIRE(-1 != access(test_filename.c_str(), F_OK));

   // load the file

   Attributes attributes;
   attributes.load(test_filename);

   BOOST_CHECK_EQUAL("Alex", attributes.get("name"));
   BOOST_CHECK_EQUAL("green", attributes.get("color"));
   BOOST_CHECK_EQUAL("16", attributes.get("height"));

   // cleanup our file

   BOOST_REQUIRE_EQUAL(0, remove(test_filename.c_str()));
}




BOOST_AUTO_TEST_CASE(a_copy_of_the_key_value_pairs_can_be_retrieved)
{
   Attributes attributes;

   attributes.set("name", "Alex");
   attributes.set("color", "green");
   attributes.set("height", 16);

   std::map<std::string, std::string> values = attributes.get_copy();

   std::map<std::string, std::string> expected;
   expected["name"] = "Alex";
   expected["color"] = "green";
   expected["height"] = "16";

   BOOST_REQUIRE_EQUAL(values.size(), expected.size());

   // p.s. I'm not a fan of this technique
   auto itv=values.begin();
   auto ite=expected.begin();
   while (itv != values.end())
   {
      BOOST_CHECK_EQUAL(itv->first, ite->first);
      BOOST_CHECK_EQUAL(itv->second, ite->second);
      itv++;
      ite++;
   }
}




BOOST_AUTO_TEST_CASE(binding_will_create_an_attribute_if_it_did_not_exist_previously)
{
   int temperature = -40;
   Attributes attributes;
   attributes.bind("temperature", &temperature);
   BOOST_CHECK_EQUAL(attributes.exists("temperature"), true);
}




BOOST_AUTO_TEST_CASE(an_attribute_identifies_as_unbound_when_not_bounded)
{
   Attributes attributes;
   attributes.set("size", "32");
   BOOST_CHECK_EQUAL(attributes.is_bound("size"), false);
}




BOOST_AUTO_TEST_CASE(an_attribute_identifies_as_bounded_when_bouneded)
{
   int size = 256;
   Attributes attributes;
   attributes.bind("size", &size);
   BOOST_CHECK_EQUAL(attributes.is_bound("size"), true);
}




BOOST_AUTO_TEST_CASE(an_attribute_is_set_to_the_value_of_the_variable_when_bound)
{
   Attributes attributes;
   attributes.set("temperature", 72);
   int temperature = -40;
   attributes.bind("temperature", &temperature);
   BOOST_CHECK_EQUAL(attributes.is_synced("temperature"), true);
}




BOOST_AUTO_TEST_CASE(an_attribute_is_not_synced_if_the_variable_is_modified)
{
   Attributes attributes;
   int temperature = -40;
   attributes.bind("temperature", &temperature);
   temperature = 72;
   BOOST_CHECK_EQUAL(attributes.is_unsynced("temperature"), true);
}




BOOST_AUTO_TEST_CASE(a_bound_attribute_will_pull_when_retrieved)
{
   Attributes attributes;
   int kilometers = 1000;
   attributes.bind("kilometers", &kilometers);
   kilometers = 42;
   BOOST_CHECK_EQUAL(attributes.get("kilometers"), "42");
}




BOOST_AUTO_TEST_CASE(a_bound_attribute_will_push_to_the_bound_variable_when_set)
{
   Attributes attributes;
   int kilometers = 1000;
   attributes.bind("kilometers", &kilometers);
   attributes.set("kilometers", "120");
   BOOST_CHECK_EQUAL(kilometers, 120);
}




BOOST_AUTO_TEST_CASE(user_can_get_the_bound_datatype_for_standard_datatypes)
{
   Attributes attributes;

   int int_val = 123;
   float float_val = 12.34f;
   std::string string_val = "Hello World!";
   bool bool_val = true;

   attributes.bind("val", &int_val);
   BOOST_CHECK_EQUAL(attributes.get_bound_type("val"), "int");

   attributes.bind("val", &float_val);
   BOOST_CHECK_EQUAL(attributes.get_bound_type("val"), "float");

   attributes.bind("val", &string_val);
   BOOST_CHECK_EQUAL(attributes.get_bound_type("val"), "string");

   attributes.bind("val", &bool_val);
   BOOST_CHECK_EQUAL(attributes.get_bound_type("val"), "bool");
}




BOOST_AUTO_TEST_CASE(an_attribute_will_identify_its_datatype_as_unbound_if_not_binded)
{
   Attributes attributes;
   attributes.set("val", "foobar");
   BOOST_CHECK_EQUAL(attributes.get_bound_type("val"), "unbound");
   BOOST_CHECK_EQUAL(attributes.is_bound_as("val", "unbound"), true);
}




BOOST_AUTO_TEST_CASE(a_bound_attribute_will_pull_when_getting_from_all_standard_datatypes)
{
   Attributes attributes;

   int int_val = 123;
   float float_val = 12.34f;
   std::string string_val = "Hello World!";
   bool bool_val = true;

   attributes.bind("val", &int_val);
   BOOST_CHECK_EQUAL(attributes.is_synced("val"), true);
   BOOST_CHECK_EQUAL(attributes.get("val"), "123");

   attributes.bind("val", &float_val);
   BOOST_CHECK_EQUAL(attributes.is_synced("val"), true);
   BOOST_CHECK_EQUAL(attributes.get("val"), "12.34");

   attributes.bind("val", &string_val);
   BOOST_CHECK_EQUAL(attributes.is_synced("val"), true);
   BOOST_CHECK_EQUAL(attributes.get("val"), "Hello World!");

   attributes.bind("val", &bool_val);
   BOOST_CHECK_EQUAL(attributes.is_synced("val"), true);
   BOOST_CHECK_EQUAL(attributes.get("val"), "true");
}




BOOST_AUTO_TEST_CASE(a_bound_attribute_will_pull_when_getting_as_all_standard_datatypes)
{
   Attributes attributes;

   int int_val = 123;
   float float_val = 12.34f;
   std::string string_val = "Hello World!";
   bool bool_val = true;

   attributes.bind("val", &int_val);
   int_val = 456;
   BOOST_CHECK_EQUAL(attributes.get_as_int("val"), 456);

   attributes.bind("val", &float_val);
   float_val = 56.78f;
   BOOST_CHECK_CLOSE(attributes.get_as_float("val"), 56.78f, 0.00001);

   attributes.bind("val", &string_val);
   string_val = "Twas a good day, today.";
   BOOST_CHECK_EQUAL(attributes.get_as_string("val"), "Twas a good day, today.");

   attributes.bind("val", &bool_val);
   bool_val = false;
   BOOST_CHECK_EQUAL(attributes.get_as_bool("val"), false);
}




BOOST_AUTO_TEST_CASE(a_bound_attribute_will_pull_when_getting_as_a_custom_datatype)
{
   Attributes attributes;
   my_custom_datatype custom_var, value_to_fill;

   custom_var.x = 0.876f;
   custom_var.y = 6.543f;

   // create custom datatype
   attributes.create_datatype_definition("my_custom_datatype",
         my_custom_datatype::to_val_func, my_custom_datatype::to_str_func);

   // bind it to an existing datatype with values
   attributes.bind("custom", "my_custom_datatype", &custom_var);

   attributes.get_as_custom(&value_to_fill, "my_custom_datatype", "custom");

   // check the value of the set variable
   BOOST_CHECK_CLOSE(value_to_fill.x, 0.876f, 0.00001);
   BOOST_CHECK_CLOSE(value_to_fill.y, 6.543f, 0.00001);
}




BOOST_AUTO_TEST_CASE(a_bound_attribute_will_push_when_setting_to_all_standard_datatypes)
{
   Attributes attributes;

   int int_val = 1984;
   float float_val = 65.4f;
   std::string string_val = "Daisy, Daisy, give me your answer, do.";
   bool bool_val = false;

   attributes.bind("val", &int_val);
   attributes.set("val", 187);
   BOOST_CHECK_EQUAL(int_val, 187);

   attributes.bind("val", &float_val);
   attributes.set("val", 32.1f);
   BOOST_CHECK_EQUAL(float_val, 32.1f);

   attributes.bind("val", &string_val);
   attributes.set("val", "Hello, Dave.");
   BOOST_CHECK_EQUAL(string_val, "Hello, Dave.");

   attributes.bind("val", &bool_val);
   attributes.set("val", true);
   BOOST_CHECK_EQUAL(bool_val, true);
}




BOOST_AUTO_TEST_CASE(a_bound_attribute_will_push_when_setting_to_a_custom_datatype)
{
   Attributes attributes;

   attributes.create_datatype_definition("my_custom_datatype",
         my_custom_datatype::to_val_func, my_custom_datatype::to_str_func);

   my_custom_datatype custom_var;

   custom_var.x = 0.876f;
   custom_var.y = 6.543f;

   attributes.bind("custom", "my_custom_datatype", &custom_var);
   attributes.set("custom", "1.1 0.8");

   BOOST_CHECK_CLOSE(custom_var.x, 1.1, 0.0001);
   BOOST_CHECK_CLOSE(custom_var.y, 0.8, 0.0001);
}




BOOST_AUTO_TEST_CASE(a_bound_attribute_can_be_unbound)
{
   Attributes attributes;
   int value = 1234;
   attributes.bind("val", &value);
   BOOST_CHECK_EQUAL(attributes.is_bound("val"), true);
   attributes.unbind("val");
   BOOST_CHECK_EQUAL(attributes.is_bound("val"), false);
}




BOOST_AUTO_TEST_CASE(user_can_get_the_known_datatypes_in_alphabetical_order)
{
   Attributes attributes;
   auto types = attributes.get_known_datatypes();

   attributes.create_datatype_definition("my_custom_datatype",
         my_custom_datatype::to_val_func, my_custom_datatype::to_str_func);

   BOOST_REQUIRE_EQUAL(types.size(), 5);
   BOOST_CHECK_EQUAL(types[0], "bool");
   BOOST_CHECK_EQUAL(types[1], "float");
   BOOST_CHECK_EQUAL(types[2], "int");
   BOOST_CHECK_EQUAL(types[3], "my_custom_datatype");
   BOOST_CHECK_EQUAL(types[4], "string");
}




