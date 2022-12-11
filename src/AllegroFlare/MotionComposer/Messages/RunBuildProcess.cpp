

#include <AllegroFlare/MotionComposer/Messages/RunBuildProcess.hpp>




namespace AllegroFlare
{
namespace MotionComposer
{
namespace Messages
{


RunBuildProcess::RunBuildProcess(std::string platform)
   : AllegroFlare::MotionComposer::Messages::Base(AllegroFlare::MotionComposer::Messages::RunBuildProcess::TYPE)
   , platform(platform)
{
}


RunBuildProcess::~RunBuildProcess()
{
}


void RunBuildProcess::set_platform(std::string platform)
{
   this->platform = platform;
}


std::string RunBuildProcess::get_platform() const
{
   return platform;
}


std::string &RunBuildProcess::get_platform_ref()
{
   return platform;
}




} // namespace Messages
} // namespace MotionComposer
} // namespace AllegroFlare


