
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <AllegroFlare/SystemInfo.hpp>
#include <thread>
#include <regex>


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
   std::vector<std::string> expected_possible_hostnames = {
      "Windows 10.0 (build 19044)", // Mark's Windows Laptop
      "Darwin",                     // Mark's MacMini, Mark's Mac Laptop
   };
   std::string actual_hostname = system_info.get_sysname();
   EXPECT_THAT(expected_possible_hostnames, testing::Contains(actual_hostname));
}


TEST(AllegroFlare_SystemInfoTest, get_hostname__will_return_a_string_representing_the_system)
{
   AllegroFlare::SystemInfo system_info;
   std::vector<std::string> expected_possible_hostnames = {
      "DESKTOP-NC9M1BH",            // Mark's Laptop
      "Marks-13-MacBook-Pro.local", // Mark's Mac Laptop
      "Marks-Mac-mini.local",       // Mark's MacMini
   };
   std::string actual_hostname = system_info.get_hostname();
   EXPECT_THAT(expected_possible_hostnames, testing::Contains(actual_hostname));
}


TEST(AllegroFlare_SystemInfoTest, get_version__will_return_a_string_representing_the_system)
{
   AllegroFlare::SystemInfo system_info;
   std::string actual_version = system_info.get_version();

#ifdef _WIN32
   // Windows-specific code
   std::vector<std::string> expected_possible_versions = {
      // Mark's Windows Laptop:
      "10.0",
   };
   EXPECT_THAT(expected_possible_versions, testing::Contains(actual_version));
#elif __APPLE__
   // macOS-specific code
   // NOTE: some example strings for this regex:
   // "Darwin Kernel Version 22.4.0: Mon Mar  6 21:00:41 PST 2023; root:xnu-8796.101.5~3/RELEASE_ARM64_T8103";
   // "Darwin Kernel Version 22.3.0: Mon Jan 30 20:39:35 PST 2023; root:xnu-8792.81.3~2/RELEASE_ARM64_T8103",
   // "Darwin Kernel Version 21.6.0: Wed Aug 10 14:25:27 PDT 2022; root:xnu-8020.141.5~2/RELEASE_X86_64",
   // TODO: Consider using a more comprehensive string, and regex_match (rather than regex_search)
   //std::regex darwin_kernel_version_regex("^Darwin Kernel Version \\d+\\.\\d+\\.\\d+: [A-Z][a-z]{2} [A-Z][a-z]{2}\\s+\\d+\\s+\\d{2}:\\d{2}:\\d{2} [A-Z]{3} \\d{4}; root:[a-z]{3}-\\d+\\.\\d+\\.\\d+~\\d{1,2}/[A-Z_]+$");
   std::regex darwin_kernel_version_regex("^Darwin Kernel Version \\d+\\.\\d+\\.\\d+: ");
   bool is_match = std::regex_search(actual_version, darwin_kernel_version_regex);
   EXPECT_TRUE(is_match);
#else
   // Other platform code
   SKIP() << "This test is not supported on this platform";
#endif
}


TEST(AllegroFlare_SystemInfoTest, get_release__will_return_a_string_representing_the_system)
{
   AllegroFlare::SystemInfo system_info;
   std::vector<std::string> expected_possible_releases = {
      "10.0 (build 19044)",
      "22.4.0", // Mark's Mac Laptop
      "22.3.0", // Mark's Mac Laptop
      "21.6.0", // Mark's MacMini
   };
   std::string actual_release = system_info.get_release();
   EXPECT_THAT(expected_possible_releases, testing::Contains(actual_release));
}


TEST(AllegroFlare_SystemInfoTest, get_machine__will_return_a_string_representing_the_system)
{
   AllegroFlare::SystemInfo system_info;
   std::vector<std::string> expected_possible_machines = {
      "arm64",  // Mark's Mac Laptop
      "x86_64", // Mark's MacMini
   };
   std::string actual_machine = system_info.get_machine();
   EXPECT_THAT(expected_possible_machines, testing::Contains(actual_machine));
}


TEST(AllegroFlare_SystemInfoTest, get_chip_kind__will_return_a_string_representing_the_system)
{
// TODO: implement this test case
#if defined(_WIN32) || defined(_WIN64)
   GTEST_SKIP() << "This test is currently not implemented for Windows.";
#endif
   AllegroFlare::SystemInfo system_info;
   std::vector<std::string> expected_possible_processor_types = {
      "arm",   // Mark's Mac Laptop
      "intel", // Mark's MacMini
   };
   std::string actual_processor_type = system_info.get_processor_type();
   EXPECT_THAT(expected_possible_processor_types, testing::Contains(actual_processor_type));
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


