

#include <AllegroFlare/GraphicsPipelines/DynamicEntityPipeline/ShadowDepthMapRenderer.hpp>

#include <allegro5/allegro_opengl.h>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace GraphicsPipelines
{
namespace DynamicEntityPipeline
{


ShadowDepthMapRenderer::ShadowDepthMapRenderer(AllegroFlare::GraphicsPipelines::DynamicEntityPipeline::EntityPool* entity_pool)
   : entity_pool(entity_pool)
{
}


ShadowDepthMapRenderer::~ShadowDepthMapRenderer()
{
}


void ShadowDepthMapRenderer::set_entity_pool(AllegroFlare::GraphicsPipelines::DynamicEntityPipeline::EntityPool* entity_pool)
{
   this->entity_pool = entity_pool;
}


AllegroFlare::GraphicsPipelines::DynamicEntityPipeline::EntityPool* ShadowDepthMapRenderer::get_entity_pool() const
{
   return entity_pool;
}


void ShadowDepthMapRenderer::render()
{
   if (!(entity_pool))
   {
      std::stringstream error_message;
      error_message << "[ShadowDepthMapRenderer::render]: error: guard \"entity_pool\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("ShadowDepthMapRenderer::render: error: guard \"entity_pool\" not met");
   }
   //if (!initialized) throw std::runtime_error("Wicked::SceneRenderer::refresh_shadow_map: ERROR: not initialized");
   //if (!_entities) throw std::runtime_error("CCc");
   //std::vector<Entity *> &entities = (*_entities);

   // TODO: store and restore states on glEnable/glCullFace, etc
   // https://www.khronos.org/registry/OpenGL-Refpages/gl2.1/xhtml/glIsEnabled.xml
   // ^^ documentation of how this might be approached

   glEnable(GL_CULL_FACE); // requiring direct OpenGL calls eventually be fazed out
   glCullFace(GL_FRONT); 

   //al_set_target_bitmap(backbuffer_sub_bitmap);

   /*

   //al_clear_to_color(color::white);
   setup_projection_SHADOW(casting_light, shadow_map_depth_pass_transform);

   // setup the shader
   //depth_shader.use();
   depth_shader->activate();

   // draw the objects
   for (unsigned i=0; i<entities.size(); i++)
   {
      entities[i]->draw_for_depth_pass(depth_shader);

      ALLEGRO_TRANSFORM transform;
      place.build_transform(&transform);
      AllegroFlare::Shaders::Base::set_mat4("position_transform", &transform);

      if (model) model->draw();

   //return;
   }

   if (pointer)
   {
       pointer->draw_for_depth_pass(depth_shader);
   }


   al_set_target_bitmap(shadow_map_depth_pass_surface); // I *believe* newer versions of allegro have a depth map
                                                        // on a bitmap this may be able to be updated so that the
                                                        // backbuffer does not need be used to render this
   al_draw_bitmap(backbuffer_sub_bitmap, 0, 0, 0);

   //glEnable(GL_CULL_FACE); // requiring opengl should eventually be fazed out
   glCullFace(GL_BACK); 
   //glCullFace(GL_FRONT);
   glDisable(GL_CULL_FACE);

   */

   return;
}


} // namespace DynamicEntityPipeline
} // namespace GraphicsPipelines
} // namespace AllegroFlare


