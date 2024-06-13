

#include <AllegroFlare/Prototypes/TileDrive/TerrainMeshFactory.hpp>

#include <AllegroFlare/Prototypes/TileDrive/TerrainMeshTMJDataLoader.hpp>
#include <AllegroFlare/Random.hpp>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Prototypes
{
namespace TileDrive
{


TerrainMeshFactory::TerrainMeshFactory(AllegroFlare::BitmapBin* bitmap_bin)
   : bitmap_bin(bitmap_bin)
{
}


TerrainMeshFactory::~TerrainMeshFactory()
{
}


void TerrainMeshFactory::set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin)
{
   this->bitmap_bin = bitmap_bin;
}


AllegroFlare::BitmapBin* TerrainMeshFactory::get_bitmap_bin() const
{
   return bitmap_bin;
}


AllegroFlare::Prototypes::TileDrive::TerrainMesh* TerrainMeshFactory::create_classic_random()
{
   if (!(bitmap_bin))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::TileDrive::TerrainMeshFactory::create_classic_random]: error: guard \"bitmap_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::TileDrive::TerrainMeshFactory::create_classic_random]: error: guard \"bitmap_bin\" not met");
   }
   AllegroFlare::Prototypes::TileDrive::TerrainMesh *result = new AllegroFlare::Prototypes::TileDrive::TerrainMesh;
   result->set_bitmap_bin(bitmap_bin);
   result->set_atlas_configuration("uv.png", 100, 100);
   result->initialize();
   result->get_prim_mesh_ref().rescale_tile_dimensions_to(2, 2*2);
   result->get_prim_mesh_ref().resize(12, 32);
   result->random_fill();
   return result;
}

AllegroFlare::Prototypes::TileDrive::TerrainMesh* TerrainMeshFactory::create_random_with_walls()
{
   if (!(bitmap_bin))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::TileDrive::TerrainMeshFactory::create_random_with_walls]: error: guard \"bitmap_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::TileDrive::TerrainMeshFactory::create_random_with_walls]: error: guard \"bitmap_bin\" not met");
   }
   AllegroFlare::Prototypes::TileDrive::TerrainMesh *result = new AllegroFlare::Prototypes::TileDrive::TerrainMesh;
   result->set_bitmap_bin(bitmap_bin);
   result->set_atlas_configuration("uv-with-decorations-0x.png", 50, 50);
   result->initialize();
   //result->rescale_tile_dimensions_to(2, 6);
   result->rescale_tile_dimensions_to(1, 1);
   result->resize(12, 32 * 2);
   random_fill_from(result, { { 2, 2 } });
   random_sparce_placement(result, { { 0, 0 } }, 20);
   random_sparce_placement(result, { { 1, 1 } }, 40);
   return result;
}

AllegroFlare::Prototypes::TileDrive::TerrainMesh* TerrainMeshFactory::create_from_tmj(std::string tmj_filename, std::string tilemap_bitmap_identifier, int tilemap_tile_width, int tilemap_tile_height)
{
   if (!(bitmap_bin))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::TileDrive::TerrainMeshFactory::create_from_tmj]: error: guard \"bitmap_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::TileDrive::TerrainMeshFactory::create_from_tmj]: error: guard \"bitmap_bin\" not met");
   }
   AllegroFlare::Prototypes::TileDrive::TerrainMeshTMJDataLoader tmj_data_loader(tmj_filename);
   tmj_data_loader.load();

   int num_columns = tmj_data_loader.get_num_columns();
   //if (num_columns != 12) // NOTE: I believe this was here for development check
   //{
      //std::stringstream error_message;
      //error_message << "AllegroFlare::Prototypes::TileDrive::TerrainMeshFactory error: "
                    //<< "Expecting data loaded from \"" << tmj_filename << "\" to have a column count of "
                    //<< "\"12\", but it is \"" << num_columns << "\"";
      //throw std::runtime_error(error_message.str());
   //}

   AllegroFlare::Prototypes::TileDrive::TerrainMesh *result = new AllegroFlare::Prototypes::TileDrive::TerrainMesh;
   result->set_bitmap_bin(bitmap_bin);
   //result->set_atlas_configuration("uv-with-decorations-0x.png", 50, 50);
   result->set_atlas_configuration(tilemap_bitmap_identifier, tilemap_tile_width, tilemap_tile_height);
   result->initialize();

   // resize the mesh and fill with data
   AllegroFlare::TileMaps::PrimMesh &prim_mesh = result->get_prim_mesh_ref();
   AllegroFlare::TileMaps::TileMap<int> &collision_tile_map = result->get_collision_tile_map_ref();
   result->resize(num_columns, tmj_data_loader.get_num_rows());
   bool collision_tile_data_is_present = tmj_data_loader.get_collision_layer_present();
   int tile_count = 0;
   for (auto &tile : tmj_data_loader.get_layer_tile_data())
   {
      int tile_x = tile_count % num_columns;
      int tile_y = tile_count / num_columns;
      int tile_value = tile - 1; // offset by one, Tiled likes to index the first tile as 1, rather than 0

      prim_mesh.set_tile_id(tile_x, tile_y, tile_value);
      // Set this only when collision layer data is not present; TODO: test this condition
      if (!collision_tile_data_is_present) collision_tile_map.set_tile(tile_x, tile_y, tile_value);

      tile_count++;
   }
   int collision_tile_count = 0;
   for (auto &tile : tmj_data_loader.get_collision_layer_tile_data())
   {
      int tile_x = collision_tile_count % num_columns;
      int tile_y = collision_tile_count / num_columns;
      int tile_value = tile - 1; // offset by one, Tiled likes to index the first tile as 1, rather than 0

      collision_tile_map.set_tile(tile_x, tile_y, tile_value);

      collision_tile_count++;
   }

   return result;
}

