
#include <gtest/gtest.h>

#include <AllegroFlare/Elements/DialogBoxRenderers/TextMessages.hpp>
#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>
#include <chrono>
#include <thread>


class Krampus21_DialogBoxRenderers_SmartPhoneTest : public ::testing::Test {};
class Krampus21_DialogBoxRenderers_SmartPhoneWithAllegroRenderingFixtureTest
   : public AllegroFlare::Testing::WithAllegroRenderingFixture {};


TEST(AllegroFlare_Elements_DialogBoxRenderers_TextMessagesTest, can_be_created_without_blowing_up)
{
   AllegroFlare::Elements::DialogBoxRenderers::TextMessages text_messages;
}


//#include <Krampus21/DialogBoxRenderers/SmartPhone.hpp>

//#ifdef _WIN32
//#define TEST_FIXTURE_FONT_FOLDER "/msys64/home/Mark/Repos/Krampus21/bin/programs/data/fonts/"
//#else
//#define TEST_FIXTURE_FONT_FOLDER "/Users/markoates/Repos/Krampus21/bin/programs/data/fonts/"
//#endif

//#include <AllegroFlare/Testing/WithAllegroRenderingFixture.hpp>
//#include <chrono>
//#include <thread>

//class Krampus21_DialogBoxRenderers_SmartPhoneTest : public ::testing::Test {};
//class Krampus21_DialogBoxRenderers_SmartPhoneWithAllegroRenderingFixtureTest
   //: public AllegroFlare::Testing::WithAllegroRenderingFixture {};


TEST_F(Krampus21_DialogBoxRenderers_SmartPhoneWithAllegroRenderingFixtureTest, can_be_created_without_blowing_up)
{
   //get_font_bin_ref().set_full_path(TEST_FIXTURE_FONT_FOLDER);

   AllegroFlare::Placement2D place{ 1920/2, 1080/2, 600/2, 600 };
   int passes = 60;
   float reveal_counter = 0;
   for (unsigned i=0; i<passes; i++)
   {
      al_clear_to_color(ALLEGRO_COLOR{0, 0, 0, 1});
      AllegroFlare::Elements::DialogBoxRenderers::TextMessages smart_phone_dialog_renderer(
         &get_font_bin_ref(),
         600,
         100,
         { "Hello, this is bubble text", "And this is a second line", "And finally the last line" },
         reveal_counter
      );

      place.start_transform();
      smart_phone_dialog_renderer.render();
      place.restore_transform();
      al_flip_display();
      std::this_thread::sleep_for(std::chrono::milliseconds(1000/60));
      reveal_counter += (1.0/60.0f) * 2;
   }

   //std::this_thread::sleep_for(std::chrono::seconds(1));
}



