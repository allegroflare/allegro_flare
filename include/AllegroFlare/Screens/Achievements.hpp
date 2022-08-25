#pragma once


#include <AllegroFlare/Achievements.hpp>
#include <AllegroFlare/Elements/AchievementsList.hpp>
#include <AllegroFlare/EventEmitter.hpp>
#include <AllegroFlare/FontBin.hpp>
#include <AllegroFlare/Screens/Base.hpp>
#include <string>
#include <tuple>
#include <vector>


namespace AllegroFlare
{
   namespace Screens
   {
      class Achievements : public AllegroFlare::Screens::Base
      {
      private:
         AllegroFlare::FontBin* font_bin;
         AllegroFlare::EventEmitter* event_emitter;
         AllegroFlare::Achievements* achievements;
         float scrollbar_dest_position;
         AllegroFlare::Elements::AchievementsList achievements_list;
         std::string game_event_name_to_emit_on_return;
         bool initialized;

      public:
         Achievements(AllegroFlare::FontBin* font_bin=nullptr, AllegroFlare::EventEmitter* event_emitter=nullptr, AllegroFlare::Achievements* achievements=nullptr, float scrollbar_dest_position=0.0f, std::string game_event_name_to_emit_on_return="achievements_screen_finished");
         virtual ~Achievements();

         void set_achievements(AllegroFlare::Achievements* achievements);
         void set_game_event_name_to_emit_on_return(std::string game_event_name_to_emit_on_return);
         std::string get_game_event_name_to_emit_on_return() const;
         AllegroFlare::Elements::AchievementsList &get_achievements_list_ref();
         void set_font_bin(AllegroFlare::FontBin* font_bin=nullptr);
         void refresh_achievements_list();
         void set_event_emitter(AllegroFlare::EventEmitter* event_emitter=nullptr);
         virtual void on_activate() override;
         virtual void on_deactivate() override;
         void initialize();
         virtual void primary_timer_func() override;
         void update();
         void move_scrollbar_position_to(float position=0.0f);
         void move_scrollbar_position_up();
         void move_scrollbar_position_down();
         virtual void virtual_control_button_down_func(int player_num=0, int button_num=0, bool is_repeat=false) override;
         void render();
         void set_placeholder_achievements();
         std::vector<std::tuple<std::string, std::string, std::string>> build_achievements();
         void limit_scrollbar_dest_position();
         void emit_event_to_set_input_hints();
         bool infer_scrollbar_is_showing();
      };
   }
}



