

#include <gtest/gtest.h>

#include <AllegroFlare/KeyboardCommandMapper.hpp>


TEST(AllegroFlare_KeyboardCommandMapperTest, can_get_and_set_mappings)
{
   AllegroFlare::KeyboardCommandMapper mapper;

   std::vector<std::string> command_identifiers = {"this_is_the_command"};

   EXPECT_TRUE(mapper.set_mapping(14 /*ALLEGRO_KEY_N*/, true, false, true, false, command_identifiers));
   EXPECT_EQ(command_identifiers, mapper.get_mapping(14 /*ALLEGRO_KEY_N*/, true, false, true, false));
}


TEST(AllegroFlare_KeyboardCommandMapperTest, can_get_and_set_all_valid_allegro_keycodes)
{
   AllegroFlare::KeyboardCommandMapper mapper;

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


TEST(AllegroFlare_KeyboardCommandMapperTest, get_mapping__returns_an_empty_vector_if_identifier_is_not_found)
{
   AllegroFlare::KeyboardCommandMapper mapper;
   std::vector<std::string> expected_return_value = {};

   EXPECT_EQ(expected_return_value, mapper.get_mapping(16, true, false, false, false));
   EXPECT_EQ(expected_return_value, mapper.get_mapping(24, false, true, false, false));
   EXPECT_EQ(expected_return_value, mapper.get_mapping(0, false, false, true, false));
}


TEST(AllegroFlare_KeyboardCommandMapperTest, has_overloads_for_getting_and_setting_mappings_with_bigflags)
{
   constexpr auto SHIFT = AllegroFlare::KeyboardCommandMapper::SHIFT;
   constexpr auto CTRL = AllegroFlare::KeyboardCommandMapper::CTRL;
   constexpr auto ALT = AllegroFlare::KeyboardCommandMapper::ALT;
   constexpr auto COMMAND = AllegroFlare::KeyboardCommandMapper::COMMAND;
   constexpr auto OPTION = AllegroFlare::KeyboardCommandMapper::OPTION;

   for (unsigned k=0 /*ALLEGRO_KEY_A*/; k<215/*ALLEGRO_KEY_MODIFIERS*/; k++)
   {
      AllegroFlare::KeyboardCommandMapper mapper;
      std::vector<std::string> commands = { "foo" };

      // bigflags for assignment

      EXPECT_TRUE(        mapper.set_mapping(k, SHIFT, commands));
      EXPECT_EQ(commands, mapper.get_mapping(k, true, false, false, false));

      EXPECT_TRUE(        mapper.set_mapping(k, CTRL, commands));
      EXPECT_EQ(commands, mapper.get_mapping(k, false, true, false, false));

      EXPECT_TRUE(        mapper.set_mapping(k, ALT, commands));
      EXPECT_EQ(commands, mapper.get_mapping(k, false, false, true, false));

      EXPECT_TRUE(        mapper.set_mapping(k, COMMAND, commands));
      EXPECT_EQ(commands, mapper.get_mapping(k, false, false, false, true));

      // bitflags for retrieval

      EXPECT_TRUE(        mapper.set_mapping(k, true, false, false, false, commands));
      EXPECT_EQ(commands, mapper.get_mapping(k, SHIFT));

      EXPECT_TRUE(        mapper.set_mapping(k, false, true, false, false, commands));
      EXPECT_EQ(commands, mapper.get_mapping(k, CTRL));

      EXPECT_TRUE(        mapper.set_mapping(k, false, false, true, false, commands));
      EXPECT_EQ(commands, mapper.get_mapping(k, ALT));

      EXPECT_TRUE(        mapper.set_mapping(k, false, false, false, true, commands));
      EXPECT_EQ(commands, mapper.get_mapping(k, COMMAND));

      // some arbitrary combinations

      EXPECT_TRUE(        mapper.set_mapping(k, SHIFT | CTRL, commands));
      EXPECT_EQ(commands, mapper.get_mapping(k, true, true, false, false));
      EXPECT_EQ(commands, mapper.get_mapping(k, SHIFT | CTRL));

      EXPECT_TRUE(        mapper.set_mapping(k, CTRL | ALT, commands));
      EXPECT_EQ(commands, mapper.get_mapping(k, false, true, true, false));
      EXPECT_EQ(commands, mapper.get_mapping(k, CTRL | ALT));

      EXPECT_TRUE(        mapper.set_mapping(k, ALT | COMMAND, commands));
      EXPECT_EQ(commands, mapper.get_mapping(k, false, false, true, true));
      EXPECT_EQ(commands, mapper.get_mapping(k, ALT | COMMAND));

      EXPECT_TRUE(        mapper.set_mapping(k, SHIFT | COMMAND, commands));
      EXPECT_EQ(commands, mapper.get_mapping(k, true, false, false, true));
      EXPECT_EQ(commands, mapper.get_mapping(k, SHIFT | COMMAND));

      EXPECT_TRUE(        mapper.set_mapping(k, SHIFT | ALT | COMMAND, commands));
      EXPECT_EQ(commands, mapper.get_mapping(k, true, false, true, true));
      EXPECT_EQ(commands, mapper.get_mapping(k, SHIFT | ALT | COMMAND));

      EXPECT_TRUE(        mapper.set_mapping(k, SHIFT | CTRL | ALT | COMMAND, commands));
      EXPECT_EQ(commands, mapper.get_mapping(k, true, true, true, true));
      EXPECT_EQ(commands, mapper.get_mapping(k, SHIFT | CTRL | ALT | COMMAND));
   }
}


