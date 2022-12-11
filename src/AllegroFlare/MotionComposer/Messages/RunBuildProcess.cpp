

#include <AllegroFlare/MotionComposer/Messages/RunBuildProcess.hpp>




namespace AllegroFlare
{
namespace MotionComposer
{
namespace Messages
{


RunBuildProcess::RunBuildProcess(std::string platform, std::string source_release_zip_url)
   : AllegroFlare::MotionComposer::Messages::Base(AllegroFlare::MotionComposer::Messages::RunBuildProcess::TYPE)
   , platform(platform)
   , source_release_zip_url(source_release_zip_url)
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


std::string RunBuildProcess::get_platform() const
{
   return platform;
}


std::string RunBuildProcess::get_source_release_zip_url() const
{
   return source_release_zip_url;
}


std::string &RunBuildProcess::get_platform_ref()
{
   return platform;
}


std::string &RunBuildProcess::get_source_release_zip_url_ref()
{
   return source_release_zip_url;
}




} // namespace Messages
} // namespace MotionComposer
} // namespace AllegroFlare


