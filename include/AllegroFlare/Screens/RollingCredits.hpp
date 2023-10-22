#pragma once


#include <AllegroFlare/Elements/RollingCredits/RollingCredits.hpp>
#include <AllegroFlare/Elements/RollingCredits/Sections/Base.hpp>
#include <AllegroFlare/EventEmitter.hpp>
#include <AllegroFlare/FontBin.hpp>
#include <AllegroFlare/Screens/Base.hpp>
#include <AllegroFlare/Screens/RollingCredits.hpp>
#include <cstdint>
#include <functional>
#include <string>
#include <vector>


namespace AllegroFlare
{
   namespace Screens
   {
      class RollingCredits : public AllegroFlare::Screens::Base
      {
      public:
         static constexpr char* DEFAULT_GAME_EVENT_NAME_TO_EMIT_AFTER_COMPLETING = (char*)"rolling_credits_finished";
         static constexpr uint32_t DEFAULT_ROUTE_EVENT_TO_EMIT_AFTER_COMPLETING = 0;

      private:
         AllegroFlare::FontBin* font_bin;
         AllegroFlare::EventEmitter* event_emitter;
         AllegroFlare::Elements::RollingCredits::RollingCredits rolling_credits_component;
         float surface_width;
         float surface_height;
         float y_offset;
         float y_speed;
         std::function<void(AllegroFlare::Screens::RollingCredits*, void*)> on_finished_callback_func;
         void* on_finished_callback_func_user_data;
         float cached_calculated_height;
         std::string game_event_name_to_emit_after_completing;
         uint32_t route_event_to_emit_after_completing;
         bool scroll_is_past_end;
         bool initialized;
         void emit_completion_event();

      protected:


      public:
         RollingCredits(AllegroFlare::FontBin* font_bin=nullptr, AllegroFlare::EventEmitter* event_emitter=nullptr, AllegroFlare::Elements::RollingCredits::RollingCredits rolling_credits_component={}, float surface_width=1920, float surface_height=1080, std::string game_event_name_to_emit_after_completing=DEFAULT_GAME_EVENT_NAME_TO_EMIT_AFTER_COMPLETING, uint32_t route_event_to_emit_after_completing=DEFAULT_ROUTE_EVENT_TO_EMIT_AFTER_COMPLETING);
         virtual ~RollingCredits();

         void set_event_emitter(AllegroFlare::EventEmitter* event_emitter);
         void set_surface_width(float surface_width);
         void set_surface_height(float surface_height);
         void set_y_offset(float y_offset);
         void set_y_speed(float y_speed);
         void set_on_finished_callback_func(std::function<void(AllegroFlare::Screens::RollingCredits*, void*)> on_finished_callback_func);
         void set_on_finished_callback_func_user_data(void* on_finished_callback_func_user_data);
         void set_game_event_name_to_emit_after_completing(std::string game_event_name_to_emit_after_completing);
         void set_route_event_to_emit_after_completing(uint32_t route_event_to_emit_after_completing);
         AllegroFlare::Elements::RollingCredits::RollingCredits get_rolling_credits_component() const;
         float get_surface_width() const;
         float get_surface_height() const;
         float get_y_offset() const;
         float get_y_speed() const;
         std::function<void(AllegroFlare::Screens::RollingCredits*, void*)> get_on_finished_callback_func() const;
         void* get_on_finished_callback_func_user_data() const;
         float get_cached_calculated_height() const;
         std::string get_game_event_name_to_emit_after_completing() const;
         uint32_t get_route_event_to_emit_after_completing() const;
         bool get_scroll_is_past_end() const;
         AllegroFlare::Elements::RollingCredits::RollingCredits &get_rolling_credits_component_ref();
         float &get_y_offset_ref();
         float &get_y_speed_ref();
         virtual void on_activate() override;
         virtual void on_deactivate() override;
         void set_font_bin(AllegroFlare::FontBin* font_bin=nullptr);
         void set_sections(std::vector<AllegroFlare::Elements::RollingCredits::Sections::Base*> sections={});
         void append_section(AllegroFlare::Elements::RollingCredits::Sections::Base* section_to_append=nullptr);
         void append_sections(std::vector<AllegroFlare::Elements::RollingCredits::Sections::Base*> sections={});
         void clear_game_event_name_to_emit_after_completing();
         void clear_route_event_to_emit_after_completing();
         void initialize();
         void update();
         void render();
         virtual void primary_timer_func() override;
      };
   }
}



