
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


