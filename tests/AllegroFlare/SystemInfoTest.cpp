
#include <gtest/gtest.h>

#include <AllegroFlare/SystemInfo.hpp>
#include <thread>


TEST(AllegroFlare_SystemInfoTest, can_be_created_without_blowing_up)
{
   AllegroFlare::SystemInfo system_info;
}


TEST(AllegroFlare_SystemInfoTest, num_available_threads__will_return_the_number_of_usable_threads_on_the_current_system)
{
   AllegroFlare::SystemInfo system_info;

   uint32_t num_reported_available_threads = std::thread::hardware_concurrency();
   EXPECT_EQ(num_reported_available_threads, system_info.num_available_threads());
}


TEST(AllegroFlare_SystemInfoTest, num_available_threads_are_known__when_the_system_can_report_it__returns_true)
{
   AllegroFlare::SystemInfo system_info;
   EXPECT_EQ(true, system_info.num_available_threads_are_known());
}


TEST(AllegroFlare_SystemInfoTest, num_available_threads_are_known__when_the_system_can_not_report_it__returns_false)
{
   // Not testable, currently
   //AllegroFlare::SystemInfo system_info;
   //EXPECT_EQ(false, system_info.num_available_threads_are_known());
}


TEST(AllegroFlare_SystemInfoTest, get_sysname__will_return_a_string_representing_the_system)
{
   AllegroFlare::SystemInfo system_info;
   EXPECT_EQ("Darwin", system_info.get_sysname());
}


TEST(AllegroFlare_SystemInfoTest, get_hostname__will_return_a_string_representing_the_system)
{
   AllegroFlare::SystemInfo system_info;
   EXPECT_EQ("Marks-13-MacBook-Pro.local", system_info.get_hostname());
}


TEST(AllegroFlare_SystemInfoTest, get_version__will_return_a_string_representing_the_system)
{
   AllegroFlare::SystemInfo system_info;
   std::string expected_version = "Darwin Kernel Version 21.6.0: Mon Aug 22 20:20:05 PDT 2022; "
                                  "root:xnu-8020.140.49~2/RELEASE_ARM64_T8101;
   EXPECT_EQ(expected_version, system_info.get_version());
}


TEST(AllegroFlare_SystemInfoTest, get_release__will_return_a_string_representing_the_system)
{
   AllegroFlare::SystemInfo system_info;
   std::string expected_release = "21.6.0";
   EXPECT_EQ(expected_release, system_info.get_release());
}


TEST(AllegroFlare_SystemInfoTest, get_machine__will_return_a_string_representing_the_system)
{
   AllegroFlare::SystemInfo system_info;
   std::string expected_machine = "arm64";
   EXPECT_EQ(expected_machine, system_info.get_machine());
}


TEST(AllegroFlare_SystemInfoTest, get_chip_kind__will_return_a_string_representing_the_system)
{
   AllegroFlare::SystemInfo system_info;
   std::string expected_processor_type = "arm";
   EXPECT_EQ(expected_processor_type, system_info.get_processor_type());
}


TEST(AllegroFlare_SystemInfoTest, operating_system__will_return_a_string_representing_the_os)
{
   AllegroFlare::SystemInfo system_info;
#ifdef _WIN32
   std::string expected_operating_system = "Windows 32-bit";
#elif __APPLE__ || __MACH__
   std::string expected_operating_system = "MacOS";
#else
   std::string expected_operating_system = "[TEST-DATA-NOT-SET-FOR-THIS-PLATFORM]";
#endif
   EXPECT_EQ(expected_operating_system, system_info.operating_system());
}


