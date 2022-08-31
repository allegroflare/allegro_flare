

#include <AllegroFlare/TimeStamper.hpp>

#include <ctime>
#include <iomanip>
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


} // namespace AllegroFlare


