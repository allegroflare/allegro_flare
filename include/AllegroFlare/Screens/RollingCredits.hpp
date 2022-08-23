#pragma once


#include <AllegroFlare/Elements/RollingCredits/RollingCredits.hpp>
#include <AllegroFlare/Elements/RollingCredits/Sections/Base.hpp>
#include <AllegroFlare/EventEmitter.hpp>
#include <AllegroFlare/FontBin.hpp>
#include <AllegroFlare/Screens/Base.hpp>
#include <string>
#include <vector>


namespace AllegroFlare
{
   namespace Screens
   {
      class RollingCredits : public AllegroFlare::Screens::Base
      {
      private:
         AllegroFlare::FontBin* font_bin;
         AllegroFlare::EventEmitter* event_emitter;
         AllegroFlare::Elements::RollingCredits::RollingCredits rolling_credits_component;
         float surface_width;
         float surface_height;
         float y_offset;
         float y_speed;
         float cached_calculated_height;
         std::string game_event_name_to_emit_after_completing;
         bool scroll_is_past_end;
         bool initialized;

      public:
         RollingCredits(AllegroFlare::FontBin* font_bin=nullptr, AllegroFlare::EventEmitter* event_emitter=nullptr, AllegroFlare::Elements::RollingCredits::RollingCredits rolling_credits_component={}, float surface_width=1920, float surface_height=1080, std::string game_event_name_to_emit_after_completing="rolling_credits_finished");
         virtual ~RollingCredits();

         void set_event_emitter(AllegroFlare::EventEmitter* event_emitter);
         void set_surface_width(float surface_width);
         void set_surface_height(float surface_height);
         void set_y_offset(float y_offset);
         void set_y_speed(float y_speed);
         void set_game_event_name_to_emit_after_completing(std::string game_event_name_to_emit_after_completing);
         AllegroFlare::Elements::RollingCredits::RollingCredits get_rolling_credits_component();
         float get_surface_width();
         float get_surface_height();
         float get_y_offset();
         float get_y_speed();
         float get_cached_calculated_height();
         std::string get_game_event_name_to_emit_after_completing();
         bool get_scroll_is_past_end();
         AllegroFlare::Elements::RollingCredits::RollingCredits &get_rolling_credits_component_ref();
         float &get_y_offset_ref();
         float &get_y_speed_ref();
         virtual void on_activate() override;
         void set_font_bin(AllegroFlare::FontBin* font_bin=nullptr);
         void set_sections(std::vector<AllegroFlare::Elements::RollingCredits::Sections::Base*> sections={});
         void initialize();
         void update();
         void emit_completion_event();
         void render();
         virtual void primary_timer_func() override;
      };
   }
}



