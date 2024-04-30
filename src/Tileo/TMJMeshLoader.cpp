

#include <Tileo/TMJMeshLoader.hpp>

#include <AllegroFlare/TileMaps/TileAtlasBuilder.hpp>
#include <Tileo/TMJDataLoader.hpp>
#include <fstream>
#include <iostream>
#include <lib/nlohmann/json.hpp>
#include <sstream>
#include <stdexcept>


namespace Tileo
{


std::string TMJMeshLoader::BITMAP_ATLAS_FILENAME = "tiles_dungeon_v1.1.png";


TMJMeshLoader::TMJMeshLoader(AllegroFlare::BitmapBin* bitmap_bin, std::string tmj_filename)
   : bitmap_bin(bitmap_bin)
   , tmj_filename(tmj_filename)
   , tile_atlas(nullptr)
   , mesh(nullptr)
   , collision_tile_map(nullptr)
   , loaded(false)
{
}


TMJMeshLoader::~TMJMeshLoader()
{
}


AllegroFlare::TileMaps::PrimMeshAtlas* TMJMeshLoader::get_tile_atlas()
{
   if (!(loaded))
   {
      std::stringstream error_message;
      error_message << "[TMJMeshLoader::get_tile_atlas]: error: guard \"loaded\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("TMJMeshLoader::get_tile_atlas: error: guard \"loaded\" not met");
   }
   return tile_atlas;
}

AllegroFlare::TileMaps::PrimMesh* TMJMeshLoader::get_mesh()
{
   if (!(loaded))
   {
      std::stringstream error_message;
      error_message << "[TMJMeshLoader::get_mesh]: error: guard \"loaded\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("TMJMeshLoader::get_mesh: error: guard \"loaded\" not met");
   }
   return mesh;
}

AllegroFlare::TileMaps::TileMap<int>* TMJMeshLoader::get_collision_tile_map()
{
   if (!(loaded))
   {
      std::stringstream error_message;
      error_message << "[TMJMeshLoader::get_collision_tile_map]: error: guard \"loaded\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("TMJMeshLoader::get_collision_tile_map: error: guard \"loaded\" not met");
   }
   return collision_tile_map;
}

