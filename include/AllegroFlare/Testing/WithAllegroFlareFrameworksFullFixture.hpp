#pragma once


#include <AllegroFlare/BitmapBin.hpp>
#include <AllegroFlare/EventEmitter.hpp>
#include <AllegroFlare/FontBin.hpp>
#include <AllegroFlare/Frameworks/Full.hpp>
#include <AllegroFlare/ModelBin.hpp>
#include <AllegroFlare/Profiler.hpp>
#include <AllegroFlare/Screens/Base.hpp>
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
         AllegroFlare::EventEmitter* framework_event_emitter;
         AllegroFlare::BitmapBin* framework_bitmap_bin;
         AllegroFlare::FontBin* framework_font_bin;
         AllegroFlare::ModelBin* framework_model_bin;
         AllegroFlare::Profiler* framework_profiler;
         std::string test_snapshots_folder;
         bool initialized;

      protected:


      public:
         WithAllegroFlareFrameworksFullFixture();
         virtual ~WithAllegroFlareFrameworksFullFixture();

         AllegroFlare::EventEmitter* get_framework_event_emitter() const;
         AllegroFlare::BitmapBin* get_framework_bitmap_bin() const;
         AllegroFlare::FontBin* get_framework_font_bin() const;
         AllegroFlare::ModelBin* get_framework_model_bin() const;
         AllegroFlare::Profiler* get_framework_profiler() const;
         AllegroFlare::Frameworks::Full &get_framework_ref();
         virtual void SetUp() override;
         virtual void TearDown() override;
         void framework_register_and_activate_screen(std::string name="[unset-name]", AllegroFlare::Screens::Base* screen=nullptr);
         void framework_run_loop(float num_seconds_to_auto_abort=3);
         std::string get_test_name();
         std::string get_test_suite_name();
         std::string build_full_test_name_str();
      };
   }
}



