
#include <gtest/gtest.h>

#include <WickedDemos/FunzDemo.hpp>

TEST(WickedDemos_FunzDemoTest, can_be_created_without_blowing_up)
{
   FunzDemo funz_demo;
}


TEST(WickedDemos_FunzDemoTest,
   INTERACTIVE__run__will_run_the_application)
   //DISABLED__INTERACTIVE__run__will_run_the_application)
{
   FunzDemo::run();
}


//#include <Wicked/SceneRenderer.hpp>
//#include <WickedDemos/FunzDemo.hpp>

//#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>


//class Wicked_SceneRendererTest : public ::testing::Test {};
//class Wicked_SceneRendererTestWithAllegroRenderingFixtureTest :
   //public AllegroFlare::Testing::WithAllegroRenderingFixture
//{};



