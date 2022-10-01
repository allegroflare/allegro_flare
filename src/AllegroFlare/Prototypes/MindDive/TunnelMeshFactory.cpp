

#include <AllegroFlare/Prototypes/MindDive/TunnelMeshFactory.hpp>

#include <AllegroFlare/Random.hpp>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Prototypes
{
namespace MindDive
{


TunnelMeshFactory::TunnelMeshFactory(AllegroFlare::BitmapBin* bitmap_bin)
   : bitmap_bin(bitmap_bin)
{
}


TunnelMeshFactory::~TunnelMeshFactory()
{
}


void TunnelMeshFactory::set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin)
{
   this->bitmap_bin = bitmap_bin;
}


AllegroFlare::BitmapBin* TunnelMeshFactory::get_bitmap_bin() const
{
   return bitmap_bin;
}


AllegroFlare::Prototypes::MindDive::TunnelMesh* TunnelMeshFactory::create_classic_random()
{
   if (!(bitmap_bin))
   {
      std::stringstream error_message;
      error_message << "TunnelMeshFactory" << "::" << "create_classic_random" << ": error: " << "guard \"bitmap_bin\" not met";
      throw std::runtime_error(error_message.str());
   }
   AllegroFlare::Prototypes::MindDive::TunnelMesh *result = new AllegroFlare::Prototypes::MindDive::TunnelMesh;
   result->set_bitmap_bin(bitmap_bin);
   result->set_atlas_configuration("uv.png", 100, 100);
   result->initialize();
   result->get_prim_mesh_ref().rescale_tile_dimentions_to(2, 2*2);
   result->get_prim_mesh_ref().resize(12, 32);
   result->random_fill();
   return result;
}

AllegroFlare::Prototypes::MindDive::TunnelMesh* TunnelMeshFactory::create_random_with_walls()
{
   if (!(bitmap_bin))
   {
      std::stringstream error_message;
      error_message << "TunnelMeshFactory" << "::" << "create_random_with_walls" << ": error: " << "guard \"bitmap_bin\" not met";
      throw std::runtime_error(error_message.str());
   }
   AllegroFlare::Prototypes::MindDive::TunnelMesh *result = new AllegroFlare::Prototypes::MindDive::TunnelMesh;
   result->set_bitmap_bin(bitmap_bin);
   result->set_atlas_configuration("uv-with-decorations-0x.png", 50, 50);
   result->initialize();
   result->rescale_tile_dimentions_to(2, 6);
   result->resize(12, 32);
   random_fill_from(result, { { 2, 2 } });
   random_sparce_placement(result, { { 0, 0 } }, 20);
   random_sparce_placement(result, { { 1, 1 } }, 40);
   return result;
}

void TunnelMeshFactory::random_fill_from(AllegroFlare::Prototypes::MindDive::TunnelMesh* tunnel_mesh, std::vector<std::pair<int, int>> inclusion_list)
{
   if (!(tunnel_mesh))
   {
      std::stringstream error_message;
      error_message << "TunnelMeshFactory" << "::" << "random_fill_from" << ": error: " << "guard \"tunnel_mesh\" not met";
      throw std::runtime_error(error_message.str());
   }
   if (!((!inclusion_list.empty())))
   {
      std::stringstream error_message;
      error_message << "TunnelMeshFactory" << "::" << "random_fill_from" << ": error: " << "guard \"(!inclusion_list.empty())\" not met";
      throw std::runtime_error(error_message.str());
   }
   AllegroFlare::TileMaps::PrimMesh &prim_mesh = tunnel_mesh->get_prim_mesh_ref();
   AllegroFlare::TileMaps::TileMap<int> &collision_tile_map = tunnel_mesh->get_collision_tile_map_ref();
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

void TunnelMeshFactory::random_sparce_placement(AllegroFlare::Prototypes::MindDive::TunnelMesh* tunnel_mesh, std::vector<std::pair<int, int>> inclusion_list, int one_in_chance)
{
   if (inclusion_list.empty()) return;
   AllegroFlare::TileMaps::PrimMesh &prim_mesh = tunnel_mesh->get_prim_mesh_ref();
   AllegroFlare::TileMaps::TileMap<int> &collision_tile_map = tunnel_mesh->get_collision_tile_map_ref();
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

void TunnelMeshFactory::random_fill_excluding(AllegroFlare::Prototypes::MindDive::TunnelMesh* tunnel_mesh, std::set<int> exclusion_list)
{
   if (!(tunnel_mesh))
   {
      std::stringstream error_message;
      error_message << "TunnelMeshFactory" << "::" << "random_fill_excluding" << ": error: " << "guard \"tunnel_mesh\" not met";
      throw std::runtime_error(error_message.str());
   }
   AllegroFlare::TileMaps::PrimMesh &prim_mesh = tunnel_mesh->get_prim_mesh_ref();
   AllegroFlare::TileMaps::TileMap<int> &collision_tile_map = tunnel_mesh->get_collision_tile_map_ref();

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


} // namespace MindDive
} // namespace Prototypes
} // namespace AllegroFlare


