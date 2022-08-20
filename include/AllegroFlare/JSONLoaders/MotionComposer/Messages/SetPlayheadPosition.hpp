#pragma once


#include <lib/nlohmann/json.hpp>
#include <AllegroFlare/MotionComposer/Messages/SetPlayheadPosition.hpp>


namespace AllegroFlare
{
   namespace MotionComposer
   {
      namespace Messages
      {
      void to_json(nlohmann::json& j, const AllegroFlare::MotionComposer::Messages::SetPlayheadPosition& object);
      void from_json(const nlohmann::json& j, AllegroFlare::MotionComposer::Messages::SetPlayheadPosition& object);
      }
   }
}


