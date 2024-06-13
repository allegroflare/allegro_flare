#include <gtest/gtest.h>

#include <AllegroFlare/Testing/ErrorAssertions.hpp>
#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>
#include <AllegroFlare/DialogSystem/StagedCharacter/Dynamic.hpp>
#include <allegro5/allegro_primitives.h> // for al_is_primitives_addon_initialized();


class AllegroFlare_DialogSystem_StagedCharacter_DynamicTest : public ::testing::Test {};
class AllegroFlare_DialogSystem_StagedCharacter_DynamicTestWithAllegroRenderingFixture
   : public AllegroFlare::Testing::WithAllegroRenderingFixture
{};



TEST_F(AllegroFlare_DialogSystem_StagedCharacter_DynamicTest, can_be_created_without_blowing_up)
{
   AllegroFlare::DialogSystem::StagedCharacter::Dynamic dynamic;
}


TEST_F(AllegroFlare_DialogSystem_StagedCharacter_DynamicTest, render__without_allegro_initialized__raises_an_error)
{
   AllegroFlare::DialogSystem::StagedCharacter::Dynamic dynamic;
   EXPECT_THROW_GUARD_ERROR(
      dynamic.render(),
      "AllegroFlare::DialogSystem::StagedCharacter::Dynamic::render",
      "al_is_system_installed()"
   );
}


TEST_F(AllegroFlare_DialogSystem_StagedCharacter_DynamicTestWithAllegroRenderingFixture,
   CAPTURE__render__will_not_blow_up)
{
   AllegroFlare::DialogSystem::StagedCharacter::Dynamic dynamic;
   dynamic.render();
   al_flip_display();
}


