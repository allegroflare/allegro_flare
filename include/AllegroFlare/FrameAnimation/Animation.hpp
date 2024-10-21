#pragma once


#include <AllegroFlare/FrameAnimation/Frame.hpp>
#include <AllegroFlare/FrameAnimation/SpriteSheet.hpp>
#include <allegro5/allegro.h>
#include <cstdint>
#include <string>
#include <tuple>
#include <utility>
#include <vector>


namespace AllegroFlare
{
   namespace FrameAnimation
   {
      class Animation
      {
      public:

         enum Playmode
         {
            PLAYMODE_UNDEF = 0,
            PLAYMODE_FORWARD_ONCE,
            PLAYMODE_FORWARD_ONCE_AND_HOLD_LAST_FRAME,
            PLAYMODE_FORWARD_LOOP,
            PLAYMODE_FORWARD_PING_PONG,
         };
      private:
         AllegroFlare::FrameAnimation::SpriteSheet* sprite_sheet;
         std::string name;
         std::vector<AllegroFlare::FrameAnimation::Frame> frames;
         uint32_t playmode;
         float playspeed_multiplier;
         float playhead;
         bool finished;
         float finished_at;
         bool initialized;
         static ALLEGRO_TRANSFORM t;
         std::tuple<AllegroFlare::FrameAnimation::Frame*, int, int> get_frame_info_at(float time=0.0f);

      protected:


      public:
         Animation(AllegroFlare::FrameAnimation::SpriteSheet* sprite_sheet=nullptr, std::string name="[unset-name]", std::vector<AllegroFlare::FrameAnimation::Frame> frames={}, uint32_t playmode=PLAYMODE_UNDEF);
         ~Animation();

         AllegroFlare::FrameAnimation::SpriteSheet* get_sprite_sheet() const;
         std::vector<AllegroFlare::FrameAnimation::Frame> get_frames() const;
         uint32_t get_playmode() const;
         float get_playspeed_multiplier() const;
         float get_playhead() const;
         bool get_finished() const;
         float get_finished_at() const;
         bool get_initialized() const;
         void initialize();
         void start();
         void reset();
         void set_playspeed_multiplier(float playspeed_multiplier=1.0);
         void update();
         void draw();
         void draw_raw();
         int get_num_frames();
         ALLEGRO_BITMAP* get_frame_bitmap_at_time(float time=0.0f);
         ALLEGRO_BITMAP* get_frame_bitmap_now();
         std::pair<bool, std::tuple<float, float, float, float, float, float>> get_frame_alignment_and_anchors_now();
         ALLEGRO_BITMAP* get_frame_alignment_and_anchors_at_time(float time=0.0f);
         int get_sprite_sheet_cell_index_num_now();
         int get_frame_num_now();
         ALLEGRO_BITMAP* get_bitmap_at_frame_num(int frame_num=0);
         std::tuple<float, float, float, float> get_alignment_and_anchors_at_frame_num(int frame_num=0);
         AllegroFlare::FrameAnimation::Frame* get_frame_at(float time=0.0f);
         int get_frame_num_at(float time=0.0f);
         int get_sprite_sheet_cell_index_num_at(float time=0.0f);
         float calculate_duration();
      };
   }
}



