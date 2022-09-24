
#include <gtest/gtest.h>

#include <WickedDemos/EntityFactory.hpp>

TEST(WickedDemos_EntityFactoryTest, DISABLED__can_be_created_without_blowing_up)
{
   // TODO: this test fails because the EntityFactory uses the old allegro_flare::Shader, which build
   // themselves in the constructor, thus requiring initialization
   EntityFactory entity_factory;
}

