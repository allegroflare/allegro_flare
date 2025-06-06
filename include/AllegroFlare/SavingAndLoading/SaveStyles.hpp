#pragma once


#include <string>
#include <utility>
#include <vector>


namespace AllegroFlare
{
   namespace SavingAndLoading
   {
      class SaveStyles
      {
      public:

         enum class StartStyle
         {
            GAME_START_STYLE_UNDEF = 0,
            GAME_START_STYLE_A,
            GAME_START_STYLE_B,
            GAME_START_STYLE_C,
            GAME_START_STYLE_D,
            GAME_START_STYLE_E,
            GAME_START_STYLE_F,
            GAME_START_STYLE_G,
         };
         enum class SaveStyle
         {
            GAME_SAVE_STYLE_UNDEF = 0,
            GAME_SAVE_STYLE_1,
            GAME_SAVE_STYLE_2,
            GAME_SAVE_STYLE_3,
            GAME_SAVE_STYLE_4,
            GAME_SAVE_STYLE_5,
            GAME_SAVE_STYLE_6,
            GAME_SAVE_STYLE_7,
            GAME_SAVE_STYLE_8,
            GAME_SAVE_STYLE_9,
         };
         enum class LoadStyle
         {
            GAME_LOAD_STYLE_UNDEF = 0,
            GAME_LOAD_STYLE_0,
            GAME_LOAD_STYLE_1,
            GAME_LOAD_STYLE_2,
            GAME_LOAD_STYLE_3,
            GAME_LOAD_STYLE_4,
            GAME_LOAD_STYLE_5,
            GAME_LOAD_STYLE_6,
            GAME_LOAD_STYLE_7,
            GAME_LOAD_STYLE_8,
         };
      private:
         AllegroFlare::SavingAndLoading::SaveStyles::StartStyle start_style;
         AllegroFlare::SavingAndLoading::SaveStyles::SaveStyle save_style;
         AllegroFlare::SavingAndLoading::SaveStyles::LoadStyle load_style;
         bool initialized;

      protected:


      public:
         SaveStyles(AllegroFlare::SavingAndLoading::SaveStyles::StartStyle start_style=AllegroFlare::SavingAndLoading::SaveStyles::StartStyle::GAME_START_STYLE_UNDEF, AllegroFlare::SavingAndLoading::SaveStyles::SaveStyle save_style=AllegroFlare::SavingAndLoading::SaveStyles::SaveStyle::GAME_SAVE_STYLE_UNDEF, AllegroFlare::SavingAndLoading::SaveStyles::LoadStyle load_style=AllegroFlare::SavingAndLoading::SaveStyles::LoadStyle::GAME_LOAD_STYLE_UNDEF);
         ~SaveStyles();

         void set_start_style(AllegroFlare::SavingAndLoading::SaveStyles::StartStyle start_style);
         void set_save_style(AllegroFlare::SavingAndLoading::SaveStyles::SaveStyle save_style);
         void set_load_style(AllegroFlare::SavingAndLoading::SaveStyles::LoadStyle load_style);
         AllegroFlare::SavingAndLoading::SaveStyles::StartStyle get_start_style() const;
         AllegroFlare::SavingAndLoading::SaveStyles::SaveStyle get_save_style() const;
         AllegroFlare::SavingAndLoading::SaveStyles::LoadStyle get_load_style() const;
         bool get_initialized() const;
         void initialize();
         std::vector<std::pair<std::string, std::string>> obtain_context_sensitive_menu_items_for_starting_or_loading_the_game();
         bool infer_existing_save_data_exists();
      };
   }
}



