

#include <AllegroFlare/SyncOracle.hpp>

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <cmath>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{


SyncOracle::SyncOracle()
   : display(nullptr)
   , primary_event_queue(nullptr)
   , primary_timer(nullptr)
   , primary_timer_is_active(false)
   , hyper_primary_timer(nullptr)
   , target_fps(60)
   , display_refresh_rate(0)
   , num_nudge_notches(16)
   , num_hyper_primary_timer_units(32)
   , hyper_primary_timer_is_active(false)
   , auto_nudge_is_active(false)
   , num_measurer_samples(64*4)
   , primary_timer_measurer({})
   , update_measurer({})
   , draw_measurer({})
   , flip_display_measurer({})
   , font(nullptr)
   , initialized(false)
{
}


SyncOracle::~SyncOracle()
{
}


ALLEGRO_DISPLAY* SyncOracle::get_display() const
{
   return display;
}


ALLEGRO_EVENT_QUEUE* SyncOracle::get_primary_event_queue() const
{
   return primary_event_queue;
}


bool SyncOracle::get_primary_timer_is_active() const
{
   return primary_timer_is_active;
}


int SyncOracle::get_target_fps() const
{
   return target_fps;
}


int SyncOracle::get_num_nudge_notches() const
{
   return num_nudge_notches;
}


int SyncOracle::get_num_hyper_primary_timer_units() const
{
   return num_hyper_primary_timer_units;
}


bool SyncOracle::get_hyper_primary_timer_is_active() const
{
   return hyper_primary_timer_is_active;
}


bool SyncOracle::get_auto_nudge_is_active() const
{
   return auto_nudge_is_active;
}


int SyncOracle::get_num_measurer_samples() const
{
   return num_measurer_samples;
}


void SyncOracle::set_display(ALLEGRO_DISPLAY* display)
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::SyncOracle::set_display]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::SyncOracle::set_display]: error: guard \"(!initialized)\" not met");
   }
   this->display = display;
   return;
}

int SyncOracle::get_display_refresh_rate()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::SyncOracle::get_display_refresh_rate]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::SyncOracle::get_display_refresh_rate]: error: guard \"initialized\" not met");
   }
   return display_refresh_rate;
}

void SyncOracle::set_primary_event_queue(ALLEGRO_EVENT_QUEUE* primary_event_queue)
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::SyncOracle::set_primary_event_queue]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::SyncOracle::set_primary_event_queue]: error: guard \"(!initialized)\" not met");
   }
   this->primary_event_queue = primary_event_queue;
   return;
}

void SyncOracle::set_target_fps(int target_fps)
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::SyncOracle::set_target_fps]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::SyncOracle::set_target_fps]: error: guard \"(!initialized)\" not met");
   }
   if (!((target_fps > 0)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::SyncOracle::set_target_fps]: error: guard \"(target_fps > 0)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::SyncOracle::set_target_fps]: error: guard \"(target_fps > 0)\" not met");
   }
   if (!((target_fps <= 240)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::SyncOracle::set_target_fps]: error: guard \"(target_fps <= 240)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::SyncOracle::set_target_fps]: error: guard \"(target_fps <= 240)\" not met");
   }
   // NOTE: < 240 is just a safety limit, has not been tested at high values
   // TODO: Handle re-creation of timers when this changes
   this->target_fps = target_fps;
   return;
}

void SyncOracle::set_num_nudge_notches(int num_nudge_notches)
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::SyncOracle::set_num_nudge_notches]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::SyncOracle::set_num_nudge_notches]: error: guard \"(!initialized)\" not met");
   }
   if (!((num_nudge_notches > 2) && (num_nudge_notches < 32)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::SyncOracle::set_num_nudge_notches]: error: guard \"(num_nudge_notches > 2) && (num_nudge_notches < 32)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::SyncOracle::set_num_nudge_notches]: error: guard \"(num_nudge_notches > 2) && (num_nudge_notches < 32)\" not met");
   }
   // NOTE: < 32 is just for sanity, it's never been used/tested at numbers higher
   // TODO: Handle re-creation of timers when this changes
   this->num_nudge_notches = num_nudge_notches;
   return;
}

