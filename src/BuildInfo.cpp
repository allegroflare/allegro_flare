

#include <BuildInfo.hpp>






std::string BuildInfo::time_of_build = "[unset]";


BuildInfo::BuildInfo()
{
}


BuildInfo::~BuildInfo()
{
}


std::string BuildInfo::get_time_of_build()
{
   return time_of_build;
}






