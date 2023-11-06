#pragma once


#include <AllegroFlare/BitmapBin.hpp>
#include <AllegroFlare/Elements/Backgrounds/Base.hpp>
#include <AllegroFlare/EventEmitter.hpp>
#include <AllegroFlare/FontBin.hpp>
#include <AllegroFlare/Frameworks/Full.hpp>
#include <AllegroFlare/GameConfigurations/Complete.hpp>
#include <AllegroFlare/GameEvent.hpp>
#include <AllegroFlare/LoadASavedGame/Screen.hpp>
#include <AllegroFlare/ModelBin.hpp>
#include <AllegroFlare/Routers/Standard.hpp>
#include <AllegroFlare/Screens/Achievements.hpp>
#include <AllegroFlare/Screens/Base.hpp>
#include <AllegroFlare/Screens/GameOverScreen.hpp>
#include <AllegroFlare/Screens/GameWonScreen.hpp>
#include <AllegroFlare/Screens/Gameplay.hpp>
#include <AllegroFlare/Screens/LevelSelectScreen.hpp>
#include <AllegroFlare/Screens/RollingCredits.hpp>
#include <AllegroFlare/Screens/SettingsScreen.hpp>
#include <AllegroFlare/Screens/Storyboard.hpp>
#include <AllegroFlare/Screens/TitleScreen.hpp>
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
         AllegroFlare::ModelBin* model_bin;
         AllegroFlare::Routers::Standard router;
         AllegroFlare::Screens::Storyboard intro_logos_screen;
         AllegroFlare::Screens::Storyboard intro_storyboard_screen;
         AllegroFlare::Screens::TitleScreen title_screen;
         AllegroFlare::Screens::Achievements achievements_screen;
         AllegroFlare::Screens::Version version_screen;
         AllegroFlare::LoadASavedGame::Screen load_a_saved_game_screen;
         AllegroFlare::Screens::Storyboard new_game_intro_storyboard_screen;
         AllegroFlare::Screens::LevelSelectScreen level_select_screen;
         AllegroFlare::Screens::GameOverScreen game_over_screen;
         AllegroFlare::Screens::GameWonScreen game_won_screen;
         AllegroFlare::Screens::Storyboard game_won_outro_storyboard_screen;
         AllegroFlare::Screens::SettingsScreen settings_screen;
         AllegroFlare::Screens::RollingCredits rolling_credits_screen;
         AllegroFlare::Screens::Gameplay primary_gameplay_screen;
         AllegroFlare::GameConfigurations::Complete* game_configuration;
         AllegroFlare::Elements::Backgrounds::Base* shared_background;
         ReleaseInfo release_info;
         bool initialized;

      protected:


      public:
         Complete(AllegroFlare::Frameworks::Full* framework=nullptr, AllegroFlare::EventEmitter* event_emitter=nullptr, AllegroFlare::BitmapBin* bitmap_bin=nullptr, AllegroFlare::FontBin* font_bin=nullptr, AllegroFlare::ModelBin* model_bin=nullptr);
         virtual ~Complete();

         AllegroFlare::GameConfigurations::Complete* create_game_configuration();
         void handle_game_event(AllegroFlare::GameEvent* game_event=nullptr);
         virtual void game_event_func(AllegroFlare::GameEvent* game_event=nullptr) override;
         void initialize();
         static bool on_route_event_unhandled_func(uint32_t unhandled_event=0, AllegroFlare::Routers::Standard* router=nullptr, void* user_data=nullptr);
         void setup_router();
         static void run(std::string deployment_environment_mode="[unset-deployment_environment_mode]");
      };
   }
}



