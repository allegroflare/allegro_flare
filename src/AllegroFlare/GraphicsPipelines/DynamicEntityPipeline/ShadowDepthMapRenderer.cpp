

#include <AllegroFlare/GraphicsPipelines/DynamicEntityPipeline/ShadowDepthMapRenderer.hpp>

#include <AllegroFlare/Errors.hpp>
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
   , casting_light({})
   , backbuffer_sub_bitmap(nullptr)
   , backbuffer_is_setup(false)
   , backbuffer_is_managed_by_this_class(false)
{
}


ShadowDepthMapRenderer::~ShadowDepthMapRenderer()
{
}


void ShadowDepthMapRenderer::set_entity_pool(AllegroFlare::GraphicsPipelines::DynamicEntityPipeline::EntityPool* entity_pool)
{
   this->entity_pool = entity_pool;
}


void ShadowDepthMapRenderer::set_casting_light(AllegroFlare::Camera3D casting_light)
{
   this->casting_light = casting_light;
}


AllegroFlare::GraphicsPipelines::DynamicEntityPipeline::EntityPool* ShadowDepthMapRenderer::get_entity_pool() const
{
   return entity_pool;
}


AllegroFlare::Camera3D ShadowDepthMapRenderer::get_casting_light() const
{
   return casting_light;
}


ALLEGRO_BITMAP* ShadowDepthMapRenderer::get_backbuffer_sub_bitmap() const
{
   return backbuffer_sub_bitmap;
}


void ShadowDepthMapRenderer::setup_backbuffer_from_display(ALLEGRO_DISPLAY* display)
{
   if (!((!backbuffer_is_setup)))
   {
      std::stringstream error_message;
      error_message << "[ShadowDepthMapRenderer::setup_backbuffer_from_display]: error: guard \"(!backbuffer_is_setup)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("ShadowDepthMapRenderer::setup_backbuffer_from_display: error: guard \"(!backbuffer_is_setup)\" not met");
   }
   if (!(display))
   {
      std::stringstream error_message;
      error_message << "[ShadowDepthMapRenderer::setup_backbuffer_from_display]: error: guard \"display\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("ShadowDepthMapRenderer::setup_backbuffer_from_display: error: guard \"display\" not met");
   }
   ALLEGRO_BITMAP *backbuffer = al_get_backbuffer(display);
   int width = al_get_display_width(display);
   int height = al_get_display_width(display);
   backbuffer_sub_bitmap = al_create_sub_bitmap(backbuffer, 0, 0, width, height);
   if (!backbuffer_sub_bitmap)
   {
      AllegroFlare::Errors::throw_error(
         "AllegroFlare/GraphicsPipelines/DynamicEntityPipeline/ShadowDepthMapRenderer",
         "Could not create backbuffer_sub_bitmapfrom display in order to create a render surface."
      );
   }
   backbuffer_is_setup = true;
   backbuffer_is_managed_by_this_class = true;
   return;
}

void ShadowDepthMapRenderer::destroy()
{
   if (backbuffer_is_setup && backbuffer_is_managed_by_this_class) al_destroy_bitmap(backbuffer_sub_bitmap);
   return;
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
   casting_light.stepout = vec3d(0, 0, 15); // note

   float light_time_of_day = 0.15f;
   casting_light.tilt = 3.141592653 * light_time_of_day; // light_time_of_day = 0.05; // sunrise
                                                         //                     0.5; // high noon
                                                         //                     0.95; // sunset

   casting_light.spin = 0.0f; //light_spin;





   //if (!initialized) throw std::runtime_error("Wicked::SceneRenderer::refresh_shadow_map: ERROR: not initialized");
   //if (!_entities) throw std::runtime_error("CCc");
   //std::vector<Entity *> &entities = (*_entities);

   // TODO: store and restore states on glEnable/glCullFace, etc
   // https://www.khronos.org/registry/OpenGL-Refpages/gl2.1/xhtml/glIsEnabled.xml
   // ^^ documentation of how this might be approached

   glEnable(GL_CULL_FACE); // requiring direct OpenGL calls eventually be fazed out
   glCullFace(GL_FRONT); 

   //al_set_target_bitmap(backbuffer_sub_bitmap);

   //al_clear_to_color(color::white);
   ///*
   /*
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

void ShadowDepthMapRenderer::setup_projection_SHADOW()
{
   if (!(backbuffer_is_setup))
   {
      std::stringstream error_message;
      error_message << "[ShadowDepthMapRenderer::setup_projection_SHADOW]: error: guard \"backbuffer_is_setup\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("ShadowDepthMapRenderer::setup_projection_SHADOW: error: guard \"backbuffer_is_setup\" not met");
   }
   //if (!initialized)
   //{
      //throw std::runtime_error("Wicked::SceneRenderer::setup_projection_SHADOW: ERROR: not initialized");
   //}
   //if (!backbuffer_sub_bitmap)
   //{
      //throw std::runtime_error("AAa");
   //}
   ///*

   // setup the render settings
   al_set_render_state(ALLEGRO_DEPTH_TEST, 1);
   al_set_render_state(ALLEGRO_WRITE_MASK, ALLEGRO_MASK_DEPTH | ALLEGRO_MASK_RGBA);
   al_clear_depth_buffer(1);
   /*

   ALLEGRO_TRANSFORM shadow_map_projection;

   shadow_casting_light.reverse_position_transform(&shadow_map_projection);

   ALLEGRO_BITMAP *bitmap = backbuffer_sub_bitmap;
   float divisor = shadow_scale_divisor;
   al_scale_transform_3d(&shadow_map_projection, 150/divisor, 150/divisor, 1); // note, increasing this divisor will
      // expand the range of the light projection, but it will reduce its resolution, a divisor of 1 will have a good
      // quality of shadow, but will have a range of about 15-20 meters; a divisor of 2 will double that size, but
      // reduce the resolution of the shadow. Original engine had a default of 1.0f;

   al_orthographic_transform(
      &shadow_map_projection,
      -al_get_bitmap_width(bitmap),
      al_get_bitmap_height(bitmap),
      30.0,
      al_get_bitmap_width(bitmap),
      -al_get_bitmap_height(bitmap),
      -30.0
   );

   if (transform_to_fill != nullptr)
   {
      al_copy_transform(transform_to_fill, &shadow_map_projection);
   }

   al_use_projection_transform(&shadow_map_projection);
   */
   return;
}


} // namespace DynamicEntityPipeline
} // namespace GraphicsPipelines
} // namespace AllegroFlare


