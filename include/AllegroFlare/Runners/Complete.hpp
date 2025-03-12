#pragma once


#include <AllegroFlare/BitmapBin.hpp>
#include <AllegroFlare/Elements/Backgrounds/Base.hpp>
#include <AllegroFlare/EventEmitter.hpp>
#include <AllegroFlare/FontBin.hpp>
#include <AllegroFlare/ForwardDeclarations/AllegroFlare/GameConfigurations/Complete.hpp>
#include <AllegroFlare/ForwardDeclarations/AllegroFlare/Runners/Complete.hpp>
#include <AllegroFlare/Frameworks/Full.hpp>
#include <AllegroFlare/GameConfigurations/Complete.hpp>
#include <AllegroFlare/GameEvent.hpp>
#include <AllegroFlare/LoadASavedGame/Screen.hpp>
#include <AllegroFlare/ModelBin.hpp>
#include <AllegroFlare/Routers/Standard.hpp>
#include <AllegroFlare/SampleBin.hpp>
#include <AllegroFlare/SavingAndLoading/SavingAndLoading.hpp>
#include <AllegroFlare/SavingAndLoading/Screen.hpp>
#include <AllegroFlare/Screens/Achievements.hpp>
#include <AllegroFlare/Screens/Base.hpp>
#include <AllegroFlare/Screens/DisplaySettings.hpp>
#include <AllegroFlare/Screens/GameOverScreen.hpp>
#include <AllegroFlare/Screens/GameWonScreen.hpp>
#include <AllegroFlare/Screens/Gameplay.hpp>
#include <AllegroFlare/Screens/LevelSelectScreen.hpp>
#include <AllegroFlare/Screens/RollingCredits.hpp>
#include <AllegroFlare/Screens/SettingsScreen.hpp>
#include <AllegroFlare/Screens/Storyboard.hpp>
#include <AllegroFlare/Screens/Subscreen/Screen.hpp>
#include <AllegroFlare/Screens/TitledMenuScreen.hpp>
#include <AllegroFlare/Screens/Version.hpp>
#include <ReleaseInfo.hpp>
#include <cstdint>
#include <string>


namespace AllegroFlare
{
   namespace Runners
   {
      class Complete : public AllegroFlare::Screens::Base
      {
      public:
         static constexpr uint32_t MY_ROUTE_EVENT_ACTIVATE_MY_CUSTOM_SCREEN = AllegroFlare::Routers::Standard::EVENT_LAST_EVENT+1;
         static constexpr char* MY_CUSTOM_SCREEN_IDENTIFIER = (char*)"my_custom_screen";
         static constexpr char* TYPE = (char*)"AllegroFlare/Runners/Complete";

      private:
         AllegroFlare::Frameworks::Full* framework;
         AllegroFlare::EventEmitter* event_emitter;
         AllegroFlare::BitmapBin* bitmap_bin;
         AllegroFlare::FontBin* font_bin;
         AllegroFlare::SampleBin* sample_bin;
         AllegroFlare::ModelBin* model_bin;
         AllegroFlare::GameConfigurations::Complete* game_configuration;
         AllegroFlare::Routers::Standard router;
         AllegroFlare::SavingAndLoading::SavingAndLoading saving_and_loading;
         int current_save_profile_id;
         AllegroFlare::Screens::Storyboard intro_logos_screen;
         AllegroFlare::Screens::Storyboard intro_storyboard_screen;
         AllegroFlare::Screens::TitledMenuScreen title_screen;
         AllegroFlare::Screens::DisplaySettings display_settings_screen;
         AllegroFlare::Screens::Achievements achievements_screen;
         AllegroFlare::Screens::Version version_screen;
         AllegroFlare::LoadASavedGame::Screen load_a_saved_game_screen;
         AllegroFlare::SavingAndLoading::Screen saving_and_loading_screen;
         AllegroFlare::Screens::Storyboard new_game_intro_storyboard_screen;
         AllegroFlare::Screens::LevelSelectScreen level_select_screen;
         AllegroFlare::Screens::Storyboard arbitrary_storyboard_screen;
         AllegroFlare::Screens::GameOverScreen game_over_screen;
         AllegroFlare::Screens::GameWonScreen game_won_screen;
         AllegroFlare::Screens::Storyboard game_won_outro_storyboard_screen;
         AllegroFlare::Screens::SettingsScreen settings_screen;
         AllegroFlare::Screens::RollingCredits rolling_credits_screen;
         AllegroFlare::Screens::Gameplay* primary_gameplay_screen;
         AllegroFlare::Screens::Subscreen::Screen* primary_gameplay_subscreen;
         AllegroFlare::Screens::Base* pause_screen;
         AllegroFlare::Elements::Backgrounds::Base* shared_background;
         AllegroFlare::Elements::Backgrounds::Base* shared_foreground;
         ReleaseInfo release_info;
         bool initialized;
         bool destroyed;

