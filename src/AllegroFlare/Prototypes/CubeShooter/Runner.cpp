

#include <AllegroFlare/Prototypes/CubeShooter/Runner.hpp>

#include <AllegroFlare/Frameworks/Full.hpp>
#include <iostream>
#include <set>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Prototypes
{
namespace CubeShooter
{


Runner::Runner(std::string mode, AllegroFlare::Frameworks::Full* framework, AllegroFlare::EventEmitter* event_emitter, AllegroFlare::BitmapBin* bitmap_bin, AllegroFlare::FontBin* font_bin, AllegroFlare::SampleBin* sample_bin, AllegroFlare::ModelBin* model_bin)
   : AllegroFlare::Screens::Base("Runner")
   , mode(mode)
   , framework(framework)
   , event_emitter(event_emitter)
   , bitmap_bin(bitmap_bin)
   , font_bin(font_bin)
   , sample_bin(sample_bin)
   , model_bin(model_bin)
   , cube_shooter_screen()
   , initialized(false)
{
}


Runner::~Runner()
{
}


void Runner::initialize()
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::CubeShooter::Runner::initialize]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::CubeShooter::Runner::initialize]: error: guard \"(!initialized)\" not met");
   }
   if (!(framework))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::CubeShooter::Runner::initialize]: error: guard \"framework\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::CubeShooter::Runner::initialize]: error: guard \"framework\" not met");
   }
   if (!(event_emitter))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::CubeShooter::Runner::initialize]: error: guard \"event_emitter\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::CubeShooter::Runner::initialize]: error: guard \"event_emitter\" not met");
   }
   if (!(bitmap_bin))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::CubeShooter::Runner::initialize]: error: guard \"bitmap_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::CubeShooter::Runner::initialize]: error: guard \"bitmap_bin\" not met");
   }
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::CubeShooter::Runner::initialize]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::CubeShooter::Runner::initialize]: error: guard \"font_bin\" not met");
   }
   if (!(sample_bin))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::CubeShooter::Runner::initialize]: error: guard \"sample_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::CubeShooter::Runner::initialize]: error: guard \"sample_bin\" not met");
   }
   if (!(model_bin))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::CubeShooter::Runner::initialize]: error: guard \"model_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::CubeShooter::Runner::initialize]: error: guard \"model_bin\" not met");
   }
   cube_shooter_screen.set_event_emitter(event_emitter);
   cube_shooter_screen.set_bitmap_bin(bitmap_bin);
   cube_shooter_screen.set_font_bin(font_bin);
   cube_shooter_screen.set_sample_bin(sample_bin);
   cube_shooter_screen.set_model_bin(model_bin);
   cube_shooter_screen.initialize();
   framework->register_screen("cube_shooter_screen", &cube_shooter_screen);
   return;
}

std::map<std::string, std::function<void()>> Runner::event_map()
{
   return {};
}

void Runner::game_event_func(AllegroFlare::GameEvent* ev)
{
   if (!(ev))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::CubeShooter::Runner::game_event_func]: error: guard \"ev\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::CubeShooter::Runner::game_event_func]: error: guard \"ev\" not met");
   }
   if (!(event_emitter))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::CubeShooter::Runner::game_event_func]: error: guard \"event_emitter\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::CubeShooter::Runner::game_event_func]: error: guard \"event_emitter\" not met");
   }
   std::string event_name = ev->get_type();
   std::cout << "EVENT_EMITTED: \"" << event_name << "\"" << std::endl;

   std::map<std::string, std::function<void()>> event_map = {
      { "initialize", [this](){
         event_emitter->emit_game_event(AllegroFlare::GameEvent(EVENT_ACTIVATE_CUBE_SHOOTER_SCREEN));
      }},
      { EVENT_ACTIVATE_CUBE_SHOOTER_SCREEN, [this](){
         framework->activate_screen("cube_shooter_screen");
      }},
      //{ EVENT_PAUSE_GAME, [this](){
         //push_screen();
         //framework->activate_screen("pause_screen");
      //}},
      //{ EVENT_UNPAUSE_GAME, [this](){
         //std::string previous_screen = pop_screen();
         //framework->activate_screen("pause_screen");
      //}},
   };

   // locate and call the function to handle the event
   if (event_map.count(event_name) == 0)
   {
      // event not found
      std::cout << "ERROR: event not found: \"" << event_name << "\"" << std::endl;
   }
   else
   {
      // call the event
      event_map[event_name]();
   }

   return;
}

void Runner::RUN(std::string mode, bool disable_escape_key_will_shutdown)
{
   if (!(is_valid_mode(mode)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Prototypes::CubeShooter::Runner::RUN]: error: guard \"is_valid_mode(mode)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Prototypes::CubeShooter::Runner::RUN]: error: guard \"is_valid_mode(mode)\" not met");
   }
   // setup the framework
   AllegroFlare::Frameworks::Full framework;
   if (disable_escape_key_will_shutdown) framework.disable_escape_key_will_shutdown();
   framework.disable_fullscreen();
   framework.initialize();

   // setup the environment/asset folders
   if (is_test_mode(mode) || is_development_mode(mode) || is_production_mode(mode))
   {
      std::string PROJECT_DATA_FOLDER = "/Users/markoates/Repos/allegro_flare/bin/data/CubeShooter";
      framework.get_font_bin_ref().set_full_path(PROJECT_DATA_FOLDER + "/fonts");
      framework.get_bitmap_bin_ref().set_full_path(PROJECT_DATA_FOLDER + "/bitmaps");
      framework.get_sample_bin_ref().set_full_path(PROJECT_DATA_FOLDER + "/samples");
      framework.get_model_bin_ref().set_full_path(PROJECT_DATA_FOLDER + "/models");
   }


   // instantiate our actual game runner
   Runner runner(
      mode,
      &framework,
      &framework.get_event_emitter_ref(),
      &framework.get_bitmap_bin_ref(),
      &framework.get_font_bin_ref(),
      &framework.get_sample_bin_ref(),
      &framework.get_model_bin_ref()
   );
   runner.initialize();
   framework.register_screen("runner", &runner);

   framework.run_loop();
   return;
}

bool Runner::is_test_mode(std::string mode)
{
   return mode == MODE_TEST;
}

bool Runner::is_development_mode(std::string mode)
{
   return mode == MODE_DEVELOPMENT;
}

bool Runner::is_production_mode(std::string mode)
{
   return mode == MODE_PRODUCTION;
}

bool Runner::in_development_mode()
{
   return mode == MODE_DEVELOPMENT;
}

bool Runner::in_production_mode()
{
   return mode == MODE_PRODUCTION;
}

bool Runner::in_test_mode()
{
   return mode == MODE_TEST;
}

bool Runner::is_valid_mode(std::string mode)
{
   static const std::set<std::string> VALID_MODES = {
      MODE_PRODUCTION,
      MODE_DEVELOPMENT,
      MODE_TEST,
   };
   return (VALID_MODES.count(mode) > 0);
}


} // namespace CubeShooter
} // namespace Prototypes
} // namespace AllegroFlare


