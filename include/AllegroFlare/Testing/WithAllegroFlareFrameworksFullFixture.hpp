#pragma once


#include <AllegroFlare/BitmapBin.hpp>
#include <AllegroFlare/DialogSystem/DialogSystem.hpp>
#include <AllegroFlare/EventEmitter.hpp>
#include <AllegroFlare/FontBin.hpp>
#include <AllegroFlare/Frameworks/Full.hpp>
#include <AllegroFlare/ModelBin.hpp>
#include <AllegroFlare/Profiler.hpp>
#include <AllegroFlare/RenderSurfaces/Base.hpp>
#include <AllegroFlare/SampleBin.hpp>
#include <AllegroFlare/Screens/Base.hpp>
#include <AllegroFlare/VideoBin.hpp>
#include <gtest/gtest.h>
#include <string>
#include <vector>


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
         AllegroFlare::SampleBin* framework_sample_bin;
         AllegroFlare::ModelBin* framework_model_bin;
         AllegroFlare::VideoBin* framework_video_bin;
         AllegroFlare::DialogSystem::DialogSystem* framework_dialog_system;
         AllegroFlare::Profiler* framework_profiler;
         std::string framework_data_folder_path;
         AllegroFlare::RenderSurfaces::Base* framework_primary_render_surface;
         std::vector<std::string> test_prefix_tokens;
         std::string test_snapshots_folder;
         bool initialized;

      protected:


      public:
         WithAllegroFlareFrameworksFullFixture();
         virtual ~WithAllegroFlareFrameworksFullFixture();

         AllegroFlare::EventEmitter* get_framework_event_emitter() const;
         AllegroFlare::BitmapBin* get_framework_bitmap_bin() const;
         AllegroFlare::FontBin* get_framework_font_bin() const;
         AllegroFlare::SampleBin* get_framework_sample_bin() const;
         AllegroFlare::ModelBin* get_framework_model_bin() const;
         AllegroFlare::VideoBin* get_framework_video_bin() const;
         AllegroFlare::DialogSystem::DialogSystem* get_framework_dialog_system() const;
         AllegroFlare::Profiler* get_framework_profiler() const;
         std::string get_framework_data_folder_path() const;
         AllegroFlare::RenderSurfaces::Base* get_framework_primary_render_surface() const;
         AllegroFlare::Frameworks::Full &get_framework_ref();
         virtual void SetUp() override;
         virtual void TearDown() override;
         void framework_register_and_activate_screen(std::string name="[unset-name]", AllegroFlare::Screens::Base* screen=nullptr);
         void framework_register_screen(std::string name="[unset-name]", AllegroFlare::Screens::Base* screen=nullptr);
         void framework_activate_screen(std::string name="[unset-name]", AllegroFlare::Screens::Base* screen=nullptr);
         void framework_run_loop(float num_seconds_to_auto_abort=3);
         std::string get_test_name();
         std::string get_test_suite_name();
         std::string build_full_test_name_str();
         std::vector<std::string> extract_test_prefix_tokens();
         bool test_name_indicates_it_wants_a_screenshot();
         bool test_name_has_prefix_token(std::string possible_prefix_token="[unset-possible_prefix_token]");
         void capture_screenshot(std::string base_filename="WithAllegroFlareFrameworksFullFixture-screenshot.png");
      };
   }
}



