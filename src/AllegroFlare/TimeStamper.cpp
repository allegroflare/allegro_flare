

#include <AllegroFlare/TimeStamper.hpp>

#include <ctime>
#include <iomanip>
#include <sstream>
#include <time.h>


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
   // For Windows (Mingw32), localtime_r does not exist. This hack is suggested in the following stack overflow:
   // https://stackoverflow.com/questions/18551409/localtime-r-support-on-mingw
   #if defined(_MSC_VER)
   #   define localtime_r(T,Tm) (localtime_s(Tm,T) ? NULL : Tm)
   #endif

   std::tm local_tm;
   localtime_r(&time_, &local_tm); // Thread-safe version of std::localtime

   std::ostringstream oss;
   oss << std::put_time(&local_tm, "%B %d %Y %I:%M:%S %p"); // Format: "June 13, 2025 4:50 PM"
   return oss.str();
}


} // namespace AllegroFlare


