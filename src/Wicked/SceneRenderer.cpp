#include <Wicked/SceneRenderer.hpp>

// This is a header-only class(?)
#include <AllegroFlare/HeaderOnly.hpp>



/*

//#ifdef __APPLE__
//#ifndef GL_SILENCE_DEPRECATION
//#define GL_SILENCE_DEPRECATION
//#define ALLEGRO_FLARE__GL_SILENCE_DEPRECIATION
//#endif
//#endif

#include <allegro5/allegro_opengl.h>

//#ifdef __APPLE__
//#ifndef ALLEGRO_FLARE__GL_SILENCE_DEPRECIATION
//#undef GL_SILENCE_DEPRECATION
//#undef ALLEGRO_FLARE__GL_SILENCE_DEPRECIATION
//#endif
//#endif


#include <iostream> // for cout

#include <AllegroFlare/UsefulPHP.hpp>


namespace Wicked
{


SceneRenderer::SceneRenderer()
   : backbuffer_sub_bitmap(nullptr)
   //, depth_shader("data/shaders/depth_vertex.glsl", "data/shaders/depth_fragment.glsl")
   , depth_shader(nullptr)
   , shadow_scale_divisor(1.0) // note, increasing this divisor will
   , initialized(false)
      // expand the range of the light projection, but it will reduce its resolution, a divisor of 1 will have a good
      // quality of shadow, but will have a range of about 15-20 meters; a divisor of 2 will double that size, but reduce
      // the resolution of the shadow. Original engine had a default of 1.0f;

      // Also, this article
      // https://docs.microsoft.com/en-us/windows/win32/dxtecharts/common-techniques-to-improve-shadow-depth-maps
{
}


void SceneRenderer::initialize()
{
   //("data/shaders/depth_vertex.glsl", "data/shaders/depth_fragment.glsl")

   // TODO revise the technique needing a hard-coded path (does not work in test vs produ vs dev environments)
   std::string ROOT_PATH_TO_DATA_FOLDER = "/Users/markoates/Repos/allegro_flare/bin/";


   std::string vertex_filename;
   std::string vertex_file_content;
   std::string fragment_filename;
   std::string fragment_file_content;

   vertex_filename = ROOT_PATH_TO_DATA_FOLDER + "data/shaders/depth_vertex.glsl";
   vertex_file_content = AllegroFlare::php::file_get_contents(vertex_filename);
   fragment_filename = ROOT_PATH_TO_DATA_FOLDER + "data/shaders/depth_fragment.glsl";
   fragment_file_content = AllegroFlare::php::file_get_contents(fragment_filename);

   depth_shader = new AllegroFlare::Shaders::Base("Base", vertex_file_content, fragment_file_content);
   depth_shader->initialize();

   initialized = true;
}


void SceneRenderer::set_shadow_scale_divisor(float shadow_scale_divisor)
{
   this->shadow_scale_divisor = shadow_scale_divisor;
}


void SceneRenderer::set_backbuffer_sub_bitmap(ALLEGRO_BITMAP *backbuffer_sub_bitmap)
{
   this->backbuffer_sub_bitmap = backbuffer_sub_bitmap;
}


void SceneRenderer::refresh_shadow_map(
      std::vector<Entity *> *_entities,
      ShadowCastingLight casting_light,
      ALLEGRO_TRANSFORM *shadow_map_depth_pass_transform,
      ALLEGRO_BITMAP *shadow_map_depth_pass_surface,
      Entity *pointer
   )
{
   if (!initialized) throw std::runtime_error("Wicked::SceneRenderer::refresh_shadow_map: ERROR: not initialized");
   if (!_entities) throw std::runtime_error("CCc");
   std::vector<Entity *> &entities = (*_entities);

   // TODO: store and restore states on glEnable/glCullFace, etc
   // https://www.khronos.org/registry/OpenGL-Refpages/gl2.1/xhtml/glIsEnabled.xml
   // ^^ documentation of how this might be approached

   glEnable(GL_CULL_FACE); // requiring direct OpenGL calls eventually be fazed out
   glCullFace(GL_FRONT); 

   //al_set_target_bitmap(backbuffer_sub_bitmap);


   //al_clear_to_color(color::white);
   setup_projection_SHADOW(casting_light, shadow_map_depth_pass_transform);

   // setup the shader
   //depth_shader.use();
   depth_shader->activate();
   
   // draw the objects
   for (unsigned i=0; i<entities.size(); i++)
   {
      entities[i]->draw_for_depth_pass(depth_shader);
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
}


void SceneRenderer::setup_projection_SHADOW(
   ShadowCastingLight &shadow_casting_light,
   ALLEGRO_TRANSFORM *transform_to_fill
)
{
   if (!initialized) throw std::runtime_error("Wicked::SceneRenderer::setup_projection_SHADOW: ERROR: not initialized");
   if (!backbuffer_sub_bitmap) throw std::runtime_error("AAa");

   // setup the render settings
   al_set_render_state(ALLEGRO_DEPTH_TEST, 1);
   al_set_render_state(ALLEGRO_WRITE_MASK, ALLEGRO_MASK_DEPTH | ALLEGRO_MASK_RGBA);
   al_clear_depth_buffer(1);

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
}


void SceneRenderer::setup_projection_SCENE(AllegroFlare::Camera3D &camera, ALLEGRO_TRANSFORM *transform_to_fill)
{
   if (!initialized) throw std::runtime_error("Wicked::SceneRenderer::setup_projection_SCENE: ERROR: not initialized");
   camera.setup_projection_on(backbuffer_sub_bitmap);
}


void SceneRenderer::draw_entities(
      vec3d camera_real_position,
      vec3d light_position,
      Entity *skybox,
      std::vector<Entity *> *_entities, 
      ALLEGRO_TRANSFORM *shadow_map_depth_pass_transform,
      ALLEGRO_BITMAP *shadow_map_depth_pass_surface,
      vec2d texture_offset,
      Entity *pointer,
      vec3d camera_looking_at_point
   )
{
   if (!initialized) throw std::runtime_error("Wicked::SceneRenderer::draw_entities: ERROR: not initialized");
   if (!skybox)
   {
      static bool skybox_error = false;
      if (!skybox_error)
      {
         //throw std::runtime_error("Xxx");
         std::cout << "SceneRenderer::draw_entities warning! - There is no skybox, the scene will be rendered with a cleared background instead." << std::endl;
         skybox_error = true;
      }
   }
   if (!_entities) throw std::runtime_error("Yyy");
   std::vector<Entity *> &entities = (*_entities);

   //vec3d camera_real_position = camera.get_real_position();
   //vec3d light_position = light.position * 100.0;

   if (skybox)
   {
      // position and draw the skybox
      skybox->place.position = camera_real_position; // note this is not included in "update_scene_physics" because
                                                // it is a rendering-step (skybox will vary depending on camera
                                                // used to render the scene), so not physics-related

      // does this skybox draw need to have a pre-cleared or not-depth checked render?
      skybox->draw(0, 0);
   }
   else
   {
      al_clear_to_color(ALLEGRO_COLOR{0.1, 0.1, 0.1, 1.0});
   }

   // clear the depth buffer from the skybox
   al_clear_depth_buffer(1);

   for (auto &entity : entities)
   {
      entity->draw(
         camera_real_position,
         light_position,
         shadow_map_depth_pass_transform,
         shadow_map_depth_pass_surface,
         texture_offset
      );
   }

   if (pointer)
   {
      pointer->place.position = camera_looking_at_point; //camera_real_position; // note this is not included in "update_scene_physics" because
      pointer->draw(
         camera_real_position,
         light_position,
         shadow_map_depth_pass_transform,
         shadow_map_depth_pass_surface,
         texture_offset
         );

          //  0, 0);
   }


   //Shader::stop();
   AllegroFlare::Shaders::Base::global_deactivate();
}


void SceneRenderer::draw_scene()
{
   if (!initialized) throw std::runtime_error("Wicked::SceneRenderer::draw_scene: ERROR: not initialized");
}


void SceneRenderer::render()
{
   if (!initialized) throw std::runtime_error("Wicked::SceneRenderer::render: ERROR: not initialized");
}


} // namespace Wicked



*/


