
#include <WickedDemos/globals.hpp>

#include <sstream>

// id (for std::map), title, image-filename, description
const std::map<int, std::tuple<std::string, std::string, std::string>> CREATORS_INVENTORY_INDEX = {
   { CURSOR_BRUSH_CUBE, { "Cube",      "cube-01.png", "A 1x1 unit cube, with rounded corners." } },
   { CURSOR_BRUSH_RING, { "Coin Ring", "coin-ring-01.png", "A reflective metalic ring." } },
   { CURSOR_BRUSH_FLOOR_10X10, { "Floor 10x10", "no-element-01.png", "A 10x10 floor with a UV texture map." } },
   //{ CURSOR_BRUSH_STONE_FENCE, { "Stone Fence", "no-element-01.png", "A stone fence!" } },
   //{ CURSOR_BRUSH_ARCHWAY, { "Archway", "no-element-01.png", "-" } },
   { CURSOR_BRUSH_BLACK_STONE, { "Black Stone", "no-element-01.png", "-" } },
   { CURSOR_BRUSH_METAL_CUBE, { "Metal cube", "gold-cube-01.png", "-" } },
   { CURSOR_BRUSH_STAIRBOX, { "Stairs", "no-element-01.png", "-" } },
   //{ CURSOR_BRUSH_PLATE_2X2, { "Plate 2x2", "no-element-01.png", "-" } },
   //{ CURSOR_BRUSH_PLATE_2X10, { "Plate 2x10", "no-element-01.png", "-" } },
   //{ CURSOR_BRUSH_PLATE_10X10, { "Plate 10x10", "no-element-01.png", "-" } },
   { CURSOR_BRUSH_MUSHED_UP_CUBE, { "Mushed Up Cube", "no-element-01.png", "A unit cube with inset edges." } },
   { CURSOR_BRUSH_PILLAR_1X1X3, { "Pillar 1x1x3", "no-element-01.png", "-" } },
   //{ CURSOR_BRUSH_PLATFORM_01, { "Platform 01", "no-element-01.png", "-" } },
   { CURSOR_BRUSH_BRIDGE_01, { "Bridge 01", "no-element-01.png", "-" } },
   { CURSOR_BRUSH_LADDER_01, { "Ladder 01", "no-element-01.png", "-" } },
   { CURSOR_BRUSH_WOOD_PLANK_01, { "Wood Plank 01", "no-element-01.png", "-" } },
   { CURSOR_BRUSH_BASIC_MESH, { "Basic Tile Mesh", "no-element-01.png", "-" } },
};


std::string inventory_index_id_to_factory_identifier(int id)
{
   if (id == CURSOR_BRUSH_CUBE) return "cube";
   if (id == CURSOR_BRUSH_FLOOR_10X10) return "10x10_floor";
   if (id == CURSOR_BRUSH_RING) return "coin_ring";
   if (id == CURSOR_BRUSH_STONE_FENCE) return "stone_fence";
   if (id == CURSOR_BRUSH_ARCHWAY) return "archway";
   if (id == CURSOR_BRUSH_BLACK_STONE) return "black_stone";
   if (id == CURSOR_BRUSH_METAL_CUBE) return "metal_cube";
   if (id == CURSOR_BRUSH_STAIRBOX) return "stairbox";
   if (id == CURSOR_BRUSH_PLATE_2X2) return "plate_2x2";
   if (id == CURSOR_BRUSH_PLATE_2X10) return "plate_2x10";
   if (id == CURSOR_BRUSH_PLATE_10X10) return "plate_10x10";
   if (id == CURSOR_BRUSH_MUSHED_UP_CUBE) return "mushed_up_cube";
   if (id == CURSOR_BRUSH_PILLAR_1X1X3) return "pillar_1x1x3";
   if (id == CURSOR_BRUSH_PLATFORM_01) return "platform_01";
   if (id == CURSOR_BRUSH_BRIDGE_01) return "bridge_01";
   if (id == CURSOR_BRUSH_LADDER_01) return "ladder_01";
   if (id == CURSOR_BRUSH_WOOD_PLANK_01) return "wood_plank_01";
   if (id == CURSOR_BRUSH_BASIC_MESH) return "basic_mesh";

   std::stringstream ss;
   ss << "[none]";
   return ss.str();
}



