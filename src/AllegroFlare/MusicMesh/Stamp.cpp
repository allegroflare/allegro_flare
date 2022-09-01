

#include <AllegroFlare/MusicMesh/Stamp.hpp>




namespace AllegroFlare
{
namespace MusicMesh
{


Stamp::Stamp(uint32_t id, float x, float y, uint32_t multi_mesh_id)
   : id(id)
   , x(x)
   , y(y)
   , multi_mesh_id(multi_mesh_id)
{
}


Stamp::~Stamp()
{
}


void Stamp::set_id(uint32_t id)
{
   this->id = id;
}


void Stamp::set_x(float x)
{
   this->x = x;
}


void Stamp::set_y(float y)
{
   this->y = y;
}


void Stamp::set_multi_mesh_id(uint32_t multi_mesh_id)
{
   this->multi_mesh_id = multi_mesh_id;
}


uint32_t Stamp::get_id() const
{
   return id;
}


float Stamp::get_x() const
{
   return x;
}


float Stamp::get_y() const
{
   return y;
}


uint32_t Stamp::get_multi_mesh_id() const
{
   return multi_mesh_id;
}


void Stamp::reassign_multi_mesh_id(uint32_t new_multi_mesh_id)
{
   multi_mesh_id = new_multi_mesh_id;
   return;
}


} // namespace MusicMesh
} // namespace AllegroFlare


