

#include <AllegroFlare/GraphicsPipelines/Basic3D/Entity.hpp>




namespace AllegroFlare
{
namespace GraphicsPipelines
{
namespace Basic3D
{


Entity::Entity()
   : model(nullptr)
   , texture(nullptr)
   , placement()
   , model_obj_filename("[unset-model_obj_filename]")
   , model_texture_filename("[unset-model_texture_filename]")
{
}


Entity::~Entity()
{
}




} // namespace Basic3D
} // namespace GraphicsPipelines
} // namespace AllegroFlare


