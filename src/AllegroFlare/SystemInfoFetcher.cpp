

#include <AllegroFlare/SystemInfoFetcher.hpp>


#ifdef _WIN32 || _WIN64
   // note: not supported
#else
   #include <sys/utsname.h> // for utsname, uname
   #include <unistd.h>      // for gethostname
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

std::string SystemInfoFetcher::get_hostname()
{
   // SUSv2 guarantees that "Host names are limited to 255 bytes".
   // POSIX.1 guarantees that "Host names (not including the
   // terminating null byte) are limited to HOST_NAME_MAX bytes".  On
   // Linux, HOST_NAME_MAX is defined with the value 64, which has been
   // the limit since Linux 1.0 (earlier kernels imposed a limit of 8
   // bytes).
   char hostname[256];

   int gethostname_response = gethostname(hostname, 256);
   if (gethostname_response != 0)
   {
      return "[could-not-determine-hostname]";
   }
   std::string result = hostname;
   return result;
}


} // namespace AllegroFlare


