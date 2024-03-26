

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


Basic2D::Basic2D()
   : AllegroFlare::Prototypes::Platforming2D::Entities::Base(AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D::TYPE)
   , place({})
   , velocity({})
   , bitmap(nullptr)
   , bitmap_placement({})
   , bitmap_alignment_strategy("top_left")
   , bitmap_flip_h(false)
   , bitmap_blend_mode(AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D::BlendMode::NORMAL)
   , shader(nullptr)
   , movement_strategy(nullptr)
   , asset_studio_database(nullptr)
   , animation_book(nullptr)
   , animation({})
   , draw_debug(false)
   , debug_box_color(ALLEGRO_COLOR{0, 0.375, 0.75, 0.75})
   , x(place.position.x)
   , y(place.position.y)
   , width(place.size.x)
   , height(place.size.y)
   , vx(velocity.position.x)
   , vy(velocity.position.y)
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


void Basic2D::set_bitmap_blend_mode(AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D::BlendMode bitmap_blend_mode)
{
   this->bitmap_blend_mode = bitmap_blend_mode;
}


void Basic2D::set_shader(AllegroFlare::Shaders::Base* shader)
{
   this->shader = shader;
}


void Basic2D::set_movement_strategy(AllegroFlare::Prototypes::Platforming2D::Entities::MovementStrategies2D::Base* movement_strategy)
{
   this->movement_strategy = movement_strategy;
}


