#pragma once


#include <string>


class BuildInfo
{
private:
   static std::string time_of_build;
   static std::string building_platform_os_name;
   static std::string building_platform_os_version;
   static std::string building_platform_chipset;
   static std::string compiler_name;
   static std::string compiler_version;
   static std::string allegro_version_num;
   static std::string allegro_version_git_branch;
   static std::string allegro_version_git_hash;
   static std::string allegro_version_git_latest_commit_date_and_time;
   static int allegro_version_git_num_commits;

protected:


public:
   BuildInfo();
   ~BuildInfo();

   static std::string get_time_of_build();
   static std::string get_building_platform_os_name();
   static std::string get_building_platform_os_version();
   static std::string get_building_platform_chipset();
   static std::string get_compiler_name();
   static std::string get_compiler_version();
   static std::string get_allegro_version_num();
   static std::string get_allegro_version_git_branch();
   static std::string get_allegro_version_git_hash();
   static std::string get_allegro_version_git_latest_commit_date_and_time();
   static int get_allegro_version_git_num_commits();
   static std::string get_cpp_version_string();
};



