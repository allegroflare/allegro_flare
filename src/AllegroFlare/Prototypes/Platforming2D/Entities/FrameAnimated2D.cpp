

#include <AllegroFlare/Prototypes/Platforming2D/Entities/FrameAnimated2D.hpp>

#include <AllegroFlare/Prototypes/Platforming2D/EntityFlagNames.hpp>
#include <allegro5/allegro_primitives.h>
#include <iostream>
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


FrameAnimated2D::FrameAnimated2D(AllegroFlare::FrameAnimation::Book* animation_book)
   : AllegroFlare::Prototypes::Platforming2D::Entities::Base(AllegroFlare::Prototypes::Platforming2D::Entities::FrameAnimated2D::TYPE)
   , animation_book(animation_book)
   , place({})
   , velocity({})
   , animation({})
   , bitmap_internal(nullptr)
   , bitmap_alignment_strategy("top_left")
   , bitmap_flip_h(false)
   , debug_box_color(ALLEGRO_COLOR{0, 0.375, 0.75, 0.75})
{
}


FrameAnimated2D::~FrameAnimated2D()
{
}


void FrameAnimated2D::set_animation_book(AllegroFlare::FrameAnimation::Book* animation_book)
{
   this->animation_book = animation_book;
}


void FrameAnimated2D::set_place(AllegroFlare::Placement2D place)
{
   this->place = place;
}


void FrameAnimated2D::set_velocity(AllegroFlare::Placement2D velocity)
{
   this->velocity = velocity;
}


void FrameAnimated2D::set_bitmap_alignment_strategy(std::string bitmap_alignment_strategy)
{
   this->bitmap_alignment_strategy = bitmap_alignment_strategy;
}


void FrameAnimated2D::set_bitmap_flip_h(bool bitmap_flip_h)
{
   this->bitmap_flip_h = bitmap_flip_h;
}


void FrameAnimated2D::set_debug_box_color(ALLEGRO_COLOR debug_box_color)
{
   this->debug_box_color = debug_box_color;
}


AllegroFlare::FrameAnimation::Book* FrameAnimated2D::get_animation_book() const
{
   return animation_book;
}


AllegroFlare::Placement2D FrameAnimated2D::get_place() const
{
   return place;
}


AllegroFlare::Placement2D FrameAnimated2D::get_velocity() const
{
   return velocity;
}


std::string FrameAnimated2D::get_bitmap_alignment_strategy() const
{
   return bitmap_alignment_strategy;
}


bool FrameAnimated2D::get_bitmap_flip_h() const
{
   return bitmap_flip_h;
}


ALLEGRO_COLOR FrameAnimated2D::get_debug_box_color() const
{
   return debug_box_color;
}


AllegroFlare::Placement2D &FrameAnimated2D::get_place_ref()
{
   return place;
}


AllegroFlare::Placement2D &FrameAnimated2D::get_velocity_ref()
{
   return velocity;
}


void FrameAnimated2D::update()
{
   animation.update();
   refresh_bitmap();
   //place.position += velocity.position; // <-- this is now managed in the stepper
   //place.rotation += velocity.rotation;

   //place.scale += velocity.scale; // TODO: figure out what/how to apply scale velocity
   // TODO: align, size, anchor, flip

   return;
}

void FrameAnimated2D::refresh_bitmap()
{
   bitmap_internal = animation.get_frame_now();
   //fit_to_bitmap(); // This may be redundant, however it's not yet determined if Animation/Book will
                    // always be returning fixed size bitmaps.  Also, in some scenarios it's likely the
                    // collision box will be different from the bitmap, and for the time being it appears
                    // the two are considered the same.
   return;
}

void FrameAnimated2D::draw()
{
   if (!(al_is_primitives_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[FrameAnimated2D::draw]: error: guard \"al_is_primitives_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("FrameAnimated2D::draw: error: guard \"al_is_primitives_addon_initialized()\" not met");
   }
   using namespace AllegroFlare::Prototypes::Platforming2D::EntityFlagNames;
   // TODO: add some reasonable guards
   //if (bitmap)
   //{
      // TODO: find a more proper place for this
      //if (bitmap_alignment_strategy == "bottom_centered_edge") place.align.y = 1.0;
      //if (bitmap_alignment_strategy == "bottom_centered") place.align.y = 0.5;

      place.start_transform();

   if (bitmap_internal)
   {
      if (bitmap_alignment_strategy == "bottom_centered_edge") place.align.y = 1.0;
      if (bitmap_alignment_strategy == "bottom_centered") place.align.y = 0.5;
      // draw the bitmap
      float bitmap_x = 0;
      float bitmap_y = 0;
      assign_alignment_strategy_values(&place, bitmap_internal, &bitmap_x, &bitmap_y, bitmap_alignment_strategy);
      assign_alignment_strategy_values(&place, bitmap_internal, &bitmap_x, &bitmap_y, bitmap_alignment_strategy);
      al_draw_bitmap(bitmap_internal, bitmap_x, bitmap_y, bitmap_flip_h ? ALLEGRO_FLIP_HORIZONTAL : 0);

      // draw the bitmap's boundary debug rectangle
      // TODO: move this out of "if (bitmap)" clause
      al_draw_rectangle(
         bitmap_x,
         bitmap_y,
         bitmap_x + al_get_bitmap_width(bitmap_internal),
         bitmap_y + al_get_bitmap_height(bitmap_internal),
         ALLEGRO_COLOR{0, 0.5, 0.25, 0.5},
         1.0
      );
   }


      // draw the bounding box rectangle
      // TODO: move this out of "if (bitmap)" clause
      al_draw_rectangle(
         0,
         0,
         place.size.x,
         place.size.y,
         debug_box_color,
         1.0
      );

      place.restore_transform();

      // draw a box around the unaltered position
      al_draw_rectangle(
         place.position.x-3,
         place.position.y-3,
         place.position.x+3,
         place.position.y+3,
         debug_box_color,
         1.0
      );

   if (exists(ADJACENT_TO_CEILING))
   {
      al_draw_filled_circle(place.position.x, place.position.y - 6, 2, debug_box_color);
   }
   if (exists(ADJACENT_TO_LEFT_WALL))
   {
      al_draw_filled_circle(place.position.x-6, place.position.y, 2, debug_box_color);
   }
   if (exists(ADJACENT_TO_RIGHT_WALL))
   {
      al_draw_filled_circle(place.position.x+6, place.position.y, 2, debug_box_color);
   }
   if (exists(ADJACENT_TO_FLOOR))
   {
      al_draw_filled_circle(place.position.x, place.position.y+6, 2, debug_box_color);
   }

   return;
}

