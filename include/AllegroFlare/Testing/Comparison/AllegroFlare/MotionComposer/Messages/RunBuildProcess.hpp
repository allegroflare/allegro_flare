#pragma once


#include <AllegroFlare/MotionComposer/Messages/RunBuildProcess.hpp>
#include <ostream>


namespace AllegroFlare::MotionComposer::Messages
{
   bool operator==(const RunBuildProcess& object, const RunBuildProcess& other_object);
   void PrintTo(const RunBuildProcess& object, ::std::ostream* os);
}


