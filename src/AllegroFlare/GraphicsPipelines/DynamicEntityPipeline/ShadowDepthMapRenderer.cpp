

#include <AllegroFlare/GraphicsPipelines/DynamicEntityPipeline/ShadowDepthMapRenderer.hpp>

#include <AllegroFlare/Errors.hpp>
#include <AllegroFlare/GraphicsPipelines/DynamicEntityPipeline/Entities/StaticModel3D.hpp>
#include <AllegroFlare/UsefulPHP.hpp>
#include <allegro5/allegro.h>
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
   , depth_map_shader(nullptr)
   , casting_light({})
   , casting_light_projection_transform({})
   , backbuffer_sub_bitmap(nullptr)
   , result_surface_bitmap(nullptr)
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


void ShadowDepthMapRenderer::set_casting_light_projection_transform(ALLEGRO_TRANSFORM casting_light_projection_transform)
{
   this->casting_light_projection_transform = casting_light_projection_transform;
}


AllegroFlare::GraphicsPipelines::DynamicEntityPipeline::EntityPool* ShadowDepthMapRenderer::get_entity_pool() const
{
   return entity_pool;
}


AllegroFlare::Camera3D ShadowDepthMapRenderer::get_casting_light() const
{
   return casting_light;
}


ALLEGRO_TRANSFORM ShadowDepthMapRenderer::get_casting_light_projection_transform() const
{
   return casting_light_projection_transform;
}


ALLEGRO_BITMAP* ShadowDepthMapRenderer::get_backbuffer_sub_bitmap() const
{
   return backbuffer_sub_bitmap;
}


AllegroFlare::Camera3D &ShadowDepthMapRenderer::get_casting_light_ref()
{
   return casting_light;
}


ALLEGRO_BITMAP* ShadowDepthMapRenderer::get_result_surface_bitmap()
{
   if (!(result_surface_bitmap))
   {
      std::stringstream error_message;
      error_message << "[ShadowDepthMapRenderer::get_result_surface_bitmap]: error: guard \"result_surface_bitmap\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("ShadowDepthMapRenderer::get_result_surface_bitmap: error: guard \"result_surface_bitmap\" not met");
   }
   return result_surface_bitmap;
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
   // TODO: Test this backbuffer is properly created (dimensions, depth values, etc)
   // TODO: Use ALLEGRO_NO_PRESERVE_TEXTURE when building bitmap
   ALLEGRO_BITMAP *backbuffer = al_get_backbuffer(display);
   int width = al_get_display_width(display);
   int height = al_get_display_height(display);
   backbuffer_sub_bitmap = al_create_sub_bitmap(backbuffer, 0, 0, width, height);
   if (!backbuffer_sub_bitmap)
   {
      AllegroFlare::Errors::throw_error(
         "AllegroFlare/GraphicsPipelines/DynamicEntityPipeline/ShadowDepthMapRenderer",
         "Could not create backbuffer_sub_bitmap from display in order to create a render surface."
      );
   }
   backbuffer_is_setup = true;
   backbuffer_is_managed_by_this_class = true;

   return;
}

void ShadowDepthMapRenderer::setup_result_surface_bitmap()
{
   if (!(backbuffer_is_setup))
   {
      std::stringstream error_message;
      error_message << "[ShadowDepthMapRenderer::setup_result_surface_bitmap]: error: guard \"backbuffer_is_setup\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("ShadowDepthMapRenderer::setup_result_surface_bitmap: error: guard \"backbuffer_is_setup\" not met");
   }
   if (!((!result_surface_bitmap)))
   {
      std::stringstream error_message;
      error_message << "[ShadowDepthMapRenderer::setup_result_surface_bitmap]: error: guard \"(!result_surface_bitmap)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("ShadowDepthMapRenderer::setup_result_surface_bitmap: error: guard \"(!result_surface_bitmap)\" not met");
   }
   result_surface_bitmap = al_create_bitmap(
      al_get_bitmap_width(backbuffer_sub_bitmap),
      al_get_bitmap_height(backbuffer_sub_bitmap)
   );
   return;
}

void ShadowDepthMapRenderer::init_shader()
{
   if (!((!depth_map_shader)))
   {
      std::stringstream error_message;
      error_message << "[ShadowDepthMapRenderer::init_shader]: error: guard \"(!depth_map_shader)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("ShadowDepthMapRenderer::init_shader: error: guard \"(!depth_map_shader)\" not met");
   }
   // TODO: Change this folder path
   std::string ROOT_PATH_TO_DATA_FOLDER = "/Users/markoates/Repos/allegro_flare/bin/";

   std::string vertex_filename;
   std::string vertex_file_content;
   std::string fragment_filename;
   std::string fragment_file_content;

   vertex_filename = ROOT_PATH_TO_DATA_FOLDER + "data/shaders/depth_vertex.glsl";
   vertex_file_content = AllegroFlare::php::file_get_contents(vertex_filename);
   fragment_filename = ROOT_PATH_TO_DATA_FOLDER + "data/shaders/depth_fragment.glsl";
   fragment_file_content = AllegroFlare::php::file_get_contents(fragment_filename);

   depth_map_shader = new AllegroFlare::Shaders::Base("Base", vertex_file_content, fragment_file_content);
   depth_map_shader->initialize();

   return;
}

void ShadowDepthMapRenderer::init_camera_defaults()
{
   casting_light.stepout = vec3d(0, 0, 15); // NOTE: This uses 15 meters as a z stepout
   float light_time_of_day = 0.15f;
   casting_light.tilt = 3.141592653 * light_time_of_day; // light_time_of_day = 0.05; // sunrise
                                                         //                     0.5; // high noon
                                                         //                     0.95; // sunset
   casting_light.spin = 0.0f;
   return;
}

