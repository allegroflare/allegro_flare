

#include <AllegroFlare/FrameAnimation/AsepriteSpriteSheetJSONLoader.hpp>

#include <AllegroFlare/Errors.hpp>
#include <AllegroFlare/FrameAnimation/Animation.hpp>
#include <AllegroFlare/FrameAnimation/Frame.hpp>
#include <AllegroFlare/UsefulPHP.hpp>
#include <iostream>
#include <lib/nlohmann/json.hpp>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace FrameAnimation
{


AsepriteSpriteSheetJSONLoader::AsepriteSpriteSheetJSONLoader(std::string filename, AllegroFlare::FrameAnimation::SpriteSheet* sprite_sheet)
   : filename(filename)
   , sprite_sheet(sprite_sheet)
{
}


AsepriteSpriteSheetJSONLoader::~AsepriteSpriteSheetJSONLoader()
{
}


std::map<std::string, AllegroFlare::FrameAnimation::Animation> AsepriteSpriteSheetJSONLoader::load()
{
   using AllegroFlare::Errors;
   //std::string filename = "./bin/data/bitmaps/sprites_grid-x.json";
   if (!AllegroFlare::php::file_exists(filename))
   {
      AllegroFlare::Errors::throw_missing_file_error(
         "AllegroFlare::FrameAnimation::AsepriteSpriteSheetJSONLoader::load",
         filename,
         "json"
      );
   }
   nlohmann::json parsed_json = nlohmann::json::parse(AllegroFlare::php::file_get_contents(filename));
   std::map<std::string, AllegroFlare::FrameAnimation::Animation> result;

   // validate expected sections

   if (!parsed_json.contains("frames"))
   {
      Errors::throw_error("AllegroFlare::FrameAnimation/AsepriteSpriteSheetJSONDataLoader", "missing \"frames\" element in json");
   }
   if (!parsed_json.contains("meta"))
   {
      Errors::throw_error("AllegroFlare::FrameAnimation/AsepriteSpriteSheetJSONDataLoader", "missing \"meta\" element in json");
   }
   if (!parsed_json["meta"].contains("frameTags"))
   {
      Errors::throw_error(
      "AllegroFlare::FrameAnimation/AsepriteSpriteSheetJSONDataLoader",
         "missing [\"meta\"][\"tags\"] element in json"
      );
   }

   // load frame data

   std::map<int, int> frame_data;
   nlohmann::json frames = parsed_json["frames"];
   int index = 0;
   if (!frames.is_array())
   {
      Errors::throw_error("AllegroFlare::FrameAnimation::AsepriteSpriteSheetJSONDataLoader::load",
                          "expecting \"frames\" element in the JSON to be an array, but it is a hash. When "
                          "exporting the "
                          "sprite sheet in Aesprite, go to File > Export Sprite Sheet. Under the \"Output\" tab, "
                          "the \"JSON data\" checkbox should be checked. In the dropdown just below, be sure "
                          "\"Array\" is selected and not \"Hash\". This is needed to ensure the frames are imported "
                          "in sequential order."
                         );

   }
   for (auto &frame : frames)
   {
      // TODO: validate frame name
      int frame_num = index;
      int duration_msec;
      frame.at("duration").get_to(duration_msec);

      frame_data[frame_num] = duration_msec;
      index++;
   }

   nlohmann::json tags = parsed_json["meta"]["frameTags"];
   //std::map<std::string, AllegroFlare::FrameAnimation::Animation> animations_dictionary;

   for (auto &tag : tags)
   {
      std::string tag_name;
      std::string mode;
      int start_frame, end_frame;

      tag.at("name").get_to(tag_name);
      tag.at("from").get_to(start_frame);
      tag.at("to").get_to(end_frame);
      tag.at("direction").get_to(mode);

      if (result.count(tag_name) > 0)
      {
         Errors::throw_error("AllegroFlare::FrameAnimation::AsepriteSpriteSheetJSONDataLoader::load",
                             "duplicate key (a.k.a. tag) for [showing-duplicate-name-key-not-supported]");
      }

      result[tag_name] = AllegroFlare::FrameAnimation::Animation(
         sprite_sheet,
         tag_name,
         _build_animation_frames_for(start_frame, end_frame, frame_data), // <- NOTE: this copy arg can be optimized
         _get_playmode_from_direction(mode)
      );
   }

   return result;
}

std::vector<AllegroFlare::FrameAnimation::Frame> AsepriteSpriteSheetJSONLoader::_build_animation_frames_for(uint32_t start_frame, uint32_t end_frame, std::map<int, int> frame_data)
{
   if (!(end_frame >= start_frame))
   {
      std::stringstream error_message;
      error_message << "[AsepriteSpriteSheetJSONLoader::_build_animation_frames_for]: error: guard \"end_frame >= start_frame\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("AsepriteSpriteSheetJSONLoader::_build_animation_frames_for: error: guard \"end_frame >= start_frame\" not met");
   }
   std::vector<AllegroFlare::FrameAnimation::Frame> result;
   for (uint32_t frame=start_frame; frame<=end_frame; frame++)
   {
      if (frame_data.count(frame) == 0)
      {
         // This frame does not exist
         Errors::throw_error("AllegroFlare::FrameAnimation::AsepriteSpriteSheetJSONDataLoader::_build_animation_frames_for",
                             "a frame does not exist for this num");
      }
      int duration_msec = frame_data[frame];
      result.push_back(AllegroFlare::FrameAnimation::Frame(frame, (float)duration_msec*0.001));
   }
   return result;
}

uint32_t AsepriteSpriteSheetJSONLoader::_get_playmode_from_direction(std::string direction)
{
   std::map<std::string, uint32_t> playmode_map = {
     { "pingpong", AllegroFlare::FrameAnimation::Animation::PLAYMODE_FORWARD_PING_PONG },
     { "forward",  AllegroFlare::FrameAnimation::Animation::PLAYMODE_FORWARD_LOOP },
   };

   if (playmode_map.count(direction) == 0)
   {
        // This playmode does not exist
        Errors::throw_error("AllegroFlare::FrameAnimation::AsepriteSpriteSheetJSONDataLoader::_get_playmode_from_direction",
                            "a playmode does not exist for this direction.");
   }

   return playmode_map[direction];
}


} // namespace FrameAnimation
} // namespace AllegroFlare


