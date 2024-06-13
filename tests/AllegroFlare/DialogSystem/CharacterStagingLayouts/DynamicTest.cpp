#include <gtest/gtest.h>

#include <AllegroFlare/Testing/ErrorAssertions.hpp>
#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>
#include <AllegroFlare/DialogSystem/CharacterStagingLayouts/Dynamic.hpp>
#include <AllegroFlare/Testing/ErrorAssertions.hpp>


class AllegroFlare_DialogSystem_CharacterStagingLayouts_DynamicTest : public ::testing::Test {};
class AllegroFlare_DialogSystem_CharacterStagingLayouts_DynamicTestWithAllegroRenderingFixture
   : public AllegroFlare::Testing::WithAllegroRenderingFixture
{};
class AllegroFlare_DialogSystem_CharacterStagingLayouts_DynamicTestWithStagedCharacters
   : public AllegroFlare::Testing::WithAllegroRenderingFixture
{
public:
   AllegroFlare::DialogSystem::CharacterStagingLayouts::Dynamic staging;
   virtual void SetUp() override
   {
      AllegroFlare::Testing::WithAllegroRenderingFixture::SetUp();
      staging.set_bitmap_bin(&get_bitmap_bin_ref());
      setup_staged_characters();
   }

   void setup_staged_characters()
   {
      staging.set_staged_character_expressions_db({
         { { "BANKER_CAT", "normal" }, "banker-01.gif" },
         { { "DETECTIVE_CAT", "normal" }, "detective-01.gif" },
      });
      staging.add_staged_character(
         "BANKER_CAT",
         {
            "normal",
            AllegroFlare::Placement3D(300, 0, 0)
         });
      staging.add_staged_character(
         "DETECTIVE_CAT",
         {
            "normal",
            AllegroFlare::Placement3D(600, 0, 0)
         }
      );
   }
};


TEST_F(AllegroFlare_DialogSystem_CharacterStagingLayouts_DynamicTest, can_be_created_without_blowing_up)
{
   AllegroFlare::DialogSystem::CharacterStagingLayouts::Dynamic staging;
}


TEST_F(AllegroFlare_DialogSystem_CharacterStagingLayouts_DynamicTest, TYPE__has_the_expected_value)
{
   EXPECT_STREQ(
     "AllegroFlare/DialogSystem/CharacterStagingLayouts/Dynamic",
     AllegroFlare::DialogSystem::CharacterStagingLayouts::Dynamic::TYPE
   );
}


TEST_F(AllegroFlare_DialogSystem_CharacterStagingLayouts_DynamicTest, type__has_the_expected_value_matching_TYPE)
{
   AllegroFlare::DialogSystem::CharacterStagingLayouts::Dynamic staging;
   EXPECT_EQ(AllegroFlare::DialogSystem::CharacterStagingLayouts::Dynamic::TYPE, staging.get_type());
}


TEST_F(AllegroFlare_DialogSystem_CharacterStagingLayouts_DynamicTest,
   add_staged_characer__will_add_the_character_to_the_staging)
{
   AllegroFlare::DialogSystem::CharacterStagingLayouts::Dynamic staging;
   staging.add_staged_character(
      "HUGO",
      {
         "hugo.png",
         AllegroFlare::Placement3D(0, 0, 0)
      }
   );
   ASSERT_EQ(1, staging.num_staged_characters());
   EXPECT_EQ(true, staging.staged_character_exists("HUGO"));
}


TEST_F(AllegroFlare_DialogSystem_CharacterStagingLayouts_DynamicTest,
   render__without_allegro_initialized__raises_an_error)
{
   AllegroFlare::DialogSystem::CharacterStagingLayouts::Dynamic staging;
   EXPECT_THROW_GUARD_ERROR(
      staging.render(),
      "AllegroFlare::DialogSystem::CharacterStagingLayouts::Dynamic::render",
      "al_is_system_installed()"
   );
}


TEST_F(AllegroFlare_DialogSystem_CharacterStagingLayouts_DynamicTest, render__without_a_bitmap_bin__raises_an_error)
{
   al_init();
   AllegroFlare::DialogSystem::CharacterStagingLayouts::Dynamic staging;
   EXPECT_THROW_GUARD_ERROR(
      staging.render(),
      "AllegroFlare::DialogSystem::CharacterStagingLayouts::Dynamic::render",
      "bitmap_bin"
   );
   al_uninstall_system();
}


TEST_F(AllegroFlare_DialogSystem_CharacterStagingLayouts_DynamicTestWithAllegroRenderingFixture,
   CAPTURE__render__will_not_blow_up)
{
   AllegroFlare::DialogSystem::CharacterStagingLayouts::Dynamic staging(&get_bitmap_bin_ref());
   staging.render();
   al_flip_display();
}


TEST_F(AllegroFlare_DialogSystem_CharacterStagingLayouts_DynamicTestWithAllegroRenderingFixture,
   CAPTURE__render__with_several_staged_characters__when_a_staged_character_expressions_db_is_not_present__will_not_\
blow_up)
{
   AllegroFlare::DialogSystem::CharacterStagingLayouts::Dynamic staging;
   staging.set_bitmap_bin(&get_bitmap_bin_ref());

   staging.add_staged_character(
      "BANKER_CAT",
      {
         "banker-01.gif",
         AllegroFlare::Placement3D(300, 0, 0)
      });
   staging.add_staged_character(
      "DETECTIVE_CAT",
      {
         "detective-01.gif",
         AllegroFlare::Placement3D(600, 0, 0)
      }
   );

   staging.render();
   al_flip_display();
   sleep_for(1);
}


TEST_F(AllegroFlare_DialogSystem_CharacterStagingLayouts_DynamicTestWithStagedCharacters,
   CAPTURE__render__with_several_staged_characters__when_an_expression_db_is_present__will_not_blow_up)
{
   staging.render();
   al_flip_display();
   sleep_for(1);
}


TEST_F(AllegroFlare_DialogSystem_CharacterStagingLayouts_DynamicTestWithStagedCharacters,
   CAPTURE__exit_character__on_a_character_that_does_not_exist__will_blow_up)
{
   EXPECT_THROW_GUARD_ERROR(
      staging.exit_character("A_CHARACTER_THAT_DOES_NOT_EXIST"),
      "AllegroFlare::DialogSystem::CharacterStagingLayouts::Dynamic::exit_character",
      "staged_character_exists(staged_character_identifier)"
   );
}


TEST_F(AllegroFlare_DialogSystem_CharacterStagingLayouts_DynamicTestWithStagedCharacters,
   CAPTURE__exit_character__will_remove_the_character_from_the_scene) // More specific
{
   staging.exit_character("BANKER_CAT");
   int passes = 120;
   for (int i=0; i<passes; i++)
   {
      staging.update();

      clear();
      staging.render();

      al_flip_display();
      sleep_for_frame();
   }
}


