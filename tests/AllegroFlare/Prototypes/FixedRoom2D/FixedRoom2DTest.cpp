
#include <gtest/gtest.h>

#include <AllegroFlare/Prototypes/FixedRoom2D/FixedRoom2D.hpp>


TEST(AllegroFlare_Prototypes_FixedRoom2D_FixedRoom2DTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Prototypes::FixedRoom2D::FixedRoom2D fixed_room2d;
}


TEST(AllegroFlare_Prototypes_FixedRoom2D_FixedRoom2DTest,
   process_script_event__on_a_subscribed_event_type__with_unknown_event_data_type__will_output_an_error_message_to_cout)
{
   // TODO
}


