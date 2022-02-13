


#define REQUIRES_LINKING_ALLEGRO_MAIN



#include <gtest/gtest.h>

#define ASSERT_THROW_WITH_MESSAGE(code, raised_exception_type, raised_exception_message) \
   try { code; FAIL() << "Expected " # raised_exception_type; } \
   catch ( raised_exception_type const &err ) { EXPECT_EQ(err.what(), std::string( raised_exception_message )); } \
   catch (...) { FAIL() << "Expected " # raised_exception_type; }



#include <allegro5/allegro.h>



#include <AllegroFlare/Config.hpp>

#include <fstream>




using namespace AllegroFlare;



class AllegroFlare_ConfigTest : public ::testing::Test
{
protected:
   virtual void SetUp() override
   {
      ASSERT_EQ(false, al_is_system_installed());
      ASSERT_EQ(true, al_init());
   }

   virtual void TearDown() override
   {
      al_uninstall_system();
   }
};



#ifdef _WIN32
#define TEST_FILENAME "/msys64/home/Mark/Repos/allegro_flare/bin/data/config/test_config.cfg"
#else
#define TEST_FILENAME "/Users/markoates/Repos/allegro_flare/bin/data/config/test_config.cfg"
#endif




TEST_F(AllegroFlare_ConfigTest, necessairy_test_file_exists)
{
   std::ifstream ifile(TEST_FILENAME);
   ASSERT_EQ(true, (bool)ifile);
}




TEST_F(AllegroFlare_ConfigTest, load__with_a_filename_that_does_not_exist__raises_an_error)
{
   std::string filename_that_does_not_exist = "/Some/file/that/does_not_exist.txt";
   Config config = Config(filename_that_does_not_exist);

   std::stringstream expected_error_message;
   expected_error_message << "[AllegroFlare::Config::load] the file \"" << filename_that_does_not_exist << "\" could not be found." << std::endl;

   ASSERT_THROW_WITH_MESSAGE(config.load(), std::runtime_error, expected_error_message.str());
}




TEST_F(AllegroFlare_ConfigTest,
   load_or_create_empty__with_a_filename_that_does_not_exist__outputs_an_error_message_to_stderr)
{
   std::string filename_that_does_not_exist = "/Some/file/that/does_not_exist.txt";
   Config config = Config(filename_that_does_not_exist);

   std::stringstream expected_error_message;
   expected_error_message
      << "[AllegroFlare::Config::load_or_create_empty] the file \""
      << filename_that_does_not_exist
      << "\" could not be found."
      << " Now creating an empty config to use in its place... Done: empty config created."
      << std::endl;

   testing::internal::CaptureStderr();
   config.load_or_create_empty();
   std::string output = testing::internal::GetCapturedStderr();

   ASSERT_EQ(expected_error_message.str(), output);
}



TEST_F(AllegroFlare_ConfigTest, reload__will_load_reload_the_config_file)
{
   // TODO
}



TEST_F(AllegroFlare_ConfigTest, retrieves_if_the_config_key_exists_in_the_global_space)
{
   Config config = Config(TEST_FILENAME);
   config.load();

   ASSERT_EQ(true, config.has_value("", "name"));
   ASSERT_EQ(true, config.has_value("", "width"));
   ASSERT_EQ(true, config.has_value("", "height"));
   ASSERT_EQ(true, config.has_value("", "pi"));
   ASSERT_EQ(false, config.has_value("", "foo"));
   ASSERT_EQ(false, config.has_value("", "bar"));
   ASSERT_EQ(false, config.has_value("", "baz"));
}




TEST_F(AllegroFlare_ConfigTest, retrieves_a_string_value)
{
   Config config = Config(TEST_FILENAME);
   config.load();

   ASSERT_EQ("Jordan", config.get_value_str("", "name"));
}




TEST_F(AllegroFlare_ConfigTest, retrieves_an_int_value)
{
   Config config = Config(TEST_FILENAME);
   config.load();

   ASSERT_EQ(1080, config.get_value_int("", "width"));
   ASSERT_EQ(320, config.get_value_int("", "height"));
}




TEST_F(AllegroFlare_ConfigTest, retrieves_a_bool_value)
{
   Config config = Config(TEST_FILENAME);
   config.load();

   ASSERT_EQ(true, config.get_value_bool("", "squatting"));
}




TEST_F(AllegroFlare_ConfigTest, retrieves_a_float_value_within_a_margin_of_error)
{
   Config config = Config(TEST_FILENAME);
   config.load();

   ASSERT_NEAR(3.14, config.get_value_float("", "pi"), 0.00001);
}




TEST_F(AllegroFlare_ConfigTest, returns_a_default_value_if_a_section_and_key_does_not_exist)
{
   Config config = Config(TEST_FILENAME);
   config.load();

   ASSERT_EQ("Beary", config.get_or_default_str("", "hero", "Beary"));
   ASSERT_EQ(false, config.get_value_bool("", "a_key_that_does_not_exist"));
   ASSERT_EQ(42, config.get_or_default_int("", "speed", 42));
   ASSERT_NEAR(6.28, config.get_or_default_float("", "tau", 6.28), 0.00001);
}




TEST_F(AllegroFlare_ConfigTest, get_value_bool__returns_a_default_value_if_a_section_and_key_does_not_exist)
{
   Config config = Config(TEST_FILENAME);
   config.load();

   ASSERT_EQ("Beary", config.get_or_default_str("", "hero", "Beary"));
   ASSERT_EQ(42, config.get_or_default_int("", "speed", 42));
   ASSERT_EQ(false, config.get_or_default_bool("", "invisibility", false));
   ASSERT_EQ(true, config.get_or_default_bool("", "blitz_mode", true));
   ASSERT_NEAR(6.28, config.get_or_default_float("", "tau", 6.28), 0.00001);
}




TEST_F(AllegroFlare_ConfigTest, when_allegro_is_not_initialized_all_member_functions_will_raise_an_exception)
{
   al_uninstall_system();

   Config config = Config(TEST_FILENAME);
   std::string expected_error_message = "[Config]: attempting to use AllegroFlare/Config but allegro is not " \
                                        "initialized.  You must call al_init() before using any of the " \
                                        "AllegroFlare/Config functions.";

   ASSERT_THROW_WITH_MESSAGE(config.load(), std::runtime_error, expected_error_message);
   ASSERT_THROW_WITH_MESSAGE(config.has_value("foo", "bar"), std::runtime_error, expected_error_message);
   ASSERT_THROW_WITH_MESSAGE(config.get_value_str("foo", "bar"), std::runtime_error, expected_error_message);
   ASSERT_THROW_WITH_MESSAGE(config.get_value_int("foo", "bar"), std::runtime_error, expected_error_message);
   ASSERT_THROW_WITH_MESSAGE(config.get_value_float("foo", "bar"), std::runtime_error, expected_error_message);
   ASSERT_THROW_WITH_MESSAGE(config.get_or_default_str("foo", "bar", "baz"), std::runtime_error, expected_error_message);
   ASSERT_THROW_WITH_MESSAGE(config.get_or_default_int("foo", "bar", 0), std::runtime_error, expected_error_message);
   ASSERT_THROW_WITH_MESSAGE(config.get_or_default_float("foo", "bar", 0.0), std::runtime_error, expected_error_message);
}



