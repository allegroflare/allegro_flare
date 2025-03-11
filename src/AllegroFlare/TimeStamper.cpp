

#include <AllegroFlare/TimeStamper.hpp>

#include <ctime>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{


TimeStamper::TimeStamper()
{
}


TimeStamper::~TimeStamper()
{
}


std::string TimeStamper::generate_now_timestamp_utc()
{
   std::time_t time_now = std::time(nullptr);
   std::stringstream result;
   //result << std::put_time(std::localtime(&time_now), "%y%m%d%OH%OM%OS%Z");
   result << std::put_time(std::gmtime(&time_now), "%y%m%d%OH%OM%OS%Z");
   return result.str();
}

std::string TimeStamper::to_iso_8601_time_str(std::tm* time_obj)
{
   if (!(time_obj))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::TimeStamper::to_iso_8601_time_str]: error: guard \"time_obj\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::TimeStamper::to_iso_8601_time_str]: error: guard \"time_obj\" not met");
   }
   // Convert time to string
   std::ostringstream oss;
   oss << std::put_time(time_obj, "%Y-%m-%dT%H:%M:%S");

   // Get timezone offset
   char tz_buffer[6]; // HHMM format
   std::strftime(tz_buffer, sizeof(tz_buffer), "%z", time_obj);

   // Format timezone as HH:MM
   std::string tz_str = std::string(tz_buffer);
   tz_str.insert(3, ":");  // Insert ':' to match ISO 8601 format

   return oss.str() + tz_str;
}

std::tuple<bool, std::tm, int> TimeStamper::str_to_iso_8601_time(std::string iso_time)
{
   if (!((!iso_time.empty())))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::TimeStamper::str_to_iso_8601_time]: error: guard \"(!iso_time.empty())\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::TimeStamper::str_to_iso_8601_time]: error: guard \"(!iso_time.empty())\" not met");
   }
   std::istringstream iss(iso_time);
   std::tm parsed_tm{};
   char separator;

   // Read date and time parts
   if (!(iss >> std::get_time(&parsed_tm, "%Y-%m-%dT%H:%M:%S")))
   {
      return { false, std::tm(), 0 };
      //throw std::runtime_error("Failed to parse date/time");
   }

   // Read timezone offset
   int tz_hour = 0, tz_minute = 0;
   char tz_sign = '+', tz_colon = ':';

   if (!(iss >> tz_sign >> tz_hour >> tz_colon >> tz_minute) || tz_colon != ':')
   {
      return { false, std::tm(), 0 };
      //throw std::runtime_error("Failed to parse timezone");
   }

   // Calculate timezone offset in seconds
   int tz_offset_seconds = (tz_hour * 3600 + tz_minute * 60) * (tz_sign == '-' ? -1 : 1);

   return {true, parsed_tm, tz_offset_seconds};
}

std::tm TimeStamper::create_local_time_now()
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


