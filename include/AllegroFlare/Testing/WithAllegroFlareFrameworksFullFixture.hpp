#pragma once


#include <AllegroFlare/BitmapBin.hpp>
#include <AllegroFlare/EventEmitter.hpp>
#include <AllegroFlare/FontBin.hpp>
#include <AllegroFlare/Frameworks/Full.hpp>
#include <gtest/gtest.h>
#include <string>


namespace AllegroFlare
{
   namespace Testing
   {
      class WithAllegroFlareFrameworksFullFixture : public ::testing::Test
      {
      private:
         AllegroFlare::Frameworks::Full framework;
         AllegroFlare::EventEmitter event_emitter;
         AllegroFlare::BitmapBin bitmap_bin;
         AllegroFlare::FontBin font_bin;
         std::string test_snapshots_folder;
         bool initialized;

      protected:


      public:
         WithAllegroFlareFrameworksFullFixture();
         virtual ~WithAllegroFlareFrameworksFullFixture();

         AllegroFlare::Frameworks::Full &get_framework_ref();
         AllegroFlare::EventEmitter &get_event_emitter_ref();
         AllegroFlare::BitmapBin &get_bitmap_bin_ref();
         AllegroFlare::FontBin &get_font_bin_ref();
         virtual void SetUp() override;
         virtual void TearDown() override;
         void run_framework_loop();
         std::string get_test_name();
         std::string get_test_suite_name();
         std::string build_full_test_name_str();
      };
   }
}



