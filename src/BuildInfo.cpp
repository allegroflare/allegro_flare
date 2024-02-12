

#include <BuildInfo.hpp>






std::string BuildInfo::time_of_build = "[unset]";


std::string BuildInfo::building_platform_os_name = "[unset]";


std::string BuildInfo::building_platform_os_version = "[unset]";


std::string BuildInfo::building_platform_chipset = "[unset]";


std::string BuildInfo::compiler_name = "[unset]";


std::string BuildInfo::compiler_version = "[unset]";


std::string BuildInfo::allegro_version_num = "[unset]";


std::string BuildInfo::allegro_version_git_branch = "[unset]";


std::string BuildInfo::allegro_version_git_hash = "[unset]";


std::string BuildInfo::allegro_version_git_latest_commit_date_and_time = "[unset]";


int BuildInfo::allegro_version_git_num_commits = 0;


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


std::string BuildInfo::get_building_platform_os_name()
{
   return building_platform_os_name;
}


std::string BuildInfo::get_building_platform_os_version()
{
   return building_platform_os_version;
}


std::string BuildInfo::get_building_platform_chipset()
{
   return building_platform_chipset;
}


std::string BuildInfo::get_compiler_name()
{
   return compiler_name;
}


std::string BuildInfo::get_compiler_version()
{
   return compiler_version;
}


std::string BuildInfo::get_allegro_version_num()
{
   return allegro_version_num;
}


std::string BuildInfo::get_allegro_version_git_branch()
{
   return allegro_version_git_branch;
}


std::string BuildInfo::get_allegro_version_git_hash()
{
   return allegro_version_git_hash;
}


std::string BuildInfo::get_allegro_version_git_latest_commit_date_and_time()
{
   return allegro_version_git_latest_commit_date_and_time;
}


int BuildInfo::get_allegro_version_git_num_commits()
{
   return allegro_version_git_num_commits;
}


std::string BuildInfo::get_cpp_version_string()
{
   return "not-implemented";
}




