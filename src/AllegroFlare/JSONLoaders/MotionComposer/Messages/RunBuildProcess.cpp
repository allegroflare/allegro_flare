

#include <AllegroFlare/JSONLoaders/MotionComposer/Messages/RunBuildProcess.hpp>



namespace AllegroFlare::MotionComposer::Messages
{


void to_json(nlohmann::json& j, const AllegroFlare::MotionComposer::Messages::RunBuildProcess& v)
{
   j = nlohmann::json{
      { "platform", v.get_platform() },
      { "source_release_zip_url", v.get_source_release_zip_url() },
      { "name_of_source_release_folder", v.get_name_of_source_release_folder() },
   };
}

void from_json(const nlohmann::json& j, AllegroFlare::MotionComposer::Messages::RunBuildProcess& v)
{
   j.at("platform").get_to(v.get_platform_ref());
   j.at("source_release_zip_url").get_to(v.get_source_release_zip_url_ref());
   j.at("name_of_source_release_folder").get_to(v.get_name_of_source_release_folder_ref());
}


} // namespace AllegroFlare/JSONLoaders/MotionComposer/Messages


