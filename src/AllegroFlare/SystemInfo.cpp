

#include <AllegroFlare/SystemInfo.hpp>
#include <AllegroFlare/Version.hpp>
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

std::string SystemInfo::operating_system()
{
   #ifdef _WIN32
   return "Windows 32-bit";
   #elif _WIN64
   return "Windows 64-bit";
   #elif __APPLE__ || __MACH__
   return "MacOSX";
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


