#pragma once


#include <AllegroFlare/FrameAnimation/Animation.hpp>
#include <AllegroFlare/FrameAnimation/Frame.hpp>
#include <AllegroFlare/FrameAnimation/SpriteSheet.hpp>
#include <cstdint>
#include <map>
#include <string>
#include <vector>


namespace AllegroFlare
{
   namespace FrameAnimation
   {
      class AsepriteSpriteSheetJSONLoader
      {
      public:
         static constexpr char PLAY_ONCE_BANG_CHAR = '.';

      private:
         std::string filename;
         AllegroFlare::FrameAnimation::SpriteSheet* sprite_sheet;
         bool load_tag_names_ending_in_bang_char_with_looping_playmode;
         bool discard_last_bang_char_in_tag_names;

      protected:


      public:
         AsepriteSpriteSheetJSONLoader(std::string filename="./bin/data/bitmaps/sprites_grid-x.json", AllegroFlare::FrameAnimation::SpriteSheet* sprite_sheet=nullptr);
         ~AsepriteSpriteSheetJSONLoader();

         void set_load_tag_names_ending_in_bang_char_with_looping_playmode(bool load_tag_names_ending_in_bang_char_with_looping_playmode);
         void set_discard_last_bang_char_in_tag_names(bool discard_last_bang_char_in_tag_names);
         bool get_load_tag_names_ending_in_bang_char_with_looping_playmode() const;
         bool get_discard_last_bang_char_in_tag_names() const;
         std::map<std::string, AllegroFlare::FrameAnimation::Animation> load();
         std::vector<AllegroFlare::FrameAnimation::Frame> _build_animation_frames_for(uint32_t start_frame=0, uint32_t end_frame=0, std::map<int, int> frame_data={});
         bool ends_in_bang_char(std::string str="[unset-str]");
         std::string strip_appended_bang_char(std::string str="[unset-str]");
         uint32_t _get_playmode_from_direction(std::string direction="[unset-direction]", bool playmode_is_looped=true);
      };
   }
}



