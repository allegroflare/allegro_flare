

#include <AllegroFlare/Prototypes/Platforming2D/Entities/Basic2D.hpp>

#include <AllegroFlare/Logger.hpp>
#include <AllegroFlare/Prototypes/Platforming2D/EntityFlagNames.hpp>
#include <allegro5/allegro_primitives.h>
#include <iostream>
#include <set>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Prototypes
{
namespace Platforming2D
{
namespace Entities
{


Basic2D::Basic2D(AllegroFlare::FrameAnimation::Book* animation_book)
   : AllegroFlare::Prototypes::Platforming2D::Entities::Base(AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D::TYPE)
   , place({})
   , velocity({})
   , bitmap(nullptr)
   , bitmap_placement({})
   , bitmap_alignment_strategy("top_left")
   , bitmap_flip_h(false)
   , movement_strategy(nullptr)
   , animation_book(animation_book)
   , animation({})
   , draw_debug(false)
   , debug_box_color(ALLEGRO_COLOR{0, 0.375, 0.75, 0.75})
{
}


Basic2D::~Basic2D()
{
}


void Basic2D::set_place(AllegroFlare::Placement2D place)
{
   this->place = place;
}


void Basic2D::set_velocity(AllegroFlare::Placement2D velocity)
{
   this->velocity = velocity;
}


void Basic2D::set_bitmap(ALLEGRO_BITMAP* bitmap)
{
   this->bitmap = bitmap;
}


void Basic2D::set_bitmap_placement(AllegroFlare::Placement2D bitmap_placement)
{
   this->bitmap_placement = bitmap_placement;
}


void Basic2D::set_bitmap_flip_h(bool bitmap_flip_h)
{
   this->bitmap_flip_h = bitmap_flip_h;
}


void Basic2D::set_movement_strategy(AllegroFlare::Prototypes::Platforming2D::Entities::MovementStrategies2D::Base* movement_strategy)
{
   this->movement_strategy = movement_strategy;
}


void Basic2D::set_animation_book(AllegroFlare::FrameAnimation::Book* animation_book)
{
   this->animation_book = animation_book;
}


void Basic2D::set_draw_debug(bool draw_debug)
{
   this->draw_debug = draw_debug;
}


void Basic2D::set_debug_box_color(ALLEGRO_COLOR debug_box_color)
{
   this->debug_box_color = debug_box_color;
}


AllegroFlare::Placement2D Basic2D::get_place() const
{
   return place;
}


AllegroFlare::Placement2D Basic2D::get_velocity() const
{
   return velocity;
}


ALLEGRO_BITMAP* Basic2D::get_bitmap() const
{
   return bitmap;
}


AllegroFlare::Placement2D Basic2D::get_bitmap_placement() const
{
   return bitmap_placement;
}


std::string Basic2D::get_bitmap_alignment_strategy() const
{
   return bitmap_alignment_strategy;
}


bool Basic2D::get_bitmap_flip_h() const
{
   return bitmap_flip_h;
}


AllegroFlare::Prototypes::Platforming2D::Entities::MovementStrategies2D::Base* Basic2D::get_movement_strategy() const
{
   return movement_strategy;
}


AllegroFlare::FrameAnimation::Book* Basic2D::get_animation_book() const
{
   return animation_book;
}


bool Basic2D::get_draw_debug() const
{
   return draw_debug;
}


ALLEGRO_COLOR Basic2D::get_debug_box_color() const
{
   return debug_box_color;
}


AllegroFlare::Placement2D &Basic2D::get_place_ref()
{
   return place;
}


AllegroFlare::Placement2D &Basic2D::get_velocity_ref()
{
   return velocity;
}


AllegroFlare::Placement2D &Basic2D::get_bitmap_placement_ref()
{
   return bitmap_placement;
}


void Basic2D::set_bitmap_alignment_strategy(std::string bitmap_alignment_strategy)
{
   static std::set<std::string> valid_bitmap_alignment_strategies = {
      "top_left",
      "top_centered",
      "centered",
      "bottom_centered",
      "bottom_centered_edge",
      "disabled"
   };

   if (valid_bitmap_alignment_strategies.find(bitmap_alignment_strategy) == valid_bitmap_alignment_strategies.end())
   {
      // Not included in list
      AllegroFlare::Logger::throw_error(
         "AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D::set_bitmap_alignment_strategy",
         "Cannot set alignment of an unrecognized alignment named \"" + bitmap_alignment_strategy + "\""
      );
   }

   this->bitmap_alignment_strategy = bitmap_alignment_strategy;

   return;
}

void Basic2D::update()
{
   //std::cout << "  Basic2D::update.." << std::endl;
   if (movement_strategy)
   {
      //std::cout << "  Basic2D::movement_strategy->update().." << std::endl;
      movement_strategy->update();
   }

   if (animation.get_initialized())
   {
      animation.update();
      refresh_bitmap_to_current_animation_frame();
   }
   //refresh_bitmap();

   //place.position += velocity.position; // <-- this is now managed in the stepper
   //place.rotation += velocity.rotation;

   //place.scale += velocity.scale; // TODO: figure out what/how to apply scale velocity
   // TODO: align, size, anchor, flip

   return;
}

void Basic2D::refresh_bitmap_to_current_animation_frame()
{
   if (animation.get_initialized())
   {
      set_bitmap(animation.get_frame_now());
   }
   return;
}

void Basic2D::on_collision_update(AllegroFlare::Vec2D previous_place_position, AllegroFlare::Vec2D previous_velocity_position, AllegroFlare::Vec2D new_place_position, AllegroFlare::Vec2D new_velocity_position, std::vector<AllegroFlare::Physics::TileMapCollisionStepperCollisionInfo>* collision_step_result)
{
   if (!(collision_step_result))
   {
      std::stringstream error_message;
      error_message << "[Basic2D::on_collision_update]: error: guard \"collision_step_result\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Basic2D::on_collision_update: error: guard \"collision_step_result\" not met");
   }
   if (movement_strategy)
   {
      //std::cout << "  Basic2D::movement_strategy->update().." << std::endl;
      movement_strategy->on_collision_update(
         previous_place_position,
         previous_velocity_position,
         new_place_position,
         new_velocity_position,
         collision_step_result
      );
   }
   return;
}

void Basic2D::draw()
{
   if (!(al_is_primitives_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[Basic2D::draw]: error: guard \"al_is_primitives_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Basic2D::draw: error: guard \"al_is_primitives_addon_initialized()\" not met");
   }
   using namespace AllegroFlare::Prototypes::Platforming2D::EntityFlagNames;
   // TODO: add some reasonable guards

   place.start_transform();

   if (bitmap)
   {
      // work out the bitmap placement and alignment

      float *bitmap_x = &bitmap_placement.position.x;
      float *bitmap_y = &bitmap_placement.position.y;
      float *bitmap_align_x = &bitmap_placement.align.x;
      float *bitmap_align_y = &bitmap_placement.align.y;

      assign_alignment_strategy_values(
         &place,
         bitmap,
         bitmap_x,
         bitmap_y,
         bitmap_align_x,
         bitmap_align_y,
         bitmap_alignment_strategy
      );

      bitmap_placement.size = { (float)al_get_bitmap_width(bitmap), (float)al_get_bitmap_height(bitmap) };

      // draw the bitmap

      bitmap_placement.start_transform();
      al_draw_bitmap(bitmap, 0, 0, bitmap_flip_h ? ALLEGRO_FLIP_HORIZONTAL : 0);

      // draw the boundary rectangle for the bitmap

      if (draw_debug)
      {
         al_draw_rectangle(
            0, //bitmap_x,
            0, //bitmap_y,
            al_get_bitmap_width(bitmap), //bitmap_x + al_get_bitmap_width(bitmap),
            al_get_bitmap_width(bitmap),//bitmap_y + al_get_bitmap_height(bitmap),
            ALLEGRO_COLOR{0, 0.5, 0.25, 0.5},
            1.0 / bitmap_placement.scale.x / place.scale.x // dividing by the scalle will ensure the lines
                                                           // have a constant thickness, regardless of the scale
                                                           // of the entity or bitmap scale
         );
      }

      bitmap_placement.restore_transform();
   }

   // draw the bounding box rectangle for the entity

   if (draw_debug)
   {
      al_draw_rectangle(
         0,
         0,
         place.size.x,
         place.size.y,
         debug_box_color,
         1.0 / place.scale.x // dividing by scale will ensure the lines have a constant thickness,
                             // regardless of the scale of the entity
      );
   }

   place.restore_transform();

   // draw a box around the origin

   if (draw_debug)
   {
      al_draw_rectangle(
         place.position.x-1,
         place.position.y-1,
         place.position.x+1,
         place.position.y+1,
         debug_box_color,
         1.0
      );

      // add markers to help indicate status (ajacent to walls, ceiling, floor, ...)
      if (exists(ADJACENT_TO_CEILING))
      {
         al_draw_filled_circle(place.position.x, place.position.y - 3, 1.5, debug_box_color);
      }
      if (exists(ADJACENT_TO_LEFT_WALL))
      {
         al_draw_filled_circle(place.position.x-3, place.position.y, 1.5, debug_box_color);
      }
      if (exists(ADJACENT_TO_RIGHT_WALL))
      {
         al_draw_filled_circle(place.position.x+3, place.position.y, 1.5, debug_box_color);
      }
      if (exists(ADJACENT_TO_FLOOR))
      {
         al_draw_filled_circle(place.position.x, place.position.y+3, 1.5, debug_box_color);
      }
   }

   return;
}

void Basic2D::fit_to_bitmap()
{
   if (!(bitmap))
   {
      std::stringstream error_message;
      error_message << "[Basic2D::fit_to_bitmap]: error: guard \"bitmap\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Basic2D::fit_to_bitmap: error: guard \"bitmap\" not met");
   }
   place.size.x = al_get_bitmap_width(bitmap);
   place.size.y = al_get_bitmap_height(bitmap);
   return;
}

void Basic2D::disable_bitmap_alignment_strategy()
{
   bitmap_alignment_strategy = "disabled";
   return;
}

void Basic2D::assign_alignment_strategy_values(AllegroFlare::Placement2D* parent_placement, ALLEGRO_BITMAP* bitmap, float* bitmap_x, float* bitmap_y, float* bitmap_align_x, float* bitmap_align_y, std::string bitmap_alignment_strategy)
{
   if (!(parent_placement))
   {
      std::stringstream error_message;
      error_message << "[Basic2D::assign_alignment_strategy_values]: error: guard \"parent_placement\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Basic2D::assign_alignment_strategy_values: error: guard \"parent_placement\" not met");
   }
   if (!(bitmap))
   {
      std::stringstream error_message;
      error_message << "[Basic2D::assign_alignment_strategy_values]: error: guard \"bitmap\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Basic2D::assign_alignment_strategy_values: error: guard \"bitmap\" not met");
   }
   if (!(bitmap_x))
   {
      std::stringstream error_message;
      error_message << "[Basic2D::assign_alignment_strategy_values]: error: guard \"bitmap_x\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Basic2D::assign_alignment_strategy_values: error: guard \"bitmap_x\" not met");
   }
   if (!(bitmap_y))
   {
      std::stringstream error_message;
      error_message << "[Basic2D::assign_alignment_strategy_values]: error: guard \"bitmap_y\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Basic2D::assign_alignment_strategy_values: error: guard \"bitmap_y\" not met");
   }
   if (!(bitmap_align_x))
   {
      std::stringstream error_message;
      error_message << "[Basic2D::assign_alignment_strategy_values]: error: guard \"bitmap_align_x\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Basic2D::assign_alignment_strategy_values: error: guard \"bitmap_align_x\" not met");
   }
   if (!(bitmap_align_y))
   {
      std::stringstream error_message;
      error_message << "[Basic2D::assign_alignment_strategy_values]: error: guard \"bitmap_align_y\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Basic2D::assign_alignment_strategy_values: error: guard \"bitmap_align_y\" not met");
   }
   if (bitmap_alignment_strategy == "top_left")
   {
      *bitmap_x = 0;
      *bitmap_y = 0;
      *bitmap_align_x = 0;
      *bitmap_align_y = 0;
   }
   else if (bitmap_alignment_strategy == "top_centered") // as in a hanging on the ceiling
   {
      *bitmap_x = parent_placement->size.x * 0.5;
      *bitmap_y = 0;
      *bitmap_align_x = 0.5;
      *bitmap_align_y = 0;
   }
   else if (bitmap_alignment_strategy == "centered") // as in a schmup
   {
      *bitmap_x = parent_placement->size.x * 0.5;
      *bitmap_y = parent_placement->size.y * 0.5;
      *bitmap_align_x = 0.5;
      *bitmap_align_y = 0.5;
   }
   else if (bitmap_alignment_strategy == "bottom_centered") // as in a top-down 2D dungeon crawler
   {
      *bitmap_x = parent_placement->size.x * 0.5;
      *bitmap_y = parent_placement->size.y * 0.5;
      *bitmap_align_x = 0.5;
      *bitmap_align_y = 1.0;
   }
   else if (bitmap_alignment_strategy == "bottom_centered_edge") // as in a 2D platformer
   {
      *bitmap_x = parent_placement->size.x * 0.5;
      *bitmap_y = parent_placement->size.y;
      *bitmap_align_x = 0.5;
      *bitmap_align_y = 1.0;
   }
   else if (bitmap_alignment_strategy == "disabled") // You can assign your own custom values and they are retained
   {
      // NOTE: do nothing here
   }
   else
   {
      throw std::runtime_error("[AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D] error: "
                               "Unrecognized bitmap_alignment_strategy");
   }
   return;
}

void Basic2D::set_animation_playback_rate(float multiplier)
{
   animation.set_playspeed_multiplier(multiplier);
   return;
}

bool Basic2D::get_animation_finished()
{
   return animation.get_finished();
}

int Basic2D::get_current_animation_frame_num()
{
   return animation.get_frame_num_now();
}

void Basic2D::set_animation(std::string animation_name)
{
   if (!(animation_book))
   {
      std::stringstream error_message;
      error_message << "[Basic2D::set_animation]: error: guard \"animation_book\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Basic2D::set_animation: error: guard \"animation_book\" not met");
   }
   if (!(animation_book->animation_exists(animation_name)))
   {
      std::stringstream error_message;
      error_message << "[Basic2D::set_animation]: error: guard \"animation_book->animation_exists(animation_name)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Basic2D::set_animation: error: guard \"animation_book->animation_exists(animation_name)\" not met");
   }
   animation = animation_book->find_animation_by_name(animation_name);
   animation.initialize();
   animation.start(); // NOTE: consider if automatic "start" is needed here
   refresh_bitmap_to_current_animation_frame();
   return;
}


} // namespace Entities
} // namespace Platforming2D
} // namespace Prototypes
} // namespace AllegroFlare


