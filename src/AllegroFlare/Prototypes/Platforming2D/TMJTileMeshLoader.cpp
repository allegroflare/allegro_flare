

#include <AllegroFlare/Prototypes/Platforming2D/TMJTileMeshLoader.hpp>

#include <AllegroFlare/Prototypes/Platforming2D/TMJDataLoader.hpp>
#include <AllegroFlare/TileMaps/TileAtlasBuilder.hpp>
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


TMJTileMeshLoader::TMJTileMeshLoader(AllegroFlare::BitmapBin* bitmap_bin, std::string tmj_filename, std::string tile_atlas_bitmap_identifier, int tile_atlas_tile_width, int tile_atlas_tile_height)
   : bitmap_bin(bitmap_bin)
   , tmj_filename(tmj_filename)
   , tile_atlas_bitmap_identifier(tile_atlas_bitmap_identifier)
   , tile_atlas_tile_width(tile_atlas_tile_width)
   , tile_atlas_tile_height(tile_atlas_tile_height)
   , tile_atlas(nullptr)
   , terrain_mesh(nullptr)
   , background_mesh(nullptr)
   , foreground_mesh(nullptr)
   , collision_tile_map(nullptr)
   , loaded(false)
{
}


TMJTileMeshLoader::~TMJTileMeshLoader()
{
}


AllegroFlare::BitmapBin* TMJTileMeshLoader::get_bitmap_bin() const
{
   return bitmap_bin;
}


std::string TMJTileMeshLoader::get_tmj_filename() const
{
   return tmj_filename;
}


std::string TMJTileMeshLoader::get_tile_atlas_bitmap_identifier() const
{
   return tile_atlas_bitmap_identifier;
}


void TMJTileMeshLoader::set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin)
{
   if (!((!loaded)))
   {
      std::stringstream error_message;
      error_message << "[TMJTileMeshLoader::set_bitmap_bin]: error: guard \"(!loaded)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("TMJTileMeshLoader::set_bitmap_bin: error: guard \"(!loaded)\" not met");
   }
   this->bitmap_bin = bitmap_bin;
}

void TMJTileMeshLoader::set_tmj_filename(std::string tmj_filename)
{
   if (!((!loaded)))
   {
      std::stringstream error_message;
      error_message << "[TMJTileMeshLoader::set_tmj_filename]: error: guard \"(!loaded)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("TMJTileMeshLoader::set_tmj_filename: error: guard \"(!loaded)\" not met");
   }
   this->tmj_filename = tmj_filename;
}

void TMJTileMeshLoader::set_tile_atlas_bitmap_identifier(std::string tile_atlas_bitmap_identifier)
{
   if (!((!loaded)))
   {
      std::stringstream error_message;
      error_message << "[TMJTileMeshLoader::set_tile_atlas_bitmap_identifier]: error: guard \"(!loaded)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("TMJTileMeshLoader::set_tile_atlas_bitmap_identifier: error: guard \"(!loaded)\" not met");
   }
   this->tile_atlas_bitmap_identifier = tile_atlas_bitmap_identifier;
}

AllegroFlare::TileMaps::PrimMeshAtlas* TMJTileMeshLoader::get_tile_atlas()
{
   if (!(loaded))
   {
      std::stringstream error_message;
      error_message << "[TMJTileMeshLoader::get_tile_atlas]: error: guard \"loaded\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("TMJTileMeshLoader::get_tile_atlas: error: guard \"loaded\" not met");
   }
   return tile_atlas;
}

AllegroFlare::TileMaps::TileMesh* TMJTileMeshLoader::get_terrain_mesh()
{
   if (!(loaded))
   {
      std::stringstream error_message;
      error_message << "[TMJTileMeshLoader::get_terrain_mesh]: error: guard \"loaded\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("TMJTileMeshLoader::get_terrain_mesh: error: guard \"loaded\" not met");
   }
   return terrain_mesh;
}

