
#include <gtest/gtest.h>

#include <AllegroFlare/DialogSystem/CharacterFactory.hpp>


TEST(AllegroFlare_DialogSystem_CharacterFactoryTest, can_be_created_without_blowing_up)
{
   AllegroFlare::DialogSystem::CharacterFactory character_factory;
}


TEST(AllegroFlare_DialogSystem_CharacterFactoryTest,
   create_basic_character__will_create_a_AllegroFlare_DialogSystem_Characters_Basic_character_with_the_expected_values)
{
   std::string description =
      "An enigmatic man with a name as commonplace as his hidden depths, conceals a trove of secrets beneath "
         "his unassuming exterior";
   AllegroFlare::DialogSystem::CharacterFactory character_factory;
   AllegroFlare::DialogSystem::Characters::Basic *actual_character = character_factory.create_basic_character(
      "John Smith",
      description,
      "john_smith-thumb.png",
      "john_smith-portrait.png"
   );

   ASSERT_NE(nullptr, actual_character);
   ASSERT_EQ("John Smith", actual_character->get_display_name());
   ASSERT_EQ(description, actual_character->get_feature_description());
   ASSERT_EQ("john_smith-thumb.png", actual_character->get_avatar_thumbnail_identifier());
   ASSERT_EQ("john_smith-portrait.png", actual_character->get_avatar_portrait_identifier());
}


