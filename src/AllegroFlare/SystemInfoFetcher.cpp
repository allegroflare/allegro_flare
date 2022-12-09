

#include <AllegroFlare/SystemInfoFetcher.hpp>


#if defined(_WIN32) || defined(_WIN64)
   // functionality below
#else
   #include <sys/utsname.h> // for utsname, uname
   #include <unistd.h>      // for gethostname
#endif


#if defined(_WIN32) || defined(_WIN64)

// Note this implementation is from:
// https://learn.microsoft.com/en-us/windows/win32/api/sysinfoapi/nf-sysinfoapi-getversion

#include <windows.h>
#include <sstream>

static std::string get_sysname_WIN()
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

static std::string get_version_WIN()
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
   result << dwMajorVersion << "." << dwMinorVersion;
   return result.str();
}


static std::string get_release_WIN()
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
   result << dwMajorVersion << "." << dwMinorVersion << " " << "(build " << dwBuild << ")";
   return result.str();
}

// Note this implementation from:
// https://learn.microsoft.com/en-us/windows/win32/sysinfo/getting-hardware-information

static std::string get_machine_WIN()
{
   SYSTEM_INFO siSysInfo;
 
   // Copy the hardware information to the SYSTEM_INFO structure. 
 
   GetSystemInfo(&siSysInfo); 
 
   // Display the contents of the SYSTEM_INFO structure. 

   std::stringstream result;

   // TODO: Update this condition to provide more accuracy. See the following link:
   // https://learn.microsoft.com/en-us/windows/win32/api/sysinfoapi/ns-sysinfoapi-system_info
   if (siSysInfo.dwProcessorType == 8664) return "x86_64";

   // TODO: consider including this additional information
   result << "OEM ID: " << siSysInfo.dwOemId
          << "; Number of processors: " << siSysInfo.dwNumberOfProcessors
          << "; Page size: " << siSysInfo.dwPageSize
          << "; Processor type: " << siSysInfo.dwProcessorType
          << "; Minimum application address: " << siSysInfo.lpMinimumApplicationAddress
          << "; Maximum application address: " << siSysInfo.lpMaximumApplicationAddress
          << "; Active processor mask: " << siSysInfo.dwActiveProcessorMask
          ;

   return result.str();
}

static std::string get_hostname_WIN()
{
   constexpr int INFO_BUFFER_SIZE = 32767;
   TCHAR  infoBuf[INFO_BUFFER_SIZE];
   DWORD  bufCharCount = INFO_BUFFER_SIZE;
   std::stringstream result;

   // Get and display the name of the computer.
   // TODO: Add fallbacks if getting computer name is unsuccessful
   bool get_computer_name_successful = GetComputerName(infoBuf, &bufCharCount);
   if (!get_computer_name_successful) std::cerr << "[AllegroFlare::SystemInfoFetcher::get_hostname()]: "
                                                << "error: Could not extract hostname." << std::endl;
   //if(!get_computer_name_successful) printError( TEXT("GetComputerName") );
      //_tprintf( TEXT("\nComputer name:      %s"), infoBuf );
   result << infoBuf;

   // Get and display the user name.
   //if( !GetUserName( infoBuf, &bufCharCount ) ) printError( TEXT("GetUserName") );
   //_tprintf( TEXT("\nUser name:          %s"), infoBuf );

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
   return get_sysname_WIN();
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
   return get_version_WIN();
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
   return get_release_WIN();
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
   return get_machine_WIN();
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
   return get_hostname_WIN();
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


