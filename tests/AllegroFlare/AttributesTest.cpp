

//#define BOOST_TEST_DYN_LINK
//#define BOOST_TEST_MODULE AttributesTestModule
//#include <boost/test/unit_test.hpp>


#include <gtest/gtest.h>

#include <AllegroFlare/Attributes.hpp>

//#include <fstream>
//#include <sstream>
//#include <unistd.h>



using namespace AllegroFlare;



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




TEST(AllegroFlare_AttributesTest, unknown_attributes_do_not_exist)
{
   Attributes attributes;
   EXPECT_EQ(false, attributes.exists("hello"));
}




TEST(AllegroFlare_AttributesTest, attributes_can_be_created)
{
   Attributes attributes;
   attributes.set("hello");
   EXPECT_EQ(true, attributes.exists("hello"));
}




TEST(AllegroFlare_AttributesTest, created_key_value_pairs_exist)
{
   Attributes attributes;
   attributes.set("size", "large");
   EXPECT_EQ(true, attributes.exists("size", "large"));
}




TEST(AllegroFlare_AttributesTest, unknown_key_value_pairs_do_not_exist)
{
   Attributes attributes;
   attributes.set("size", "large");
   EXPECT_EQ(false, attributes.exists("size", "small"));
}




TEST(AllegroFlare_AttributesTest, attribute_values_can_be_retrieved)
{
   Attributes attributes;
   attributes.set("name", "Alex");
   EXPECT_EQ("Alex", attributes.get("name"));
}




TEST(AllegroFlare_AttributesTest, attributes_can_be_counted)
{
   Attributes attributes;
   attributes.set("name", "Alex");
   EXPECT_EQ(1, attributes.num_attributes());
   attributes.set("color", "green");
   EXPECT_EQ(2, attributes.num_attributes());
   attributes.set("animal", "alligator");
   EXPECT_EQ(3, attributes.num_attributes());
}




TEST(AllegroFlare_AttributesTest, attribute_values_can_be_changed)
{
   Attributes attributes;
   attributes.set("name", "Alex");
   attributes.set("name", "Beary");
   EXPECT_EQ("Beary", attributes.get("name"));
}




TEST(AllegroFlare_AttributesTest, attributes_can_be_removed)
{
   Attributes attributes;
   attributes.set("os", "OSX");
   attributes.remove("os");
   EXPECT_EQ(0, attributes.num_attributes());
}




TEST(AllegroFlare_AttributesTest, attributes_matching_key_value_can_be_removed)
{
   Attributes attributes;
   attributes.set("os", "Windows");
   attributes.remove("os", "Windows");
   EXPECT_EQ(0, attributes.num_attributes());
}




TEST(AllegroFlare_AttributesTest, attributes_can_be_set_with_standard_datatypes)
{
   Attributes attributes;

   attributes.set("name", "Mark");
   EXPECT_EQ("Mark", attributes.get("name"));

   attributes.set("father", std::string("Tony"));
   EXPECT_EQ("Tony", attributes.get("father"));

   attributes.set("answer", 42);
   EXPECT_EQ("42", attributes.get("answer"));

   attributes.set("pi", 3.14f);
   EXPECT_EQ("3.14", attributes.get("pi"));

   attributes.set("tau", 6.28);
   EXPECT_EQ("6.28", attributes.get("tau"));

   attributes.set("happy", true);
   EXPECT_EQ("true", attributes.get("happy"));

   attributes.set("caffinated", false);
   EXPECT_EQ("false", attributes.get("caffinated"));
}




TEST(AllegroFlare_AttributesTest, attributes_can_be_retrieved_as_standard_datatypes)
{
   Attributes attributes;

   attributes.set("value", "128");
   EXPECT_EQ(128, attributes.get_as_int("value"));

   attributes.set("phi", "1.618");
   EXPECT_NEAR(1.618f, attributes.get_as_float("phi"), 0.00001f);

   attributes.set("flavor", "sweet");
   EXPECT_EQ(std::string("sweet"), attributes.get_as_string("flavor"));

   attributes.set("should_do_laundry", "true");
   EXPECT_EQ(true, attributes.get_as_bool("should_do_laundry"));

   attributes.set("doing_laundry_now", "false");
   EXPECT_EQ(false, attributes.get_as_bool("doing_laundry_now"));
}




TEST(AllegroFlare_AttributesTest, a_datatype_that_has_not_been_created_is_inknown)
{
   Attributes attributes;
   EXPECT_EQ(Attributes::datatype_is_known("my_custom_datatype"), false);
}




