#pragma once


#include <AllegroFlare/Instrumentation/DurationMeasurer.hpp>
#include <AllegroFlare/Instrumentation/Metrics/Double.hpp>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <vector>


namespace AllegroFlare
{
   class SyncOracle
   {
   private:
      ALLEGRO_DISPLAY* display;
      ALLEGRO_EVENT_QUEUE* primary_event_queue;
      ALLEGRO_TIMER* primary_timer;
      bool primary_timer_is_active;
      ALLEGRO_TIMER* hyper_primary_timer;
      int target_fps;
      int display_refresh_rate;
      int num_nudge_notches;
      int num_hyper_primary_timer_units;
      bool hyper_primary_timer_is_active;
      bool auto_nudge_is_active;
      int num_measurer_samples;
      AllegroFlare::Instrumentation::Metrics::Double primary_timer_measurer;
      AllegroFlare::Instrumentation::DurationMeasurer update_measurer;
      AllegroFlare::Instrumentation::DurationMeasurer draw_measurer;
      AllegroFlare::Instrumentation::DurationMeasurer flip_display_measurer;
      ALLEGRO_FONT* font;
      bool initialized;

   protected:


   public:
      SyncOracle();
      ~SyncOracle();

      ALLEGRO_DISPLAY* get_display() const;
      ALLEGRO_EVENT_QUEUE* get_primary_event_queue() const;
      bool get_primary_timer_is_active() const;
      int get_target_fps() const;
      int get_num_nudge_notches() const;
      int get_num_hyper_primary_timer_units() const;
      bool get_hyper_primary_timer_is_active() const;
      bool get_auto_nudge_is_active() const;
      int get_num_measurer_samples() const;
      void set_display(ALLEGRO_DISPLAY* display=nullptr);
      int get_display_refresh_rate();
      void set_primary_event_queue(ALLEGRO_EVENT_QUEUE* primary_event_queue=nullptr);
      void set_target_fps(int target_fps=60);
      void set_num_hyper_primary_timer_units(int num_hyper_primary_timer_units=32);
      void set_num_nudge_notches(int num_nudge_notches=16);
      void set_num_measurer_samples(int num_measurer_samples=64*4);
      void initialize();
      void activate_primary_timer();
      void deactivate_primary_timer();
      void shutdown();
      void activate_hyper_timer();
      void deactivate_hyper_timer();
      void toggle_hyper_timer();
      void activate_auto_nudge();
      void deactivate_auto_nudge();
      void toggle_auto_nudge();
      bool is_primary_timer_event(ALLEGRO_EVENT* al_event=nullptr);
      void capture_primary_timer_event_time(double timer_event_time=0.0);
      void start_flip_measure();
      void end_flip_measure();
      void start_update_measure();
      void end_update_measure();
      void start_draw_measure();
      void end_draw_measure();
      double calculate_frame_duration_sec();
      double calculate_duration_of_previous_frame_for_delta_time();
      int calculate_practical_fps();
      double calculate_nudge_duration(int num_nudge_notches_delta=1);
      void nudge_primary_timer(int num_nudge_notches_to_move=1);
      void nudge_primary_timer_forward();
      void nudge_primary_timer_backward();
      void draw_graph();
      static void draw_metric(std::vector<double>* samples=nullptr, ALLEGRO_COLOR color=ALLEGRO_COLOR{1, 1, 1, 1}, float x=0.0f, float y=0.0f, float h=0.0f, float chart_min=0.0f, float chart_max=0.0f, int num_samples=64*4, int scale=4);
      static void draw_triangle(float x=0.0f, float y=0.0f, float width=0.0f, float height=0.0f, ALLEGRO_COLOR color=ALLEGRO_COLOR{0.0f, 0.0f, 0.0f, 0.0f});
   };
}



