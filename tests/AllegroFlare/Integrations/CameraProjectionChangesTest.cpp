
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


