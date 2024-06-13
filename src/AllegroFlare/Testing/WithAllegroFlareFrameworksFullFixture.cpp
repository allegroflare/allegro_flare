

#include <AllegroFlare/Testing/WithAllegroFlareFrameworksFullFixture.hpp>

#include <AllegroFlare/Testing/TestNameInference.hpp>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Testing
{


WithAllegroFlareFrameworksFullFixture::WithAllegroFlareFrameworksFullFixture()
   : ::testing::Test()
   , framework({})
   , framework_event_emitter(nullptr)
   , framework_bitmap_bin(nullptr)
   , framework_font_bin(nullptr)
   , framework_sample_bin(nullptr)
   , framework_model_bin(nullptr)
   , framework_video_bin(nullptr)
   , framework_profiler(nullptr)
   , framework_data_folder_path("[unset-framework_data_folder_path]")
   , framework_primary_render_surface(nullptr)
   , test_prefix_tokens({})
   , test_snapshots_folder("[unset-test_snapshots_folder]")
   , initialized(false)
{
}


WithAllegroFlareFrameworksFullFixture::~WithAllegroFlareFrameworksFullFixture()
{
}


AllegroFlare::EventEmitter* WithAllegroFlareFrameworksFullFixture::get_framework_event_emitter() const
{
   return framework_event_emitter;
}


AllegroFlare::BitmapBin* WithAllegroFlareFrameworksFullFixture::get_framework_bitmap_bin() const
{
   return framework_bitmap_bin;
}


AllegroFlare::FontBin* WithAllegroFlareFrameworksFullFixture::get_framework_font_bin() const
{
   return framework_font_bin;
}


AllegroFlare::SampleBin* WithAllegroFlareFrameworksFullFixture::get_framework_sample_bin() const
{
   return framework_sample_bin;
}


AllegroFlare::ModelBin* WithAllegroFlareFrameworksFullFixture::get_framework_model_bin() const
{
   return framework_model_bin;
}


AllegroFlare::VideoBin* WithAllegroFlareFrameworksFullFixture::get_framework_video_bin() const
{
   return framework_video_bin;
}


AllegroFlare::Profiler* WithAllegroFlareFrameworksFullFixture::get_framework_profiler() const
{
   return framework_profiler;
}


std::string WithAllegroFlareFrameworksFullFixture::get_framework_data_folder_path() const
{
   return framework_data_folder_path;
}


AllegroFlare::RenderSurfaces::Base* WithAllegroFlareFrameworksFullFixture::get_framework_primary_render_surface() const
{
   return framework_primary_render_surface;
}


AllegroFlare::Frameworks::Full &WithAllegroFlareFrameworksFullFixture::get_framework_ref()
{
   return framework;
}


void WithAllegroFlareFrameworksFullFixture::SetUp()
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Testing::WithAllegroFlareFrameworksFullFixture::SetUp]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Testing::WithAllegroFlareFrameworksFullFixture::SetUp]: error: guard \"(!initialized)\" not met");
   }
   test_prefix_tokens = extract_test_prefix_tokens();

   framework.set_deployment_environment("test");
   framework.disable_auto_created_config_warning();
   framework.disable_fullscreen();
   framework.initialize();

   this->framework_event_emitter = &framework.get_event_emitter_ref();
   this->framework_bitmap_bin = &framework.get_bitmap_bin_ref();
   this->framework_font_bin = &framework.get_font_bin_ref();
   this->framework_model_bin = &framework.get_model_bin_ref();
   this->framework_video_bin = &framework.get_video_bin_ref();
   this->framework_sample_bin = &framework.get_sample_bin_ref();
   this->framework_data_folder_path = framework.get_data_folder_path();
   this->framework_profiler = &framework.get_profiler_ref();
   this->framework_primary_render_surface = framework.get_primary_render_surface();

   test_snapshots_folder = "./tmp/test_snapshots/";

   // TODO: consider setting this value in the framework
   //al_clear_to_color(ALLEGRO_COLOR{0.05f, 0.05f, 0.055f, 1.0f});

   // TODO: set the window title to the current test name
   //std::string new_window_title = build_full_test_name_str();
   //al_set_window_title(display, new_window_title.c_str());

   initialized = true;

   return;
}

void WithAllegroFlareFrameworksFullFixture::TearDown()
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Testing::WithAllegroFlareFrameworksFullFixture::TearDown]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Testing::WithAllegroFlareFrameworksFullFixture::TearDown]: error: guard \"initialized\" not met");
   }
   // TODO: Test this screenshot inference and action logic
   if (test_name_indicates_it_wants_a_screenshot())
   {
      capture_screenshot(build_full_test_name_str() + ".png");
   }

   framework.shutdown();
   this->framework_event_emitter = nullptr;
   this->framework_bitmap_bin = nullptr;
   this->framework_font_bin = nullptr;
   this->framework_model_bin = nullptr;
   this->framework_video_bin = nullptr;
   this->framework_sample_bin = nullptr;
   // TODO: Add test for this "framework_data
   this->framework_data_folder_path = "[unset-framewor_data_folder_path]";
   this->framework_profiler = nullptr;
   this->framework_primary_render_surface = nullptr;
   initialized = false;
   return;
}

