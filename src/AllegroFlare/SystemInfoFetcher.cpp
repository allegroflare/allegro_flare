

#include <AllegroFlare/SystemInfoFetcher.hpp>


#if defined(_WIN32) || defined(_WIN64)
   // functionality below
#else
   #include <sys/utsname.h> // for utsname, uname
   #include <unistd.h>      // for gethostname
#endif


#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#include <sstream>
static std::string build_version_name()
{
   DWORD dwVersion = 0;
   DWORD dwMajorVersion = 0;
   DWORD dwMinorVersion = 0;
   DWORD dwBuild = 0;

   dwVersion = GetVersion();

   // Get the Windows version.

   dwMajorVersion = (DWORD)(LOBYTE(LOWORD(dwVersion)));
   dwMinorVersion = (DWORD)(HIBYTE(LOWORD(dwVersion)));

   // Get the build number.

   if (dwVersion < 0x80000000)
      dwBuild = (DWORD)(HIWORD(dwVersion));

   std::stringstream result;
   result << "Windows " << dwMajorVersion << "." << dwMinorVersion << " " << "(build " << dwBuild << ")";
   return result.str();
}
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
#if defined(_WIN32) || defined(_WIN64)
   return build_version_name(); 
#else
   utsname buf;
   uname(&buf);
   std::string sysname = buf.sysname;
   return sysname;
#endif
}

std::string SystemInfoFetcher::get_version()
{
#if defined(_WIN32) || defined(_WIN64)
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
#if defined(_WIN32) || defined(_WIN64)
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
#if defined(_WIN32) || defined(_WIN64)
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
#if defined(_WIN32) || defined(_WIN64)
   return "[not-supported-on-this-system]";
#else
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
#endif
}


} // namespace AllegroFlare


