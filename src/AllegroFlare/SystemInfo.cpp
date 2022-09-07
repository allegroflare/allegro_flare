

#include <AllegroFlare/SystemInfo.hpp>

#include <AllegroFlare/Version.hpp>
#include <sys/utsname.h>
#include <thread>


namespace AllegroFlare
{


SystemInfo::SystemInfo()
{
}


SystemInfo::~SystemInfo()
{
}


std::string SystemInfo::allegro_flare_version()
{
   AllegroFlare::Version version;
   return version.get_allegro_flare_version_string();
}

std::string SystemInfo::allegro_version()
{
   AllegroFlare::Version version;
   return version.get_allegro_version_string();
}

uint32_t SystemInfo::num_available_threads()
{
   return std::thread::hardware_concurrency();
}

bool SystemInfo::num_available_threads_are_known()
{
   return (std::thread::hardware_concurrency() != 0);
}

std::string SystemInfo::get_processor_type()
{
   std::string machine = get_machine();
   if (machine.empty()) return "[unable-to-detect]";
   if (machine.substr(0, 3) == "arm") return "arm";
   if (machine.substr(0, 1) == "i") return "intel";
   return "[chip-kind-not-detected]";
}

std::string SystemInfo::get_sysname()
{
   utsname buf;
   uname(&buf);
   std::string sysname = buf.sysname;
   return sysname;
}

std::string SystemInfo::get_version()
{
   utsname buf;
   uname(&buf);
   std::string version = buf.version;
   return version;
}

std::string SystemInfo::get_release()
{
   utsname buf;
   uname(&buf);
   std::string release = buf.release;
   return release;
}

std::string SystemInfo::get_machine()
{
   utsname buf;
   uname(&buf);
   std::string machine = buf.machine;
   return machine;
}

std::string SystemInfo::operating_system()
{
   // TODO: this might be incorrect, might be detecting WIN32 even when WIN64 is present

   #ifdef _WIN32
   return "Windows 32-bit";
   #elif _WIN64
   return "Windows 64-bit";
   #elif __APPLE__ || __MACH__
   return "MacOS";
   #elif __linux__
   return "Linux";
   #elif __FreeBSD__
   return "FreeBSD";
   #elif __unix || __unix__
   return "Unix";
   #else
   return "Other";
   #endif
}


} // namespace AllegroFlare


