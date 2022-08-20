#pragma once


#include <AllegroFlare/MotionComposer/Messages/SetPlayheadPosition.hpp>
#include <ostream>


namespace AllegroFlare::MotionComposer::Messages
{
   bool operator==(const SetPlayheadPosition& vec, const SetPlayheadPosition& other_vec);
   void PrintTo(const SetPlayheadPosition& vec, ::std::ostream* os);
}


