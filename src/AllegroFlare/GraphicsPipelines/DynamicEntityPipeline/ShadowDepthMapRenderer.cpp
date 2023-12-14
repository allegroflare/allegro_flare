

#include <AllegroFlare/GraphicsPipelines/DynamicEntityPipeline/ShadowDepthMapRenderer.hpp>

#include <AllegroFlare/ALLEGRO_VERTEX_WITH_TWO_UVS_AND_NORMAL.hpp>
#include <AllegroFlare/GraphicsPipelines/DynamicEntityPipeline/Entities/DynamicModel3D.hpp>
#include <AllegroFlare/GraphicsPipelines/DynamicEntityPipeline/Entities/StaticModel3D.hpp>
#include <AllegroFlare/GraphicsPipelines/DynamicEntityPipeline/Entities/StaticMultitextureModel3D.hpp>
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
   , render_surface()
   , render_surface_is_setup(false)
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


AllegroFlare::Camera3D &ShadowDepthMapRenderer::get_casting_light_ref()
{
   return casting_light;
}


ALLEGRO_BITMAP* ShadowDepthMapRenderer::get_result_surface_bitmap()
{
   return render_surface.obtain_surface();
   //return result_surface_bitmap;
}

void ShadowDepthMapRenderer::setup_result_surface_bitmap(int width, int height)
{
   render_surface.set_surface_width(width);
   render_surface.set_surface_height(height);
   render_surface.set_multisamples(0);
   render_surface.set_depth(32);
   render_surface.initialize();

   render_surface_is_setup = true;

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
   //if (backbuffer_is_setup && backbuffer_is_managed_by_this_class) al_destroy_bitmap(backbuffer_sub_bitmap);
   if (depth_map_shader) { delete depth_map_shader; depth_map_shader = nullptr; } // NOTE: Does this destroy the
                                                                                  // shader? Does Shaders::Base have
                                                                                  // a destructor here?
   //if (result_surface_bitmap) { al_destroy_bitmap(result_surface_bitmap); result_surface_bitmap = nullptr; }
   // TODO: Destroy render surface
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

   // TODO: Consider culling
   //glEnable(GL_CULL_FACE); // requiring direct OpenGL calls eventually be fazed out
   //glCullFace(GL_FRONT); 
   ALLEGRO_STATE prev_render_state;
   al_store_state(&prev_render_state, ALLEGRO_STATE_TARGET_BITMAP);

   // TODO: Test this line (backbuffer_sub_bitmap is set as target)
   al_set_target_bitmap(render_surface.obtain_surface());
   //al_set_target_bitmap(backbuffer_sub_bitmap);

   setup_projection_on_render_surface();
   //al_clear_to_color(color::white); // TODO: Consider clearing the bitmap
   //al_clear_to_color(ALLEGRO_COLOR{1, 1, 1, 1});
   //setup_projection_on_render_surface();

   al_clear_depth_buffer(1);
   al_clear_to_color(ALLEGRO_COLOR{1, 1, 1, 1});
   al_set_render_state(ALLEGRO_DEPTH_TEST, 1);
   al_set_render_state(ALLEGRO_WRITE_MASK, ALLEGRO_MASK_DEPTH | ALLEGRO_MASK_RGBA); // TODO: Consider using only a
                                                                                    // single color component
   //al_clear_depth_buffer(1);
   //al_clear_to_color(ALLEGRO_COLOR{1, 1, 1, 1});

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
      else if (entity->is_type(AllegroFlare::GraphicsPipelines::DynamicEntityPipeline::Entities::DynamicModel3D::TYPE))
      {
         AllegroFlare::GraphicsPipelines::DynamicEntityPipeline::Entities::DynamicModel3D* as_dyn_model_3d =
            static_cast<AllegroFlare::GraphicsPipelines::DynamicEntityPipeline::Entities::DynamicModel3D*>(entity);

         ALLEGRO_TRANSFORM transform;
         as_dyn_model_3d->get_placement_ref().build_transform(&transform);
         AllegroFlare::Shaders::Base::set_mat4("position_transform", &transform);

         AllegroFlare::Model3D *model = as_dyn_model_3d->get_model_3d();
         if (model) model->draw();
      }
      else if (entity->is_type(AllegroFlare::GraphicsPipelines::DynamicEntityPipeline::Entities::StaticMultitextureModel3D::TYPE))
      {
         AllegroFlare::GraphicsPipelines::DynamicEntityPipeline::Entities::StaticMultitextureModel3D *as =
            static_cast<
               AllegroFlare::GraphicsPipelines::DynamicEntityPipeline::Entities::StaticMultitextureModel3D*
            >(entity);

         //throw std::runtime_error("foo ");
         ALLEGRO_TRANSFORM transform;
         as->get_placement_ref().build_transform(&transform);
         AllegroFlare::Shaders::Base::set_mat4("position_transform", &transform);

         AllegroFlare::MultitextureModel3D* mtm = get_multitexture_model_3d(entity);
         if (mtm) render_multitexture_model_3d(mtm);
      }
   }

   //al_set_target_bitmap(result_surface_bitmap); // I *believe* newer versions of allegro have a depth map
                                                // on a bitmap this may be able to be updated so that the
                                                // backbuffer does not need be used to render this
   //al_draw_bitmap(backbuffer_sub_bitmap, 0, 0, 0);

   ////glEnable(GL_CULL_FACE); // requiring opengl should eventually be fazed out
   depth_map_shader->deactivate();
   al_restore_state(&prev_render_state);
   // TODO: Consider culling
   //glCullFace(GL_BACK); 
   //glDisable(GL_CULL_FACE);

   return;
}

