#pragma once


#include <AllegroFlare/MotionComposer/Messages/Clear.hpp>
#include <ostream>


namespace AllegroFlare::MotionComposer::Messages
{
   bool operator==(const Clear& object, const Clear& other_object);
   void PrintTo(const Clear& object, ::std::ostream* os);
}


