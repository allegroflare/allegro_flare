

#include <AllegroFlare/Runners/Complete.hpp>

#include <AllegroFlare/Color.hpp>
#include <AllegroFlare/Elements/Backgrounds/ClearToColor.hpp>
#include <AllegroFlare/Frameworks/Full.hpp>
#include <AllegroFlare/GameProgressAndStateInfos/Base.hpp>
#include <AllegroFlare/GameSession.hpp>
#include <AllegroFlare/LoadASavedGame/SaveSlots/Empty.hpp>
#include <AllegroFlare/Logger.hpp>
#include <AllegroFlare/RouteEventDatas/StartLevel.hpp>
#include <AllegroFlare/Screens/TitledMenuScreen.hpp>
#include <AllegroFlare/StoryboardFactory.hpp>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Runners
{


Complete::Complete(AllegroFlare::Frameworks::Full* framework, AllegroFlare::EventEmitter* event_emitter, AllegroFlare::BitmapBin* bitmap_bin, AllegroFlare::FontBin* font_bin, AllegroFlare::SampleBin* sample_bin, AllegroFlare::ModelBin* model_bin, AllegroFlare::GameConfigurations::Complete* game_configuration)
   : AllegroFlare::Screens::Base(AllegroFlare::Runners::Complete::TYPE)
   , framework(framework)
   , event_emitter(event_emitter)
   , bitmap_bin(bitmap_bin)
   , font_bin(font_bin)
   , sample_bin(sample_bin)
   , model_bin(model_bin)
   , game_configuration(game_configuration)
   , router()
   , intro_logos_screen()
   , intro_storyboard_screen()
   , title_screen()
   , display_settings_screen()
   , achievements_screen()
   , version_screen()
   , load_a_saved_game_screen()
   , new_game_intro_storyboard_screen()
   , level_select_screen()
   , arbitrary_storyboard_screen()
   , game_over_screen()
   , game_won_screen()
   , game_won_outro_storyboard_screen()
   , settings_screen()
   , rolling_credits_screen()
   , primary_gameplay_screen(nullptr)
   , primary_gameplay_subscreen(nullptr)
   , pause_screen(nullptr)
   , shared_background(nullptr)
   , shared_foreground(nullptr)
   , release_info({})
   , initialized(false)
   , destroyed(false)
{
}


Complete::~Complete()
{
}


AllegroFlare::Frameworks::Full* Complete::get_framework() const
{
   return framework;
}


AllegroFlare::EventEmitter* Complete::get_event_emitter() const
{
   return event_emitter;
}


AllegroFlare::BitmapBin* Complete::get_bitmap_bin() const
{
   return bitmap_bin;
}


AllegroFlare::FontBin* Complete::get_font_bin() const
{
   return font_bin;
}


AllegroFlare::SampleBin* Complete::get_sample_bin() const
{
   return sample_bin;
}


AllegroFlare::ModelBin* Complete::get_model_bin() const
{
   return model_bin;
}


AllegroFlare::Screens::Storyboard &Complete::get_intro_logos_screen_ref()
{
   return intro_logos_screen;
}


AllegroFlare::Screens::Storyboard &Complete::get_intro_storyboard_screen_ref()
{
   return intro_storyboard_screen;
}


AllegroFlare::Screens::TitledMenuScreen &Complete::get_title_screen_ref()
{
   return title_screen;
}


AllegroFlare::Screens::DisplaySettings &Complete::get_display_settings_screen_ref()
{
   return display_settings_screen;
}


AllegroFlare::Screens::Achievements &Complete::get_achievements_screen_ref()
{
   return achievements_screen;
}


AllegroFlare::Screens::Version &Complete::get_version_screen_ref()
{
   return version_screen;
}


AllegroFlare::LoadASavedGame::Screen &Complete::get_load_a_saved_game_screen_ref()
{
   return load_a_saved_game_screen;
}


AllegroFlare::Screens::Storyboard &Complete::get_new_game_intro_storyboard_screen_ref()
{
   return new_game_intro_storyboard_screen;
}


AllegroFlare::Screens::LevelSelectScreen &Complete::get_level_select_screen_ref()
{
   return level_select_screen;
}


AllegroFlare::Screens::Storyboard &Complete::get_arbitrary_storyboard_screen_ref()
{
   return arbitrary_storyboard_screen;
}


AllegroFlare::Screens::GameOverScreen &Complete::get_game_over_screen_ref()
{
   return game_over_screen;
}


AllegroFlare::Screens::GameWonScreen &Complete::get_game_won_screen_ref()
{
   return game_won_screen;
}


AllegroFlare::Screens::Storyboard &Complete::get_game_won_outro_storyboard_screen_ref()
{
   return game_won_outro_storyboard_screen;
}


AllegroFlare::Screens::SettingsScreen &Complete::get_settings_screen_ref()
{
   return settings_screen;
}


AllegroFlare::Screens::RollingCredits &Complete::get_rolling_credits_screen_ref()
{
   return rolling_credits_screen;
}


void Complete::game_event_func(AllegroFlare::GameEvent* game_event)
{
   if (!(game_event))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Runners::Complete::game_event_func]: error: guard \"game_event\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Runners::Complete::game_event_func]: error: guard \"game_event\" not met");
   }
   // TODO: See if this have "guards: [ initialized, (!destroyed) ]" as well?
   game_configuration->handle_game_event(game_event);
   return;
}