void SyncOracle::set_num_hyper_primary_timer_units(int num_hyper_primary_timer_units)
{
   if (!((!hyper_primary_timer_is_active)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::SyncOracle::set_num_hyper_primary_timer_units]: error: guard \"(!hyper_primary_timer_is_active)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::SyncOracle::set_num_hyper_primary_timer_units]: error: guard \"(!hyper_primary_timer_is_active)\" not met");
   }
   if (!((num_hyper_primary_timer_units > 2)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::SyncOracle::set_num_hyper_primary_timer_units]: error: guard \"(num_hyper_primary_timer_units > 2)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::SyncOracle::set_num_hyper_primary_timer_units]: error: guard \"(num_hyper_primary_timer_units > 2)\" not met");
   }
   if (!((num_hyper_primary_timer_units < 128)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::SyncOracle::set_num_hyper_primary_timer_units]: error: guard \"(num_hyper_primary_timer_units < 128)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::SyncOracle::set_num_hyper_primary_timer_units]: error: guard \"(num_hyper_primary_timer_units < 128)\" not met");
   }
   // NOTE: < 128 is just for sanity, it's never been used/tested at numbers higher
   // TODO: Handle re-creation of timers when this changes
   this->num_hyper_primary_timer_units = num_hyper_primary_timer_units;
   return;
}

void SyncOracle::set_num_measurer_samples(int num_measurer_samples)
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::SyncOracle::set_num_measurer_samples]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::SyncOracle::set_num_measurer_samples]: error: guard \"(!initialized)\" not met");
   }
   if (!((num_measurer_samples > 0) && (num_measurer_samples < 64*8)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::SyncOracle::set_num_measurer_samples]: error: guard \"(num_measurer_samples > 0) && (num_measurer_samples < 64*8)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::SyncOracle::set_num_measurer_samples]: error: guard \"(num_measurer_samples > 0) && (num_measurer_samples < 64*8)\" not met");
   }
   // NOTE: < 64*8 is just for sanity, it's never been used/tested at numbers higher
   // TODO: Handle re-creation of timers when this changes
   this->num_measurer_samples = num_measurer_samples;
   return;
}

void SyncOracle::initialize()
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::SyncOracle::initialize]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::SyncOracle::initialize]: error: guard \"(!initialized)\" not met");
   }
   if (!(display))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::SyncOracle::initialize]: error: guard \"display\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::SyncOracle::initialize]: error: guard \"display\" not met");
   }
   if (!(primary_event_queue))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::SyncOracle::initialize]: error: guard \"primary_event_queue\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::SyncOracle::initialize]: error: guard \"primary_event_queue\" not met");
   }
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::SyncOracle::initialize]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::SyncOracle::initialize]: error: guard \"al_is_system_installed()\" not met");
   }
   if (!(al_is_font_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::SyncOracle::initialize]: error: guard \"al_is_font_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::SyncOracle::initialize]: error: guard \"al_is_font_addon_initialized()\" not met");
   }
   // Setup the timer
   primary_timer = al_create_timer(calculate_frame_duration_sec());
   al_register_event_source(primary_event_queue, al_get_timer_event_source(primary_timer));

   // Setup our instrumentation
   primary_timer_measurer.set_size(num_measurer_samples);
   primary_timer_measurer.initialize();
   update_measurer.set_size(num_measurer_samples);
   update_measurer.initialize();
   draw_measurer.set_size(num_measurer_samples);
   draw_measurer.initialize();
   flip_display_measurer.set_size(num_measurer_samples);
   flip_display_measurer.initialize();

   // Load our font
   font = al_create_builtin_font();

   // Extract our display info
   display_refresh_rate = al_get_display_refresh_rate(display);

   initialized = true;
   return;
}

void SyncOracle::activate_primary_timer()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::SyncOracle::activate_primary_timer]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::SyncOracle::activate_primary_timer]: error: guard \"initialized\" not met");
   }
   if (primary_timer_is_active) return;
   al_start_timer(primary_timer);
   primary_timer_is_active = true;
   return;
}

void SyncOracle::deactivate_primary_timer()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::SyncOracle::deactivate_primary_timer]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::SyncOracle::deactivate_primary_timer]: error: guard \"initialized\" not met");
   }
   if (!primary_timer_is_active) return;
   al_stop_timer(primary_timer);
   primary_timer_is_active = false;
   return;
}

