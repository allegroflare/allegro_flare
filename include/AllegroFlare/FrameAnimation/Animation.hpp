#pragma once


#include <AllegroFlare/FrameAnimation/Frame.hpp>
#include <AllegroFlare/FrameAnimation/SpriteSheet.hpp>
#include <allegro5/allegro.h>
#include <cstdint>
#include <string>
#include <utility>
#include <vector>


namespace AllegroFlare
{
   namespace FrameAnimation
   {
      class Animation
      {
      public:
         static constexpr uint32_t PLAYMODE_UNDEF = 0;
         static constexpr uint32_t PLAYMODE_FORWARD_ONCE = 1;
         static constexpr uint32_t PLAYMODE_FORWARD_LOOP = 2;
         static constexpr uint32_t PLAYMODE_FORWARD_PING_PONG = 3;

      private:
         AllegroFlare::FrameAnimation::SpriteSheet* sprite_sheet;
         std::string name;
         std::vector<AllegroFlare::FrameAnimation::Frame> frames;
         uint32_t playmode;
         float playspeed_multiplier;
         float playhead;
         bool finished;
         bool initialized;
         std::pair<int, int> get_frame_info_at(float time=0.0f);

      protected:


      public:
         Animation(AllegroFlare::FrameAnimation::SpriteSheet* sprite_sheet=nullptr, std::string name="[unset-name]", std::vector<AllegroFlare::FrameAnimation::Frame> frames={}, uint32_t playmode=PLAYMODE_UNDEF);
         ~Animation();

         std::vector<AllegroFlare::FrameAnimation::Frame> get_frames() const;
         uint32_t get_playmode() const;
         float get_playspeed_multiplier() const;
         float get_playhead() const;
         bool get_finished() const;
         bool get_initialized() const;
         void initialize();
         void start();
         void set_playspeed_multiplier(float playspeed_multiplier=1.0);
         void update();
         void draw();
         int get_num_frames();
         ALLEGRO_BITMAP* get_frame_at(float time=0.0f);
         ALLEGRO_BITMAP* get_frame_now();
         int get_frame_id_now();
         int get_frame_num_now();
         ALLEGRO_BITMAP* get_bitmap_at_frame_num(int frame_num=0);
         int get_frame_id_at(float time=0.0f);
         int get_frame_num_at(float time=0.0f);
         float calculate_duration();
      };
   }
}



