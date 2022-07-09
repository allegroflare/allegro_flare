
#include <gtest/gtest.h>

#include <AllegroFlare/Elements/StoryboardPlayer.hpp>


class StoryboardPageTestClass : public AllegroFlare::Elements::StoryboardPages::Base
{
};


TEST(AllegroFlare_Elements_StoryboardPlayerTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Elements::StoryboardPlayer storyboard_player;
}


