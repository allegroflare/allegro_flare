
#include <gtest/gtest.h>

#include <AllegroFlare/SavingAndLoading/SaveStyles.hpp>


TEST(AllegroFlare_SavingAndLoading_SaveStylesTest, can_be_created_without_blowing_up)
{
   AllegroFlare::SavingAndLoading::SaveStyles save_styles;
}


TEST(AllegroFlare_SavingAndLoading_SaveStylesTest, initialize__will_not_blow_up)
{
   AllegroFlare::SavingAndLoading::SaveStyles save_styles(
      AllegroFlare::SavingAndLoading::SaveStyles::StartStyle::GAME_START_STYLE_A,
      AllegroFlare::SavingAndLoading::SaveStyles::SaveStyle::GAME_SAVE_STYLE_4,
      AllegroFlare::SavingAndLoading::SaveStyles::LoadStyle::GAME_LOAD_STYLE_0
   );
   save_styles.initialize();
}