void Complete::initialize()
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Runners::Complete::initialize]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Runners::Complete::initialize]: error: guard \"(!initialized)\" not met");
   }
   if (!((!destroyed)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Runners::Complete::initialize]: error: guard \"(!destroyed)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Runners::Complete::initialize]: error: guard \"(!destroyed)\" not met");
   }
   if (!(framework))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Runners::Complete::initialize]: error: guard \"framework\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Runners::Complete::initialize]: error: guard \"framework\" not met");
   }
   if (!(event_emitter))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Runners::Complete::initialize]: error: guard \"event_emitter\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Runners::Complete::initialize]: error: guard \"event_emitter\" not met");
   }
   if (!(bitmap_bin))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Runners::Complete::initialize]: error: guard \"bitmap_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Runners::Complete::initialize]: error: guard \"bitmap_bin\" not met");
   }
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Runners::Complete::initialize]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Runners::Complete::initialize]: error: guard \"font_bin\" not met");
   }
   if (!(sample_bin))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Runners::Complete::initialize]: error: guard \"sample_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Runners::Complete::initialize]: error: guard \"sample_bin\" not met");
   }
   if (!(model_bin))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Runners::Complete::initialize]: error: guard \"model_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Runners::Complete::initialize]: error: guard \"model_bin\" not met");
   }
   if (!(game_configuration))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Runners::Complete::initialize]: error: guard \"game_configuration\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Runners::Complete::initialize]: error: guard \"game_configuration\" not met");
   }
   // Create some references for convenience
   AllegroFlare::Achievements &achievements = framework->get_achievements_ref();
   AllegroFlare::AudioController &audio_controller = framework->get_audio_controller_ref();

   // Pass along the runner into the configuration (for convenience)
   // TODO: Review this as a design concept, should the dependencies in game_configuration be more explicit
   game_configuration->set_runner(this);

   // Create the shared background
   shared_background = game_configuration->create_shared_background();
   shared_foreground = game_configuration->create_shared_foreground();

   // Create the primary_gameplay_screen
   primary_gameplay_screen = game_configuration->create_primary_gameplay_screen(this);

   // Create the primary_gameplay_screen
   primary_gameplay_subscreen = game_configuration->create_primary_gameplay_subscreen(this);

   // Create the pause_screen
   pause_screen = game_configuration->create_pause_screen(this);

   // Setup our router
   setup_router();

   // Set the framework to use the router we've created here
   framework->set_router(&router);

   // Fill our dialog bank
   framework->set_dialog_system_dialog_node_bank(game_configuration->build_dialog_bank_by_identifier());

   // Setup achievements
   achievements.set_achievements(game_configuration->build_achievements());

   // Setup intro logos screen (if empty, will simply be skipped)
   intro_logos_screen.set_event_emitter(event_emitter);
   intro_logos_screen.set_font_bin(font_bin);
   intro_logos_screen.set_auto_advance(true);
   intro_logos_screen.set_foreground(shared_foreground);
   intro_logos_screen.set_background(shared_background);
   intro_logos_screen.initialize();
   intro_logos_screen.get_storyboard_element_ref().set_pages(
      game_configuration->create_intro_logos_storyboard_pages()
   );

   // Setup intro storyboard screen (if empty, will simply be skipped)
   intro_storyboard_screen.set_event_emitter(event_emitter);
   intro_storyboard_screen.set_font_bin(font_bin);
   intro_storyboard_screen.set_auto_advance(true);
   intro_storyboard_screen.set_foreground(shared_foreground);
   intro_storyboard_screen.set_background(shared_background);
   intro_storyboard_screen.initialize();
   intro_storyboard_screen.get_storyboard_element_ref().set_pages(
      game_configuration->create_intro_storyboard_pages()
   );

   // Setup title screen
   title_screen.set_data_folder_path(get_framework()->get_data_folder_path());
   title_screen.set_title_text(game_configuration->title_screen_title());
   title_screen.set_footer_text(game_configuration->build_copyright_text(&release_info));
   title_screen.set_menu_options(game_configuration->build_title_screen_menu_options());
   //{
      //{ "Start new game", "start_new_game" }, // NOTE: This value is a constant expected by Routers/Complete
      //{ "Load a saved game", "goto_load_a_saved_game_screen" }, // NOTE: This value is a constant expected by Routers/Complete
      //{ "Credits", "goto_credits_screen" }, // NOTE: This value is a constant expected by Routers/Complete
      //{ "Exit", "quit" } // NOTE: This value is a constant expected by Routers/Complete
   //});
   title_screen.set_menu_font_name("RobotoCondensed-Regular.ttf");
   title_screen.set_foreground(shared_foreground);
   title_screen.set_background(shared_background);
   title_screen.initialize();

   // Setup the display settings screen
   display_settings_screen.set_event_emitter(event_emitter);
   display_settings_screen.set_bitmap_bin(bitmap_bin);
   display_settings_screen.set_font_bin(font_bin);
   display_settings_screen.set_model_bin(model_bin);
   display_settings_screen.set_display_settings_interface(framework->get_display_settings_interface());
   display_settings_screen.set_label_for_menu_option_to_exit_screen("Return to Title Screen");
   display_settings_screen.set_foreground(shared_foreground);
   display_settings_screen.set_background(shared_background);
   display_settings_screen.initialize();

   // Setup achievements screen
   achievements_screen.set_achievements(&achievements);
   achievements_screen.set_event_emitter(event_emitter);
   achievements_screen.set_font_bin(font_bin);
   achievements_screen.set_foreground(shared_foreground);
   achievements_screen.set_background(shared_background);
   achievements_screen.initialize();

   // Setup version screen
   version_screen.set_bitmap_bin(bitmap_bin);
   version_screen.set_font_bin(font_bin);
   version_screen.set_model_bin(model_bin);
   version_screen.set_event_emitter(event_emitter);
   version_screen.set_foreground(shared_foreground);
   version_screen.set_background(shared_background);
   version_screen.initialize();

   // Setup new game intro storyboard screen
   new_game_intro_storyboard_screen.set_event_emitter(event_emitter);
   new_game_intro_storyboard_screen.set_font_bin(font_bin);
   new_game_intro_storyboard_screen.set_foreground(shared_foreground);
   new_game_intro_storyboard_screen.set_background(shared_background);
   new_game_intro_storyboard_screen.initialize();
   new_game_intro_storyboard_screen.get_storyboard_element_ref().set_pages(
      game_configuration->create_new_game_intro_storyboard_pages()
   );

   // Setup arbitrary storyboard screen
   arbitrary_storyboard_screen.set_event_emitter(event_emitter);
   arbitrary_storyboard_screen.set_font_bin(font_bin);
   //arbitrary_storyboard_screen.set_auto_advance(true); // TODO: This was recently changed to false by default
   arbitrary_storyboard_screen.set_foreground(shared_foreground);
   arbitrary_storyboard_screen.set_background(shared_background);
   arbitrary_storyboard_screen.initialize();
   //arbitrary_storyboard_screen.get_storyboard_element_ref().set_pages(
      //game_configuration->create_intro_storyboard_pages()
   //);

   // Setup load a saved game screen
   load_a_saved_game_screen.set_event_emitter(event_emitter);
   load_a_saved_game_screen.set_bitmap_bin(bitmap_bin);
   load_a_saved_game_screen.set_font_bin(font_bin);
   load_a_saved_game_screen.set_model_bin(model_bin); // Currently not used, but required
   load_a_saved_game_screen.initialize();
   load_a_saved_game_screen.set_foreground(shared_foreground);
   load_a_saved_game_screen.set_background(shared_background);
   load_a_saved_game_screen.set_save_slots(game_configuration->build_save_slots_for_load_a_saved_game_screen());

   // TODO: Setup level select screen
   level_select_screen.set_event_emitter(event_emitter);
   level_select_screen.set_bitmap_bin(bitmap_bin);
   level_select_screen.set_font_bin(font_bin);
   level_select_screen.set_levels_list(
      // NOTE: if this list is empty, then the screen will automatically submit on activate
      game_configuration->build_level_list_for_level_select_screen_by_identifier("discarded-for-now")
   );
   level_select_screen.set_locked_list(
      game_configuration->build_locked_list_for_level_select_screen()
   );
   level_select_screen.set_foreground(shared_foreground);
   level_select_screen.set_background(shared_background);
   level_select_screen.initialize();

   // TODO: Setup game over screen
   game_over_screen.set_event_emitter(event_emitter);
   game_over_screen.set_font_bin(font_bin);
   game_over_screen.set_foreground(shared_foreground);
   game_over_screen.set_background(shared_background);
   game_over_screen.initialize();

   // Setup game won screen
   game_won_screen.set_font_bin(font_bin);
   game_won_screen.set_foreground(shared_foreground);
   game_won_screen.set_background(shared_background);
   //game_won_screen.initialize(); // NOTE: Initialization is not necessary for this screen

   // Setup game won outro storyboard screen
   game_won_outro_storyboard_screen.set_event_emitter(event_emitter);
   game_won_outro_storyboard_screen.set_foreground(shared_foreground);
   game_won_outro_storyboard_screen.set_background(shared_background);
   game_won_outro_storyboard_screen.initialize();

   // Setup the settings screen
   settings_screen.set_event_emitter(event_emitter); // TODO: See if this is necessary
   settings_screen.set_bitmap_bin(bitmap_bin); // Currently not used, but required
   settings_screen.set_font_bin(font_bin);
   settings_screen.set_model_bin(model_bin); // Currently not used, but required
   settings_screen.set_foreground(shared_foreground);
   settings_screen.set_background(shared_background);
   settings_screen.initialize();

   // Setup rolling credits screen
   rolling_credits_screen.set_event_emitter(event_emitter); // TODO: See if this is necessary
   rolling_credits_screen.set_font_bin(font_bin);
   rolling_credits_screen.set_foreground(shared_foreground);
   rolling_credits_screen.set_background(shared_background);
   rolling_credits_screen.set_sections(game_configuration->build_rolling_credits_sections());
   rolling_credits_screen.initialize();

   // Load up our sound effects and music tracks
   game_configuration->load_audio_controller(&framework->get_audio_controller_ref());

   // TODO: Consider adding a free-for-all, "post-initialization" method to the configuration. Would be useful
   // for example, for setting up and configuring the settings on the dialog system or anything else left
   // un specified.
   game_configuration->on_runner_after_initialization_func(this);

   initialized = true;

   return;
}

