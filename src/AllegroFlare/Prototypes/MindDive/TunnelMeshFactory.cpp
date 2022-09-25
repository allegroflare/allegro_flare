

#include <AllegroFlare/Prototypes/MindDive/TunnelMeshFactory.hpp>

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
   result->get_prim_mesh_ref().rescale_tile_dimentions_to(2, 2);
   result->get_prim_mesh_ref().resize(12, 32);
   result->random_fill();
   return result;
}


} // namespace MindDive
} // namespace Prototypes
} // namespace AllegroFlare


