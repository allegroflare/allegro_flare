#pragma once


#include <framework/vec2i.hpp>


class TileMap;
class Sprite;
class ALLEGRO_BITMAP;


class TileMapCollisionResponse
{
public:
   enum direction_t
   {
      SPRITE_MOVING_UP,
      SPRITE_MOVING_DOWN,
      SPRITE_MOVING_LEFT,
      SPRITE_MOVING_RIGHT
   };

private:
   TileMap *tile_map;
   Sprite *sprite;

public:
   TileMapCollisionResponse(TileMap *tile_map, Sprite *sprite);
   ~TileMapCollisionResponse();

   void process(bool (*on_collide)(TileMap *, Sprite *, vec2i tile_coordinate, TileMapCollisionResponse::direction_t, void *data)=nullptr, void *data=nullptr);
};