void TerrainMeshFactory::random_fill_from(AllegroFlare::Prototypes::TileDrive::TerrainMesh* terrain_mesh, std::vector<std::pair<int, int>> inclusion_list)
{
   if (!(terrain_mesh))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::TileDrive::TerrainMeshFactory::random_fill_from]: error: guard \"terrain_mesh\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::TileDrive::TerrainMeshFactory::random_fill_from]: error: guard \"terrain_mesh\" not met");
   }
   if (!((!inclusion_list.empty())))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::TileDrive::TerrainMeshFactory::random_fill_from]: error: guard \"(!inclusion_list.empty())\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::TileDrive::TerrainMeshFactory::random_fill_from]: error: guard \"(!inclusion_list.empty())\" not met");
   }
   AllegroFlare::TileMaps::PrimMesh &prim_mesh = terrain_mesh->get_prim_mesh_ref();
   AllegroFlare::TileMaps::TileMap<int> &collision_tile_map = terrain_mesh->get_collision_tile_map_ref();
   AllegroFlare::Random random;
   for (int y=0; y<prim_mesh.get_num_rows(); y++)
      for (int x=0; x<prim_mesh.get_num_columns(); x++)
      {
         std::pair<int, int> random_element = random.get_random_element(inclusion_list);
         prim_mesh.set_tile_id(x, y, random_element.first);
         collision_tile_map.set_tile(x, y, random_element.second);
      }
   return;
}

void TerrainMeshFactory::random_sparce_placement(AllegroFlare::Prototypes::TileDrive::TerrainMesh* terrain_mesh, std::vector<std::pair<int, int>> inclusion_list, int one_in_chance)
{
   if (inclusion_list.empty()) return;
   AllegroFlare::TileMaps::PrimMesh &prim_mesh = terrain_mesh->get_prim_mesh_ref();
   AllegroFlare::TileMaps::TileMap<int> &collision_tile_map = terrain_mesh->get_collision_tile_map_ref();
   AllegroFlare::Random random;
   for (int y=0; y<prim_mesh.get_num_rows(); y++)
      for (int x=0; x<prim_mesh.get_num_columns(); x++)
      {
         bool will_place = random.get_one_in_chance(one_in_chance);
         if (will_place)
         {
            std::pair<int, int> random_element = random.get_random_element(inclusion_list);
            prim_mesh.set_tile_id(x, y, random_element.first);
            collision_tile_map.set_tile(x, y, random_element.second);
         }
      }
   return;
}

void TerrainMeshFactory::random_fill_excluding(AllegroFlare::Prototypes::TileDrive::TerrainMesh* terrain_mesh, std::set<int> exclusion_list)
{
   if (!(terrain_mesh))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::TileDrive::TerrainMeshFactory::random_fill_excluding]: error: guard \"terrain_mesh\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::TileDrive::TerrainMeshFactory::random_fill_excluding]: error: guard \"terrain_mesh\" not met");
   }
   AllegroFlare::TileMaps::PrimMesh &prim_mesh = terrain_mesh->get_prim_mesh_ref();
   AllegroFlare::TileMaps::TileMap<int> &collision_tile_map = terrain_mesh->get_collision_tile_map_ref();

   AllegroFlare::Random random;
   int num_tiles_in_atlas = 100;
   for (int y=0; y<prim_mesh.get_num_rows(); y++)
      for (int x=0; x<prim_mesh.get_num_columns(); x++)
      {
         bool int_is_excluded = false;
         int random_int = -1;
         int tries_left = 100;
         bool still_tries_left = true;

         do
         {
            random_int = random.get_random_int(0, num_tiles_in_atlas-1);
            int_is_excluded =
               std::find(exclusion_list.begin(), exclusion_list.end(), random_int) != exclusion_list.end();
            tries_left--;
            if (tries_left < 0) still_tries_left = false;
         } while(int_is_excluded && still_tries_left);

         prim_mesh.set_tile_id(x, y, random_int);
      }
   return;
}


} // namespace TileDrive
} // namespace Prototypes
} // namespace AllegroFlare


