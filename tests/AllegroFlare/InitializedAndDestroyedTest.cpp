
#include <gtest/gtest.h>

#include <AllegroFlare/InitializedAndDestroyed.hpp>


class TestClass : public AllegroFlare::InitializedAndDestroyed
{
   virtual void on_initialize() override {};
   virtual void on_destroy() override {};
};


TEST(AllegroFlare_InitializedAndDestroyedTest, can_be_created_without_blowing_up)
{
   AllegroFlare::InitializedAndDestroyed initialized_and_destroyed;
}


TEST(AllegroFlare_InitializedAndDestroyedTest, when_initialized_and_destroyed__will_not_output_an_warning_message)
{
   auto test_class = new TestClass;
   test_class->initialize();
   test_class->destroy();
   delete test_class;
}


