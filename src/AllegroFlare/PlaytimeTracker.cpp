

#include <AllegroFlare/PlaytimeTracker.hpp>

#include <AllegroFlare/TimerFormatter.hpp>
#include <sstream>


namespace AllegroFlare
{


PlaytimeTracker::PlaytimeTracker()
   : previous_accumulated_playtime_msec({})
   , current_playtime_timer({})
{
}


PlaytimeTracker::~PlaytimeTracker()
{
}


std::chrono::milliseconds PlaytimeTracker::get_previous_accumulated_playtime_msec() const
{
   return previous_accumulated_playtime_msec;
}


void PlaytimeTracker::start()
{
   current_playtime_timer.start();
   return;
}

void PlaytimeTracker::pause()
{
   current_playtime_timer.pause();
   return;
}

void PlaytimeTracker::unpause()
{
   // TODO: Test this unpause works as expected to restart the tier
   current_playtime_timer.start();
   return;
}

std::chrono::milliseconds PlaytimeTracker::calculate_total_playtime()
{
   std::chrono::milliseconds current_playtime(current_playtime_timer.get_elapsed_time_milliseconds());
   return previous_accumulated_playtime_msec + current_playtime;
}

std::string PlaytimeTracker::formatted_current_total_playtime_hms()
{
   // NOTE: Will appear as "2h 42m 12s", and will not include hours if it is 0.
   // TODO: Test this works with very large numbers like 800+ hours
   AllegroFlare::TimerFormatter timer_formatter(calculate_total_playtime().count());
   return timer_formatter.format_hms();
}

std::string PlaytimeTracker::to_string()
{
   return milliseconds_to_string(calculate_total_playtime());
}

void PlaytimeTracker::from_string(std::string milliseconds_str)
{
   previous_accumulated_playtime_msec = milliseconds_from_string(milliseconds_str);
   current_playtime_timer.stop();
   current_playtime_timer.reset();
}

std::string PlaytimeTracker::milliseconds_to_string(std::chrono::milliseconds milliseconds)
{
   std::stringstream ss;
   ss << milliseconds.count();
   return ss.str();
}

std::chrono::milliseconds PlaytimeTracker::milliseconds_from_string(std::string milliseconds_str)
{
   std::stringstream ss(milliseconds_str);
   int64_t value;
   ss >> value;
   return std::chrono::milliseconds(value);
}


} // namespace AllegroFlare


