

#include <AllegroFlare/TimeAgo.hpp>

#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{


TimeAgo::TimeAgo()
{
}


TimeAgo::~TimeAgo()
{
}


std::string TimeAgo::time_ago(std::tm* past, std::tm* current)
{
   if (!(past))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::TimeAgo::time_ago]: error: guard \"past\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::TimeAgo::time_ago]: error: guard \"past\" not met");
   }
   if (!(current))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::TimeAgo::time_ago]: error: guard \"current\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::TimeAgo::time_ago]: error: guard \"current\" not met");
   }
   std::time_t past_time = std::mktime(const_cast<std::tm*>(past));
   std::time_t current_time = std::mktime(const_cast<std::tm*>(current));

   double seconds = std::difftime(current_time, past_time);

   if (seconds < 0)
   {
      return "Invalid time (future date)";
   }

   struct TimeUnit
   {
      const char* name;
      int duration;
   };

   static const TimeUnit time_units[] = {
      {"year", 31536000},
      {"month", 2592000},
      {"week", 604800},
      {"day", 86400},
      {"hour", 3600},
      {"minute", 60},
      {"second", 1}
   };

   for (const auto& unit : time_units)
   {
      int value = static_cast<int>(seconds / unit.duration);
      if (value >= 1)
      {
         std::ostringstream oss;
         oss << value << " " << unit.name << (value > 1 ? "s" : "") << " ago";
         return oss.str();
      }
   }

   return "Just now";
}

std::tm TimeAgo::create_local_time_now()
{
   // Get current time
   std::time_t t = std::time(nullptr);
   std::tm local_tm = *std::localtime(&t);
   return local_tm;

   // Convert to ISO 8601 string
   //std::string iso_time = get_iso_8601_time(local_tm);
   //std::cout << "Generated ISO 8601 time: " << iso_time << std::endl;
   //return;
}


} // namespace AllegroFlare


