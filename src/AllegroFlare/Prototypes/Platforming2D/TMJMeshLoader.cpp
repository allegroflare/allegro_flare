

#include <AllegroFlare/Prototypes/Platforming2D/TMJMeshLoader.hpp>

#include <AllegroFlare/Prototypes/Platforming2D/TMJDataLoader.hpp>
#include <AllegroFlare/TileMaps/TileAtlasBuilder.hpp>
#include <fstream>
#include <iostream>
#include <lib/nlohmann/json.hpp>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Prototypes
{
namespace Platforming2D
{


TMJMeshLoader::TMJMeshLoader(AllegroFlare::BitmapBin* bitmap_bin, std::string tmj_filename, std::string tile_atlas_bitmap_identifier, int tile_atlas_tile_width, int tile_atlas_tile_height)
   : bitmap_bin(bitmap_bin)
   , tmj_filename(tmj_filename)
   , tile_atlas_bitmap_identifier(tile_atlas_bitmap_identifier)
   , tile_atlas_tile_width(tile_atlas_tile_width)
   , tile_atlas_tile_height(tile_atlas_tile_height)
   , tile_atlas(nullptr)
   , mesh(nullptr)
   , background_mesh(nullptr)
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

AllegroFlare::TileMaps::PrimMesh* TMJMeshLoader::get_background_mesh()
{
   if (!(loaded))
   {
      std::stringstream error_message;
      error_message << "[TMJMeshLoader::get_background_mesh]: error: guard \"loaded\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("TMJMeshLoader::get_background_mesh: error: guard \"loaded\" not met");
   }
   return background_mesh;
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

   AllegroFlare::Prototypes::Platforming2D::TMJDataLoader tmj_data_loader(tmj_filename);
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

   int background_tilelayer_exists = tmj_data_loader.get_background_tilelayer_exists();
   int background_tilelayer_width = tmj_data_loader.get_background_tilelayer_num_columns();
   int background_tilelayer_height = tmj_data_loader.get_background_tilelayer_num_rows();
   std::vector<int> background_tiles = tmj_data_loader.get_background_tilelayer_tile_data();


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
      // TODO: Improve this error message
      throw std::runtime_error("TMJMeshLoader: error: asjlasjl;afsdj;afjl");
   }
   if (tilelayer_height != collision_layer_num_rows)
   {
      // TODO: Improve this error message
      throw std::runtime_error("TMJMeshLoader: error: quopiwequworeueo");
   }
   if (background_tilelayer_exists)
   {
      if (tilelayer_width != background_tilelayer_width)
      {
         // TODO: Improve this error message
         throw std::runtime_error("TMJMeshLoader: error: zxnyzvnyzvxcnr");
      }
      if (tilelayer_height != background_tilelayer_height)
      {
         // TODO: Improve this error message
         throw std::runtime_error("TMJMeshLoader: error: zsboizbeiozsnroi");
      }
      if (background_tiles.size() != tmx_width * tmx_height)
      {
         // TODO: Improve this error message
         throw std::runtime_error("TMJMeshLoader: error: aqwoyzhawehopaso");
      }
   }
   if (collision_layer_tiles.size() != tmx_width * tmx_height)
   {
      // TODO: add test for this
      throw std::runtime_error("TMJMeshLoader: error: num tiles (in \"data\" field) for collision_layer "
                               "does not match width*height.");
   }



   // Filter out any "flipped" tiles. Tiled will give *very large* numbers to tiles that have been flipped,
   // which could result in unexpected/missing tiles if they have been flipped accidentally. For now,
   // this feature is unexpected to we will "filter out" the flipped data from the tile id here.  Note we'll
   // do this twice, once for the visual tiles, and a second time for the "collision" tiles.
   // For more information, see this discourse support page:
   // https://discourse.mapeditor.org/t/tiled-csv-format-has-exceptionally-large-tile-values-solved/4765

   bool filter_out_flipped_tile_numbers = true;
   if (filter_out_flipped_tile_numbers)
   {
      for (auto &tile : tiles)
      {
         bool horizontalFlip = tile & 0x80000000;
         bool verticalFlip = tile & 0x40000000;
         bool diagonalFlip = tile & 0x20000000;
         int filtered_tile_id = tile & ~(0x80000000 | 0x40000000 | 0x20000000); //clear the flags
         tile = filtered_tile_id;
      }

      for (auto &tile : collision_layer_tiles)
      {
         bool horizontalFlip = tile & 0x80000000;
         bool verticalFlip = tile & 0x40000000;
         bool diagonalFlip = tile & 0x20000000;
         int filtered_tile_id = tile & ~(0x80000000 | 0x40000000 | 0x20000000); //clear the flags
         tile = filtered_tile_id;
      }

      for (auto &tile : background_tiles)
      {
         bool horizontalFlip = tile & 0x80000000;
         bool verticalFlip = tile & 0x40000000;
         bool diagonalFlip = tile & 0x20000000;
         int filtered_tile_id = tile & ~(0x80000000 | 0x40000000 | 0x20000000); //clear the flags
         tile = filtered_tile_id;
      }
   }




   // ##
   // create the atlas
   // TODO: These will need to be passed in eventually:
   //int tile_width = 16;
   //int tile_height = 16;

   AllegroFlare::TileMaps::PrimMeshAtlas *created_tile_atlas = new AllegroFlare::TileMaps::PrimMeshAtlas;
   ALLEGRO_BITMAP *tile_map_bitmap = bitmap_bin->operator[](tile_atlas_bitmap_identifier);
   created_tile_atlas->set_bitmap_filename(tile_atlas_bitmap_identifier);

   bool scaled_and_extruded = true;
   if (scaled_and_extruded)
   {
      int scale = 3;
      // TODO: factor out this step
      ALLEGRO_BITMAP *scaled_extruded_tile_map_bitmap =
         AllegroFlare::TileMaps::TileAtlasBuilder::build_scaled_and_extruded(tile_map_bitmap, scale);
      created_tile_atlas->duplicate_bitmap_and_load(
         scaled_extruded_tile_map_bitmap, tile_atlas_tile_width*scale, tile_atlas_tile_height*scale, 1
      );
   }
   else
   {
      created_tile_atlas->duplicate_bitmap_and_load(tile_map_bitmap, tile_atlas_tile_width, tile_atlas_tile_height);
   }


   // ##
   // create the mesh
   int num_columns = tmx_width;
   int num_rows = tmx_height;
   AllegroFlare::TileMaps::PrimMesh* created_mesh = new AllegroFlare::TileMaps::PrimMesh(
         created_tile_atlas,
         num_columns,
         num_rows,
         tile_atlas_tile_width, // TODO: Verify if this value is correlated only to the tile atlas, or the mesh's
                                // tile width, both? or what the relationship is between them.
         tile_atlas_tile_height // TODO: Verify if this value is correlated only to the tile atlas, or the mesh's
                                // tile height, both? or what the relationship is between them.
      );
   created_mesh->initialize();


   // ##
   // fill the data on the mesh
   for (int y=0; y<num_rows; y++)
   {
      for (int x=0; x<num_columns; x++)
      {
         int tile_id = tiles[y * num_columns + x];
         if (tile_id == 0) created_mesh->set_tile_id(x, y, 72);
                        // <- TODO: this is a hack to have 0 be transparent
                        // ^^ TODO: CRITICAL Modify this to make more sense. Consider *removing* the tile from
                        // the mesh
         else created_mesh->set_tile_id(x, y, tile_id-1);
      }
   }


   // ##
   // create the background_mesh
   //int num_columns = tmx_width;
   //int num_rows = tmx_height;
   AllegroFlare::TileMaps::PrimMesh* created_background_mesh = nullptr;
   if (background_tilelayer_exists)
   {
      created_background_mesh = new AllegroFlare::TileMaps::PrimMesh(
            created_tile_atlas,
            num_columns,
            num_rows,
            tile_atlas_tile_width, // TODO: Verify if this value is correlated only to the tile atlas, or the
                                   // background mesh's tile width, both? or what the relationship is between them.
            tile_atlas_tile_height // TODO: Verify if this value is correlated only to the tile atlas, or the
                                   // background mesh's tile height, both? or what the relationship is between them.
         );
      created_background_mesh->initialize();


      // ##
      // fill the data on the background_mesh
      for (int y=0; y<num_rows; y++)
      {
         for (int x=0; x<num_columns; x++)
         {
            int tile_id = background_tiles[y * num_columns + x];
            if (tile_id == 0) created_background_mesh->set_tile_id(x, y, 72);
                              // ^^ TODO: this is a hack to have 0 be transparent
                              // ^^ TODO: CRITICAL Modify this to make more sense. Consider *removing* the tile from
                              // the mesh
            else created_background_mesh->set_tile_id(x, y, tile_id-1);
         }
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
   this->background_mesh = created_background_mesh;
   this->collision_tile_map = created_collision_tile_map;
   loaded = true;

   return true;
}


} // namespace Platforming2D
} // namespace Prototypes
} // namespace AllegroFlare


