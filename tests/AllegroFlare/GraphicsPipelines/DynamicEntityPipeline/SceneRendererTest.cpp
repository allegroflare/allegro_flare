
#include <gtest/gtest.h>

#include <AllegroFlare/GraphicsPipelines/DynamicEntityPipeline/SceneRenderer.hpp>
#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>
#include <AllegroFlare/GraphicsPipelines/DynamicEntityPipeline/EntityFactory.hpp>
#include <AllegroFlare/ModelBin.hpp>
#include <AllegroFlare/SceneGraph/EntityPool.hpp>
#include <AllegroFlare/CubemapBuilder.hpp>
#include <AllegroFlare/GraphicsPipelines/DynamicEntityPipeline/Entities/DynamicModel3D.hpp>
#include <AllegroFlare/GraphicsPipelines/DynamicEntityPipeline/EntityRenderFlags.hpp>
#include <AllegroFlare/GraphicsPipelines/DynamicEntityPipeline/Entities/StaticMultitextureModel3D.hpp>


class AllegroFlare_GraphicsPipelines_DynamicEntityPipeline_SceneRendererTest : public ::testing::Test {};
class AllegroFlare_GraphicsPipelines_DynamicEntityPipeline_SceneRendererTestWithAllegroRenderingFixtureTest :
   public AllegroFlare::Testing::WithAllegroRenderingFixture
{};


TEST_F(AllegroFlare_GraphicsPipelines_DynamicEntityPipeline_SceneRendererTest, can_be_created_without_blowing_up)
{
   AllegroFlare::GraphicsPipelines::DynamicEntityPipeline::SceneRenderer scene_renderer;
}


TEST_F(AllegroFlare_GraphicsPipelines_DynamicEntityPipeline_SceneRendererTestWithAllegroRenderingFixtureTest,
   CAPTURE__VISUAL__render__renders_the_iridescent)
{
   AllegroFlare::ModelBin model_bin;
   model_bin.set_full_path(get_fixtures_path() + "models");
   AllegroFlare::Shaders::Multitexture multitexture_shader;
   AllegroFlare::Shaders::Cubemap cubemap_shader;
   AllegroFlare::Cubemap* cubemap = nullptr;
   AllegroFlare::GraphicsPipelines::DynamicEntityPipeline::EntityPool entity_pool;
   AllegroFlare::GraphicsPipelines::DynamicEntityPipeline::EntityFactory entity_factory;
   entity_factory.set_bitmap_bin(&get_bitmap_bin_ref());
   entity_factory.set_model_bin(&model_bin);

   AllegroFlare::CubemapBuilder builder;
   std::string cube_map_texture_filename = get_fixtures_path() + "bitmaps/black_prism_1-01.png";
   cubemap = builder.glsl_create_cubemap_from_vertical_strip(cube_map_texture_filename.c_str());

   //cubemap_shader.initialize();
   //cubemap_shader.set_cube_map(cubemap);

   multitexture_shader.initialize();

   cubemap_shader.initialize();
   cubemap_shader.set_cube_map(cubemap);

   // Create the camera

   AllegroFlare::GraphicsPipelines::DynamicEntityPipeline::Entities::Camera3D* camera_entity =
      entity_factory.create_camera_3d();
   AllegroFlare::Camera3D &camera = camera_entity->get_camera_3d_ref();
   camera_entity->set("primary_camera");
   camera.stepout = { 0, 1.0, 3.0 };
   camera.spin = -0.4;
   entity_pool.add(camera_entity);

   AllegroFlare::GraphicsPipelines::DynamicEntityPipeline::SceneRenderer scene_renderer;
   scene_renderer.set_cubemap_shader(&cubemap_shader);
   scene_renderer.set_multitexture_shader(&multitexture_shader);
   scene_renderer.set_entity_pool(&entity_pool);

   // TODO: Use an EntityFactory for this setup
   AllegroFlare::GraphicsPipelines::DynamicEntityPipeline::Entities::DynamicModel3D *item = 
      new AllegroFlare::GraphicsPipelines::DynamicEntityPipeline::Entities::DynamicModel3D();
   item->set_model_3d(model_bin.auto_get("rounded_unit_cube-01.obj"));
   item->set(AllegroFlare::GraphicsPipelines::DynamicEntityPipeline::EntityRenderFlags::RENDER_WITH_SKYBOX);
   item->get_placement_ref().position.y = 1.0;
   item->get_placement_ref().rotation.x = 0.05;
   item->get_placement_ref().rotation.z = 0.03547;
   entity_pool.add(item);

   // TODO: Use an EntityFactory for this setup
   AllegroFlare::GraphicsPipelines::DynamicEntityPipeline::Entities::DynamicModel3D *dynamic_cube = 
      new AllegroFlare::GraphicsPipelines::DynamicEntityPipeline::Entities::DynamicModel3D();
   dynamic_cube->set_model_3d(model_bin.auto_get("rounded_unit_cube-01.obj"));
   dynamic_cube->set_model_3d_texture(get_bitmap_bin_ref().auto_get("uv.png"));
   dynamic_cube->get_placement_ref().position.x = 1.5;
   dynamic_cube->get_placement_ref().position.y = 0.5;
   entity_pool.add(dynamic_cube);

   // TODO: Use an EntityFactory for this setup
   std::string TEST_FIXTURES_FOLDER = get_fixtures_path();
   std::string base_obj_filename = TEST_FIXTURES_FOLDER + "models/simple_scene-01.obj";
   std::string uv2_obj_filename = TEST_FIXTURES_FOLDER + "models/simple_scene-01-ao-01.obj";
   AllegroFlare::MultitextureModel3D multitexture_model;
   multitexture_model.initialize();
   multitexture_model.load_obj_file(base_obj_filename, uv2_obj_filename.c_str());

   AllegroFlare::GraphicsPipelines::DynamicEntityPipeline::Entities::StaticMultitextureModel3D *environment_mesh = 
      new AllegroFlare::GraphicsPipelines::DynamicEntityPipeline::Entities::StaticMultitextureModel3D();
   environment_mesh->set_multitexture_model_3d(&multitexture_model);
   environment_mesh->set_multitexture_model_3d_texture_1(get_bitmap_bin_ref().auto_get("simple_scene-01-1024.jpg"));
   environment_mesh->set_multitexture_model_3d_texture_2(get_bitmap_bin_ref().auto_get("simple_scene-01-ao-01.jpg"));
   entity_pool.add(environment_mesh);

   // Render the scene
   int frames = 90;
   for (int i=0; i<frames; i++)
   {
      item->get_placement_ref().rotation.x += 0.005;
      item->get_placement_ref().rotation.z += 0.003547;

      camera.stepout.z += 0.03;
      camera.spin += 0.01;

      scene_renderer.render();
      al_flip_display();
      al_rest(1.0/60.0f);
   }
}

