

#include <AllegroFlare/MusicMesh/Stamp.hpp>




namespace AllegroFlare
{
namespace MusicMesh
{


Stamp::Stamp(uint32_t id, uint32_t multimesh_id)
   : id(id)
   , multimesh_id(multimesh_id)
{
}


Stamp::~Stamp()
{
}


void Stamp::set_id(uint32_t id)
{
   this->id = id;
}


void Stamp::set_multimesh_id(uint32_t multimesh_id)
{
   this->multimesh_id = multimesh_id;
}


uint32_t Stamp::get_id() const
{
   return id;
}


uint32_t Stamp::get_multimesh_id() const
{
   return multimesh_id;
}


void Stamp::reassign_multimesh_id(uint32_t new_multimesh_id)
{
   multimesh_id = new_multimesh_id;
   return;
}


} // namespace MusicMesh
} // namespace AllegroFlare