void ShadowDepthMapRenderer::destroy()
{
   if (backbuffer_is_setup && backbuffer_is_managed_by_this_class) al_destroy_bitmap(backbuffer_sub_bitmap);
   if (depth_map_shader) { delete depth_map_shader; depth_map_shader = nullptr; } // NOTE: Does this destroy the
                                                                                  // shader? Does Shaders::Base have
                                                                                  // a destructor here?
   if (result_surface_bitmap) { al_destroy_bitmap(result_surface_bitmap); result_surface_bitmap = nullptr; }
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
   // TODO: store and restore states on glEnable/glCullFace, etc
   // https://www.khronos.org/registry/OpenGL-Refpages/gl2.1/xhtml/glIsEnabled.xml
   // ^^ documentation of how this might be approached

   glEnable(GL_CULL_FACE); // requiring direct OpenGL calls eventually be fazed out
   glCullFace(GL_FRONT); 

   // TODO: Test this line (backbuffer_sub_bitmap is set as target)
   al_set_target_bitmap(backbuffer_sub_bitmap);

   //al_clear_to_color(color::white); // TODO: Consider clearing the bitmap
   al_clear_to_color(ALLEGRO_COLOR{1, 1, 1, 1});
   setup_projection_on_render_surface();

   // setup the shader
   depth_map_shader->activate();

   // draw the objects
   for (auto &entity : entity_pool->get_entity_pool_ref())
   {
      // IMPORTANT: For now, assume all entities are StaticModel3D
      // TODO: Use "is rendered" and/or !"does_not_cast_shadow" flag

      if (entity->is_type(AllegroFlare::GraphicsPipelines::DynamicEntityPipeline::Entities::StaticModel3D::TYPE))
      {
         AllegroFlare::GraphicsPipelines::DynamicEntityPipeline::Entities::StaticModel3D* as_static_model_3d =
            static_cast<AllegroFlare::GraphicsPipelines::DynamicEntityPipeline::Entities::StaticModel3D*>(entity);

         ALLEGRO_TRANSFORM transform;
         as_static_model_3d->get_placement_ref().build_transform(&transform);
         AllegroFlare::Shaders::Base::set_mat4("position_transform", &transform);

         AllegroFlare::Model3D *model = as_static_model_3d->get_model_3d();
         if (model) model->draw();
      }
   }

   al_set_target_bitmap(result_surface_bitmap); // I *believe* newer versions of allegro have a depth map
                                                // on a bitmap this may be able to be updated so that the
                                                // backbuffer does not need be used to render this
   al_draw_bitmap(backbuffer_sub_bitmap, 0, 0, 0);

   //glEnable(GL_CULL_FACE); // requiring opengl should eventually be fazed out
   glCullFace(GL_BACK); 
   //glCullFace(GL_FRONT);
   glDisable(GL_CULL_FACE);

   return;
}

void ShadowDepthMapRenderer::setup_projection_on_render_surface()
{
   if (!(backbuffer_is_setup))
   {
      std::stringstream error_message;
      error_message << "[ShadowDepthMapRenderer::setup_projection_on_render_surface]: error: guard \"backbuffer_is_setup\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("ShadowDepthMapRenderer::setup_projection_on_render_surface: error: guard \"backbuffer_is_setup\" not met");
   }
   if (!(depth_map_shader))
   {
      std::stringstream error_message;
      error_message << "[ShadowDepthMapRenderer::setup_projection_on_render_surface]: error: guard \"depth_map_shader\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("ShadowDepthMapRenderer::setup_projection_on_render_surface: error: guard \"depth_map_shader\" not met");
   }
   float shadow_scale_divisor = 1.0; // See comment further down for more detail

   // setup the render settings
   al_set_render_state(ALLEGRO_DEPTH_TEST, 1);
   al_set_render_state(ALLEGRO_WRITE_MASK, ALLEGRO_MASK_DEPTH | ALLEGRO_MASK_RGBA);
   al_clear_depth_buffer(1);

   ALLEGRO_TRANSFORM casting_light_projection_transform;

   casting_light.reverse_position_transform(&casting_light_projection_transform);


   ALLEGRO_BITMAP *bitmap = backbuffer_sub_bitmap;
   float divisor = shadow_scale_divisor;
   al_scale_transform_3d(&casting_light_projection_transform, 150/divisor, 150/divisor, 1); // note, increasing
      // this divisor will
      // expand the range of the light projection, but it will reduce its resolution, a divisor of 1 will have a good
      // quality of shadow, but will have a range of about 15-20 meters; a divisor of 2 will double that size, but
      // reduce the resolution of the shadow. Original engine had a default of 1.0f;

   // Adding some rotation
   //static float rotation = 0.0f;
   //rotation += 0.01f;
   //al_rotate_transform_3d(&casting_light_projection_transform, 0, 1, 0, rotation);


   al_orthographic_transform(
      &casting_light_projection_transform,
      -al_get_bitmap_width(bitmap),
      al_get_bitmap_height(bitmap),
      30.0,
      al_get_bitmap_width(bitmap),
      -al_get_bitmap_height(bitmap),
      -30.0
   );

   // TODO: Remove this line:
   //al_copy_transform(&casting_light_projection_transform, &shadow_map_projection);

   al_use_projection_transform(&casting_light_projection_transform);
   return;
}


} // namespace DynamicEntityPipeline
} // namespace GraphicsPipelines
} // namespace AllegroFlare


