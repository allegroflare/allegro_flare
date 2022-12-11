#pragma once


#include <lib/nlohmann/json.hpp>
#include <AllegroFlare/MotionComposer/Messages/RunBuildProcess.hpp>


namespace AllegroFlare::MotionComposer::Messages
{
  void to_json(nlohmann::json& j, const RunBuildProcess& object);
  void from_json(const nlohmann::json& j, RunBuildProcess& object);
}


