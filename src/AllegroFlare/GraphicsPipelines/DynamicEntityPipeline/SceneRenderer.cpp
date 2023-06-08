

#include <AllegroFlare/GraphicsPipelines/DynamicEntityPipeline/SceneRenderer.hpp>

#include <AllegroFlare/GraphicsPipelines/DynamicEntityPipeline/Entities/Camera3D.hpp>
#include <AllegroFlare/GraphicsPipelines/DynamicEntityPipeline/Entities/DynamicModel3D.hpp>
#include <AllegroFlare/GraphicsPipelines/DynamicEntityPipeline/Entities/StaticModel3D.hpp>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace GraphicsPipelines
{
namespace DynamicEntityPipeline
{


SceneRenderer::SceneRenderer(AllegroFlare::Shaders::Cubemap* cubemap_shader, AllegroFlare::GraphicsPipelines::DynamicEntityPipeline::EntityPool* entity_pool)
   : cubemap_shader(cubemap_shader)
   , entity_pool(entity_pool)
{
}


SceneRenderer::~SceneRenderer()
{
}


void SceneRenderer::set_cubemap_shader(AllegroFlare::Shaders::Cubemap* cubemap_shader)
{
   this->cubemap_shader = cubemap_shader;
}


void SceneRenderer::set_entity_pool(AllegroFlare::GraphicsPipelines::DynamicEntityPipeline::EntityPool* entity_pool)
{
   this->entity_pool = entity_pool;
}


AllegroFlare::Shaders::Cubemap* SceneRenderer::get_cubemap_shader() const
{
   return cubemap_shader;
}


AllegroFlare::GraphicsPipelines::DynamicEntityPipeline::EntityPool* SceneRenderer::get_entity_pool() const
{
   return entity_pool;
}


void SceneRenderer::render()
{
   if (!(entity_pool))
   {
      std::stringstream error_message;
      error_message << "[SceneRenderer::render]: error: guard \"entity_pool\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("SceneRenderer::render: error: guard \"entity_pool\" not met");
   }
   if (!(cubemap_shader))
   {
      std::stringstream error_message;
      error_message << "[SceneRenderer::render]: error: guard \"cubemap_shader\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("SceneRenderer::render: error: guard \"cubemap_shader\" not met");
   }
   using namespace AllegroFlare::GraphicsPipelines::DynamicEntityPipeline;
   //headers: [ AllegroFlare/GraphicsPipelines/DynamicEntityPipeline/SceneRenderer.hpp ]

   // Extract out the camera and render the scene
   Entities::Base *entity = entity_pool->find_with_attribute("primary_camera");
   if (!entity) throw std::runtime_error("no camera present");
   // TODO: validate the camera is of type Entities::Camera
   Entities::Camera3D *as_camera = static_cast<Entities::Camera3D*>(entity);

   // TODO: Get a proper render surface, rather than pulling from the current display
   ALLEGRO_BITMAP *render_surface = al_get_backbuffer(al_get_current_display()); // TODO: replace with render surface
   al_clear_depth_buffer(1);
   al_clear_to_color(ALLEGRO_COLOR{0.1, 0.105, 0.12, 1.0});

   AllegroFlare::Camera3D &camera = as_camera->get_camera_3d_ref();
   camera.setup_projection_on(render_surface);

   // Set the camera position in the iridescent shder
   cubemap_shader->set_camera_position(camera.get_real_position());

   //std::unordered_set<AllegroFlare::SceneGraph::Entities::Base*>
   for (auto &entity : entity_pool->get_entity_pool_ref())
   {
      // TODO: Rename legacy "as_agc_entity" to something more appropriate
      Entities::Base *as_agc_entity = static_cast<Entities::Base*>(entity);

      // Skip if entity is flagged as "do not render"
      // TODO: Introduce DO_NOT_RENDER flags
      //if (as_agc_entity->exists(EntityFlags::DO_NOT_RENDER)) continue;
      

      AllegroFlare::Model3D *model = get_model_3d(as_agc_entity); //as_agc_entity->get_model();

      /*
      if (model)
      {
         // Collect render flags
         bool renders_with_iridescent =
            //true;
            as_agc_entity->exists(ArtGalleryOfCats::Gameplay::EntityFlags::RENDERS_WITH_IRIDESCENT);

         // Setup the render for this object
         if (renders_with_iridescent)
         {
            ArtGalleryOfCats::Gameplay::Entities::Base *as_gac_base =
               static_cast<ArtGalleryOfCats::Gameplay::Entities::Base*>(entity);
            cubemap_shader->set_object_placement(&as_gac_base->get_placement_ref()); // NOTE: For now, this has to be set before activating the shader

            cubemap_shader->activate();
         }
         else
         {
            ALLEGRO_BITMAP *texture = as_agc_entity->get_texture();
            if (texture) model->set_texture(texture);
            as_agc_entity->get_placement_ref().start_transform();
         }

         // Draw the model
         model->draw();

         // Teardown the render for this object
         if (renders_with_iridescent)
         {
            cubemap_shader->deactivate();
            // TODO: turn off shader
         }
         else
         {
            as_agc_entity->get_placement_ref().restore_transform();
         }
      }
      else // (!model)
      {
         ALLEGRO_BITMAP *texture = as_agc_entity->get_texture();
         //if (texture) model->set_texture(texture);

         if (texture)
         {
            as_agc_entity->get_placement_ref().start_transform();

            AllegroFlare::Placement3D inner_transform;
            al_draw_bitmap(texture, 0, 0, ALLEGRO_FLIP_VERTICAL);
            as_agc_entity->get_placement_ref().restore_transform();
         }
      }
      */
   }

   //as_camera->start_reverse_transform();
   return;
}

AllegroFlare::Model3D* SceneRenderer::get_model_3d(AllegroFlare::GraphicsPipelines::DynamicEntityPipeline::Entities::Base* entity)
{
   if (!(entity))
   {
      std::stringstream error_message;
      error_message << "[SceneRenderer::get_model_3d]: error: guard \"entity\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("SceneRenderer::get_model_3d: error: guard \"entity\" not met");
   }
   // TODO: Optimize this lookup
   if (entity->is_type(AllegroFlare::GraphicsPipelines::DynamicEntityPipeline::Entities::DynamicModel3D::TYPE))
   {
      // TODO: Static cast and return model
   }
   else if (entity->is_type(AllegroFlare::GraphicsPipelines::DynamicEntityPipeline::Entities::StaticModel3D::TYPE))
   {
      // TODO: Static cast and return model
   }
   return nullptr;
}


} // namespace DynamicEntityPipeline
} // namespace GraphicsPipelines
} // namespace AllegroFlare