AllegroFlare::TileMaps::TileMesh* TMJTileMeshLoader::get_background_mesh()
{
   if (!(loaded))
   {
      std::stringstream error_message;
      error_message << "[TMJTileMeshLoader::get_background_mesh]: error: guard \"loaded\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("TMJTileMeshLoader::get_background_mesh: error: guard \"loaded\" not met");
   }
   return background_mesh;
}

AllegroFlare::TileMaps::TileMesh* TMJTileMeshLoader::get_foreground_mesh()
{
   if (!(loaded))
   {
      std::stringstream error_message;
      error_message << "[TMJTileMeshLoader::get_foreground_mesh]: error: guard \"loaded\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("TMJTileMeshLoader::get_foreground_mesh: error: guard \"loaded\" not met");
   }
   return foreground_mesh;
}

AllegroFlare::TileMaps::TileMap<int>* TMJTileMeshLoader::get_collision_tile_map()
{
   if (!(loaded))
   {
      std::stringstream error_message;
      error_message << "[TMJTileMeshLoader::get_collision_tile_map]: error: guard \"loaded\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("TMJTileMeshLoader::get_collision_tile_map: error: guard \"loaded\" not met");
   }
   return collision_tile_map;
}

bool TMJTileMeshLoader::load()
{
   if (!(bitmap_bin))
   {
      std::stringstream error_message;
      error_message << "[TMJTileMeshLoader::load]: error: guard \"bitmap_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("TMJTileMeshLoader::load: error: guard \"bitmap_bin\" not met");
   }
   if (!((!loaded)))
   {
      std::stringstream error_message;
      error_message << "[TMJTileMeshLoader::load]: error: guard \"(!loaded)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("TMJTileMeshLoader::load: error: guard \"(!loaded)\" not met");
   }
   AllegroFlare::Prototypes::Platforming2D::TMJDataLoader tmj_data_loader(tmj_filename);
   tmj_data_loader.load();


   int tmx_num_rows = tmj_data_loader.get_num_rows();
   int tmx_num_columns = tmj_data_loader.get_num_columns();
   int tmx_tile_height = tmj_data_loader.get_tile_height();
   int tmx_tile_width = tmj_data_loader.get_tile_width();

   int terrain_tilelayer_width = tmj_data_loader.get_layer_num_columns();
   int terrain_tilelayer_height = tmj_data_loader.get_layer_num_rows();
   std::vector<int> terrain_tile_data = tmj_data_loader.get_layer_tile_data();

   int collision_layer_num_columns = tmj_data_loader.get_collision_layer_num_columns();
   int collision_layer_num_rows = tmj_data_loader.get_collision_layer_num_rows();
   std::vector<int> collision_layer_tile_data = tmj_data_loader.get_collision_layer_tile_data();

   int foreground_tilelayer_exists = tmj_data_loader.get_foreground_tilelayer_exists();
   int foreground_tilelayer_width = tmj_data_loader.get_foreground_tilelayer_num_columns();
   int foreground_tilelayer_height = tmj_data_loader.get_foreground_tilelayer_num_rows();
   std::vector<int> foreground_tile_data = tmj_data_loader.get_foreground_tilelayer_tile_data();

   int background_tilelayer_exists = tmj_data_loader.get_background_tilelayer_exists();
   int background_tilelayer_width = tmj_data_loader.get_background_tilelayer_num_columns();
   int background_tilelayer_height = tmj_data_loader.get_background_tilelayer_num_rows();
   std::vector<int> background_tile_data = tmj_data_loader.get_background_tilelayer_tile_data();


   // validate widths and heights match
   // TODO: Improve the validation code here
   if (terrain_tilelayer_width != tmx_num_columns)
   {
      throw std::runtime_error("TMJMeshLoader: error: tilelayer width does not match tmx_num_columns.");
   }
   if (terrain_tilelayer_height != tmx_num_rows)
   {
      throw std::runtime_error("TMJMeshLoader: error: tilelayer height does not match tmx_num_rows.");
   }
   if (tmx_tile_height != 16 || tmx_tile_width != 16)
   {
      throw std::runtime_error("TMJMeshLoader: error: tmx tileheight and tilewidth other than 16 not supported.");
   }
   if (terrain_tile_data.size() != tmx_num_columns * tmx_num_rows)
   {
      throw std::runtime_error("TMJMeshLoader: error: num terrain tiles (in \"data\" field) does not match width*height.");
   }
   if (terrain_tilelayer_width != collision_layer_num_columns)
   {
      // TODO: Improve this error message
      throw std::runtime_error("TMJMeshLoader: error: asjlasjl;afsdj;afjl");
   }
   if (terrain_tilelayer_height != collision_layer_num_rows)
   {
      // TODO: Improve this error message
      throw std::runtime_error("TMJMeshLoader: error: quopiwequworeueo");
   }
   if (foreground_tilelayer_exists)
   {
      if (terrain_tilelayer_width != foreground_tilelayer_width)
      {
         // TODO: Improve this error message
         throw std::runtime_error("TMJMeshLoader: error: zxnyzvnyzvxcnr");
      }
      if (terrain_tilelayer_height != foreground_tilelayer_height)
      {
         // TODO: Improve this error message
         throw std::runtime_error("TMJMeshLoader: error: zsboizbeiozsnroi");
      }
      if (foreground_tile_data.size() != tmx_num_columns * tmx_num_rows)
      {
         // TODO: Improve this error message
         throw std::runtime_error("TMJMeshLoader: error: aqwoyzhawehopaso");
      }
   }
   if (background_tilelayer_exists)
   {
      if (terrain_tilelayer_width != background_tilelayer_width)
      {
         // TODO: Improve this error message
         throw std::runtime_error("TMJMeshLoader: error: zxnyzvnyzvxcnr");
      }
      if (terrain_tilelayer_height != background_tilelayer_height)
      {
         // TODO: Improve this error message
         throw std::runtime_error("TMJMeshLoader: error: zsboizbeiozsnroi");
      }
      if (background_tile_data.size() != tmx_num_columns * tmx_num_rows)
      {
         // TODO: Improve this error message
         throw std::runtime_error("TMJMeshLoader: error: aqwoyzhawehopaso");
      }
   }
   if (collision_layer_tile_data.size() != tmx_num_columns * tmx_num_rows)
   {
      // TODO: add test for this
      throw std::runtime_error("TMJMeshLoader: error: num collision layer tiles (in \"data\" field) for collision_layer "
                               "does not match width*height.");
   }



   // Filter out any "flipped" tiles. Tiled will give *very large* numbers to tiles that have been flipped,
   // which could result in unexpected/missing tiles if they have been flipped accidentally. For now,
   // this feature is unexpected so we will "filter out" the flipped data from the tile id here.  Note we'll
   // do this for each layer.
   // For more information, see this discourse support page:
   // https://discourse.mapeditor.org/t/tiled-csv-format-has-exceptionally-large-tile-values-solved/4765

   // TODO: There are four options here:
   //   1) Allow flipped tiles
   //   2) Continue not allowing flipped tiles, but throw when a flipped tile is detected
   //   3) Continue not allowing flipped tiles, and flip them automatically with a warning
   //   4) Continue not allowing flipped tiles, and flip them implicitly with no warning. (current behavior)

   bool filter_out_flipped_tile_numbers_on_collision_layer_tile_data = true;
   if (filter_out_flipped_tile_numbers_on_collision_layer_tile_data)
   {
      for (auto &tile : collision_layer_tile_data)
      {
         int filtered_tile_id = tile & ~(0x80000000 | 0x40000000 | 0x20000000 | 0x1000000); //clear the flags
         tile = filtered_tile_id;
      }
   }



   // Create the atlas
   // TODO: Use a TileAtlasRepository

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


   // Some helper vars
   int &num_columns = tmx_num_columns;
   int &num_rows = tmx_num_rows;
   int &tile_width = tmx_tile_width;
   int &tile_height = tmx_tile_height;



   // terrain

   AllegroFlare::TileMaps::TileMesh* created_terrain_mesh = nullptr;
   created_terrain_mesh = create_mesh(
      created_tile_atlas,
      num_columns,
      num_rows,
      tile_width,
      tile_height,
      terrain_tile_data,
      false
   );



   // foreground

   AllegroFlare::TileMaps::TileMesh* created_foreground_mesh = nullptr;
   if (foreground_tilelayer_exists)
   {
      created_foreground_mesh = create_mesh(
         created_tile_atlas,
         num_columns,
         num_rows,
         tile_width,
         tile_height,
         foreground_tile_data,
         false
      );
   }



   // background

   AllegroFlare::TileMaps::TileMesh* created_background_mesh = nullptr;
   if (background_tilelayer_exists)
   {
      created_background_mesh = create_mesh(
         created_tile_atlas,
         num_columns,
         num_rows,
         tile_width,
         tile_height,
         background_tile_data,
         false
      );
   }



   // collision

   AllegroFlare::TileMaps::TileMap<int>* created_collision_tile_map = new AllegroFlare::TileMaps::TileMap<int>(
      collision_layer_num_columns,
      collision_layer_num_rows);
   created_collision_tile_map->initialize();

   for (int y=0; y<num_rows; y++)
   {
      for (int x=0; x<num_columns; x++)
      {
         // TODO
         int tile_id = collision_layer_tile_data[y * num_columns + x];
         created_collision_tile_map->set_tile(x, y, tile_id);
      }
   }


   // Assign all of our created objects into the final result
   this->tile_atlas = created_tile_atlas;
   this->terrain_mesh = created_terrain_mesh;
   this->foreground_mesh = created_foreground_mesh;
   this->background_mesh = created_background_mesh;
   this->collision_tile_map = created_collision_tile_map;

   // Set loaded to true
   loaded = true;

   return true;
}

