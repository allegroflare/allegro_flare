

#include <AllegroFlare/Testing/WithAllegroFlareFrameworksFullFixture.hpp>

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
   , framework_profiler(nullptr)
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


AllegroFlare::Profiler* WithAllegroFlareFrameworksFullFixture::get_framework_profiler() const
{
   return framework_profiler;
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
      error_message << "[WithAllegroFlareFrameworksFullFixture::SetUp]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("WithAllegroFlareFrameworksFullFixture::SetUp: error: guard \"(!initialized)\" not met");
   }
   framework.set_deployment_environment("test");
   framework.disable_auto_created_config_warning();
   framework.disable_fullscreen();
   framework.initialize();

   this->framework_event_emitter = &framework.get_event_emitter_ref();
   this->framework_bitmap_bin = &framework.get_bitmap_bin_ref();
   this->framework_font_bin = &framework.get_font_bin_ref();
   this->framework_model_bin = &framework.get_model_bin_ref();
   this->framework_sample_bin = &framework.get_sample_bin_ref();
   this->framework_profiler = &framework.get_profiler_ref();

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
      error_message << "[WithAllegroFlareFrameworksFullFixture::TearDown]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("WithAllegroFlareFrameworksFullFixture::TearDown: error: guard \"initialized\" not met");
   }
   framework.shutdown();
   this->framework_event_emitter = nullptr;
   this->framework_bitmap_bin = nullptr;
   this->framework_font_bin = nullptr;
   this->framework_model_bin = nullptr;
   this->framework_sample_bin = nullptr;
   this->framework_profiler = nullptr;
   initialized = false;
   return;
}

void WithAllegroFlareFrameworksFullFixture::framework_register_and_activate_screen(std::string name, AllegroFlare::Screens::Base* screen)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[WithAllegroFlareFrameworksFullFixture::framework_register_and_activate_screen]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("WithAllegroFlareFrameworksFullFixture::framework_register_and_activate_screen: error: guard \"initialized\" not met");
   }
   framework.register_and_activate_screen(name, screen);
   return;
}

void WithAllegroFlareFrameworksFullFixture::framework_run_loop(float num_seconds_to_auto_abort)
{
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[WithAllegroFlareFrameworksFullFixture::framework_run_loop]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("WithAllegroFlareFrameworksFullFixture::framework_run_loop: error: guard \"initialized\" not met");
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


} // namespace Testing
} // namespace AllegroFlare


