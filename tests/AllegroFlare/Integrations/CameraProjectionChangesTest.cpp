
#include <gtest/gtest.h>

#include <AllegroFlare/Integrations/CameraProjectionChanges.hpp>


TEST(AllegroFlare_Integrations_CameraProjectionChangesTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Integrations::CameraProjectionChanges camera_projection_changes;
}


TEST(AllegroFlare_Integrations_CameraProjectionChangesTest,
   initialize__will_not_blow_up)
{
   AllegroFlare::Integrations::CameraProjectionChanges camera_projection_changes;
   camera_projection_changes.initialize();
}


TEST(AllegroFlare_Integrations_CameraProjectionChangesTest,
   DISABLED__INTERACTIVE__start__will_work_as_expected)
   //INTERACTIVE__start__will_work_as_expected)
{
   // TODO: Note that this does not work, please review
   AllegroFlare::Integrations::CameraProjectionChanges camera_projection_changes;
   camera_projection_changes.initialize();

   camera_projection_changes.run();
}