bool TMJMeshLoader::load()
{
   if (!(bitmap_bin))
   {
      std::stringstream error_message;
      error_message << "[TMJMeshLoader::load]: error: guard \"bitmap_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("TMJMeshLoader::load: error: guard \"bitmap_bin\" not met");
   }
   if (!((!loaded)))
   {
      std::stringstream error_message;
      error_message << "[TMJMeshLoader::load]: error: guard \"(!loaded)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("TMJMeshLoader::load: error: guard \"(!loaded)\" not met");
   }
   // 1
   // load and validate the json data to variables
   // TODO: replace this with the TMJDataLoader

   Tileo::TMJDataLoader tmj_data_loader(tmj_filename);
   tmj_data_loader.load();


   //// TODO: remove dead code for manual loading (now using only the tmj_data_loader data yay!)
   //std::ifstream i(tmj_filename);
   //nlohmann::json j;
   //i >> j;

   int tmx_height = tmj_data_loader.get_num_rows(); //j["height"];// get height
   int tmx_width = tmj_data_loader.get_num_columns(); //j["width"];// get width
   int tmx_tileheight = tmj_data_loader.get_tile_height(); //j["tileheight"]; // get height
   int tmx_tilewidth = tmj_data_loader.get_tile_width(); //j["tilewidth"]; // get width

   //// get first j["layers"] that is a ["type"] == "tilelayer"
   //bool tilelayer_type_found = false;
   //nlohmann::json tilelayer;
   //for (auto &layer : j["layers"].items())
   //{
      //if (layer.value()["type"] == "tilelayer")
      //{
         //tilelayer = layer.value();
         //tilelayer_type_found = true;
         //break;
      //}
   //{}
   //if (!tilelayer_type_found) throw std::runtime_error("TMJMeshLoader: error: tilelayer type not found.");

   int tilelayer_width = tmj_data_loader.get_layer_num_columns(); //tilelayer["width"];
   int tilelayer_height = tmj_data_loader.get_layer_num_rows(); //tilelayer["height"];
   std::vector<int> tiles = tmj_data_loader.get_layer_tile_data(); //tilelayer["data"].get<std::vector<int>>();

   int collision_layer_num_columns = tmj_data_loader.get_collision_layer_num_columns();
   int collision_layer_num_rows = tmj_data_loader.get_collision_layer_num_rows();
   std::vector<int> collision_layer_tiles = tmj_data_loader.get_collision_layer_tile_data();



   // validate widths and heights match
   if (tilelayer_width != tmx_width)
   {
      throw std::runtime_error("TMJMeshLoader: error: tilelayer width does not match tmx_width.");
   }
   if (tilelayer_height != tmx_height)
   {
      throw std::runtime_error("TMJMeshLoader: error: tilelayer height does not match tmx_height.");
   }
   if (tmx_tileheight != 16 || tmx_tilewidth != 16)
   {
      throw std::runtime_error("TMJMeshLoader: error: tmx tileheight and tilewidth other than 16 not supported.");
   }
   if (tiles.size() != tmx_width * tmx_height)
   {
      throw std::runtime_error("TMJMeshLoader: error: num tiles (in \"data\" field) does not match width*height.");
   }
   if (tilelayer_width != collision_layer_num_columns)
   {
      // TODO: validate collision mesh dimensions, tile_width, and tile_height match the other values
   }
   if (tilelayer_height != collision_layer_num_rows)
   {
      // TODO: validate collision mesh dimensions, tile_width, and tile_height match the other values
   }
   if (collision_layer_tiles.size() != tmx_width * tmx_height)
   {
      // TODO: add test for this
      throw std::runtime_error("TMJMeshLoader: error: num tiles (in \"data\" field) for collision_layer "
                               "does not match width*height.");
   }


   // ##
   // create the atlas
   int tile_width = 16;
   int tile_height = 16;

   AllegroFlare::TileMaps::PrimMeshAtlas *created_tile_atlas = new AllegroFlare::TileMaps::PrimMeshAtlas;
   ALLEGRO_BITMAP *tile_map_bitmap = bitmap_bin->operator[](BITMAP_ATLAS_FILENAME);
   created_tile_atlas->set_bitmap_filename(BITMAP_ATLAS_FILENAME);

   bool scaled_and_extruded = true;
   if (scaled_and_extruded)
   {
      int scale = 3;
      // TODO: factor out this step
      ALLEGRO_BITMAP *scaled_extruded_tile_map_bitmap =
         AllegroFlare::TileMaps::TileAtlasBuilder::build_scaled_and_extruded(tile_map_bitmap, scale);
      created_tile_atlas->duplicate_bitmap_and_load(
         scaled_extruded_tile_map_bitmap, tile_width*scale, tile_height*scale, 1
      );
   }
   else
   {
      created_tile_atlas->duplicate_bitmap_and_load(tile_map_bitmap, tile_width, tile_height);
   }


   // ##
   // create the mesh
   int num_columns = tmx_width;
   int num_rows = tmx_height;
   AllegroFlare::TileMaps::PrimMesh* created_mesh = new AllegroFlare::TileMaps::PrimMesh(created_tile_atlas, num_columns, num_rows, tile_width, tile_height);
   created_mesh->initialize();


   // ##
   // fill the data on the mesh
   for (int y=0; y<num_rows; y++)
   {
      for (int x=0; x<num_columns; x++)
      {
         int tile_id = tiles[y * num_columns + x];
         if (tile_id == 0) created_mesh->set_tile_id(x, y, 72); // <- TODO: this is a hack to have 0 be transparent
         else created_mesh->set_tile_id(x, y, tile_id-1);
      }
   }


   // ##
   // create the collision tile map
   AllegroFlare::TileMaps::TileMap<int>* created_collision_tile_map = new AllegroFlare::TileMaps::TileMap<int>(
      collision_layer_num_columns,
      collision_layer_num_rows);
   created_collision_tile_map->initialize();


   // ##
   // fill the data on the collision tile map
   for (int y=0; y<num_rows; y++)
   {
      for (int x=0; x<num_columns; x++)
      {
         // TODO
         int tile_id = collision_layer_tiles[y * num_columns + x];
         created_collision_tile_map->set_tile(x, y, tile_id);
      }
   }

   // ##
   // assign the created objects to the class
   this->tile_atlas = created_tile_atlas;
   this->mesh = created_mesh;
   this->collision_tile_map = created_collision_tile_map;
   loaded = true;

   return true;
}


} // namespace Tileo


