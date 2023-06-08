
#include <gtest/gtest.h>

#include <AllegroFlare/GraphicsPipelines/DynamicEntityPipeline/SceneRenderer.hpp>
#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>
#include <AllegroFlare/GraphicsPipelines/DynamicEntityPipeline/EntityFactory.hpp>
#include <AllegroFlare/ModelBin.hpp>
#include <AllegroFlare/SceneGraph/EntityPool.hpp>
#include <AllegroFlare/CubemapBuilder.hpp>
#include <AllegroFlare/GraphicsPipelines/DynamicEntityPipeline/Entities/DynamicModel3D.hpp>


class AllegroFlare_GraphicsPipelines_DynamicEntityPipeline_SceneRendererTest : public ::testing::Test {};
class AllegroFlare_GraphicsPipelines_DynamicEntityPipeline_SceneRendererTestWithAllegroRenderingFixtureTest :
   public AllegroFlare::Testing::WithAllegroRenderingFixture
{};


TEST_F(AllegroFlare_GraphicsPipelines_DynamicEntityPipeline_SceneRendererTest, can_be_created_without_blowing_up)
{
   AllegroFlare::GraphicsPipelines::DynamicEntityPipeline::SceneRenderer scene_renderer;
}


TEST_F(AllegroFlare_GraphicsPipelines_DynamicEntityPipeline_SceneRendererTestWithAllegroRenderingFixtureTest,
   VISUAL__render__renders_the_iridescent)
{
   AllegroFlare::ModelBin model_bin;
   model_bin.set_full_path(get_fixtures_path() + "models");
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

   cubemap_shader.initialize();
   cubemap_shader.set_cube_map(cubemap);

   // Create the camera

   AllegroFlare::GraphicsPipelines::DynamicEntityPipeline::Entities::Camera3D* camera_entity =
      entity_factory.create_camera_3d();
   AllegroFlare::Camera3D &camera = camera_entity->get_camera_3d_ref();
   camera_entity->set("primary_camera");
   camera.stepout = { 0, 0, 3.0 };
   entity_pool.add(camera_entity);

   AllegroFlare::GraphicsPipelines::DynamicEntityPipeline::SceneRenderer scene_renderer;
   scene_renderer.set_cubemap_shader(&cubemap_shader);
   scene_renderer.set_entity_pool(&entity_pool);

   // TODO: Use an EntityFactory for this setup
   AllegroFlare::GraphicsPipelines::DynamicEntityPipeline::Entities::DynamicModel3D *item = 
      new AllegroFlare::GraphicsPipelines::DynamicEntityPipeline::Entities::DynamicModel3D();
   item->set_model_3d(model_bin.auto_get("rounded_unit_cube-01.obj"));
   //item->set_model_3d_texture(model_bin.auto_get("rounded_unit_cube-01.obj"));
   item->set("irid");

   //ArtGalleryOfCats::Gameplay::Entities::Base* collectable = entity_factory.create_collectable_object(
      //{ 0, 0, 0 },
      //"rounded_unit_cube-01.obj"
   //);
   //collectable->get_placement_ref().rotation.x = 0.05;
   //collectable->get_placement_ref().rotation.z = 0.03547;
   //entity_pool.add(collectable);

   item->get_placement_ref().rotation.x = 0.05;
   item->get_placement_ref().rotation.z = 0.03547;
   entity_pool.add(item);

   // Render the scene
   int frames = 20;
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

   throw std::runtime_error("Blow");
}


/* // TODO: Uncomment this test
TEST_F(AllegroFlare_GraphicsPipelines_DynamicEntityPipeline_SceneRendererTestWithAllegroRenderingFixtureTest,
//TEST_F(ArtGalleryOfCats_Gameplay_SceneRendererTestWithAllegroRenderingFixtureTest,
   VISUAL__render__renders_the_wall_art)
{
   AllegroFlare::ModelBin model_bin;
   model_bin.set_full_path(get_fixtures_path() + "models");
   AllegroFlare::Shaders::Cubemap cubemap_shader;
   AllegroFlare::Cubemap* cubemap = nullptr;
   AllegroFlare::SceneGraph::EntityPool entity_pool;
   AllegroFlare::GraphicsPipelines::DynamicEntityPipeline::EntityFactory entity_factory;
   entity_factory.set_bitmap_bin(&get_bitmap_bin_ref());
   entity_factory.set_model_bin(&model_bin);

   AllegroFlare::CubemapBuilder builder;
   std::string cube_map_texture_filename = get_fixtures_path() + "bitmaps/black_prism_1-01.png";
   cubemap = builder.glsl_create_cubemap_from_vertical_strip(cube_map_texture_filename.c_str());

   //cubemap_shader.initialize();
   //cubemap_shader.set_cube_map(cubemap);

   cubemap_shader.initialize();
   cubemap_shader.set_cube_map(cubemap);

   // Create the camera

   ArtGalleryOfCats::Gameplay::Entities::Camera3D* camera = entity_factory.create_camera();
   camera->set("primary_camera");
   camera->stepout = { 0, 0, 3.0 };
   entity_pool.add(camera);

   AllegroFlare::GraphicsPipelines::DynamicEntityPipeline::SceneRenderer scene_renderer;
   scene_renderer.set_cubemap_shader(&cubemap_shader);
   scene_renderer.set_entity_pool(&entity_pool);

   // Add some items to our scene

   ArtGalleryOfCats::Gameplay::Entities::Base* collectable = entity_factory.create_wall_art(
      "foobar_art",
      "storyboard-2-01-1165x500.png",
      { 0, 0, 0 },
      0.0,
      {}
   );
   collectable->get_placement_ref().rotation.x = 0.05;
   collectable->get_placement_ref().rotation.z = 0.03547;
   entity_pool.add(collectable);

   // Render the scene
   int frames = 90;
   for (int i=0; i<frames; i++)
   {
      collectable->get_placement_ref().rotation.x += 0.005;
      collectable->get_placement_ref().rotation.z += 0.003547;

      camera->stepout.z += 0.03;
      camera->spin += 0.01;

      scene_renderer.render();
      al_flip_display();
      al_rest(1.0/60.0f);
   }
}
*/


