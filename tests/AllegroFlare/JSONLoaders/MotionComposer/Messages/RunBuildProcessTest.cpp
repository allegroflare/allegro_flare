
#include <gtest/gtest.h>

#include <AllegroFlare/JSONLoaders/MotionComposer/Messages/RunBuildProcess.hpp>
#include <AllegroFlare/Testing/Comparison/AllegroFlare/MotionComposer/Messages/RunBuildProcess.hpp>
// TODO: this needs to be moved to:
//#include <AllegroFlare/Testing/Comparison/AllegroFlare/JSONLoaders/MotionComposer/Messages/RunBuildProcess.hpp>


TEST(AllegroFlare_JSONLoaders_MotionComposer_Messages_RunBuildProcessTest,
   to_json__returns_the_object_as_json_with_the_expected_values)
{
   AllegroFlare::MotionComposer::Messages::RunBuildProcess run_build_process(
      "windows",
      "https://foo.io/release42.zip",
      "KrampusHack22-SourceRelease-221209175604UTC"
   );
   nlohmann::json j = run_build_process;

   std::string expected_values =
R"({
  "name_of_source_release_folder": "KrampusHack22-SourceRelease-221209175604UTC",
  "platform": "windows",
  "source_release_zip_url": "https://foo.io/release42.zip"
})";

   std::string actual_values = j.dump(2);
   EXPECT_EQ(expected_values, actual_values);
}


TEST(AllegroFlare_JSONLoaders_MotionComposer_Messages_RunBuildProcessTest,
   from_json__loads_json_data_into_the_object)
{
   AllegroFlare::MotionComposer::Messages::RunBuildProcess run_build_process;

   std::string json =
R"({
  "name_of_source_release_folder": "KrampusHack22-SourceRelease-221209175604UTC",
  "platform": "windows",
  "source_release_zip_url": "https://foo.io/release42.zip"
})";

   nlohmann::json parsed_json = nlohmann::json::parse(json);
   parsed_json.get_to(run_build_process);

   AllegroFlare::MotionComposer::Messages::RunBuildProcess expected(
      "windows",
      "https://foo.io/release42.zip",
      "KrampusHack22-SourceRelease-221209175604UTC"
   );

   EXPECT_EQ(expected, run_build_process);
}



