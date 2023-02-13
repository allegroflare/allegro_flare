
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


TEST(AllegroFlare_ShaderSourcePollerTest, DISABLED__poll__does_not_blow_up)
{
   AllegroFlare::DeploymentEnvironment deployment_environment("test");
   std::string fixture_path = deployment_environment.get_data_folder_path();
   std::string vertex_source_path = "/shaders/allegro_default_vertex.glsl";
   std::string fragment_source_path = "/shaders/allegro_default_fragment.glsl";
   ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();

   AllegroFlare::ShaderSourcePoller shader_source_poller(
      event_queue,
      vertex_source_path,
      fragment_source_path,
      fixture_path
   );
   shader_source_poller.initialize();
   shader_source_poller.poll();

   al_destroy_event_queue(event_queue);
}


TEST(AllegroFlare_ShaderSourcePollerTest,
   poll__if_the_polled_source_time_has_not_changed_from_the_previous__will_return_false)
{
   AllegroFlare::DeploymentEnvironment deployment_environment("test");
   std::string fixture_path = deployment_environment.get_data_folder_path();
   std::string vertex_source_path = "/shaders/allegro_default_vertex.glsl";
   std::string fragment_source_path = "/shaders/allegro_default_fragment.glsl";
   ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();

   AllegroFlare::ShaderSourcePoller shader_source_poller(
      event_queue,
      vertex_source_path,
      fragment_source_path,
      fixture_path
   );
   shader_source_poller.initialize();

   EXPECT_EQ(false, shader_source_poller.poll());

   al_destroy_event_queue(event_queue);
}



TEST(AllegroFlare_ShaderSourcePollerTest,
   poll__if_the_last_modified_time_of_the_vertex_source_file_has_changed__will_return_true)
{
   AllegroFlare::DeploymentEnvironment deployment_environment("test");
   std::string fixture_path = deployment_environment.get_data_folder_path();
   std::string vertex_source_path = "/shaders/allegro_default_vertex.glsl";
   std::string fragment_source_path = "/shaders/allegro_default_fragment.glsl";
   ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();

   AllegroFlare::ShaderSourcePoller shader_source_poller(
      event_queue,
      vertex_source_path,
      fragment_source_path,
      fixture_path
   );
   shader_source_poller.initialize();

   std::filesystem::last_write_time(
      fixture_path + vertex_source_path,
      shader_source_poller.get_last_recorded_vertex_source_file_changed_at() + std::chrono::seconds(1)
   );

   EXPECT_EQ(true, shader_source_poller.poll());

   al_destroy_event_queue(event_queue);
}


TEST(AllegroFlare_ShaderSourcePollerTest,
   poll__if_the_last_modified_time_of_the_fragment_source_file_has_changed__will_return_true)
{
   AllegroFlare::DeploymentEnvironment deployment_environment("test");
   std::string fixture_path = deployment_environment.get_data_folder_path();
   std::string vertex_source_path = "/shaders/allegro_default_vertex.glsl";
   std::string fragment_source_path = "/shaders/allegro_default_fragment.glsl";
   ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();

   AllegroFlare::ShaderSourcePoller shader_source_poller(
      event_queue,
      vertex_source_path,
      fragment_source_path,
      fixture_path
   );
   shader_source_poller.initialize();

   std::filesystem::last_write_time(
      fixture_path + fragment_source_path,
      shader_source_poller.get_last_recorded_fragment_source_file_changed_at() + std::chrono::seconds(1)
   );

   EXPECT_EQ(true, shader_source_poller.poll());

   al_destroy_event_queue(event_queue);
}


TEST(AllegroFlare_ShaderSourcePollerTest,
   poll__when_the_vertex_file_last_modified_time_has_been_changed__will_update_its_last_modified_time)
{
   AllegroFlare::DeploymentEnvironment deployment_environment("test");
   std::string fixture_path = deployment_environment.get_data_folder_path();
   std::string vertex_source_path = "/shaders/allegro_default_vertex.glsl";
   std::string fragment_source_path = "/shaders/allegro_default_fragment.glsl";
   ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();

   AllegroFlare::ShaderSourcePoller shader_source_poller(
      event_queue,
      vertex_source_path,
      fragment_source_path,
      fixture_path
   );
   shader_source_poller.initialize();

   std::filesystem::file_time_type initial_modified_time =
      shader_source_poller.get_last_recorded_vertex_source_file_changed_at();
   std::filesystem::file_time_type new_modified_time = initial_modified_time + std::chrono::seconds(1);

   std::filesystem::last_write_time(fixture_path + vertex_source_path, new_modified_time);

   shader_source_poller.poll();

   std::filesystem::file_time_type updated_modified_time =
      shader_source_poller.get_last_recorded_vertex_source_file_changed_at();

   EXPECT_EQ(new_modified_time, updated_modified_time);

   EXPECT_EQ(false, shader_source_poller.poll());

   al_destroy_event_queue(event_queue);
}


TEST(AllegroFlare_ShaderSourcePollerTest,
   poll__when_the_fragment_file_last_modified_time_has_been_changed__will_update_its_last_modified_time)
{
   AllegroFlare::DeploymentEnvironment deployment_environment("test");
   std::string fixture_path = deployment_environment.get_data_folder_path();
   std::string vertex_source_path = "/shaders/allegro_default_vertex.glsl";
   std::string fragment_source_path = "/shaders/allegro_default_fragment.glsl";
   ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();

   AllegroFlare::ShaderSourcePoller shader_source_poller(
      event_queue,
      vertex_source_path,
      fragment_source_path,
      fixture_path
   );
   shader_source_poller.initialize();

   std::filesystem::file_time_type initial_modified_time =
      shader_source_poller.get_last_recorded_fragment_source_file_changed_at();
   std::filesystem::file_time_type new_modified_time = initial_modified_time + std::chrono::seconds(1);

   std::filesystem::last_write_time(fixture_path + fragment_source_path, new_modified_time);

   shader_source_poller.poll();

   std::filesystem::file_time_type updated_modified_time =
      shader_source_poller.get_last_recorded_fragment_source_file_changed_at();

   EXPECT_EQ(new_modified_time, updated_modified_time);

   EXPECT_EQ(false, shader_source_poller.poll());

   al_destroy_event_queue(event_queue);
}


