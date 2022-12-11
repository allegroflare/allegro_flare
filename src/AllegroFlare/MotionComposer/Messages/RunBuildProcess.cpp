

#include <AllegroFlare/MotionComposer/Messages/RunBuildProcess.hpp>




namespace AllegroFlare
{
namespace MotionComposer
{
namespace Messages
{


RunBuildProcess::RunBuildProcess(std::string platform, std::string source_release_zip_url, std::string name_of_source_release_folder)
   : AllegroFlare::MotionComposer::Messages::Base(AllegroFlare::MotionComposer::Messages::RunBuildProcess::TYPE)
   , platform(platform)
   , source_release_zip_url(source_release_zip_url)
   , name_of_source_release_folder(name_of_source_release_folder)
{
}


RunBuildProcess::~RunBuildProcess()
{
}


void RunBuildProcess::set_platform(std::string platform)
{
   this->platform = platform;
}


void RunBuildProcess::set_source_release_zip_url(std::string source_release_zip_url)
{
   this->source_release_zip_url = source_release_zip_url;
}


void RunBuildProcess::set_name_of_source_release_folder(std::string name_of_source_release_folder)
{
   this->name_of_source_release_folder = name_of_source_release_folder;
}


std::string RunBuildProcess::get_platform() const
{
   return platform;
}


std::string RunBuildProcess::get_source_release_zip_url() const
{
   return source_release_zip_url;
}


std::string RunBuildProcess::get_name_of_source_release_folder() const
{
   return name_of_source_release_folder;
}


std::string &RunBuildProcess::get_platform_ref()
{
   return platform;
}


std::string &RunBuildProcess::get_source_release_zip_url_ref()
{
   return source_release_zip_url;
}


std::string &RunBuildProcess::get_name_of_source_release_folder_ref()
{
   return name_of_source_release_folder;
}




} // namespace Messages
} // namespace MotionComposer
} // namespace AllegroFlare


