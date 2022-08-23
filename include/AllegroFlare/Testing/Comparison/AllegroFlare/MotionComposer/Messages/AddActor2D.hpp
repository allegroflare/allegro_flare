#pragma once


#include <AllegroFlare/MotionComposer/Messages/AddActor2D.hpp>
#include <ostream>


namespace AllegroFlare::MotionComposer::Messages
{
   bool operator==(const AddActor2D& object, const AddActor2D& other_object);
   void PrintTo(const AddActor2D& object, ::std::ostream* os);
}


