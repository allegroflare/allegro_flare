

#include <AllegroFlare/GraphicsPipelines/Basic3D/Scene.hpp>

#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace GraphicsPipelines
{
namespace Basic3D
{


Scene::Scene()
   : bitmap_bin(nullptr)
   , model_bin(nullptr)
   , camera()
   , entities({})
   , initialized(false)
{
}


Scene::~Scene()
{
}


void Scene::set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin)
{
   this->bitmap_bin = bitmap_bin;
}


void Scene::set_model_bin(AllegroFlare::ModelBin* model_bin)
{
   this->model_bin = model_bin;
}


void Scene::set_camera(AllegroFlare::Camera3D camera)
{
   this->camera = camera;
}


AllegroFlare::BitmapBin* Scene::get_bitmap_bin() const
{
   return bitmap_bin;
}


AllegroFlare::ModelBin* Scene::get_model_bin() const
{
   return model_bin;
}


AllegroFlare::Camera3D &Scene::get_camera_ref()
{
   return camera;
}


void Scene::initialize()
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[Scene::initialize]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Scene::initialize: error: guard \"(!initialized)\" not met");
   }
   if (!(model_bin))
   {
      std::stringstream error_message;
      error_message << "[Scene::initialize]: error: guard \"model_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Scene::initialize: error: guard \"model_bin\" not met");
   }
   if (!(bitmap_bin))
   {
      std::stringstream error_message;
      error_message << "[Scene::initialize]: error: guard \"bitmap_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Scene::initialize: error: guard \"bitmap_bin\" not met");
   }
   // Position the camera 5 meters back while looking at the origin (0, 0, 0)
   camera.stepout = AllegroFlare::Vec3D(0, 0, 5);

   // Tilt the camera, so it is looking down slightly at the target
   camera.tilt = 0.4;

   initialized = true;

   return;
}

void Scene::add_entity()
{
   AllegroFlare::GraphicsPipelines::Basic3D::Entity result_entity;
   result_entity.model = model_bin->auto_get("heart_item-01.obj");
   result_entity.texture = bitmap_bin->auto_get("heart_item-02.png");

   entities.emplace_back(result_entity);

   //model.initialize();
   //AllegroFlare::Model3DObjLoader loader(&model, model_obj_filename.c_str(), 1.0);
   //loader.load();
   //texture = al_load_bitmap(model_texture_filename.c_str());
   //if (!texture) throw std::runtime_error("Texture not found");
   //model.set_texture(texture);
   return;
}

void Scene::update()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[Scene::update]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Scene::update: error: guard \"initialized\" not met");
   }
   for (auto &entity : entities)
   {
      entity.placement.rotation.y += 0.00025;
   }
   return;
}

void Scene::render()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[Scene::render]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Scene::render: error: guard \"initialized\" not met");
   }
   // TODO: Validate the render surface has depth
   // TODO: Clear the depth on the render surface

   // Setup the projection
   ALLEGRO_BITMAP *render_surface = al_get_target_bitmap();
   camera.setup_projection_on(render_surface);

   // Use the default allegro shader
   al_use_shader(NULL);

   // Draw all of the entities
   for (auto &entity : entities)
   {
      // Position and render model
      entity.placement.start_transform();
      entity.model->set_texture(entity.texture);
      entity.model->draw();
      entity.placement.restore_transform();
   }

   return;
}


} // namespace Basic3D
} // namespace GraphicsPipelines
} // namespace AllegroFlare


