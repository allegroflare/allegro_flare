

#include <AllegroFlare/Version.hpp>


#include <allegro5/allegro.h>
#include <sstream>


namespace AllegroFlare
{


std::string Version::get_allegro_version_string()
{
   uint32_t version = al_get_allegro_version();
   int major = version >> 24;
   int minor = (version >> 16) & 255;
   int revision = (version >> 8) & 255;
   int release = version & 255;

   // TODO: If release is 0, consider appending a "pre-release" and possibly a hash(?)

   std::stringstream str;
   str << major << '.' << minor << '.' << revision;
   if (release == 0)
   {
      str << "-prerelease";
   }
   else
   {
      str << "-rel" << release;
   }
   return str.str();
}



std::string Version::get_allegro_flare_version_string()
{
   return ALLEGRO_FLARE_VERSION;
}


std::string Version::get_cpp_version_string()
{
   std::string result = "unknown C++ version";
   #if __cplusplus == 199711L
       result = "C++98";
   #elif __cplusplus == 201103L
       result = "C++11";
   #elif __cplusplus == 201402L
       result ="C++14";
   #elif __cplusplus == 201703L
       result = "C++17";
   #elif __cplusplus == 202002L
       result = "C++20";
   #endif
   return result;
}



} // namespace AllegroFlare