void Basic2D::set_asset_studio_database(AllegroFlare::AssetStudio::Database* asset_studio_database)
{
   this->asset_studio_database = asset_studio_database;
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


AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D::BlendMode Basic2D::get_bitmap_blend_mode() const
{
   return bitmap_blend_mode;
}


AllegroFlare::Shaders::Base* Basic2D::get_shader() const
{
   return shader;
}


AllegroFlare::Prototypes::Platforming2D::Entities::MovementStrategies2D::Base* Basic2D::get_movement_strategy() const
{
   return movement_strategy;
}


AllegroFlare::AssetStudio::Database* Basic2D::get_asset_studio_database() const
{
   return asset_studio_database;
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


AllegroFlare::AssetStudio::Database* &Basic2D::get_asset_studio_database_ref()
{
   return asset_studio_database;
}


AllegroFlare::FrameAnimation::Book* &Basic2D::get_animation_book_ref()
{
   return animation_book;
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

void Basic2D::on_collides_with_player(AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D* player_controlled_entity)
{
   // NOTE: This method will only be called if this entity is tagged with COLLIDES_WITH_PLAYER and there is a
   // collision that occurs during the physics step
   return;
}

void Basic2D::on_collision_update(AllegroFlare::Vec2D previous_place_position, AllegroFlare::Vec2D previous_velocity_position, AllegroFlare::Vec2D new_place_position, AllegroFlare::Vec2D new_velocity_position, std::vector<AllegroFlare::Physics::TileMapCollisionStepperCollisionInfo>* collision_step_result, bool top_edge_is_currently_adjacent_to_wall, bool right_edge_is_currently_adjacent_to_wall, bool bottom_edge_is_currently_adjacent_to_wall, bool left_edge_is_currently_adjacent_to_wall)
{
   if (!(collision_step_result))
   {
      std::stringstream error_message;
      error_message << "[Basic2D::on_collision_update]: error: guard \"collision_step_result\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Basic2D::on_collision_update: error: guard \"collision_step_result\" not met");
   }
   using namespace AllegroFlare::Prototypes::Platforming2D::EntityFlagNames;

   if (movement_strategy)
   {
      //std::cout << "  Basic2D::movement_strategy->update().." << std::endl;
      movement_strategy->on_collision_update(
         previous_place_position,
         previous_velocity_position,
         new_place_position,
         new_velocity_position,
         collision_step_result,
         top_edge_is_currently_adjacent_to_wall,
         right_edge_is_currently_adjacent_to_wall,
         bottom_edge_is_currently_adjacent_to_wall,
         left_edge_is_currently_adjacent_to_wall
      );
   }

   // TODO: Test this behavior
   // TODO: See if this behavior can be extracted out:

   {
      bool is_currently_adjacent_to_floor = bottom_edge_is_currently_adjacent_to_wall;
      bool is_currently_adjacent_to_ceiling = top_edge_is_currently_adjacent_to_wall;
      bool is_currently_adjacent_to_left_wall = left_edge_is_currently_adjacent_to_wall;
      bool is_currently_adjacent_to_right_wall = right_edge_is_currently_adjacent_to_wall;

      bool was_adjacent_to_floor_prior = exists(ADJACENT_TO_FLOOR);
      if (was_adjacent_to_floor_prior && is_currently_adjacent_to_floor) {} // on stay
      else if (!was_adjacent_to_floor_prior && is_currently_adjacent_to_floor) // on enter
      {
         set(ADJACENT_TO_FLOOR);
         //on_attribute_added(ADJACENT_TO_FLOOR);
      }
      else if (was_adjacent_to_floor_prior && !is_currently_adjacent_to_floor) // on exit
      {
         remove(ADJACENT_TO_FLOOR);
         //on_attribute_removed(ADJACENT_TO_FLOOR);
      }
      else if (!was_adjacent_to_floor_prior && !is_currently_adjacent_to_floor) {} // while off

      bool was_adjacent_to_ceiling_prior = exists(ADJACENT_TO_CEILING);
      if (is_currently_adjacent_to_ceiling) set(ADJACENT_TO_CEILING);
      else remove(ADJACENT_TO_CEILING);

      bool was_adjacent_to_left_wall_prior = exists(ADJACENT_TO_LEFT_WALL);
      if (is_currently_adjacent_to_left_wall) set(ADJACENT_TO_LEFT_WALL);
      else remove(ADJACENT_TO_LEFT_WALL);

      bool was_adjacent_to_right_wall_prior = exists(ADJACENT_TO_RIGHT_WALL);
      if (is_currently_adjacent_to_right_wall) set(ADJACENT_TO_RIGHT_WALL);
      else remove(ADJACENT_TO_RIGHT_WALL);
   }

   return;
}

void Basic2D::set_blending_mode_if_not_normal()
{
   switch (bitmap_blend_mode)
   {
      case NORMAL: {
         // Do nothing
      } break;

      case MULTIPLY: {
         // NOTE: The manual recommends ALLEGRO_ZERO as the last argument:
         //al_set_blender(ALLEGRO_ADD, ALLEGRO_DEST_COLOR, ALLEGRO_ZERO);
         // NOTE: However, It was modified to ALLEGRO_INVERSE_ALPHA to respect the alpha of the drawing bitmap,
         // but it's unsure if there are side effects
         al_set_blender(ALLEGRO_ADD, ALLEGRO_DEST_COLOR, ALLEGRO_INVERSE_ALPHA);
      } break;

      case ADDITIVE: {
         al_set_blender(ALLEGRO_ADD, ALLEGRO_ONE, ALLEGRO_ONE);
      } break;

      default: {
         // TODO: Figure out what to do in this case, maybe throw?
      } break;
   };
   return;
}

void Basic2D::restore_blending_mode()
{
   switch (bitmap_blend_mode)
   {
      case NORMAL: {
         // Do nothing
      } break;

      case MULTIPLY: {
         al_set_blender(ALLEGRO_ADD, ALLEGRO_ONE, ALLEGRO_INVERSE_ALPHA);
      } break;

      case ADDITIVE: {
         al_set_blender(ALLEGRO_ADD, ALLEGRO_ONE, ALLEGRO_INVERSE_ALPHA);
      } break;

      default: {
         // TODO: Figure out what to do in this case, maybe throw?
      } break;
   };
   return;
}

void Basic2D::activate_shader()
{
   if (shader) shader->activate();
   return;
}

void Basic2D::deactivate_shader()
{
   if (shader) shader->deactivate();
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

      // TODO: Consider if continually assigning the size is preferred or not
      bitmap_placement.size = { (float)al_get_bitmap_width(bitmap), (float)al_get_bitmap_height(bitmap) };

      // draw the bitmap

      bitmap_placement.start_transform();

      // Activate custom shader (if there is one)
      // TODO: Consider alternatives to this, particularly how the previous shader would be restored
      activate_shader();

      // Set the blending mode
      set_blending_mode_if_not_normal();

      // Draw the sprite
      al_draw_bitmap(bitmap, 0, 0, bitmap_flip_h ? ALLEGRO_FLIP_HORIZONTAL : 0);

      // Restore the blending mode
      restore_blending_mode();

      // Deactivate the shader to the default
      // TODO: Consider alternatives to this, particularly how the previous shader would be restored
      deactivate_shader();

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
   if (!((animation_book || asset_studio_database)))
   {
      std::stringstream error_message;
      error_message << "[Basic2D::set_animation]: error: guard \"(animation_book || asset_studio_database)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Basic2D::set_animation: error: guard \"(animation_book || asset_studio_database)\" not met");
   }
   //if (animation_book && asset_studio_database)
   //{
      //AllegroFlare::Logger::throw_error(
            //"AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D::set_animation",
            //"This entity contains pointers to both an \"animation_book\" and an \"asset_studio_database\", but "
               //"only one should be present."
         //);
   //}

   //AllegroFlare::Animation *found_animation_book_animation = nullptr;
   //AllegroFlare::Animation *found_asset_studio_animation = nullptr;

   // Find the asset in the animation_book
   bool animation_book_animation_found = false;
   bool asset_studio_database_animation_found = false;

   if (animation_book)
   {
      if (!animation_book->animation_exists(animation_name))
      {
         //AllegroFlare::Logger::throw_error(
               //"AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D::set_animation",
               //"The animation \"" + animation_name + "\" does not exist in the \"animation_book\"."
            //);
      }
      else
      {
         animation = animation_book->find_animation_by_name(animation_name);
         animation.initialize();
         animation.start(); // NOTE: consider if automatic "start" is needed here
         refresh_bitmap_to_current_animation_frame();
         animation_book_animation_found = true;
      }
   }

   // Find the asset in the asset_studio_database
   if (asset_studio_database)
   {
      if (!asset_studio_database->asset_exists_as_animation(animation_name))
      {
         // Nothing to do
      }
      else
      {
         animation = *asset_studio_database->find_animation_by_identifier(animation_name);
         animation.initialize();
         animation.start(); // NOTE: consider if automatic "start" is needed here
         refresh_bitmap_to_current_animation_frame();
         asset_studio_database_animation_found = true;
      }
   }

   if (!animation_book_animation_found && !asset_studio_database_animation_found)
   {
      if (animation_book && !asset_studio_database)
      {
         AllegroFlare::Logger::throw_error(
               "AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D::set_animation",
               "The animation \"" + animation_name + "\" was not found in the \"animation_book\". (There "
                  "was no \"asset_studio_database\" present to look in, either.)"
            );
      }
      else if (!animation_book && asset_studio_database)
      {
         AllegroFlare::Logger::throw_error(
               "AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D::set_animation",
               "The animation \"" + animation_name + "\" was not found in the \"asset_studio_database\". (There "
                  "was no \"animation_book\" present to look in, either.)"
            );
      }
      else if (animation_book && asset_studio_database)
      {
         AllegroFlare::Logger::throw_error(
               "AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D::set_animation",
               "The animation \"" + animation_name + "\" was not found in either the \"animation_book\" or the "
                  "\"asset_studio_database\"."
            );
      }
   }

   if (animation_book_animation_found && asset_studio_database_animation_found)
   {
      AllegroFlare::Logger::throw_error(
            "AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D::set_animation",
            "The animation \"" + animation_name + "\" was found in both the \"animation_book\" and the "
               "\"asset_studio_database\". It is only expected to be in one or the other."
         );
   }

   //animation = *found_animation_book_animation;

   return;
}


} // namespace Entities
} // namespace Platforming2D
} // namespace Prototypes
} // namespace AllegroFlare


