

#include <ReleaseInfo.hpp>






std::string ReleaseInfo::version = "[unset]";


std::string ReleaseInfo::allegro_flare_version_git_hash = "[unset]";


std::string ReleaseInfo::blast_version_git_hash = "[unset]";


ReleaseInfo::ReleaseInfo()
{
}


ReleaseInfo::~ReleaseInfo()
{
}


std::string ReleaseInfo::get_version()
{
   return version;
}


std::string ReleaseInfo::get_allegro_flare_version_git_hash()
{
   return allegro_flare_version_git_hash;
}


std::string ReleaseInfo::get_blast_version_git_hash()
{
   return blast_version_git_hash;
}






