

#include <AllegroFlare/Cubemap.hpp>




namespace AllegroFlare
{


Cubemap::Cubemap(GLuint id)
   : id(id)
{
}


Cubemap::~Cubemap()
{
}


GLuint Cubemap::get_id() const
{
   return id;
}




} // namespace AllegroFlare


