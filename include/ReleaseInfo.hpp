#pragma once


#include <string>


class ReleaseInfo
{
private:
   static std::string version;
   static std::string allegro_flare_version_git_hash;
   static std::string blast_version_git_hash;

protected:


public:
   ReleaseInfo();
   ~ReleaseInfo();

   static std::string get_version();
   static std::string get_allegro_flare_version_git_hash();
   static std::string get_blast_version_git_hash();
};



