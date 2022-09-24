#pragma once


#include <map>
#include <string>


enum
{
   CURSOR_BRUSH_CUBE = 1,
   CURSOR_BRUSH_RING,
   CURSOR_BRUSH_FLOOR_10X10,
   CURSOR_BRUSH_STONE_FENCE,
   CURSOR_BRUSH_ARCHWAY,
   CURSOR_BRUSH_BLACK_STONE,
   CURSOR_BRUSH_METAL_CUBE,
   CURSOR_BRUSH_STAIRBOX,
   CURSOR_BRUSH_PLATE_2X2,
   CURSOR_BRUSH_PLATE_2X10,
   CURSOR_BRUSH_PLATE_10X10,
   CURSOR_BRUSH_MUSHED_UP_CUBE,
   CURSOR_BRUSH_PILLAR_1X1X3,
   CURSOR_BRUSH_PLATFORM_01,
   CURSOR_BRUSH_BRIDGE_01,
   CURSOR_BRUSH_LADDER_01,
   CURSOR_BRUSH_WOOD_PLANK_01,
   CURSOR_BRUSH_BASIC_MESH,

   CURSOR_BRUSH_MAX
};


#include <AllegroFlare/InventoryIndexItem.hpp>

// id (for std::map), title, image-filename, description
extern const std::map<int, std::tuple<std::string, std::string, std::string>> CREATORS_INVENTORY_INDEX;
extern const std::map<int, AllegroFlare::InventoryIndexItem> CREATORS_INVENTORY_INDEX2;


std::string inventory_index_id_to_factory_identifier(int id);


enum input_mode_t
{
   INPUT_MODE_WORLD_BUILDING = 0,
   INPUT_MODE_INVENTORY,
   INPUT_MODE_PLAYER_CONTROL,
   INPUT_MODE_MAX
};