std::tuple<bool, bool, bool, bool, int> TMJTileMeshLoader::extract_tmj_tile_flip_properties(uint32_t tmj_tile_value)
{
   // Extract the flag values
   bool horizontal_flip_flag_present = (tmj_tile_value & 0x80000000) != 0;
   bool vertical_flip_flag_present = (tmj_tile_value & 0x40000000) != 0;
   bool antidiagonal_flip_flag_present = (tmj_tile_value & 0x20000000) != 0;
   bool hex_120_rotation_flag_present = (tmj_tile_value & 0x10000000) != 0;

   // Clear all the flags
   int filtered_tile_value = tmj_tile_value& ~(0x80000000 | 0x40000000 | 0x20000000 | 0x1000000);

   return std::tuple<bool, bool, bool, bool, int>{
      horizontal_flip_flag_present,
      vertical_flip_flag_present,
      antidiagonal_flip_flag_present,
      hex_120_rotation_flag_present,
      filtered_tile_value
   };
}

AllegroFlare::TileMaps::TileMesh* TMJTileMeshLoader::create_mesh(AllegroFlare::TileMaps::PrimMeshAtlas* tile_atlas, int num_columns, int num_rows, int tile_width, int tile_height, std::vector<int> tile_data, bool filter_out_flipped_tile_numbers)
{
   if (!(tile_atlas))
   {
      std::stringstream error_message;
      error_message << "[TMJTileMeshLoader::create_mesh]: error: guard \"tile_atlas\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("TMJTileMeshLoader::create_mesh: error: guard \"tile_atlas\" not met");
   }
   if (!((tile_data.size() == num_rows * num_columns)))
   {
      std::stringstream error_message;
      error_message << "[TMJTileMeshLoader::create_mesh]: error: guard \"(tile_data.size() == num_rows * num_columns)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("TMJTileMeshLoader::create_mesh: error: guard \"(tile_data.size() == num_rows * num_columns)\" not met");
   }
   if (filter_out_flipped_tile_numbers)
   {
      for (auto &tile : tile_data)
      {
         // TODO: Sort out flip flags as loaded here and below
         // Help on flip flags:
         // https://discourse.mapeditor.org/t/need-help-understanding-exported-flipped-tiles/5383/3

         //bool horizontalFlip = (tile & 0x80000000) != 0;
         //bool verticalFlip = (tile & 0x40000000) != 0;
         //bool antidiagonalFlip = (tile & 0x20000000) != 0;
         //bool Hex120Rotation = (tile & 0x10000000) != 0;
         int filtered_tile_id = tile & ~(0x80000000 | 0x40000000 | 0x20000000 | 0x1000000); // clear the flags
         tile = filtered_tile_id;
      }
   }

   AllegroFlare::TileMaps::TileMesh* created_mesh = new AllegroFlare::TileMaps::TileMesh(
         tile_atlas,
         num_columns,
         num_rows,
         tile_width,
         tile_height
      );
   created_mesh->initialize();
   //created_mesh->enable_holding_vertex_buffer_update_until_refresh();

   std::vector<std::pair<int, int>> tile_coords_to_remove;

   // Fill the tile data
   for (int y=0; y<num_rows; y++)
   {
      for (int x=0; x<num_columns; x++)
      {
         int tile_id = tile_data[y * num_columns + x];

         auto tile_flip_data = extract_tmj_tile_flip_properties(tile_id);

         bool horizontal_flip_flag_present = std::get<0>(tile_flip_data);
         bool vertical_flip_flag_present = std::get<1>(tile_flip_data);
         bool antidiagonal_flip_flag_present = std::get<2>(tile_flip_data);
         bool hex_120_rotation_flag_present = std::get<3>(tile_flip_data);
         int raw_tile_id = std::get<4>(tile_flip_data);

         bool has_horizontal_flip = horizontal_flip_flag_present;
         bool has_vertical_flip = vertical_flip_flag_present;
         bool has_diagonal_flip = antidiagonal_flip_flag_present;

         //std::cout << "[" << tile_id << ":";
         //if (tile_id < 0) tile_id = static_cast<unsigned int>(tile_id);

         tile_id = raw_tile_id;
         //if (tile_id < 0) = static_cast<unsigned int>

         //std::cout << tile_id << "]:" << horizontal_flip_flag_present << vertical_flip_flag_present << " ";
         // TODO: Consider updating this to (tile_id == -1), this will require the tile_data to be 0-indexed, which
         // it does not appear to be. This should probably happen at the TMJDataLoader stage (though TMJMeshLoader
         // is dependent on it, so will need to be updated there as well).
         // Also, using "tile_id-1" below should be set to simply "tile_id" after having made the above change.

         if (tile_id == 0)
         {
            created_mesh->set_tile_id(x, y, 0, has_horizontal_flip, has_vertical_flip, has_diagonal_flip);
            tile_coords_to_remove.push_back(std::pair<int, int>(x, y));
            //created_mesh->set_tile_id(x, y, 72); // <- Previously
         }
         else
         {
            created_mesh->set_tile_id(x, y, tile_id-1, has_horizontal_flip, has_vertical_flip, has_diagonal_flip);
         }
      }
      std::cout << std::endl;
   }

   for (auto &tile_coord_to_remove : tile_coords_to_remove)
   {
      // TODO: Consider a performance improvement here, locking the index update until all tiles are removed
      created_mesh->remove_tile_xy_from_index(tile_coord_to_remove.first, tile_coord_to_remove.second);
   }

   created_mesh->refresh_vertex_buffer();
   //std::cout << "Tiles removed from index in TileMesh: " << tile_coords_to_remove.size() << std::endl;

   return created_mesh;
}


} // namespace Platforming2D
} // namespace Prototypes
} // namespace AllegroFlare


