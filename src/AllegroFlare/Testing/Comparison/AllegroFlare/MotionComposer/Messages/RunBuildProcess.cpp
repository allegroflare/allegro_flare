

#include <AllegroFlare/Testing/Comparison/AllegroFlare/MotionComposer/Messages/RunBuildProcess.hpp>


namespace AllegroFlare::MotionComposer::Messages
{


bool operator==(const RunBuildProcess& object, const RunBuildProcess& other_object)
{
   if (object.get_platform() != other_object.get_platform()) return false;
   if (object.get_source_release_zip_url() != other_object.get_source_release_zip_url()) return false;
   return true;
}


void PrintTo(const RunBuildProcess& object, ::std::ostream* os)
{
   *os << "RunBuildProcess("
          << "platform: \"" << object.get_platform() << "\""
          << ", "
          << "source_release_zip_url: \"" << object.get_source_release_zip_url() << "\""
       << ")";
}


} // AllegroFlare::MotionComposer::Messages