void Complete::destroy()
{
   if (!((!destroyed)))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Runners::Complete::destroy]: error: guard \"(!destroyed)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Runners::Complete::destroy]: error: guard \"(!destroyed)\" not met");
   }
   if (!(initialized))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Runners::Complete::destroy]: error: guard \"initialized\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Runners::Complete::destroy]: error: guard \"initialized\" not met");
   }
   game_configuration->destroy_primary_gameplay_screen();
   game_configuration->destroy_pause_screen();

   title_screen.destroy();
   // TODO: Add additional destroy virtual methods for each object created
   // TODO: Consider if this method should be virtual as well, or if game_configuration should have "destroy()"
   destroyed = true;
   return;
}

bool Complete::on_route_event_unhandled_func(uint32_t unhandled_event, AllegroFlare::Routers::Standard* router, void* user_data)
{
   if (!(router))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Runners::Complete::on_route_event_unhandled_func]: error: guard \"router\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Runners::Complete::on_route_event_unhandled_func]: error: guard \"router\" not met");
   }
   if (!(user_data))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Runners::Complete::on_route_event_unhandled_func]: error: guard \"user_data\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Runners::Complete::on_route_event_unhandled_func]: error: guard \"user_data\" not met");
   }
   // TODO: Consider removing this method and having all Routers/Standard events be internal
   AllegroFlare::Runners::Complete* this_runner = static_cast<AllegroFlare::Runners::Complete*>(user_data);

   bool handled = false;

   switch(unhandled_event)
   {
      //case MY_ROUTE_EVENT_ACTIVATE_MY_CUSTOM_SCREEN:
         //router->activate_screen(MY_CUSTOM_SCREEN_IDENTIFIER);
         //handled = true;
      //break;
   }

   return handled;
}

