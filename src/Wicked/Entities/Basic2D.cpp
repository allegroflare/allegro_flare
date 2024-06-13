

#include <Wicked/Entities/Basic2D.hpp>

#include <Wicked/EntityFlagNames.hpp>
#include <allegro5/allegro_primitives.h>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace Wicked
{
namespace Entities
{


Basic2D::Basic2D()
   : Wicked::Entities::Base()
   , place({})
   , velocity({})
   , bitmap(nullptr)
   , bitmap_alignment_strategy("top_left")
   , bitmap_flip_h(false)
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


void Basic2D::set_bitmap_alignment_strategy(std::string bitmap_alignment_strategy)
{
   this->bitmap_alignment_strategy = bitmap_alignment_strategy;
}


void Basic2D::set_bitmap_flip_h(bool bitmap_flip_h)
{
   this->bitmap_flip_h = bitmap_flip_h;
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


std::string Basic2D::get_bitmap_alignment_strategy() const
{
   return bitmap_alignment_strategy;
}


bool Basic2D::get_bitmap_flip_h() const
{
   return bitmap_flip_h;
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


void Basic2D::update()
{
   //place.position += velocity.position; // <-- this is now managed in the stepper
   //place.rotation += velocity.rotation;

   //place.scale += velocity.scale; // TODO: figure out what/how to apply scale velocity
   // TODO: align, size, anchor, flip

   return;
}

void Basic2D::draw()
{
   if (!(al_is_primitives_addon_initialized()))
   {
      std::stringstream error_message;
      error_message << "[Wicked::Entities::Basic2D::draw]: error: guard \"al_is_primitives_addon_initialized()\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Wicked::Entities::Basic2D::draw]: error: guard \"al_is_primitives_addon_initialized()\" not met");
   }
   // TODO: add some reasonable guards
   //if (bitmap)
   //{
      // TODO: find a more proper place for this
      //if (bitmap_alignment_strategy == "bottom_centered_edge") place.align.y = 1.0;
      //if (bitmap_alignment_strategy == "bottom_centered") place.align.y = 0.5;

      place.start_transform();

   if (bitmap)
   {
      if (bitmap_alignment_strategy == "bottom_centered_edge") place.align.y = 1.0;
      if (bitmap_alignment_strategy == "bottom_centered") place.align.y = 0.5;
      // draw the bitmap
      float bitmap_x = 0;
      float bitmap_y = 0;
      assign_alignment_strategy_values(&place, bitmap, &bitmap_x, &bitmap_y, bitmap_alignment_strategy);
      assign_alignment_strategy_values(&place, bitmap, &bitmap_x, &bitmap_y, bitmap_alignment_strategy);
      al_draw_bitmap(bitmap, bitmap_x, bitmap_y, bitmap_flip_h ? ALLEGRO_FLIP_HORIZONTAL : 0);

      // draw the bitmap's boundary debug rectangle
      // TODO: move this out of "if (bitmap)" clause
      al_draw_rectangle(
         bitmap_x,
         bitmap_y,
         bitmap_x + al_get_bitmap_width(bitmap),
         bitmap_y + al_get_bitmap_height(bitmap),
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

   //}
   return;
}

void Basic2D::fit_to_bitmap()
{
   if (!(bitmap))
   {
      std::stringstream error_message;
      error_message << "[Wicked::Entities::Basic2D::fit_to_bitmap]: error: guard \"bitmap\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Wicked::Entities::Basic2D::fit_to_bitmap]: error: guard \"bitmap\" not met");
   }
   place.size.x = al_get_bitmap_width(bitmap);
   place.size.y = al_get_bitmap_height(bitmap);
   return;
}

void Basic2D::assign_alignment_strategy_values(AllegroFlare::Placement2D* parent_placement, ALLEGRO_BITMAP* bitmap, float* bitmap_x, float* bitmap_y, std::string bitmap_alignment_strategy)
{
   if (!(parent_placement))
   {
      std::stringstream error_message;
      error_message << "[Wicked::Entities::Basic2D::assign_alignment_strategy_values]: error: guard \"parent_placement\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Wicked::Entities::Basic2D::assign_alignment_strategy_values]: error: guard \"parent_placement\" not met");
   }
   if (!(bitmap))
   {
      std::stringstream error_message;
      error_message << "[Wicked::Entities::Basic2D::assign_alignment_strategy_values]: error: guard \"bitmap\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Wicked::Entities::Basic2D::assign_alignment_strategy_values]: error: guard \"bitmap\" not met");
   }
   if (!(bitmap_x))
   {
      std::stringstream error_message;
      error_message << "[Wicked::Entities::Basic2D::assign_alignment_strategy_values]: error: guard \"bitmap_x\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Wicked::Entities::Basic2D::assign_alignment_strategy_values]: error: guard \"bitmap_x\" not met");
   }
   if (!(bitmap_y))
   {
      std::stringstream error_message;
      error_message << "[Wicked::Entities::Basic2D::assign_alignment_strategy_values]: error: guard \"bitmap_y\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[Wicked::Entities::Basic2D::assign_alignment_strategy_values]: error: guard \"bitmap_y\" not met");
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
      throw std::runtime_error("[Wicked/Entities/Basic2D] error: Unrecognized bitmap_alignment_strategy");
   }
   return;
}


} // namespace Entities
} // namespace Wicked


