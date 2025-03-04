

#include <AllegroFlare/FrameAnimation/Animation.hpp>

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <cmath>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace FrameAnimation
{


ALLEGRO_TRANSFORM Animation::t = {};


Animation::Animation(AllegroFlare::FrameAnimation::SpriteSheet* sprite_sheet, std::string name, std::vector<AllegroFlare::FrameAnimation::Frame> frames, uint32_t playmode)
   : sprite_sheet(sprite_sheet)
   , name(name)
   , frames(frames)
   , playmode(playmode)
   , playspeed_multiplier(1.0f)
   , playhead(0.0f)
   , finished(false)
   , finished_at(0.0f)
   , initialized(false)
{
}


Animation::~Animation()
{
}


AllegroFlare::FrameAnimation::SpriteSheet* Animation::get_sprite_sheet() const
{
   return sprite_sheet;
}


std::vector<AllegroFlare::FrameAnimation::Frame> Animation::get_frames() const
{
   return frames;
}


uint32_t Animation::get_playmode() const
{
   return playmode;
}


float Animation::get_playspeed_multiplier() const
{
   return playspeed_multiplier;
}


float Animation::get_playhead() const
{
   return playhead;
}


bool Animation::get_finished() const
{
   return finished;
}


float Animation::get_finished_at() const
{
   return finished_at;
}


bool Animation::get_initialized() const
{
   return initialized;
}


void Animation::initialize()
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::FrameAnimation::Animation::initialize]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::FrameAnimation::Animation::initialize]: error: guard \"(!initialized)\" not met");
   }
   if (!(sprite_sheet))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::FrameAnimation::Animation::initialize]: error: guard \"sprite_sheet\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::FrameAnimation::Animation::initialize]: error: guard \"sprite_sheet\" not met");
   }
   if (!(sprite_sheet->get_initialized()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::FrameAnimation::Animation::initialize]: error: guard \"sprite_sheet->get_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::FrameAnimation::Animation::initialize]: error: guard \"sprite_sheet->get_initialized()\" not met");
   }
   if (!(al_is_system_installed()))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::FrameAnimation::Animation::initialize]: error: guard \"al_is_system_installed()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::FrameAnimation::Animation::initialize]: error: guard \"al_is_system_installed()\" not met");
   }
   initialized = true;
   return;
}

void Animation::start()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::FrameAnimation::Animation::start]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::FrameAnimation::Animation::start]: error: guard \"initialized\" not met");
   }
   playhead = 0.0f;
   finished = false;
   finished_at = 0.0f;
   return;
}

void Animation::reset()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::FrameAnimation::Animation::reset]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::FrameAnimation::Animation::reset]: error: guard \"initialized\" not met");
   }
   // NOTE: Internally, this is functionally the same as start()
   playhead = 0.0f;
   finished = false;
   finished_at = 0.0f;
   return;
}

void Animation::set_playspeed_multiplier(float playspeed_multiplier)
{
   if (!((playspeed_multiplier >= 0.0f)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::FrameAnimation::Animation::set_playspeed_multiplier]: error: guard \"(playspeed_multiplier >= 0.0f)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::FrameAnimation::Animation::set_playspeed_multiplier]: error: guard \"(playspeed_multiplier >= 0.0f)\" not met");
   }
   this->playspeed_multiplier = playspeed_multiplier;
   return;
}

void Animation::update(float time_step)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::FrameAnimation::Animation::update]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::FrameAnimation::Animation::update]: error: guard \"initialized\" not met");
   }
   // TODO: Pass in time_now (for capturing "finished_at")

   playhead += (time_step * playspeed_multiplier);

   // update "finished"
   switch(playmode)
   {
      case PLAYMODE_FORWARD_ONCE:
      case PLAYMODE_FORWARD_ONCE_AND_HOLD_LAST_FRAME:
         if (playhead > calculate_duration())
         {
            if (!finished)
            {
               finished = true;
               finished_at = al_get_time(); // NOTE: This will crash if al_init has not been called
            }
         }
      break;

      case PLAYMODE_FORWARD_LOOP:
        // NOTE: nothing to do, FORWARD_LOOP plays indefinitely
      break;

      case PLAYMODE_FORWARD_PING_PONG:
        // NOTE: nothing to do, PING_PONG plays indefinitely
      break;
   }
   return;
}