void ShadowDepthMapRenderer::setup_projection_on_render_surface()
{
   float shadow_scale_divisor = 1.0; // See comment further down for more detail

   // setup the render settings
   //al_set_render_state(ALLEGRO_DEPTH_TEST, 1);
   //al_set_render_state(ALLEGRO_WRITE_MASK, ALLEGRO_MASK_DEPTH | ALLEGRO_MASK_RGBA);
   //al_clear_depth_buffer(1);

   ALLEGRO_TRANSFORM casting_light_projection_transform;

   casting_light.reverse_position_transform(&casting_light_projection_transform);


   ALLEGRO_BITMAP *bitmap = render_surface.obtain_surface(); //backbuffer_sub_bitmap;
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

AllegroFlare::MultitextureModel3D* ShadowDepthMapRenderer::get_multitexture_model_3d(AllegroFlare::GraphicsPipelines::DynamicEntityPipeline::Entities::Base* entity)
{
   if (!(entity))
   {
      std::stringstream error_message;
      error_message << "[ShadowDepthMapRenderer::get_multitexture_model_3d]: error: guard \"entity\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("ShadowDepthMapRenderer::get_multitexture_model_3d: error: guard \"entity\" not met");
   }
   using namespace AllegroFlare::GraphicsPipelines::DynamicEntityPipeline;

   // TODO: Optimize this lookup
   // TODO: Consider throw on unhandled type
   if (entity->is_type(Entities::StaticMultitextureModel3D::TYPE))
   {
      Entities::StaticMultitextureModel3D *as_casted = static_cast<Entities::StaticMultitextureModel3D*>(entity);
      return as_casted->get_multitexture_model_3d();
   }
   return nullptr;
}

void ShadowDepthMapRenderer::render_multitexture_model_3d(AllegroFlare::MultitextureModel3D* multitexture_model_3d)
{
   // Render our subject
   // NOTE: For this test, will not be using "subject.draw()". Instead we will be rendering manually, and
   // setting  textures on the shader manually
   std::vector<AllegroFlare::ALLEGRO_VERTEX_WITH_TWO_UVS_AND_NORMAL> &vertices =
      multitexture_model_3d->vertexes;

   ALLEGRO_BITMAP* texture_a = nullptr; // NOTE: No texture is needed for shadow

   al_draw_prim(
      &vertices[0],
      multitexture_model_3d->vertex_declaration,
      texture_a, // TODO: In this sloppy case, this texture is used to determine the
                 // dimensionality of the textures(s) of the shader. Note that at the time of this writing, the
                 // textures and dimensions are all inter-dependent on each other in this way. This kink
                 // should eventually be worked out and cleaned up.
      0,
      vertices.size(),
      ALLEGRO_PRIM_TRIANGLE_LIST
   );
   return;
}


} // namespace DynamicEntityPipeline
} // namespace GraphicsPipelines
} // namespace AllegroFlare