void SyncOracle::shutdown()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::SyncOracle::shutdown]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::SyncOracle::shutdown]: error: guard \"initialized\" not met");
   }
   if (primary_timer)
   {
      if (primary_timer_is_active)
      {
         al_stop_timer(primary_timer);
         primary_timer_is_active = false;
      }
      al_unregister_event_source(primary_event_queue, al_get_timer_event_source(primary_timer));
      al_destroy_timer(primary_timer);
      primary_timer = nullptr;
   }

   if (hyper_primary_timer)
   {
      al_stop_timer(hyper_primary_timer);
      al_destroy_timer(hyper_primary_timer);
      hyper_primary_timer = nullptr;
      hyper_primary_timer_is_active = false;
   }

   al_destroy_font(font);

   initialized = false;
   return;
}

void SyncOracle::activate_hyper_timer()
{
   if (hyper_primary_timer_is_active) return;

   hyper_primary_timer = al_create_timer(calculate_frame_duration_sec() / num_hyper_primary_timer_units);
   al_start_timer(hyper_primary_timer);
   hyper_primary_timer_is_active = true;
   return;
}

void SyncOracle::deactivate_hyper_timer()
{
   if (!hyper_primary_timer_is_active) return;

   al_stop_timer(hyper_primary_timer);
   al_destroy_timer(hyper_primary_timer);
   hyper_primary_timer = nullptr;
   hyper_primary_timer_is_active = false;
   return;
}

void SyncOracle::toggle_hyper_timer()
{
   if (!hyper_primary_timer_is_active) activate_hyper_timer();
   else deactivate_hyper_timer();
   return;
}

void SyncOracle::activate_auto_nudge()
{
   if (auto_nudge_is_active) return;
   auto_nudge_is_active = true;
   return;
}

void SyncOracle::deactivate_auto_nudge()
{
   if (!auto_nudge_is_active) return;
   auto_nudge_is_active = false;
   return;
}

void SyncOracle::toggle_auto_nudge()
{
   if (!auto_nudge_is_active) activate_auto_nudge();
   else deactivate_auto_nudge();
   return;
}

bool SyncOracle::is_primary_timer_event(ALLEGRO_EVENT* al_event)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::SyncOracle::is_primary_timer_event]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::SyncOracle::is_primary_timer_event]: error: guard \"initialized\" not met");
   }
   if (!al_event) return false;
   return (al_event->type == ALLEGRO_EVENT_TIMER && al_event->timer.source == primary_timer);
}

void SyncOracle::capture_primary_timer_event_time(double timer_event_time)
{
   double modded = std::fmod(timer_event_time, calculate_frame_duration_sec());
   primary_timer_measurer.capture(modded);
   return;
}

void SyncOracle::start_flip_measure()
{
   flip_display_measurer.start_capture();
   return;
}

void SyncOracle::end_flip_measure()
{
   flip_display_measurer.end_capture();
   if (auto_nudge_is_active)
   {
      double most_recent_flip_duration = flip_display_measurer.get_last_metric();
      if (most_recent_flip_duration > calculate_frame_duration_sec())
      {
         // TODO: Track this autonudge
         nudge_primary_timer(-2);
      }
   }
}

void SyncOracle::start_update_measure()
{
   update_measurer.start_capture();
   return;
}

void SyncOracle::end_update_measure()
{
   update_measurer.end_capture();
}

void SyncOracle::start_draw_measure()
{
   draw_measurer.start_capture();
   return;
}

void SyncOracle::end_draw_measure()
{
   draw_measurer.end_capture();
}

double SyncOracle::calculate_frame_duration_sec()
{
   return 1.0 / target_fps;
}

double SyncOracle::calculate_duration_of_previous_frame_for_delta_time()
{
   return calculate_frame_duration_sec(); // TODO: Find out best way to calcualte this frame duration
}

int SyncOracle::calculate_practical_fps()
{
   // Practical FPS is the FPS that your game's operations (updating game state, drawing game state) are running at.
   // This is independent of any synchronization delays or offsets (which are managed by the SyncOracle).
   int average_over_n_samples = 20;

   double update_measurer_last_n_avg = update_measurer.average_of_last_n_metrics(average_over_n_samples);
   double draw_measurer_last_n_avg = draw_measurer.average_of_last_n_metrics(average_over_n_samples);

   double practical_duration_total = update_measurer_last_n_avg + draw_measurer_last_n_avg;

   return (int)(60.0 / practical_duration_total);
}

