


#define REQUIRES_LINKING_ALLEGRO_MAIN



#include <gtest/gtest.h>
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



#define TEST_FILENAME "bin/data/tests/config.cfg"




TEST_F(AllegroFlare_ConfigTest, necessairy_test_file_exists)
{
   std::ifstream ifile(TEST_FILENAME);
   ASSERT_EQ(true, (bool)ifile);
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
   ASSERT_EQ(42, config.get_or_default_int("", "speed", 42));
   ASSERT_NEAR(6.28, config.get_or_default_float("", "tau", 6.28), 0.00001);
}