      protected:


      public:
         Complete(AllegroFlare::Frameworks::Full* framework=nullptr, AllegroFlare::EventEmitter* event_emitter=nullptr, AllegroFlare::BitmapBin* bitmap_bin=nullptr, AllegroFlare::FontBin* font_bin=nullptr, AllegroFlare::SampleBin* sample_bin=nullptr, AllegroFlare::ModelBin* model_bin=nullptr, AllegroFlare::GameConfigurations::Complete* game_configuration=nullptr);
         virtual ~Complete();

         AllegroFlare::Frameworks::Full* get_framework() const;
         AllegroFlare::EventEmitter* get_event_emitter() const;
         AllegroFlare::BitmapBin* get_bitmap_bin() const;
         AllegroFlare::FontBin* get_font_bin() const;
         AllegroFlare::SampleBin* get_sample_bin() const;
         AllegroFlare::ModelBin* get_model_bin() const;
         AllegroFlare::SavingAndLoading::SavingAndLoading &get_saving_and_loading_ref();
         AllegroFlare::Screens::Storyboard &get_intro_logos_screen_ref();
         AllegroFlare::Screens::Storyboard &get_intro_storyboard_screen_ref();
         AllegroFlare::Screens::TitledMenuScreen &get_title_screen_ref();
         AllegroFlare::Screens::DisplaySettings &get_display_settings_screen_ref();
         AllegroFlare::Screens::Achievements &get_achievements_screen_ref();
         AllegroFlare::Screens::Version &get_version_screen_ref();
         AllegroFlare::LoadASavedGame::Screen &get_load_a_saved_game_screen_ref();
         AllegroFlare::SavingAndLoading::Screen &get_saving_and_loading_screen_ref();
         AllegroFlare::Screens::Storyboard &get_new_game_intro_storyboard_screen_ref();
         AllegroFlare::Screens::LevelSelectScreen &get_level_select_screen_ref();
         AllegroFlare::Screens::Storyboard &get_arbitrary_storyboard_screen_ref();
         AllegroFlare::Screens::GameOverScreen &get_game_over_screen_ref();
         AllegroFlare::Screens::GameWonScreen &get_game_won_screen_ref();
         AllegroFlare::Screens::Storyboard &get_game_won_outro_storyboard_screen_ref();
         AllegroFlare::Screens::SettingsScreen &get_settings_screen_ref();
         AllegroFlare::Screens::RollingCredits &get_rolling_credits_screen_ref();
         virtual void game_event_func(AllegroFlare::GameEvent* game_event=nullptr) override;
         void initialize();
         virtual void destroy() override;
         int get_current_save_profile_id();
         void set_current_save_profile_id(int current_save_profile_id=1);
         static bool on_route_event_unhandled_func(uint32_t unhandled_event=0, AllegroFlare::Routers::Standard* router=nullptr, void* user_data=nullptr);
         static bool on_gameplay_paused_func(AllegroFlare::Routers::Standard* router=nullptr, void* user_data=nullptr);
         static bool on_gameplay_unpaused_func(AllegroFlare::Routers::Standard* router=nullptr, void* user_data=nullptr);
         static bool on_primary_gameplay_screen_finished_func(AllegroFlare::Routers::Standard* router=nullptr, void* user_data=nullptr);
         static bool on_arbitrary_storyboard_screen_finished_func(AllegroFlare::Routers::Standard* router=nullptr, void* user_data=nullptr);
         static bool on_arbitrary_storyboard_screen_activated_func(AllegroFlare::Routers::Standard* router=nullptr, void* user_data=nullptr);
         void setup_router();
         static void run(AllegroFlare::GameConfigurations::Complete* game_configuration=nullptr, std::string deployment_environment_mode="[unset-deployment_environment_mode]");
      };
   }
}



