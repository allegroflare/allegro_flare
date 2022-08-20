

#include <AllegroFlare/Testing/Comparison/AllegroFlare/MotionComposer/Messages/SetPlayheadPosition.hpp>



namespace AllegroFlare::MotionComposer::Messages
{


bool operator==(const SetPlayheadPosition& vec, const SetPlayheadPosition& other_vec)
{
   if (vec.get_position() != other_vec.get_position()) return false;
   return true;
}


void PrintTo(const SetPlayheadPosition& vec, ::std::ostream* os)
{
   *os << "SetPlayheadPosition(" << vec.get_position() << ")";
}


} // namespace AllegroFlare::MotionComposer::Messages