double SyncOracle::calculate_nudge_duration(int num_nudge_notches_delta)
{
   while (num_nudge_notches_delta < 0) num_nudge_notches_delta += num_nudge_notches;
   num_nudge_notches_delta = num_nudge_notches_delta % num_nudge_notches;
   return calculate_frame_duration_sec() / num_nudge_notches * num_nudge_notches_delta;
}

void SyncOracle::nudge_primary_timer(int num_nudge_notches_to_move)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::SyncOracle::nudge_primary_timer]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::SyncOracle::nudge_primary_timer]: error: guard \"initialized\" not met");
   }
   // TODO: Test this
   bool primary_timer_is_running = al_get_timer_started(primary_timer);
   if (!primary_timer_is_running) return;

   double offset = calculate_nudge_duration(num_nudge_notches_to_move);
   double primary_timer_speed = al_get_timer_speed(primary_timer);
   double offsetting_timer_speed = primary_timer_speed + offset;

   ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
   al_register_event_source(event_queue, al_get_timer_event_source(primary_timer));
   ALLEGRO_EVENT this_event;

   al_wait_for_event(event_queue, &this_event);
   al_set_timer_speed(primary_timer, offsetting_timer_speed);
   al_wait_for_event(event_queue, &this_event);
   al_set_timer_speed(primary_timer, primary_timer_speed);

   al_unregister_event_source(event_queue, al_get_timer_event_source(primary_timer));
   al_destroy_event_queue(event_queue);
   return;
}

void SyncOracle::nudge_primary_timer_forward()
{
   nudge_primary_timer(1);
   return;
}

void SyncOracle::nudge_primary_timer_backward()
{
   nudge_primary_timer(-1);
   return;
}

void SyncOracle::draw_graph()
{
   float x = 100;
   float y = 200;
   float h = 500;
   int x_scale = 4;
   double min = 0;
   double max = calculate_frame_duration_sec();
   float range = (max - min);
   std::vector<double> samples;

   ALLEGRO_COLOR white = ALLEGRO_COLOR{1.0, 1.0, 1.0, 1.0};
   ALLEGRO_COLOR primary_timer_color = ALLEGRO_COLOR{1.0, 0.4, 0.0, 1};
   ALLEGRO_COLOR update_color = ALLEGRO_COLOR{0.4, 0.4, 0.55, 1};
   ALLEGRO_COLOR draw_color = ALLEGRO_COLOR{0.3, 0.6, 0.9, 1};
   ALLEGRO_COLOR flip_display_color = ALLEGRO_COLOR{0, 1.0, 0.45, 1};

   al_draw_textf(font, primary_timer_color, x, y-20, 0, "primary_timer");
   al_draw_textf(font, update_color, x+150, y-20, 0, "update");
   al_draw_textf(font, draw_color, x+300, y-20, 0, "draw");
   al_draw_textf(font, flip_display_color, x+450, y-20, 0, "flip");

   // Draw the hyper_primary_timer status
   if (hyper_primary_timer_is_active)
   {
      al_draw_textf(font, white, x, y-60, 0, "hyper_primary_timer: ON");
   }
   else
   {
      al_draw_textf(font, white, x, y-60, 0, "hyper_primary_timer: OFF");
   }

   // Draw the auto_nudge status
   if (auto_nudge_is_active)
   {
      al_draw_textf(font, white, x, y-40, 0, "auto_nudge: ON");
   }
   else
   {
      al_draw_textf(font, white, x, y-40, 0, "auto_nudge: OFF");
   }

   // Draw our estimated "practical fps"
   {
      al_draw_textf(font, ALLEGRO_COLOR{1, 1, 1, 1}, x, y-80, 0, "practical fps:");
      al_draw_textf(font, ALLEGRO_COLOR{1, 1, 1, 1}, x+180, y-80, 0, "%d", calculate_practical_fps());
   }

   // Draw the primary_timer_measurer
   {
      ALLEGRO_COLOR color = primary_timer_color; //ALLEGRO_COLOR{1.0, 0.4, 0.0, 1};
      int num_samples = primary_timer_measurer.get_size();
      samples = primary_timer_measurer.get_last_n_metrics(num_samples);
      draw_metric(&samples, color, x, y, h, min, max, num_samples, x_scale);

      double avg = primary_timer_measurer.average_of_last_n_metrics(20);
      float nval = (avg - min) / range;
      float yy = y + (1.0 - nval) * h;
      draw_triangle(x-10, yy, 20, 18, color);
   }

   // Draw the update_measurer
   {
      ALLEGRO_COLOR color = update_color; //ALLEGRO_COLOR{0.5, 0.7, 0.8, 1};
      int num_samples = update_measurer.get_size();
      samples = update_measurer.get_last_n_metrics(num_samples);
      draw_metric(&samples, color, x, y, h, min, max, num_samples, x_scale);

      double avg = update_measurer.average_of_last_n_metrics(20);
      float nval = (avg - min) / range;
      float yy = y + (1.0 - nval) * h;
      draw_triangle(x-10, yy, 20, 18, color);
   }

   // Draw the draw_measurer
   {
      ALLEGRO_COLOR color = draw_color; //ALLEGRO_COLOR{0.3, 0.6, 0.9, 1};
      int num_samples = draw_measurer.get_size();
      samples = draw_measurer.get_last_n_metrics(num_samples);
      draw_metric(&samples, color, x, y, h, min, max, num_samples, x_scale);

      double avg = draw_measurer.average_of_last_n_metrics(20);
      float nval = (avg - min) / range;
      float yy = y + (1.0 - nval) * h;
      draw_triangle(x-10, yy, 20, 18, color);
   }

   // Draw the flip_display_measurer
   {
      ALLEGRO_COLOR color = flip_display_color; //ALLEGRO_COLOR{0, 1.0, 0.45, 1};
      int num_samples = flip_display_measurer.get_size();
      samples = flip_display_measurer.get_last_n_metrics(num_samples);
      draw_metric(&samples, color, x, y, h, min, max, num_samples, x_scale);

      double avg = flip_display_measurer.average_of_last_n_metrics(20);
      float nval = (avg - min) / range;
      float yy = y + (1.0 - nval) * h;
      draw_triangle(x-10, yy, 20, 18, color);
   }
   return;
}

