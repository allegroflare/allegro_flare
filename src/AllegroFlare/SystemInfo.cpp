

#include <AllegroFlare/SystemInfo.hpp>

#include <AllegroFlare/SystemInfoFetcher.hpp>
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

std::string SystemInfo::get_processor_type()
{
   std::string machine = get_machine();
   if (machine.empty()) return "[unable-to-detect]";
   if (machine.substr(0, 3) == "arm") return "arm";
   if (machine.substr(0, 3) == "x86" && operating_system() == "MacOS") return "intel";
   return "[chip-kind-not-detected]";
}

std::string SystemInfo::get_sysname()
{
   return AllegroFlare::SystemInfoFetcher().get_sysname();
}

std::string SystemInfo::get_version()
{
   return AllegroFlare::SystemInfoFetcher().get_version();
}

std::string SystemInfo::get_release()
{
   return AllegroFlare::SystemInfoFetcher().get_release();
}

std::string SystemInfo::get_hostname()
{
   return AllegroFlare::SystemInfoFetcher().get_hostname();
}

std::string SystemInfo::get_machine()
{
   return AllegroFlare::SystemInfoFetcher().get_machine();
}

std::string SystemInfo::operating_system()
{
   // TODO: this might be incorrect, might be detecting WIN32 even when WIN64 is present

   #ifdef _WIN32
   return OPERATING_SYSTEM_WINDOWS_32_BIT;
   #elif _WIN64
   return OPERATING_SYSTEM_WINDOWS_64_BIT;
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