TEST(AllegroFlare_AttributesTest, custom_datatypes_that_have_been_created_are_known)
{
   Attributes attributes;

   attributes.create_datatype_definition("my_custom_datatype",
         my_custom_datatype::to_val_func, my_custom_datatype::to_str_func);

   EXPECT_EQ(true, Attributes::datatype_is_known("my_custom_datatype"));
}




TEST(AllegroFlare_AttributesTest, an_attribute_can_not_be_set_as_an_unknown_datatype)
{
   Attributes attributes;
   my_custom_datatype custom;
   EXPECT_EQ(false, attributes.set("key", "an_unknown_datatype", (void *)&custom));
}




TEST(AllegroFlare_AttributesTest, a_variable_cannot_be_bound_to_a_datatype_that_does_not_exist)
{
   Attributes attributes;
   my_custom_datatype custom;
   EXPECT_EQ(false, attributes.bind("key", "an_unknown_datatype", &custom));
}




TEST(AllegroFlare_AttributesTest, custom_datatypes_can_be_bound)
{
   Attributes attributes;
   my_custom_datatype custom;

   attributes.create_datatype_definition("my_custom_datatype",
         my_custom_datatype::to_val_func, my_custom_datatype::to_str_func);

   EXPECT_EQ(true, attributes.bind("foo", "my_custom_datatype", &custom));
}




TEST(AllegroFlare_AttributesTest, attributes_can_be_set_using_custom_datatypes)
{
   Attributes attributes;
   my_custom_datatype my_2d_vector;
   my_2d_vector.x = 0.35;
   my_2d_vector.y = 0.01;

   attributes.create_datatype_definition("my_custom_datatype",
         my_custom_datatype::to_val_func, my_custom_datatype::to_str_func);

   attributes.set("position", "my_custom_datatype", (void *)&my_2d_vector);

   EXPECT_EQ("0.35 0.01", attributes.get("position"));
}




TEST(AllegroFlare_AttributesTest, a_custom_attribute_is_set_to_the_value_of_the_variable_when_bound)
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

   EXPECT_EQ(true, attributes.is_synced("custom"));
}




TEST(AllegroFlare_AttributesTest, attributes_can_be_retrieved_as_a_custom_datatype)
{
   Attributes attributes;
   my_custom_datatype my_2d_vector;

   attributes.create_datatype_definition("my_custom_datatype",
         my_custom_datatype::to_val_func, my_custom_datatype::to_str_func);

   attributes.set("position", "123.4 567.8");
   attributes.get_as_custom(&my_2d_vector, "my_custom_datatype", "position");

   EXPECT_NEAR(my_2d_vector.x, 123.4f, 0.00001);
   EXPECT_NEAR(my_2d_vector.y, 567.8f, 0.00001);
}




//TODO: this test
//TEST(AllegroFlare_AttributesTest, attributes_can_be_saved_to_a_file)
//{
   //std::string test_filename = "TEST_alex_attributes_1.txt";

   //// remove the test file if it already exists

   //if (access(test_filename.c_str(), F_OK) != -1)
      //ASSERT_EQ(0, remove(test_filename.c_str()));

   //// create and save our attributes

   //Attributes attributes;

   //attributes.set("name", "Alex");
   //attributes.set("color", "green");
   //attributes.set("height", "16");

   //attributes.save(test_filename);

   //// validate the file was created

   //std::ifstream file(test_filename);
   //ASSERT_EQ(file.fail(), false);

   //// validate the contents of the file

   //std::string expected_file_contents = "";
   //expected_file_contents += "name: Alex\n";
   //expected_file_contents += "color: green\n";
   //expected_file_contents += "height: 16\n";

   //file.open(test_filename);
   //std::stringstream contents;
   //contents << file.rdbuf();

   //EXPECT_EQ(expected_file_contents, contents.str());

   //file.close();

   //// remove the test file if it already exists

   //ASSERT_EQ(0, remove(test_filename.c_str()));
//}



//TODO: this test
//TEST(AllegroFlare_AttributesTest, attributes_can_be_loaded_from_a_file)
//{
   //std::string test_filename = "TEST_alex_attributes_2.txt";

   //// remove the test file if it already exists

   //if (access(test_filename.c_str(), F_OK) != -1)
      //ASSERT_EQ(0, remove(test_filename.c_str()));

   //// create a faux file

   //std::ofstream outfile(test_filename);
   //outfile << "name: Alex\n";
   //outfile << "color: green\n";
   //outfile << "height: 16\n";
   //outfile.close();

   //BOOST_REQUIRE(-1 != access(test_filename.c_str(), F_OK));

   //// load the file

   //Attributes attributes;
   //attributes.load(test_filename);

   //EXPECT_EQ("Alex", attributes.get("name"));
   //EXPECT_EQ("green", attributes.get("color"));
   //EXPECT_EQ("16", attributes.get("height"));

   //// cleanup our file

   //ASSERT_EQ(0, remove(test_filename.c_str()));