void SyncOracle::draw_metric(std::vector<double>* samples, ALLEGRO_COLOR color, float x, float y, float h, float chart_min, float chart_max, int num_samples, int scale)
{
   if (!(al_get_current_display()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::SyncOracle::draw_metric]: error: guard \"al_get_current_display()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::SyncOracle::draw_metric]: error: guard \"al_get_current_display()\" not met");
   }
   if (!(al_is_primitives_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::SyncOracle::draw_metric]: error: guard \"al_is_primitives_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::SyncOracle::draw_metric]: error: guard \"al_is_primitives_addon_initialized()\" not met");
   }
   if (!(samples))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::SyncOracle::draw_metric]: error: guard \"samples\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::SyncOracle::draw_metric]: error: guard \"samples\" not met");
   }
   //float x_scale = 4.0; //w / num_samples; //3.0f; // IMPORTANT: Consider keeping this as an integer for visual
                                                   // pixel alignment making the motion smoother to read

   float w = num_samples * scale;

   float chart_range = (chart_max - chart_min);
   std::vector<ALLEGRO_VERTEX> v;
   v.resize(num_samples);
   //std::vector<double> samples = metric->get_last_n_metrics(num_samples);

   int i=0;
   for (auto &sample : *samples)
   {
      float chart_y = h - (sample / chart_range) * h;
      v[i] = ALLEGRO_VERTEX{
               .x = x+i*scale,
               .y = y + chart_y,
               .z = 0,
               .u = 0,
               .v = 0,
               .color = color,
            };
      i++;
   }
      
   al_draw_rectangle(x, y, x+w, y+h, ALLEGRO_COLOR{0.8, 0.2, 0.7, 1.0}, 1.0);
   al_draw_prim(&v[0], NULL, NULL, 0, v.size(), ALLEGRO_PRIM_LINE_STRIP);

   return;
}

void SyncOracle::draw_triangle(float x, float y, float width, float height, ALLEGRO_COLOR color)
{
   x -= width;
   y -= height * 0.5;
   al_draw_filled_triangle(x, y, x+width, y+height*0.5, x, y+height, color);
   return;
}


} // namespace AllegroFlare


