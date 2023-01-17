

#include <tilemap/tile_map_collision_response.hpp>

#include <tilemap/lib/NextCollidingTilesCalculator.hpp>
#include <tilemap/tile_map.hpp>
#include <tilemap/sprite.hpp>


TileMapCollisionResponse::TileMapCollisionResponse(TileMap *tile_map, Sprite *sprite)
   : tile_map(tile_map)
   , sprite(sprite)
{
}


TileMapCollisionResponse::~TileMapCollisionResponse()
{
}


void TileMapCollisionResponse::process(bool (*on_collide)(TileMap *tile, Sprite *sprite, vec2i tile_coordinate, TileMapCollisionResponse::direction_t direction_of_collision, void *data), void *data)
{
   NextCollidingTilesCalculator horizontal_calculator(
         NextCollidingTilesCalculator::X_AXIS,
         sprite->placement.position.x,
         sprite->placement.position.y,
         sprite->placement.size.x,
         sprite->placement.size.y,
         sprite->velocity.position.x,
         sprite->velocity.position.y
      );

   std::vector<vec2i> horizontal_colliding_tiles = horizontal_calculator.next_colliding_tiles();
   TileMapCollisionResponse::direction_t sprite_horizontal_direction_of_travel = sprite->velocity.x > 0.0 ? SPRITE_MOVING_RIGHT : SPRITE_MOVING_LEFT;
   for (auto &tile : horizontal_colliding_tiles) on_collide(tile_map, sprite, tile, sprite_horizontal_direction_of_travel, data);
   sprite->placement.x += sprite->velocity.x;

   NextCollidingTilesCalculator vertical_calculator(
         NextCollidingTilesCalculator::Y_AXIS,
         sprite->placement.position.x,
         sprite->placement.position.y,
         sprite->placement.size.x,
         sprite->placement.size.y,
         sprite->velocity.position.x,
         sprite->velocity.position.y
      );

   std::vector<vec2i> vertically_colliding_tiles = vertical_calculator.next_colliding_tiles();
   TileMapCollisionResponse::direction_t sprite_vertical_direction_of_travel = sprite->velocity.y > 0.0 ? SPRITE_MOVING_DOWN : SPRITE_MOVING_UP;
   for (auto &tile : vertically_colliding_tiles) on_collide(tile_map, sprite, tile, sprite_vertical_direction_of_travel, data);
   sprite->placement.y += sprite->velocity.y;
}