void Animation::draw_in_context(bool flip_x, bool flip_y, bool draw_debug)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::FrameAnimation::Animation::draw_in_context]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::FrameAnimation::Animation::draw_in_context]: error: guard \"initialized\" not met");
   }
   if (!(((!draw_debug) || (draw_debug && al_is_primitives_addon_initialized()))))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::FrameAnimation::Animation::draw_in_context]: error: guard \"((!draw_debug) || (draw_debug && al_is_primitives_addon_initialized()))\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::FrameAnimation::Animation::draw_in_context]: error: guard \"((!draw_debug) || (draw_debug && al_is_primitives_addon_initialized()))\" not met");
   }
   ALLEGRO_BITMAP *bitmap = get_frame_bitmap_at_time(playhead);
   if (!bitmap) return;

   ALLEGRO_STATE previous_state;
   al_store_state(&previous_state, ALLEGRO_STATE_TRANSFORM);

   // std::pair<bool, std::tuple<float, float, float, float, float, float>>
   //auto [present, [align_x, align_y, container_align_x, container_align_y, anchor_x, anchor_y]] =
   auto vals = get_frame_alignment_and_anchors_now();
   auto &align_x = std::get<0>(vals.second);
   auto &align_y = std::get<1>(vals.second);
   auto &anchor_x = std::get<4>(vals.second);
   auto &anchor_y = std::get<5>(vals.second);
   // TODO: Account for anchors (container_align) is the responsibillity of the containing box

   // TODO: Introduce accounting for sprite sheet scale when rendering
   int bitmap_width = al_get_bitmap_width(bitmap);
   int bitmap_height = al_get_bitmap_height(bitmap);
   int sprite_sheet_scale = sprite_sheet->get_scale();
   float inv_sprite_sheet_scale = 1.0f / sprite_sheet_scale;

   al_identity_transform(&t);
   // Should these transforms be in 3d? Should y and z be flipped?

   // TODO: Work in anchors
   // NOTE: Here is order of transforms for Placement2D
   //al_translate_transform(transform, -align.x*size.x, -align.y*size.y);
   //al_scale_transform(transform, scale.x * (flip.get_x() ? -1 : 1), scale.y * (flip.get_y() ? -1 : 1));
   //al_translate_transform(transform, anchor.x, anchor.y);
   //al_rotate_transform(transform, rotation);
   //al_translate_transform(transform, position.x, position.y);


   al_translate_transform(&t, -bitmap_width * align_x, -bitmap_height * align_y);
   //if (flip_x || flip_y) al_scale_transform(&t, (flip_x ? -1 : 1), (flip_y ? -1 : 1)); // TODO: Test this appears
                                                                                       // as expected
   al_scale_transform(&t, inv_sprite_sheet_scale, inv_sprite_sheet_scale);

   al_compose_transform(&t, al_get_current_transform());

   al_use_transform(&t);
   int bitmap_flags = 0;
   if (flip_x) bitmap_flags = bitmap_flags | ALLEGRO_FLIP_HORIZONTAL;
   if (flip_y) bitmap_flags = bitmap_flags | ALLEGRO_FLIP_VERTICAL;
   al_draw_bitmap(bitmap, 0, 0, bitmap_flags);

   if (draw_debug)
   {
      al_draw_rectangle(
         0,
         0,
         bitmap_width,
         bitmap_height,
         ALLEGRO_COLOR{1, 0.5, 0, 1},
         sprite_sheet_scale
      );
   }

   al_identity_transform(&t);
   al_use_transform(&t);


   // TODO: Test that state is restored
   al_restore_state(&previous_state);

   return;
}

void Animation::draw()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::FrameAnimation::Animation::draw]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::FrameAnimation::Animation::draw]: error: guard \"initialized\" not met");
   }
   // Consider renaming this "draw_raw"
   ALLEGRO_BITMAP *bitmap = get_frame_bitmap_at_time(playhead);
   if (!bitmap) return;
   al_draw_bitmap(bitmap, 0, 0, 0);
   return;
}

int Animation::get_num_frames()
{
   return frames.size();
}

ALLEGRO_BITMAP* Animation::get_frame_bitmap_at_time(float time)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::FrameAnimation::Animation::get_frame_bitmap_at_time]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::FrameAnimation::Animation::get_frame_bitmap_at_time]: error: guard \"initialized\" not met");
   }
   int sprite_sheet_cell_index_num = get_sprite_sheet_cell_index_num_at(time);
   if (sprite_sheet_cell_index_num == -1) return nullptr;
   return sprite_sheet->get_cell(sprite_sheet_cell_index_num);
}

ALLEGRO_BITMAP* Animation::get_frame_bitmap_now()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::FrameAnimation::Animation::get_frame_bitmap_now]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::FrameAnimation::Animation::get_frame_bitmap_now]: error: guard \"initialized\" not met");
   }
   return get_frame_bitmap_at_time(playhead);
}