//}




TEST(AllegroFlare_AttributesTest, a_copy_of_the_key_value_pairs_can_be_retrieved)
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

   ASSERT_EQ(expected.size(), values.size());

   // p.s. I'm not a fan of this technique
   auto itv=values.begin();
   auto ite=expected.begin();
   while (itv != values.end())
   {
      EXPECT_EQ(itv->first, ite->first);
      EXPECT_EQ(itv->second, ite->second);
      itv++;
      ite++;
   }
}




TEST(AllegroFlare_AttributesTest, binding_will_create_an_attribute_if_it_did_not_exist_previously)
{
   int temperature = -40;
   Attributes attributes;
   attributes.bind("temperature", &temperature);
   EXPECT_EQ(true, attributes.exists("temperature"));
}




TEST(AllegroFlare_AttributesTest, an_attribute_identifies_as_unbound_when_not_bounded)
{
   Attributes attributes;
   attributes.set("size", "32");
   EXPECT_EQ(false, attributes.is_bound("size"));
}




TEST(AllegroFlare_AttributesTest, an_attribute_identifies_as_bounded_when_bouneded)
{
   int size = 256;
   Attributes attributes;
   attributes.bind("size", &size);
   EXPECT_EQ(true, attributes.is_bound("size"));
}




TEST(AllegroFlare_AttributesTest, an_attribute_is_set_to_the_value_of_the_variable_when_bound)
{
   Attributes attributes;
   attributes.set("temperature", 72);
   int temperature = -40;
   attributes.bind("temperature", &temperature);
   EXPECT_EQ(true, attributes.is_synced("temperature"));
}




TEST(AllegroFlare_AttributesTest, an_attribute_is_not_synced_if_the_variable_is_modified)
{
   Attributes attributes;
   int temperature = -40;
   attributes.bind("temperature", &temperature);
   temperature = 72;
   EXPECT_EQ(true, attributes.is_unsynced("temperature"));
}




TEST(AllegroFlare_AttributesTest, a_bound_attribute_will_pull_when_retrieved)
{
   Attributes attributes;
   int kilometers = 1000;
   attributes.bind("kilometers", &kilometers);
   kilometers = 42;
   EXPECT_EQ("42", attributes.get("kilometers"));
}




TEST(AllegroFlare_AttributesTest, a_bound_attribute_will_push_to_the_bound_variable_when_set)
{
   Attributes attributes;
   int kilometers = 1000;
   attributes.bind("kilometers", &kilometers);
   attributes.set("kilometers", "120");
   EXPECT_EQ(120, kilometers);
}




TEST(AllegroFlare_AttributesTest, user_can_get_the_bound_datatype_for_standard_datatypes)
{
   Attributes attributes;

   int int_val = 123;
   float float_val = 12.34f;
   std::string string_val = "Hello World!";
   bool bool_val = true;

   attributes.bind("val", &int_val);
   EXPECT_EQ("int", attributes.get_bound_type("val"));

   attributes.bind("val", &float_val);
   EXPECT_EQ("float", attributes.get_bound_type("val"));

   attributes.bind("val", &string_val);
   EXPECT_EQ("string", attributes.get_bound_type("val"));

   attributes.bind("val", &bool_val);
   EXPECT_EQ("bool", attributes.get_bound_type("val"));
}




TEST(AllegroFlare_AttributesTest, an_attribute_will_identify_its_datatype_as_unbound_if_not_binded)
{
   Attributes attributes;
   attributes.set("val", "foobar");
   EXPECT_EQ("unbound", attributes.get_bound_type("val"));
   EXPECT_EQ(true, attributes.is_bound_as("val", "unbound"));
}




TEST(AllegroFlare_AttributesTest, a_bound_attribute_will_pull_when_getting_from_all_standard_datatypes)
{
   Attributes attributes;

   int int_val = 123;
   float float_val = 12.34f;
   std::string string_val = "Hello World!";
   bool bool_val = true;

   attributes.bind("val", &int_val);
   EXPECT_EQ(true, attributes.is_synced("val"));
   EXPECT_EQ("123", attributes.get("val"));

   attributes.bind("val", &float_val);
   EXPECT_EQ(true, attributes.is_synced("val"));
   EXPECT_EQ("12.34", attributes.get("val"));

   attributes.bind("val", &string_val);
   EXPECT_EQ(true, attributes.is_synced("val"));
   EXPECT_EQ("Hello World!", attributes.get("val"));

   attributes.bind("val", &bool_val);
   EXPECT_EQ(true, attributes.is_synced("val"));
   EXPECT_EQ("true", attributes.get("val"));
}




