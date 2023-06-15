
#include <gtest/gtest.h>

#include <Wicked/SceneRenderer.hpp>
#include <WickedDemos/FunzDemo.hpp>

TEST(Wicked_SceneRendererTest, can_be_created_without_blowing_up)
{
   // TODO: this will crash because it uses the old legacy allegro_flare::shader which
   // does logic in the constructor

   Wicked::SceneRenderer scene_renderer;
}


TEST(Wicked_SceneRendererTest,
   //INTERACTIVE__run__will_run_the_application)
   DISABLED__INTERACTIVE__run__will_run_the_application)
{
   FunzDemo::run();
}