bool Complete::on_gameplay_paused_func(AllegroFlare::Routers::Standard* router, void* user_data)
{
   if (!(router))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Runners::Complete::on_gameplay_paused_func]: error: guard \"router\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Runners::Complete::on_gameplay_paused_func]: error: guard \"router\" not met");
   }
   if (!(user_data))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Runners::Complete::on_gameplay_paused_func]: error: guard \"user_data\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Runners::Complete::on_gameplay_paused_func]: error: guard \"user_data\" not met");
   }
   AllegroFlare::Runners::Complete* this_runner = static_cast<AllegroFlare::Runners::Complete*>(user_data);
   this_runner->game_configuration->handle_primary_gameplay_screen_paused();
   return true;
}

bool Complete::on_gameplay_unpaused_func(AllegroFlare::Routers::Standard* router, void* user_data)
{
   if (!(router))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Runners::Complete::on_gameplay_unpaused_func]: error: guard \"router\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Runners::Complete::on_gameplay_unpaused_func]: error: guard \"router\" not met");
   }
   if (!(user_data))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Runners::Complete::on_gameplay_unpaused_func]: error: guard \"user_data\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Runners::Complete::on_gameplay_unpaused_func]: error: guard \"user_data\" not met");
   }
   AllegroFlare::Runners::Complete* this_runner = static_cast<AllegroFlare::Runners::Complete*>(user_data);
   this_runner->game_configuration->handle_primary_gameplay_screen_unpaused();
   return true;
}

bool Complete::on_primary_gameplay_screen_finished_func(AllegroFlare::Routers::Standard* router, void* user_data)
{
   if (!(router))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Runners::Complete::on_primary_gameplay_screen_finished_func]: error: guard \"router\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Runners::Complete::on_primary_gameplay_screen_finished_func]: error: guard \"router\" not met");
   }
   if (!(user_data))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Runners::Complete::on_primary_gameplay_screen_finished_func]: error: guard \"user_data\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Runners::Complete::on_primary_gameplay_screen_finished_func]: error: guard \"user_data\" not met");
   }
   AllegroFlare::Runners::Complete* this_runner = static_cast<AllegroFlare::Runners::Complete*>(user_data);
   this_runner->game_configuration->handle_primary_gameplay_screen_finished();
   return true;
}

bool Complete::on_arbitrary_storyboard_screen_finished_func(AllegroFlare::Routers::Standard* router, void* user_data)
{
   if (!(router))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Runners::Complete::on_arbitrary_storyboard_screen_finished_func]: error: guard \"router\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Runners::Complete::on_arbitrary_storyboard_screen_finished_func]: error: guard \"router\" not met");
   }
   if (!(user_data))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Runners::Complete::on_arbitrary_storyboard_screen_finished_func]: error: guard \"user_data\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Runners::Complete::on_arbitrary_storyboard_screen_finished_func]: error: guard \"user_data\" not met");
   }
   AllegroFlare::Runners::Complete* this_runner = static_cast<AllegroFlare::Runners::Complete*>(user_data);
   this_runner->game_configuration->handle_arbitrary_storyboard_screen_finished();
   return true;
}

bool Complete::on_arbitrary_storyboard_screen_activated_func(AllegroFlare::Routers::Standard* router, void* user_data)
{
   if (!(router))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Runners::Complete::on_arbitrary_storyboard_screen_activated_func]: error: guard \"router\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Runners::Complete::on_arbitrary_storyboard_screen_activated_func]: error: guard \"router\" not met");
   }
   if (!(user_data))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Runners::Complete::on_arbitrary_storyboard_screen_activated_func]: error: guard \"user_data\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Runners::Complete::on_arbitrary_storyboard_screen_activated_func]: error: guard \"user_data\" not met");
   }
   AllegroFlare::Runners::Complete* this_runner = static_cast<AllegroFlare::Runners::Complete*>(user_data);
   //this_runner->game_configuration->handle_arbitrary_storyboard_screen_activated(); // TODO: Is this necessary?

   // TODO: Consider how to pass along a storyboard identifier that should be loaded
   std::string storyboard_identifier = "[unset-storyboard_identifier]";
   // Set the pages of the storyboard to this storyboard
   // TODO: Consider if the arbitrary_storyboard_screen should be a pointer and created new here
   this_runner->arbitrary_storyboard_screen.get_storyboard_element_ref().set_pages(
      this_runner->game_configuration->create_arbitrary_storyboard_pages_by_identifier(storyboard_identifier)
   );
   return true;
}