void WithAllegroFlareFrameworksFullFixture::framework_register_and_activate_screen(std::string name, AllegroFlare::Screens::Base* screen)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Testing::WithAllegroFlareFrameworksFullFixture::framework_register_and_activate_screen]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Testing::WithAllegroFlareFrameworksFullFixture::framework_register_and_activate_screen]: error: guard \"initialized\" not met");
   }
   framework.register_and_activate_screen(name, screen);
   return;
}

void WithAllegroFlareFrameworksFullFixture::framework_register_screen(std::string name, AllegroFlare::Screens::Base* screen)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Testing::WithAllegroFlareFrameworksFullFixture::framework_register_screen]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Testing::WithAllegroFlareFrameworksFullFixture::framework_register_screen]: error: guard \"initialized\" not met");
   }
   // TODO: Test this method
   framework.register_screen(name, screen);
   return;
}

void WithAllegroFlareFrameworksFullFixture::framework_activate_screen(std::string name, AllegroFlare::Screens::Base* screen)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Testing::WithAllegroFlareFrameworksFullFixture::framework_activate_screen]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Testing::WithAllegroFlareFrameworksFullFixture::framework_activate_screen]: error: guard \"initialized\" not met");
   }
   // TODO: Test this method
   framework.activate_screen(name);
   return;
}

void WithAllegroFlareFrameworksFullFixture::framework_run_loop(float num_seconds_to_auto_abort)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Testing::WithAllegroFlareFrameworksFullFixture::framework_run_loop]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Testing::WithAllegroFlareFrameworksFullFixture::framework_run_loop]: error: guard \"initialized\" not met");
   }
   framework.run_loop(num_seconds_to_auto_abort);
   return;
}

std::string WithAllegroFlareFrameworksFullFixture::get_test_name()
{
   // TODO: use AllegroFlare::Testing::TestNameInference for this logic
   const testing::TestInfo* const test_info = testing::UnitTest::GetInstance()->current_test_info();
   return test_info->name();
}

std::string WithAllegroFlareFrameworksFullFixture::get_test_suite_name()
{
   // TODO: use AllegroFlare::Testing::TestNameInference for this logic
   const testing::TestInfo* const test_info = testing::UnitTest::GetInstance()->current_test_info();
   return test_info->test_suite_name();
}

std::string WithAllegroFlareFrameworksFullFixture::build_full_test_name_str()
{
   // TODO: use AllegroFlare::Testing::TestNameInference for this logic
   return get_test_suite_name() + " - " + get_test_name();
}

std::vector<std::string> WithAllegroFlareFrameworksFullFixture::extract_test_prefix_tokens()
{
   return AllegroFlare::Testing::TestNameInference::extract_prefix_tokens(get_test_name());
}

bool WithAllegroFlareFrameworksFullFixture::test_name_indicates_it_wants_a_screenshot()
{
   return test_name_has_prefix_token("CAPTURE");
}

bool WithAllegroFlareFrameworksFullFixture::test_name_has_prefix_token(std::string possible_prefix_token)
{
   // TODO: convert this to an std::set
   return (std::find(test_prefix_tokens.begin(), test_prefix_tokens.end(), possible_prefix_token) != test_prefix_tokens.end());
}

void WithAllegroFlareFrameworksFullFixture::capture_screenshot(std::string base_filename)
{
   // TODO: use AllegroFlare::Testing::TestNameInference for this logic
   std::string full_file_save_location = test_snapshots_folder + base_filename;

   al_flip_display(); // this capture_screenshot technique assumes the pixels to capture are currently being
                      // shown on the display.  This al_flip_display is added here in order to flip the
                      // front-buffer *back* to the backbuffer so it can be used to capture the screenshot

   // TODO: Consider using the primary rendering surface instead of the display
   ALLEGRO_BITMAP *bitmap_to_save = al_get_backbuffer(framework.get_primary_display()->al_display);

   bool screenshot_successful = al_save_bitmap(full_file_save_location.c_str(), bitmap_to_save);
   if (screenshot_successful)
   {
      // TODO: Use Logger
      std::cout //<< AllegroFlare::TerminalColors::CYAN
                << "[AllegroFlare::Testing::WithAllegroRenderingFixture::screenshot]: info: screenshot saved to "
                << "\"" << full_file_save_location << "\""
                //<< AllegroFlare::TerminalColors::DEFAULT
                << std::endl;
   }
   else
   {
      std::cout //<< AllegroFlare::TerminalColors::RED
                << "[AllegroFlare::Testing::WithAllegroRenderingFixture::screenshot]: error: screenshot "
                << "CAPTURE was not successful when trying to saving to \"" << full_file_save_location << "\""
                //<< AllegroFlare::TerminalColors::DEFAULT
                << std::endl;
   }
}


} // namespace Testing
} // namespace AllegroFlare


