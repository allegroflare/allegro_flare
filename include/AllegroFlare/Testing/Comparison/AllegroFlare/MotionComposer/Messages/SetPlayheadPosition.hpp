#pragma once


#include <AllegroFlare/MotionComposer/Messages/SetPlayheadPosition.hpp>
#include <ostream>


bool operator==(
   const AllegroFlare::MotionComposer::Messages::SetPlayheadPosition& vec,
   const AllegroFlare::MotionComposer::Messages::SetPlayheadPosition& other_vec
);


namespace AllegroFlare::MotionComposer::Messages
{
   void PrintTo(
      const AllegroFlare::MotionComposer::Messages::SetPlayheadPosition& vec,
      ::std::ostream* os
   );
}


