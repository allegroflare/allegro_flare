#pragma once


#include <AllegroFlare/Elements/Storyboard.hpp>
#include <AllegroFlare/EventEmitter.hpp>
#include <AllegroFlare/FontBin.hpp>
#include <AllegroFlare/Player.hpp>
#include <AllegroFlare/Screens/Base.hpp>
#include <AllegroFlare/Screens/Storyboard.hpp>
#include <AllegroFlare/VirtualControllers/Base.hpp>
#include <cstdint>
#include <functional>
#include <string>


namespace AllegroFlare
{
   namespace Screens
   {
      class Storyboard : public AllegroFlare::Screens::Base
      {
      public:
         static constexpr char* DEFAULT_GAME_EVENT_NAME_TO_EMIT_AFTER_COMPLETING = (char*)"storyboard_finished";
         static constexpr uint32_t DEFAULT_ROUTE_EVENT_TO_EMIT_AFTER_COMPLETING = 0;

      private:
         AllegroFlare::EventEmitter* event_emitter;
         AllegroFlare::FontBin* font_bin;
         AllegroFlare::Elements::Storyboard storyboard_element;
         std::function<void(AllegroFlare::Screens::Storyboard*, void*)> on_finished_callback_func;
         void* on_finished_callback_func_user_data;
         bool auto_advance;
         std::string game_event_name_to_emit_after_completing;
         uint32_t route_event_to_emit_after_completing;
         bool initialized;
         void emit_completion_event();
         void advance();

      protected:


      public:
         Storyboard(AllegroFlare::EventEmitter* event_emitter=nullptr, AllegroFlare::FontBin* font_bin=nullptr, std::string game_event_name_to_emit_after_completing=DEFAULT_GAME_EVENT_NAME_TO_EMIT_AFTER_COMPLETING, uint32_t route_event_to_emit_after_completing=DEFAULT_ROUTE_EVENT_TO_EMIT_AFTER_COMPLETING);
         virtual ~Storyboard();

         void set_event_emitter(AllegroFlare::EventEmitter* event_emitter);
         void set_font_bin(AllegroFlare::FontBin* font_bin);
         void set_on_finished_callback_func(std::function<void(AllegroFlare::Screens::Storyboard*, void*)> on_finished_callback_func);
         void set_on_finished_callback_func_user_data(void* on_finished_callback_func_user_data);
         void set_auto_advance(bool auto_advance);
         void set_game_event_name_to_emit_after_completing(std::string game_event_name_to_emit_after_completing);
         void set_route_event_to_emit_after_completing(uint32_t route_event_to_emit_after_completing);
         std::function<void(AllegroFlare::Screens::Storyboard*, void*)> get_on_finished_callback_func() const;
         void* get_on_finished_callback_func_user_data() const;
         bool get_auto_advance() const;
         std::string get_game_event_name_to_emit_after_completing() const;
         uint32_t get_route_event_to_emit_after_completing() const;
         AllegroFlare::Elements::Storyboard &get_storyboard_element_ref();
         void initialize();
         virtual void on_activate() override;
         virtual void on_deactivate() override;
         virtual void primary_timer_func() override;
         void clear_game_event_name_to_emit_after_completing();
         void clear_route_event_to_emit_after_completing();
         virtual void virtual_control_button_down_func(AllegroFlare::Player* player=nullptr, AllegroFlare::VirtualControllers::Base* virtual_controller=nullptr, int virtual_controller_button_num=0, bool is_repeat=false) override;
      };
   }
}



