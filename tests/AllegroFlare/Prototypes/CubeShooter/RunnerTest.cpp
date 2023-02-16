
#include <gtest/gtest.h>

#include <AllegroFlare/Prototypes/CubeShooter/Runner.hpp>


TEST(AllegroFlare_Prototypes_CubeShooter_RunnerTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Prototypes::CubeShooter::Runner runner;
}


TEST(AllegroFlare_Prototypes_CubeShooter_RunnerTest, DISABLE__INTERACTIVE__run__returns_the_expected_response)
{
   AllegroFlare::Prototypes::CubeShooter::Runner runner;
   runner.RUN("test");
}