void Complete::setup_router()
{
   if (!(primary_gameplay_screen))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Runners::Complete::setup_router]: error: guard \"primary_gameplay_screen\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Runners::Complete::setup_router]: error: guard \"primary_gameplay_screen\" not met");
   }
   router.set_screen_manager(&framework->get_screen_manager_ref());
   router.set_event_emitter(event_emitter);
   //router.set_pause_managed_gameplay_screen(primary_gameplay_screen); // TODO: Test this // TODO: Remove this line

   // Set handlers for route events
   router.set_on_route_event_unhandled_func(on_route_event_unhandled_func);
   router.set_on_route_event_unhandled_func_user_data(this);

   // Set the "load_level" handler
   router.set_load_level_handler([this](AllegroFlare::RouteEventDatas::Base* route_event_data) -> bool {
      // TODO: Fill in the body of this function:
      // TODO: Validate route_event_data is non-void
      // TODO: Validate route_event_data is StartLevel type

      AllegroFlare::RouteEventDatas::StartLevel *as_start_level =
         static_cast<AllegroFlare::RouteEventDatas::StartLevel*>(route_event_data);

      std::string level_identifier_to_load = as_start_level->get_level_identifier();

      // NOTE: Here, legacy systems will load_level_by_identifer as a call to the primary_gameplay_screen. Newer
      // systems will manage loading from the game_configuration. The latter system is preferible so that the list
      // of levels can be managed at the game_configuration level, and level-specific classes, (something like
      // YourGame::Levels:MyUndergroundLevel) do not become dependencies with the logic in the primary gameplay
      // screen. In a lot of cases (all?) the former legacy technique simply routes to the game_configuration
      // anyway. Updating them could be good. This design remains in flux.

      bool level_was_loaded_via_the_legacy_method = false;
      {
         if (!primary_gameplay_screen)
         {
            AllegroFlare::Logger::throw_error(
               "AllegroFlare::Runners::Complete::setup_router",
               "primary_gameplay_screen is nullptr"
            );
         }

         // TODO: Consider adding a begin_gameplay() after this step
         bool loaded_level = primary_gameplay_screen->load_level_by_identifier(level_identifier_to_load);
         if (loaded_level == true)
         {
            level_was_loaded_via_the_legacy_method = true;
            AllegroFlare::Logger::warn_from_once(
              "AllegroFlare::Runners::Complete::setup_router",
              "In the load_level_handler callback, the primary_gameplay_screen returned a created level after "
                 "calling load_level_by_identifier. This is legacy behavior. Consider moving the level loading "
                 "logic to the game_configuration instead, and have "
                 "primary_gameplay_screen->load_level_by_identifier return "
                 "false."
            );
         }
      }

      if (!level_was_loaded_via_the_legacy_method)
      {
         AllegroFlare::Logger::info_from(
           "AllegroFlare::Runners::Complete::setup_router",
           "In the load_level_handler callback, proceeding to load the level \"" + level_identifier_to_load + "\" "
              "through game_configuration."
         );

         this->game_configuration->load_level_by_identifier(level_identifier_to_load);
      }

      // TODO: Improve design and address a "return false" if the level did not load or does not exist
      // TODO: Address concern that return type of lambda may not be the same signature of the load_level_handler
      return true;
   });

   // Set the callbacks related related to GameSession
   router.set_on_create_new_session_func(
      [this](AllegroFlare::Routers::Standard* screen, void* user_data) {
         // TODO: Test this method

         AllegroFlare::GameSession &game_session = screen->get_game_session_ref();

         // TODO: Test this case
         if (game_session.get_game_progress_and_state_info() != nullptr)
         {
            AllegroFlare::Logger::info_from(
               "AllegroFlare::Runners::Complete::setup_router",
               "In the on_create_new_session_func callback, the game_session already has a created "
                  "\"game_progress_and_state_info\" member present. This is expected to be empty at this point, "
                  "with the member only being created once, here, at the beginning of the application's setup."
            );
         }

         // Create the game_progress_and_state_info saver/loader object. This is created on a per-game basis
         // by the configuration.
         AllegroFlare::GameProgressAndStateInfos::Base *game_progress_and_state_info_saver_loader =
            this->game_configuration->create_game_progress_and_state_info_saver_loader();

         // Assigns the created game progress and state info to the game session object
         game_session.set_game_progress_and_state_info(game_progress_and_state_info_saver_loader);
      }
   );
   //router.set_on_create_new_session_func_user_data(this);

   router.set_on_load_last_played_session_or_start_new_func(
      [this](AllegroFlare::Routers::Standard* screen, void* user_data) {
         // TODO: Test this method
         AllegroFlare::GameSession &game_session = screen->get_game_session_ref();
         // NOTE: user_data is not necessary
         this->game_configuration->load_last_played_session_or_start_new(&game_session);
      }
   );
   //router.set_on_load_last_played_session_or_start_new_func_user_data(this); // NOTE: user_data is not necessary

   // Set handlers for when the primary gameplay screen is finished
   // TODO: Rename these methods to "on_primary_gameplay_screen_finished"
   router.set_on_primary_gameplay_screen_finished_func(on_primary_gameplay_screen_finished_func);
   router.set_on_primary_gameplay_screen_finished_func_user_data(this);
   router.set_on_gameplay_paused_func(on_gameplay_paused_func);
   router.set_on_gameplay_paused_func_user_data(this);
   router.set_on_gameplay_unpaused_func(on_gameplay_unpaused_func);
   router.set_on_gameplay_unpaused_func_user_data(this);

   router.set_on_arbitrary_storyboard_screen_finished_func(on_arbitrary_storyboard_screen_finished_func);
   router.set_on_arbitrary_storyboard_screen_finished_func_user_data(this);

   router.set_on_arbitrary_storyboard_screen_activated_func(on_arbitrary_storyboard_screen_activated_func);
   router.set_on_arbitrary_storyboard_screen_activated_func_user_data(this);

   //router.set_on_before_activate_screen_func(AllegroFlare::Runners::Complete::on_before_activate_screen_func);
   //router.set_on_before_activate_screen_func_user_data(this);
   router.set_on_before_activate_screen_func(
      [this](std::string activating, std::string current, AllegroFlare::Routers::Base*, void*) {
         //: std::function<void(
         //std::string, std::string, AllegroFlare::Routers::Base*, void*
         //)>
         this->game_configuration->before_activate_screen_callback(activating, current);
      });
   router.set_on_before_activate_screen_func_user_data(this);

   // When loading save file content
   router.set_on_load_save_file_content_into_gameplay_func(
      // TODO: Test this callback
      // TODO: Ensure this callback is thoroughly vetted with the right purpose. It was thrown together ad-hoc for
      // the purpose of this code block, but might not fully contain the comprehensive solution expected. Please
      // review.
      // TODO: Determine if this callback func signature needs to be tweaked with more proper arguments
      [this](AllegroFlare::Routers::Standard* router, void* user_data) {
         if (!this->game_configuration)
         {
            AllegroFlare::Logger::throw_error(THIS_CLASS_AND_METHOD_NAME,
               "In router.on_load_save_file_content_into_gameplay_func lambda, a game_configuration is "
               "required and expected but is not present."
            );
         }

         // TODO: Obtain save file content to pass down into method
         std::string save_file_content = "{}";
         this->game_configuration->load_save_file_content_into_gameplay(save_file_content);
      });
   router.set_on_load_save_file_content_into_gameplay_func_user_data(this);

   /*
     type: std::function<void(AllegroFlare::Routers::Standard*, void*)>
     init_with: '{}'
     getter: true
     setter: true

   - name: on_load_save_file_content_into_gameplay_user_data
     type: void*
     init_with: nullptr
     getter: true
     setter: true
   */


   // Set the routes
   router.register_screen(
      AllegroFlare::Routers::Standard::INTRO_LOGOS_SCREEN_IDENTIFIER,
      &intro_logos_screen
   );
   router.register_screen(
      AllegroFlare::Routers::Standard::INTRO_STORYBOARD_SCREEN_IDENTIFIER,
      &intro_storyboard_screen
   );
   router.register_screen(
      AllegroFlare::Routers::Standard::TITLE_SCREEN_IDENTIFIER,
      &title_screen
   );
   router.register_screen(
      AllegroFlare::Routers::Standard::ACHIEVEMENTS_SCREEN_IDENTIFIER,
      &achievements_screen
   );
   router.register_screen(
      AllegroFlare::Routers::Standard::DISPLAY_SETTINGS_SCREEN_IDENTIFIER,
      &display_settings_screen
   );
   router.register_screen(
      AllegroFlare::Routers::Standard::VERSION_SCREEN_IDENTIFIER,
      &version_screen
   );
   router.register_screen(
      AllegroFlare::Routers::Standard::NEW_GAME_INTRO_STORYBOARD_SCREEN_IDENTIFIER,
      &new_game_intro_storyboard_screen
   );
   router.register_screen(
      AllegroFlare::Routers::Standard::LEVEL_SELECT_SCREEN_IDENTIFIER,
      &level_select_screen
   );
   router.register_screen(
      AllegroFlare::Routers::Standard::ARBITRARY_STORYBOARD_SCREEN_IDENTIFIER,
      &arbitrary_storyboard_screen
   );
   router.register_screen(
      AllegroFlare::Routers::Standard::GAME_OVER_SCREEN_IDENTIFIER,
      &game_over_screen
   );
   router.register_screen(
      AllegroFlare::Routers::Standard::GAME_WON_SCREEN_IDENTIFIER,
      &game_won_screen
   );
   router.register_screen(
      AllegroFlare::Routers::Standard::SETTINGS_SCREEN_IDENTIFIER,
      &settings_screen
   );
   router.register_screen(
      AllegroFlare::Routers::Standard::GAME_WON_OUTRO_STORYBOARD_SCREEN_IDENTIFIER,
      &game_won_outro_storyboard_screen
   );
   router.register_screen(
      AllegroFlare::Routers::Standard::LOAD_A_SAVED_GAME_SCREEN_IDENTIFIER,
      &load_a_saved_game_screen
   );
   router.register_screen(
      AllegroFlare::Routers::Standard::CREDITS_SCREEN_IDENTIFIER,
      &rolling_credits_screen
   );
   router.register_screen(
      AllegroFlare::Routers::Standard::PRIMARY_GAMEPLAY_SCREEN_IDENTIFIER,
      primary_gameplay_screen
   );
   router.register_screen(
      AllegroFlare::Routers::Standard::PRIMARY_GAMEPLAY_SUBSCREEN_IDENTIFIER,
      primary_gameplay_subscreen
   );
   router.register_screen(
      AllegroFlare::Routers::Standard::PAUSE_SCREEN_IDENTIFIER,
      pause_screen
   );

   // Set the callbacks
   intro_logos_screen.set_on_finished_callback_func(
      [this](AllegroFlare::Screens::Storyboard* screen, void* data) {
         this->router.emit_route_event(
            AllegroFlare::Routers::Standard::EVENT_INTRO_LOGOS_SCREEN_FINISHED,
            nullptr,
            al_get_time()
         );
      }
   );
   intro_storyboard_screen.set_on_finished_callback_func(
      [this](AllegroFlare::Screens::Storyboard* screen, void* data) {
         this->router.emit_route_event(
            AllegroFlare::Routers::Standard::EVENT_INTRO_STORYBOARD_SCREEN_FINISHED,
            nullptr,
            al_get_time()
         );
      }
   );
   load_a_saved_game_screen.set_on_menu_choice_callback_func(
      [this](AllegroFlare::LoadASavedGame::Screen* screen, void* data) {
         // TODO: Handle here
         this->router.emit_route_event(
            AllegroFlare::Routers::Standard::EVENT_LOAD_A_SAVED_GAME,
            nullptr, // TODO: Pass along data required to determine which save data to load
            al_get_time()
         );
      }
   );
   load_a_saved_game_screen.set_on_erase_focused_save_slot_func(
      [this](AllegroFlare::LoadASavedGame::Screen* screen, void* data) {
         // TODO: Handle here
         (void)(this); // TODO: Consider if this argument could be removed
         AllegroFlare::Logger::info_from(
           "Router::setup_router",
           "in on_erase_focused_save_slot_func, Currently there is no action implemented on this callback"
        );
      }
   );
   load_a_saved_game_screen.set_on_exit_callback_func(
      [this](AllegroFlare::LoadASavedGame::Screen* screen, void* data) {
         this->router.emit_route_event(
            AllegroFlare::Routers::Standard::EVENT_ACTIVATE_TITLE_SCREEN,
            nullptr,
            al_get_time()
         );
      }
   );
   new_game_intro_storyboard_screen.set_on_finished_callback_func(
      [this](AllegroFlare::Screens::Storyboard* screen, void* data) {
         this->router.emit_route_event(
            AllegroFlare::Routers::Standard::EVENT_NEW_GAME_INTRO_STORYBOARD_SCREEN_FINISHED,
            nullptr,
            al_get_time()
         );
      }
   );
   level_select_screen.set_on_menu_choice_callback_func(
      [this](AllegroFlare::Screens::LevelSelectScreen* screen, void* data) {
         // TODO: validate "screen" is non-void

         std::string selected_menu_option_value = screen->infer_current_menu_option_value();

         AllegroFlare::RouteEventDatas::StartLevel *route_event_data = new AllegroFlare::RouteEventDatas::StartLevel;
         route_event_data->set_level_identifier(selected_menu_option_value);

         this->router.emit_route_event(
            AllegroFlare::Routers::Standard::EVENT_START_LEVEL,
            route_event_data,
            al_get_time()
         );
      }
   );
   arbitrary_storyboard_screen.set_on_finished_callback_func(
      [this](AllegroFlare::Screens::Storyboard* screen, void* data) {
         this->router.emit_route_event(
            AllegroFlare::Routers::Standard::EVENT_ARBITRARY_STORYBOARD_SCREEN_FINISHED,
            nullptr,
            al_get_time()
         );
      }
   );
   primary_gameplay_screen->set_on_finished_callback_func(
      [this](AllegroFlare::Screens::Gameplay* screen, void* data) {
         this->router.emit_route_event(
            AllegroFlare::Routers::Standard::EVENT_PRIMARY_GAMEPLAY_SCREEN_FINISHED,
            nullptr,
            al_get_time()
         );
      }
   );
   settings_screen.set_on_exit_callback_func(
      [this](AllegroFlare::Screens::SettingsScreen* screen, void* data) {
         this->router.emit_route_event(
            AllegroFlare::Routers::Standard::EVENT_ACTIVATE_TITLE_SCREEN, // NOTE: If the settings screen is
                                                                          // made accessible during gameplay,
                                                                          // this event will need to modified
                                                                          // for that case
            nullptr,
            al_get_time()
         );
      }
   );
   game_won_screen.set_on_submit_callback_func(
      [this](AllegroFlare::Screens::GameWonScreen* screen, void* data) {
         // TODO: validate "screen" is non-void

         this->router.emit_route_event(
            AllegroFlare::Routers::Standard::EVENT_ACTIVATE_TITLE_SCREEN,
            nullptr,
            al_get_time()
         );
      }
   );
   game_over_screen.set_on_menu_choice_callback_func(
      [this](AllegroFlare::Screens::GameOverScreen* screen, void* data) {
         // TODO: validate "screen" is non-void

         std::string menu_choice = screen->infer_current_menu_option_value();

         if (menu_choice == "try_again")
         {
            this->router.emit_route_event(
               AllegroFlare::Routers::Standard::EVENT_CONTINUE_FROM_LAST_SAVE, // NOTE: This event currently does not
                                                                               // have an effect
               nullptr,
               al_get_time()
            );
         }
         else if (menu_choice == "start_title_screen")
         {
            this->router.emit_route_event(
               AllegroFlare::Routers::Standard::EVENT_ACTIVATE_TITLE_SCREEN, // TODO: Have this activate a
                                                                             // confirmation dialog
               nullptr,
               al_get_time()
            );
         }
         else
         {
            AllegroFlare::Logger::throw_error("Boobaz", "buzz");
         }
      }
   );
   game_won_outro_storyboard_screen.set_on_finished_callback_func(
      [this](AllegroFlare::Screens::Storyboard* screen, void* data) {
         this->router.emit_route_event(
            AllegroFlare::Routers::Standard::EVENT_GAME_WON_OUTRO_STORYBOARD_SCREEN_FINISHED,
            nullptr,
            al_get_time()
         );
      }
   );
   rolling_credits_screen.set_on_finished_callback_func(
      [this](AllegroFlare::Screens::RollingCredits* screen, void* data) {
         this->router.emit_route_event(
            AllegroFlare::Routers::Standard::EVENT_CREDITS_SCREEN_FINISHED,
            nullptr,
            al_get_time()
         );
      }
   );
   title_screen.set_on_finished_callback_func(
      [this](AllegroFlare::Screens::TitledMenuScreen* screen, void* data) {
         this->router.emit_route_event(
            AllegroFlare::Routers::Standard::EVENT_TITLE_SCREEN_FINISHED,
            nullptr,
            al_get_time()
         );
      }
   );
   title_screen.set_on_menu_choice_callback_func(
      [this](AllegroFlare::Screens::TitledMenuScreen* screen, std::string menu_choice, void* data) {
         //std::string menu_choice = screen->infer_current_menu_option_value();

         if (menu_choice == "start_new_game")
         {
            // TODO: If current game session is valid and has a running GameProgressAndSaveInfo,
            // Emit a confirmation dialog "this will destroy the current game, do you wish to
            // continue" OR move the gamer to a "pick a save slot to start new game" screen
            this->router.emit_route_event(
               AllegroFlare::Routers::Standard::EVENT_START_NEW_GAME,
               nullptr,
               al_get_time()
            );
         }
         else if (menu_choice == "continue_from_last_save")
         {
            // TODO: Consider this implementation is unclear and my not be ideal (it's a license to change it)
            this->game_configuration->load_game_progress_and_state_info_into_universe(); // was "continue_from_last_save"
            this->router.emit_route_event(
               AllegroFlare::Routers::Standard::EVENT_ACTIVATE_PRIMARY_GAMEPLAY_SCREEN,
               nullptr,
               al_get_time()
            );
         }
         else if (menu_choice == "quit")
         {
            this->router.emit_route_event(
               AllegroFlare::Routers::Standard::EVENT_EXIT_GAME,
               nullptr,
               al_get_time()
            );
         }
         else if (menu_choice == "goto_load_a_saved_game_screen")
         {
            this->router.emit_route_event(
               AllegroFlare::Routers::Standard::EVENT_ACTIVATE_LOAD_A_SAVED_GAME_SCREEN,
               nullptr,
               al_get_time()
            );
         }
         else if (menu_choice == "goto_achievements_screen")
         {
            this->router.emit_route_event(
               AllegroFlare::Routers::Standard::EVENT_ACTIVATE_ACHIEVEMENTS_SCREEN,
               nullptr,
               al_get_time()
            );
         }
         else if (menu_choice == "goto_display_settings_screen")
         {
            this->router.emit_route_event(
               AllegroFlare::Routers::Standard::EVENT_ACTIVATE_DISPLAY_SETTINGS_SCREEN,
               nullptr,
               al_get_time()
            );
         }
         else if (menu_choice == "goto_version_screen")
         {
            this->router.emit_route_event(
               AllegroFlare::Routers::Standard::EVENT_ACTIVATE_VERSION_SCREEN,
               nullptr,
               al_get_time()
            );
         }
         else if (menu_choice == "goto_settings_screen")
         {
            this->router.emit_route_event(
               AllegroFlare::Routers::Standard::EVENT_ACTIVATE_SETTINGS_SCREEN,
               nullptr,
               al_get_time()
            );
         }
         else if (menu_choice == "goto_credits_screen")
         {
            this->router.emit_route_event(
               AllegroFlare::Routers::Standard::EVENT_ACTIVATE_CREDITS_SCREEN,
               nullptr,
               al_get_time()
            );
         }
         else
         {
            AllegroFlare::Logger::throw_error(
               "AllegroFlare::Runners::Complete::setup_router",
               "Within the definition for title_screen.on_menu_choice_callback_func, there is no case to handle the "
                  "menu_choice \"" + menu_choice + "\"."
            );
         }
      }
   );
   achievements_screen.set_on_exit_callback_func(
      [this](AllegroFlare::Screens::Achievements* screen, void* data) {
         // TODO: This should be a push/pop'd screen
         this->router.emit_route_event(
            AllegroFlare::Routers::Standard::EVENT_ACTIVATE_TITLE_SCREEN,
            nullptr,
            al_get_time()
         );
      }
   );
   display_settings_screen.set_on_exit_callback_func(
      [this](AllegroFlare::Screens::DisplaySettings* screen, void* data) {
         // TODO: This should be a push/pop'd screen
         this->router.emit_route_event(
            AllegroFlare::Routers::Standard::EVENT_ACTIVATE_TITLE_SCREEN,
            nullptr,
            al_get_time()
         );
      }
   );
   version_screen.set_on_exit_callback_func(
      [this](AllegroFlare::Screens::Version* screen, void* data) {
         // TODO: This should be a push/pop'd screen
         this->router.emit_route_event(
            AllegroFlare::Routers::Standard::EVENT_ACTIVATE_TITLE_SCREEN,
            nullptr,
            al_get_time()
         );
      }
   );

   return;
}

void Complete::run(AllegroFlare::GameConfigurations::Complete* game_configuration, std::string deployment_environment_mode)
{
   if (!(game_configuration))
   {
      std::stringstream error_message;
      error_message << "[AllegroFlare::Runners::Complete::run]: error: guard \"game_configuration\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("[AllegroFlare::Runners::Complete::run]: error: guard \"game_configuration\" not met");
   }
   // setup the framework
   AllegroFlare::Frameworks::Full *framework = new AllegroFlare::Frameworks::Full();
   framework->set_deployment_environment(deployment_environment_mode);
   //if (disable_escape_key_will_shutdown) framework.disable_escape_key_will_shutdown();
   framework->initialize();

   // instantiate our actual game runner
   AllegroFlare::Runners::Complete runner(
      framework,
      &framework->get_event_emitter_ref(),
      &framework->get_bitmap_bin_ref(),
      &framework->get_font_bin_ref(),
      &framework->get_sample_bin_ref(),
      &framework->get_model_bin_ref(),
      game_configuration
   );
   runner.initialize();
   framework->register_screen("runner", &runner);

   framework->run_loop();

   runner.destroy();

   delete framework;
   return;
}


} // namespace Runners
} // namespace AllegroFlare


