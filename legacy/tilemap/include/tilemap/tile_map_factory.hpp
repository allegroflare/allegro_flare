#pragma once


#include <tilemap/lib/SixteenEdgeTileSet.hpp>
#include <tilemap/sprite_sheet.hpp>
#include <set>


class TileMap;


class TileMapFactory
{
private:
   SpriteSheet forest_tiles_sprite_sheet;
   SpriteSheet zoria_tiles_sprite_sheet;
   SixteenEdgeTileSet zoria_grass_16_tileset;
   SixteenEdgeTileSet zoria_wall_16_tileset;

public:
   TileMapFactory();
   ~TileMapFactory();

   TileMap *create_forest_tile_map();
   TileMap *create_zoria_tile_map();
   TileMap *create_zoria_grass_map();
   TileMap *create_zoria_processed_map();

   std::set<ALLEGRO_BITMAP *> get_zoria_solids();
};


