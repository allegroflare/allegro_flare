

#include <AllegroFlare/TimeAgo.hpp>

#include <ctime>


namespace AllegroFlare
{


TimeAgo::TimeAgo()
{
}


TimeAgo::~TimeAgo()
{
}


std::pair<std::time_t, std::string> TimeAgo::time_ago(std::time_t past_time, std::time_t current_time)
{
   //std::time_t current_time = std::time(0);
   double diff_seconds = difftime(current_time, past_time);

   // Calculate time difference in different units
   const int seconds_in_minute = 60;
   const int seconds_in_hour = 3600;
   const int seconds_in_day = 86400;
   const int seconds_in_month = 2592000; // Approximation (30 days)
   const int seconds_in_year = 31536000; // Approximation (365 days)

   const int margin_of_error_for_just_now = 14; // 0-14 seconds is "Just now", 15 seconds is "15 seconds ago"

   if (diff_seconds < 0)
   {
      return { 0, "Invalid time (future date)" };
   }
   else if (diff_seconds <= margin_of_error_for_just_now)
   {
      return { 0, "Just now" };
   }
   else if (diff_seconds < seconds_in_minute)
   {
      //return std::to_string(static_cast<int>(diff_seconds)) + " seconds ago";
      return { diff_seconds, format(static_cast<int>(diff_seconds), "second") };
      //return std::to_string(static_cast<int>(diff_seconds)) + " seconds ago";
   }
   else if (diff_seconds < seconds_in_hour)
   {
      //return std::to_string(static_cast<int>(diff_seconds / seconds_in_minute)) + " minutes ago";
      return { diff_seconds, format(static_cast<int>(diff_seconds / seconds_in_minute), "minute") };
   }
   else if (diff_seconds < seconds_in_day)
   {
      //return std::to_string(static_cast<int>(diff_seconds / seconds_in_hour)) + " hours ago";
      return { diff_seconds, format(static_cast<int>(diff_seconds / seconds_in_hour), "hour") };
   }
   else if (diff_seconds < seconds_in_month)
   {
      //return std::to_string(static_cast<int>(diff_seconds / seconds_in_day)) + " days ago";
      return { diff_seconds, format(static_cast<int>(diff_seconds / seconds_in_day), "day") };
   }
   else if (diff_seconds < seconds_in_year)
   {
      //return std::to_string(static_cast<int>(diff_seconds / seconds_in_month)) + " months ago";
      return { diff_seconds, format(static_cast<int>(diff_seconds / seconds_in_month), "month") };
   }
   else
   {
      //return std::to_string(static_cast<int>(diff_seconds / seconds_in_year)) + " years ago";
      return { diff_seconds, format(static_cast<int>(diff_seconds / seconds_in_year), "year") };
   }

   // TODO: Consider throwing error

   return { 0, "Error" };
}

std::time_t TimeAgo::generate_time_now_since_epoch()
{
   return std::time(nullptr);
}

std::string TimeAgo::format(int value, std::string unit)
{
   return std::to_string(value) + " " + unit + (value == 1 ? "" : "s") + " ago";
}


} // namespace AllegroFlare


