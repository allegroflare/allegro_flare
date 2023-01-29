

#include <AllegroFlare/Testing/WithAllegroFlareFrameworksFullFixture.hpp>




namespace AllegroFlare
{
namespace Testing
{


WithAllegroFlareFrameworksFullFixture::WithAllegroFlareFrameworksFullFixture()
   : ::testing::Test()
   , framework({})
   , event_emitter(framework.get_event_emitter_ref())
   , bitmap_bin(framework.get_bitmap_bin_ref())
   , font_bin(framework.get_font_bin_ref())
   , test_snapshots_folder("[unset-test_snapshots_folder]")
   , initialized(false)
{
}


WithAllegroFlareFrameworksFullFixture::~WithAllegroFlareFrameworksFullFixture()
{
}


AllegroFlare::Frameworks::Full &WithAllegroFlareFrameworksFullFixture::get_framework_ref()
{
   return framework;
}


AllegroFlare::EventEmitter &WithAllegroFlareFrameworksFullFixture::get_event_emitter_ref()
{
   return event_emitter;
}


AllegroFlare::BitmapBin &WithAllegroFlareFrameworksFullFixture::get_bitmap_bin_ref()
{
   return bitmap_bin;
}


AllegroFlare::FontBin &WithAllegroFlareFrameworksFullFixture::get_font_bin_ref()
{
   return font_bin;
}


void WithAllegroFlareFrameworksFullFixture::SetUp()
{
   framework.set_deployment_environment("test");
   framework.disable_auto_created_config_warning();
   framework.disable_fullscreen();
   framework.initialize();

   test_snapshots_folder = "./tmp/test_snapshots/";

   //event_emitter = &framework.get_event_emitter_ref();
   //bitmap_bin = &framework.get_bitmap_bin_ref();
   //font_bin = &framework.get_font_bin_ref();

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
   framework.shutdown();
   initialized = false;
   return;
}

void WithAllegroFlareFrameworksFullFixture::run_framework_loop()
{
   framework.run_loop(4); // TODO: make this number of seconds a more comprehensive argument
   initialized = false;
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


