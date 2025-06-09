

#include <AllegroFlare/TimeStamper.hpp>

#include <ctime>
#include <iomanip>
#include <mutex>
#include <sstream>


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

std::string TimeStamper::generate_time_now_utc_iso8601()
{
   std::time_t time_now = generate_time_now_since_epoch();
   std::stringstream result;
   result << std::put_time(std::gmtime(&time_now), "%Y-%m-%dT%H:%M:%SZ");
   return result.str();
}

std::time_t TimeStamper::generate_time_now_since_epoch()
{
   return std::time(nullptr);
}

std::string TimeStamper::user_friendly_time(std::time_t time_)
{
   static std::mutex localtime_mutex;
   std::tm local_tm;

   { // These braces ensure the mutex lock is released immediately after copying the std::tm
      std::lock_guard<std::mutex> lock(localtime_mutex);
      std::tm* tmp = std::localtime(&time_);
      if (!tmp)
      {
         return "Error formatting time";
      }
      local_tm = *tmp;
   }

   std::ostringstream oss;
   oss << std::put_time(&local_tm, "%B %d %Y %I:%M:%S %p");
   return oss.str();
}


} // namespace AllegroFlare


