
#include <gtest/gtest.h>

#include <AllegroFlare/MotionComposer/MessageFactory.hpp>


#include <AllegroFlare/MotionComposer/Messages/SetPlayheadPosition.hpp>



TEST(AllegroFlare_MotionComposer_MessageFactoryTest, can_be_created_without_blowing_up)
{
   AllegroFlare::MotionComposer::MessageFactory message_factory;
}


TEST(AllegroFlare_MotionComposer_MessageFactoryTest,
   create_set_playead_position_message__will_create_the_message_with_the_expected_properties)
{
   // TODO
}


