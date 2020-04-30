

#include <gtest/gtest.h>

#include <AllegroFlare/KeyboardCommandMapper.hpp>


TEST(KeyboardCommandMapperTest, can_get_and_set_mappings)
{
   KeyboardCommandMapper mapper;

   std::vector<std::string> command_identifiers = {"this_is_the_command"};

   EXPECT_TRUE(mapper.set_mapping(14 /*ALLEGRO_KEY_N*/, true, false, true, false, command_identifiers));
   EXPECT_EQ(command_identifiers, mapper.get_mapping(14 /*ALLEGRO_KEY_N*/, true, false, true, false));
}


TEST(KeyboardCommandMapperTest, can_get_and_set_all_valid_allegro_keycodes)
{
   KeyboardCommandMapper mapper;

   for (unsigned k=0 /*ALLEGRO_KEY_A*/; k<215/*ALLEGRO_KEY_MODIFIERS*/; k++)
   {
      std::vector<std::string> mapped_command_identifiers = {"this is a test identifier"};

      EXPECT_TRUE(                          mapper.set_mapping(k, true, true, true, false, mapped_command_identifiers));
      EXPECT_EQ(mapped_command_identifiers, mapper.get_mapping(k, true, true, true, false));

      EXPECT_TRUE(                          mapper.set_mapping(k, true, false, true, false, mapped_command_identifiers));
      EXPECT_EQ(mapped_command_identifiers, mapper.get_mapping(k, true, false, true, false));

      EXPECT_TRUE(                          mapper.set_mapping(k, true, true, false, false, mapped_command_identifiers));
      EXPECT_EQ(mapped_command_identifiers, mapper.get_mapping(k, true, true, false, false));
   }
}


TEST(KeyboardCommandMapperTest, returns_an_empty_vector_if_identifier_is_not_found)
{
   KeyboardCommandMapper mapper;
   std::vector<std::string> expected_return_value = {};

   EXPECT_EQ(expected_return_value, mapper.get_mapping(16, true, false, false, false));
   EXPECT_EQ(expected_return_value, mapper.get_mapping(24, false, true, false, false));
   EXPECT_EQ(expected_return_value, mapper.get_mapping(0, false, false, true, false));
}