//TEST(AllegroFlare_AttributesTest, a_bound_attribute_will_pull_when_getting_as_all_standard_datatypes)
//{
   //Attributes attributes;

   //int int_val = 123;
   //float float_val = 12.34f;
   //std::string string_val = "Hello World!";
   //bool bool_val = true;

   //attributes.bind("val", &int_val);
   //int_val = 456;
   //EXPECT_EQ(attributes.get_as_int("val"), 456);

   //attributes.bind("val", &float_val);
   //float_val = 56.78f;
   //BOOST_CHECK_CLOSE(attributes.get_as_float("val"), 56.78f, 0.00001);

   //attributes.bind("val", &string_val);
   //string_val = "Twas a good day, today.";
   //EXPECT_EQ(attributes.get_as_string("val"), "Twas a good day, today.");

   //attributes.bind("val", &bool_val);
   //bool_val = false;
   //EXPECT_EQ(attributes.get_as_bool("val"), false);
//}




//TEST(AllegroFlare_AttributesTest, a_bound_attribute_will_pull_when_getting_as_a_custom_datatype)
//{
   //Attributes attributes;
   //my_custom_datatype custom_var, value_to_fill;

   //custom_var.x = 0.876f;
   //custom_var.y = 6.543f;

   //// create custom datatype
   //attributes.create_datatype_definition("my_custom_datatype",
         //my_custom_datatype::to_val_func, my_custom_datatype::to_str_func);

   //// bind it to an existing datatype with values
   //attributes.bind("custom", "my_custom_datatype", &custom_var);

   //attributes.get_as_custom(&value_to_fill, "my_custom_datatype", "custom");

   //// check the value of the set variable
   //BOOST_CHECK_CLOSE(value_to_fill.x, 0.876f, 0.00001);
   //BOOST_CHECK_CLOSE(value_to_fill.y, 6.543f, 0.00001);
//}




//TEST(AllegroFlare_AttributesTest, a_bound_attribute_will_push_when_setting_to_all_standard_datatypes)
//{
   //Attributes attributes;

   //int int_val = 1984;
   //float float_val = 65.4f;
   //std::string string_val = "Daisy, Daisy, give me your answer, do.";
   //bool bool_val = false;

   //attributes.bind("val", &int_val);
   //attributes.set("val", 187);
   //EXPECT_EQ(int_val, 187);

   //attributes.bind("val", &float_val);
   //attributes.set("val", 32.1f);
   //EXPECT_EQ(float_val, 32.1f);

   //attributes.bind("val", &string_val);
   //attributes.set("val", "Hello, Dave.");
   //EXPECT_EQ(string_val, "Hello, Dave.");

   //attributes.bind("val", &bool_val);
   //attributes.set("val", true);
   //EXPECT_EQ(bool_val, true);
//}




//TEST(AllegroFlare_AttributesTest, a_bound_attribute_will_push_when_setting_to_a_custom_datatype)
//{
   //Attributes attributes;

   //attributes.create_datatype_definition("my_custom_datatype",
         //my_custom_datatype::to_val_func, my_custom_datatype::to_str_func);

   //my_custom_datatype custom_var;

   //custom_var.x = 0.876f;
   //custom_var.y = 6.543f;

   //attributes.bind("custom", "my_custom_datatype", &custom_var);
   //attributes.set("custom", "1.1 0.8");

   //BOOST_CHECK_CLOSE(custom_var.x, 1.1, 0.0001);
   //BOOST_CHECK_CLOSE(custom_var.y, 0.8, 0.0001);
//}




//TEST(AllegroFlare_AttributesTest, a_bound_attribute_can_be_unbound)
//{
   //Attributes attributes;
   //int value = 1234;
   //attributes.bind("val", &value);
   //EXPECT_EQ(attributes.is_bound("val"), true);
   //attributes.unbind("val");
   //EXPECT_EQ(attributes.is_bound("val"), false);
//}




//TEST(AllegroFlare_AttributesTest, user_can_get_the_known_datatypes_in_alphabetical_order)
//{
   //Attributes attributes;
   //auto types = attributes.get_known_datatypes();

   //attributes.create_datatype_definition("my_custom_datatype",
         //my_custom_datatype::to_val_func, my_custom_datatype::to_str_func);

   //ASSERT_EQ(types.size(), 5);
   //EXPECT_EQ(types[0], "bool");
   //EXPECT_EQ(types[1], "float");
   //EXPECT_EQ(types[2], "int");
   //EXPECT_EQ(types[3], "my_custom_datatype");
   //EXPECT_EQ(types[4], "string");
//}