std::pair<bool, std::tuple<float, float, float, float, float, float>> Animation::get_frame_alignment_and_anchors_now()
{
   AllegroFlare::FrameAnimation::Frame *frame = get_frame_at(playhead);
   if (!frame) return { false, { 0, 0, 0, 0, 0, 0 } };
   return { true, {
      frame->get_align_x(),
      frame->get_align_y(),
      frame->get_align_in_container_x(),
      frame->get_align_in_container_y(),
      frame->get_anchor_x(),
      frame->get_anchor_y(),
   }};
}

ALLEGRO_BITMAP* Animation::get_frame_alignment_and_anchors_at_time(float time)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::FrameAnimation::Animation::get_frame_alignment_and_anchors_at_time]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::FrameAnimation::Animation::get_frame_alignment_and_anchors_at_time]: error: guard \"initialized\" not met");
   }
   // HERE
   int sprite_sheet_cell_index_num = get_sprite_sheet_cell_index_num_at(time);
   if (sprite_sheet_cell_index_num == -1) return nullptr;
   return sprite_sheet->get_cell(sprite_sheet_cell_index_num);
}

int Animation::get_sprite_sheet_cell_index_num_now()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::FrameAnimation::Animation::get_sprite_sheet_cell_index_num_now]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::FrameAnimation::Animation::get_sprite_sheet_cell_index_num_now]: error: guard \"initialized\" not met");
   }
   return get_sprite_sheet_cell_index_num_at(playhead);
}

int Animation::get_frame_num_now()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::FrameAnimation::Animation::get_frame_num_now]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::FrameAnimation::Animation::get_frame_num_now]: error: guard \"initialized\" not met");
   }
   return get_frame_num_at(playhead);
}

ALLEGRO_BITMAP* Animation::get_bitmap_at_frame_num(int frame_num)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::FrameAnimation::Animation::get_bitmap_at_frame_num]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::FrameAnimation::Animation::get_bitmap_at_frame_num]: error: guard \"initialized\" not met");
   }
   if (!((frame_num >= 0)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::FrameAnimation::Animation::get_bitmap_at_frame_num]: error: guard \"(frame_num >= 0)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::FrameAnimation::Animation::get_bitmap_at_frame_num]: error: guard \"(frame_num >= 0)\" not met");
   }
   if (!((frame_num < frames.size())))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::FrameAnimation::Animation::get_bitmap_at_frame_num]: error: guard \"(frame_num < frames.size())\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::FrameAnimation::Animation::get_bitmap_at_frame_num]: error: guard \"(frame_num < frames.size())\" not met");
   }
   int sprite_sheet_cell_index_num = frames[frame_num].get_index();
   return sprite_sheet->get_cell(sprite_sheet_cell_index_num);
}

std::tuple<float, float, float, float> Animation::get_alignment_and_anchors_at_frame_num(int frame_num)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::FrameAnimation::Animation::get_alignment_and_anchors_at_frame_num]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::FrameAnimation::Animation::get_alignment_and_anchors_at_frame_num]: error: guard \"initialized\" not met");
   }
   if (!((frame_num >= 0)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::FrameAnimation::Animation::get_alignment_and_anchors_at_frame_num]: error: guard \"(frame_num >= 0)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::FrameAnimation::Animation::get_alignment_and_anchors_at_frame_num]: error: guard \"(frame_num >= 0)\" not met");
   }
   if (!((frame_num < frames.size())))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::FrameAnimation::Animation::get_alignment_and_anchors_at_frame_num]: error: guard \"(frame_num < frames.size())\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::FrameAnimation::Animation::get_alignment_and_anchors_at_frame_num]: error: guard \"(frame_num < frames.size())\" not met");
   }
   // TODO: Never tested, never used
   std::tuple<float, float, float, float> result;

   auto &frame = frames[frame_num];

   result = {
      frame.get_align_x(),
      frame.get_align_y(),
      frame.get_anchor_x(),
      frame.get_anchor_y(),
   };

   return result;
}

AllegroFlare::FrameAnimation::Frame* Animation::get_frame_at(float time)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::FrameAnimation::Animation::get_frame_at]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::FrameAnimation::Animation::get_frame_at]: error: guard \"initialized\" not met");
   }
   return std::get<0>(get_frame_info_at(time));
}

int Animation::get_frame_num_at(float time)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::FrameAnimation::Animation::get_frame_num_at]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::FrameAnimation::Animation::get_frame_num_at]: error: guard \"initialized\" not met");
   }
   return std::get<1>(get_frame_info_at(time));
}