void FrameAnimated2D::set_animation(std::string animation_name)
{
   if (!(animation_book))
   {
      std::stringstream error_message;
      error_message << "[FrameAnimated2D::set_animation]: error: guard \"animation_book\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("FrameAnimated2D::set_animation: error: guard \"animation_book\" not met");
   }
   if (!(animation_book->animation_exists(animation_name)))
   {
      std::stringstream error_message;
      error_message << "[FrameAnimated2D::set_animation]: error: guard \"animation_book->animation_exists(animation_name)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("FrameAnimated2D::set_animation: error: guard \"animation_book->animation_exists(animation_name)\" not met");
   }
   // TODO: check "exists" in animation_book
   animation = animation_book->find_animation_by_name(animation_name);
   animation.initialize();
   animation.start(); // NOTE: consider if automatic "start" is needed here
   refresh_bitmap();
   return;
}

void FrameAnimated2D::fit_to_bitmap()
{
   if (!(bitmap_internal))
   {
      std::stringstream error_message;
      error_message << "[FrameAnimated2D::fit_to_bitmap]: error: guard \"bitmap_internal\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("FrameAnimated2D::fit_to_bitmap: error: guard \"bitmap_internal\" not met");
   }
   place.size.x = al_get_bitmap_width(bitmap_internal);
   place.size.y = al_get_bitmap_height(bitmap_internal);
   return;
}

void FrameAnimated2D::assign_alignment_strategy_values(AllegroFlare::Placement2D* parent_placement, ALLEGRO_BITMAP* bitmap, float* bitmap_x, float* bitmap_y, std::string bitmap_alignment_strategy)
{
   if (!(parent_placement))
   {
      std::stringstream error_message;
      error_message << "[FrameAnimated2D::assign_alignment_strategy_values]: error: guard \"parent_placement\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("FrameAnimated2D::assign_alignment_strategy_values: error: guard \"parent_placement\" not met");
   }
   if (!(bitmap))
   {
      std::stringstream error_message;
      error_message << "[FrameAnimated2D::assign_alignment_strategy_values]: error: guard \"bitmap\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("FrameAnimated2D::assign_alignment_strategy_values: error: guard \"bitmap\" not met");
   }
   if (!(bitmap_x))
   {
      std::stringstream error_message;
      error_message << "[FrameAnimated2D::assign_alignment_strategy_values]: error: guard \"bitmap_x\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("FrameAnimated2D::assign_alignment_strategy_values: error: guard \"bitmap_x\" not met");
   }
   if (!(bitmap_y))
   {
      std::stringstream error_message;
      error_message << "[FrameAnimated2D::assign_alignment_strategy_values]: error: guard \"bitmap_y\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("FrameAnimated2D::assign_alignment_strategy_values: error: guard \"bitmap_y\" not met");
   }
   if (bitmap_alignment_strategy == "top_left")
   {
      *bitmap_x = 0;
      *bitmap_y = 0;
   }
   else if (bitmap_alignment_strategy == "centered") // as in a schmup
   {
      // TODO: fix this so that it works as expected with different parent_placement alignment
      *bitmap_x = -(al_get_bitmap_width(bitmap) * 0.5) + parent_placement->size.x * 0.5;
      *bitmap_y = -(al_get_bitmap_height(bitmap) * 0.5) + parent_placement->size.y * 0.5;
   }
   else if (bitmap_alignment_strategy == "bottom_centered") // as in a top-down 2D dungeon crawler
   {
      //TODO: clarify this concept
      *bitmap_x = -(al_get_bitmap_width(bitmap) * 0.5) + parent_placement->size.x * 0.5;
      *bitmap_y = -al_get_bitmap_height(bitmap) + parent_placement->size.y * 0.5;
   }
   else if (bitmap_alignment_strategy == "bottom_centered_edge") // as in a 2D platformer
   {
      // TODO: this is broken for different types of sizes.
      *bitmap_x = -(al_get_bitmap_width(bitmap) * 0.5) + parent_placement->size.x * 0.5;
      *bitmap_y = -(al_get_bitmap_height(bitmap) * 0.25);
   }
   else
   {
      throw std::runtime_error("[AllegroFlare::Prototypes::Platforming2D::Entities::FrameAnimated2D] error: "
                               "Unrecognized bitmap_alignment_strategy");
   }
   return;
}


} // namespace Entities
} // namespace Platforming2D
} // namespace Prototypes
} // namespace AllegroFlare


