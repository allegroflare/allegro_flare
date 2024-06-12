

#include <AllegroFlare/Prototypes/CubeShooter/EntityFactory.hpp>

#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Prototypes
{
namespace CubeShooter
{


EntityFactory::EntityFactory(AllegroFlare::ElementID* scene_root, AllegroFlare::BitmapBin* bitmap_bin, AllegroFlare::ModelBin* model_bin)
   : scene_root(scene_root)
   , bitmap_bin(bitmap_bin)
   , model_bin(model_bin)
   , initialized(false)
{
}


EntityFactory::~EntityFactory()
{
}


void EntityFactory::set_scene_root(AllegroFlare::ElementID* scene_root)
{
   this->scene_root = scene_root;
}


void EntityFactory::set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin)
{
   this->bitmap_bin = bitmap_bin;
}


void EntityFactory::set_model_bin(AllegroFlare::ModelBin* model_bin)
{
   this->model_bin = model_bin;
}


AllegroFlare::ElementID* EntityFactory::get_scene_root() const
{
   return scene_root;
}


AllegroFlare::BitmapBin* EntityFactory::get_bitmap_bin() const
{
   return bitmap_bin;
}


AllegroFlare::ModelBin* EntityFactory::get_model_bin() const
{
   return model_bin;
}


void EntityFactory::initialize()
{
   if (!(scene_root))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::CubeShooter::EntityFactory::initialize]: error: guard \"scene_root\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::CubeShooter::EntityFactory::initialize]: error: guard \"scene_root\" not met");
   }
   if (!(bitmap_bin))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::CubeShooter::EntityFactory::initialize]: error: guard \"bitmap_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::CubeShooter::EntityFactory::initialize]: error: guard \"bitmap_bin\" not met");
   }
   if (!(model_bin))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::CubeShooter::EntityFactory::initialize]: error: guard \"model_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::CubeShooter::EntityFactory::initialize]: error: guard \"model_bin\" not met");
   }
   initialized = true;
   return;
}

AllegroFlare::Prototypes::CubeShooter::Entity* EntityFactory::add_cube(float x, float y, float z)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::CubeShooter::EntityFactory::add_cube]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::CubeShooter::EntityFactory::add_cube]: error: guard \"initialized\" not met");
   }
   AllegroFlare::Prototypes::CubeShooter::Entity* result = new AllegroFlare::Prototypes::CubeShooter::Entity;
   result->reassign_parent(scene_root);
   result->set_created_at(al_get_time());

   result->get_placement_ref().position = AllegroFlare::Vec3D(x, y, z);

   AllegroFlare::Model3D *model = model_bin->auto_get("unit_cube-01.obj");
   result->set_model_3d(model);
   result->set_min_bounding_box_coordinates(model->get_min_vertex_coordinate());
   result->set_max_bounding_box_coordinates(model->get_max_vertex_coordinate());

   return result;
}

AllegroFlare::Prototypes::CubeShooter::Entity* EntityFactory::add_player_bullet(float x, float y, float z)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::CubeShooter::EntityFactory::add_player_bullet]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::CubeShooter::EntityFactory::add_player_bullet]: error: guard \"initialized\" not met");
   }
   AllegroFlare::Prototypes::CubeShooter::Entity* result = new AllegroFlare::Prototypes::CubeShooter::Entity;
   result->reassign_parent(scene_root);
   result->set_created_at(al_get_time());

   AllegroFlare::Model3D *model = model_bin->auto_get("unit_cube-01.obj");

   // size and movement
   result->get_placement_ref().position = AllegroFlare::Vec3D(x, y, z);
   result->get_velocity_ref().position = AllegroFlare::Vec3D(0, 0, -1);
   result->set_model_3d(model);
   result->set_min_bounding_box_coordinates(model->get_min_vertex_coordinate());
   result->set_max_bounding_box_coordinates(model->get_max_vertex_coordinate());

   // attributes
   result->set_attribute("ignore_environmental_physics");
   result->set_attribute("player_bullet");
   result->set("lifespan", 1.0);

   // appearance
   result->get_placement_ref().scale = AllegroFlare::Vec3D(0.4, 0.4, 0.4);
   result->get_velocity_ref().rotation = AllegroFlare::Vec3D(-1.6, 4.7, -3.14);
   return result;
}

AllegroFlare::Prototypes::CubeShooter::Entity* EntityFactory::add_player_ship(float x, float y, float z)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::CubeShooter::EntityFactory::add_player_ship]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::CubeShooter::EntityFactory::add_player_ship]: error: guard \"initialized\" not met");
   }
   static bool loaded_already = false;
   AllegroFlare::Prototypes::CubeShooter::Entity* result = new AllegroFlare::Prototypes::CubeShooter::Entity;
   result->reassign_parent(scene_root);
   result->set_created_at(al_get_time());

   AllegroFlare::Model3D *model = model_bin->auto_get("ship-01.obj");
   model->set_texture(bitmap_bin->auto_get("ship-01.png"));
   if (!loaded_already) { model->scale(0.5); loaded_already = true; }
   result->set_model_3d(model);
   result->set_min_bounding_box_coordinates(model->get_min_vertex_coordinate() * 0.7);
   result->set_max_bounding_box_coordinates(model->get_max_vertex_coordinate() * 0.7);

   result->get_placement_ref().position = AllegroFlare::Vec3D(x, y, z);
   result->get_placement_ref().rotation.y = 0.5;
   result->set_model_3d(model_bin->auto_get("ship-01.obj"));

   return result;
}

AllegroFlare::Prototypes::CubeShooter::Entity* EntityFactory::add_world_mesh()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::CubeShooter::EntityFactory::add_world_mesh]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::CubeShooter::EntityFactory::add_world_mesh]: error: guard \"initialized\" not met");
   }
   AllegroFlare::Prototypes::CubeShooter::Entity* result = new AllegroFlare::Prototypes::CubeShooter::Entity;
   result->reassign_parent(scene_root);
   result->set_created_at(al_get_time());

   AllegroFlare::Model3D *model = model_bin->auto_get("level-03-long.obj");
   model->set_texture(bitmap_bin->auto_get("level-03.png"));
   result->set_model_3d(model);
   result->set_min_bounding_box_coordinates(model->get_min_vertex_coordinate());
   result->set_max_bounding_box_coordinates(model->get_max_vertex_coordinate());

   result->set_attribute("ignore_environmental_physics");
   result->set_attribute("ignore");

   return result;
}


} // namespace CubeShooter
} // namespace Prototypes
} // namespace AllegroFlare


