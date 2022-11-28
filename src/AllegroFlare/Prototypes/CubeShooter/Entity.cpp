

#include <AllegroFlare/Prototypes/CubeShooter/Entity.hpp>




namespace AllegroFlare
{
namespace Prototypes
{
namespace CubeShooter
{


Entity::Entity()
   : AllegroFlare::ElementID()
   , placement()
   , velocity()
   , model_3d(nullptr)
   , created_at(0.0f)
   , min_bounding_box_coordinates()
   , max_bounding_box_coordinates()
{
}


Entity::~Entity()
{
}


void Entity::set_placement(AllegroFlare::Placement3D placement)
{
   this->placement = placement;
}


void Entity::set_velocity(AllegroFlare::Placement3D velocity)
{
   this->velocity = velocity;
}


void Entity::set_model_3d(AllegroFlare::Model3D* model_3d)
{
   this->model_3d = model_3d;
}


void Entity::set_created_at(float created_at)
{
   this->created_at = created_at;
}


void Entity::set_min_bounding_box_coordinates(AllegroFlare::Vec3D min_bounding_box_coordinates)
{
   this->min_bounding_box_coordinates = min_bounding_box_coordinates;
}


void Entity::set_max_bounding_box_coordinates(AllegroFlare::Vec3D max_bounding_box_coordinates)
{
   this->max_bounding_box_coordinates = max_bounding_box_coordinates;
}


AllegroFlare::Placement3D Entity::get_placement() const
{
   return placement;
}


AllegroFlare::Placement3D Entity::get_velocity() const
{
   return velocity;
}


AllegroFlare::Model3D* Entity::get_model_3d() const
{
   return model_3d;
}


float Entity::get_created_at() const
{
   return created_at;
}


AllegroFlare::Vec3D Entity::get_min_bounding_box_coordinates() const
{
   return min_bounding_box_coordinates;
}


AllegroFlare::Vec3D Entity::get_max_bounding_box_coordinates() const
{
   return max_bounding_box_coordinates;
}


AllegroFlare::Placement3D &Entity::get_placement_ref()
{
   return placement;
}


AllegroFlare::Placement3D &Entity::get_velocity_ref()
{
   return velocity;
}


AllegroFlare::Model3D* &Entity::get_model_3d_ref()
{
   return model_3d;
}


float Entity::infer_age(float time_now)
{
   return time_now - created_at;
}

bool Entity::has_attribute(std::string attribute)
{
   return AllegroFlare::Attributes::exists(attribute);
}

void Entity::set_attribute(std::string attribute)
{
   AllegroFlare::Attributes::set(attribute);
}

void Entity::unset_attribute(std::string attribute)
{
   AllegroFlare::Attributes::remove(attribute);
}


} // namespace CubeShooter
} // namespace Prototypes
} // namespace AllegroFlare


