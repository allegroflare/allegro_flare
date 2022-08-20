

#include <AllegroFlare/Testing/Comparison/AllegroFlare/MotionComposer/Messages/SetPlayheadPosition.hpp>


bool operator==(
   const AllegroFlare::MotionComposer::Messages::SetPlayheadPosition& vec,
   const AllegroFlare::MotionComposer::Messages::SetPlayheadPosition& other_vec
)
{
   if (vec.get_position() != other_vec.get_position()) return false;
   return true;
}


namespace AllegroFlare::MotionComposer::Messages
{
   void PrintTo(
         const AllegroFlare::MotionComposer::Messages::SetPlayheadPosition& vec,
         ::std::ostream* os
      )
   {
      *os << "AllegroFlare::MotionComposer::Messages::SetPlayheadPosition(" << vec.get_position() << ")";
   }
}


