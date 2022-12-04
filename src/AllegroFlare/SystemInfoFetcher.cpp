

#include <AllegroFlare/SystemInfoFetcher.hpp>


#ifdef _WIN32 || _WIN64
   // note: not supported
#else
   #include <sys/utsname.h>
#endif


namespace AllegroFlare
{


SystemInfoFetcher::SystemInfoFetcher()
{
}


SystemInfoFetcher::~SystemInfoFetcher()
{
}


std::string SystemInfoFetcher::get_sysname()
{
#ifdef _WIN32 || _WIN64
   return "[not-supported-on-this-system]";
#else
   utsname buf;
   uname(&buf);
   std::string sysname = buf.sysname;
   return sysname;
#endif
}

std::string SystemInfoFetcher::get_version()
{
#ifdef _WIN32 || _WIN64
   return "[not-supported-on-this-system]";
#else
   utsname buf;
   uname(&buf);
   std::string version = buf.version;
   return version;
#endif
}

std::string SystemInfoFetcher::get_release()
{
#ifdef _WIN32 || _WIN64
   return "[not-supported-on-this-system]";
#else
   utsname buf;
   uname(&buf);
   std::string release = buf.release;
   return release;
#endif
}

std::string SystemInfoFetcher::get_machine()
{
#ifdef _WIN32 || _WIN64
   return "[not-supported-on-this-system]";
#else
   utsname buf;
   uname(&buf);
   std::string machine = buf.machine;
   return machine;
#endif
}


} // namespace AllegroFlare


