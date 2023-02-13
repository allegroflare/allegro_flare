
#include <gtest/gtest.h>

#include <AllegroFlare/ShaderSourcePoller.hpp>
#include <AllegroFlare/DeploymentEnvironment.hpp>


TEST(AllegroFlare_ShaderSourcePollerTest, can_be_created_without_blowing_up)
{
   AllegroFlare::ShaderSourcePoller shader_source_poller;
}


TEST(AllegroFlare_ShaderSourcePollerTest, poll__before_initialization__will_throw_an_error)
{
   // TODO
}


TEST(AllegroFlare_ShaderSourcePollerTest, poll__does_not_blow_up)
{
   AllegroFlare::DeploymentEnvironment deployment_environment("test");
   std::string fixture_path = deployment_environment.get_data_folder_path();
   std::string vertex_source_path = "/shaders/allegro_default_vertex.glsl";
   std::string fragment_source_path = "/shaders/allegro_default_fragment.glsl";

   AllegroFlare::ShaderSourcePoller shader_source_poller(
      vertex_source_path,
      fragment_source_path,
      fixture_path
   );
   shader_source_poller.initialize();
   shader_source_poller.poll();
}