int Animation::get_sprite_sheet_cell_index_num_at(float time)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::FrameAnimation::Animation::get_sprite_sheet_cell_index_num_at]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::FrameAnimation::Animation::get_sprite_sheet_cell_index_num_at]: error: guard \"initialized\" not met");
   }
   return std::get<2>(get_frame_info_at(time));
}

std::tuple<AllegroFlare::FrameAnimation::Frame*, int, int> Animation::get_frame_info_at(float time)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::FrameAnimation::Animation::get_frame_info_at]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::FrameAnimation::Animation::get_frame_info_at]: error: guard \"initialized\" not met");
   }
   // Note the return value is std::pair<frame, current_animations_frame_number, sprite_sheet_frame_index>

   float duration = calculate_duration();
   // The animation has a very very short duration (this is a technique to evaluate if it is invalid and contains
   // no frames)
   if (frames.empty()) return { nullptr, 0, -1 };
   // Previously: TODO: clear these lines
   //if (duration < 0.0001) return { nullptr, 0, 0 }; // TODO: have a value other than 0 representing the frame_count
                                                     // when not present
   int current_frame_count = 0;

   switch(playmode)
   {
      case PLAYMODE_FORWARD_ONCE: {
         float duration_so_far = 0.0f;
         for (auto &frame : frames)
         {
            duration_so_far += frame.get_duration();
            if (time < duration_so_far)
            {
               AllegroFlare::FrameAnimation::Frame* result_frame = nullptr;
               if (current_frame_count < frames.size()) result_frame = &frames[current_frame_count];
               return { result_frame, current_frame_count, frame.get_index() };
            }
            current_frame_count++;
         }
      } break;

      case PLAYMODE_FORWARD_ONCE_AND_HOLD_LAST_FRAME: {
         float duration_so_far = 0.0f;
         for (auto &frame : frames)
         {
            duration_so_far += frame.get_duration();
            if (time < duration_so_far)
            {
               AllegroFlare::FrameAnimation::Frame* result_frame = nullptr;
               if (current_frame_count < frames.size()) result_frame = &frames[current_frame_count];
               return { result_frame, current_frame_count, frame.get_index() };
            }
            current_frame_count++;
         }

         int last_frame_index = frames.size()-1;
         AllegroFlare::FrameAnimation::Frame* result_frame = &frames[last_frame_index];
         return { result_frame, last_frame_index, result_frame->get_index() };
      } break;

      case PLAYMODE_FORWARD_LOOP: {
         float duration_so_far = 0.0f;
         float duration = calculate_duration();
         float looped_playhead = fmod(time, duration);
         for (auto &frame : frames)
         {
            duration_so_far += frame.get_duration();
            if (looped_playhead < duration_so_far)
            {
               AllegroFlare::FrameAnimation::Frame* result_frame = nullptr;
               if (current_frame_count < frames.size()) result_frame = &frames[current_frame_count];
               return { result_frame, current_frame_count, frame.get_index() };
            }
            current_frame_count++;
         }
      } break;

      case PLAYMODE_FORWARD_PING_PONG: {
         float duration_so_far = 0.0f;
         float duration = calculate_duration();

         // Create an virtual ping_pong_playhead that will play in reverse after the initial duration
         float ping_pong_playhead = fmod(time, duration*2);
         // If the virtual ping_pong_playhead is over half the duration, then have the playhead play in reverse
         if (ping_pong_playhead >= duration) ping_pong_playhead = duration*2 - ping_pong_playhead;

         if (ping_pong_playhead == duration) // The playhead is exactly at the end
         {
            // Return the last frame
            int last_frame_index = frames.size()-1;
            AllegroFlare::FrameAnimation::Frame* result_frame = &frames[last_frame_index];
            return { result_frame, last_frame_index, result_frame->get_index() };
         }

         // Find the current frame
         for (auto &frame : frames)
         {
            duration_so_far += frame.get_duration();
            if (ping_pong_playhead < duration_so_far)
            {
               AllegroFlare::FrameAnimation::Frame* result_frame = nullptr;
               if (current_frame_count < frames.size()) result_frame = &frames[current_frame_count];
               return { result_frame, current_frame_count, frame.get_index() };
            }
            current_frame_count++;
         }
      } break;
   }

   return { nullptr, current_frame_count, -1 };
}

float Animation::calculate_duration()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::FrameAnimation::Animation::calculate_duration]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::FrameAnimation::Animation::calculate_duration]: error: guard \"initialized\" not met");
   }
   float result = 0.0f;
   for (auto &frame : frames)
   {
      result += frame.get_duration();
   }
   return result;
}


} // namespace FrameAnimation
} // namespace AllegroFlare


