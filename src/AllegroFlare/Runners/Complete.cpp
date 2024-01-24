

#include <AllegroFlare/Runners/Complete.hpp>

#include <AllegroFlare/Color.hpp>
#include <AllegroFlare/Elements/Backgrounds/ClearToColor.hpp>
#include <AllegroFlare/Frameworks/Full.hpp>
#include <AllegroFlare/GameSession.hpp>
#include <AllegroFlare/LoadASavedGame/SaveSlots/Empty.hpp>
#include <AllegroFlare/Logger.hpp>
#include <AllegroFlare/RouteEventDatas/StartLevel.hpp>
#include <AllegroFlare/StoryboardFactory.hpp>
#include <iostream>
#include <sstream>
#include <stdexcept>


namespace AllegroFlare
{
namespace Runners
{


Complete::Complete(AllegroFlare::Frameworks::Full* framework, AllegroFlare::EventEmitter* event_emitter, AllegroFlare::BitmapBin* bitmap_bin, AllegroFlare::FontBin* font_bin, AllegroFlare::ModelBin* model_bin, AllegroFlare::GameConfigurations::Complete* game_configuration)
   : AllegroFlare::Screens::Base(AllegroFlare::Runners::Complete::TYPE)
   , framework(framework)
   , event_emitter(event_emitter)
   , bitmap_bin(bitmap_bin)
   , font_bin(font_bin)
   , model_bin(model_bin)
   , game_configuration(game_configuration)
   , router()
   , intro_logos_screen()
   , intro_storyboard_screen()
   , title_screen()
   , achievements_screen()
   , version_screen()
   , load_a_saved_game_screen()
   , new_game_intro_storyboard_screen()
   , level_select_screen()
   , game_over_screen()
   , game_won_screen()
   , game_won_outro_storyboard_screen()
   , settings_screen()
   , rolling_credits_screen()
   , primary_gameplay_screen(nullptr)
   , shared_background(nullptr)
   , shared_foreground(nullptr)
   , release_info({})
   , initialized(false)
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


AllegroFlare::ModelBin* Complete::get_model_bin() const
{
   return model_bin;
}


void Complete::game_event_func(AllegroFlare::GameEvent* game_event)
{
   if (!(game_event))
   {
      std::stringstream error_message;
      error_message << "[Complete::game_event_func]: error: guard \"game_event\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Complete::game_event_func: error: guard \"game_event\" not met");
   }
   game_configuration->handle_game_event(game_event);
   return;
}

void Complete::initialize()
{
   if (!((!initialized)))
   {
      std::stringstream error_message;
      error_message << "[Complete::initialize]: error: guard \"(!initialized)\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Complete::initialize: error: guard \"(!initialized)\" not met");
   }
   if (!(framework))
   {
      std::stringstream error_message;
      error_message << "[Complete::initialize]: error: guard \"framework\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Complete::initialize: error: guard \"framework\" not met");
   }
   if (!(event_emitter))
   {
      std::stringstream error_message;
      error_message << "[Complete::initialize]: error: guard \"event_emitter\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Complete::initialize: error: guard \"event_emitter\" not met");
   }
   if (!(bitmap_bin))
   {
      std::stringstream error_message;
      error_message << "[Complete::initialize]: error: guard \"bitmap_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Complete::initialize: error: guard \"bitmap_bin\" not met");
   }
   if (!(font_bin))
   {
      std::stringstream error_message;
      error_message << "[Complete::initialize]: error: guard \"font_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Complete::initialize: error: guard \"font_bin\" not met");
   }
   if (!(model_bin))
   {
      std::stringstream error_message;
      error_message << "[Complete::initialize]: error: guard \"model_bin\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Complete::initialize: error: guard \"model_bin\" not met");
   }
   if (!(game_configuration))
   {
      std::stringstream error_message;
      error_message << "[Complete::initialize]: error: guard \"game_configuration\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Complete::initialize: error: guard \"game_configuration\" not met");
   }
   // Create some references for convenience
   AllegroFlare::Achievements &achievements = framework->get_achievements_ref();
   AllegroFlare::AudioController &audio_controller = framework->get_audio_controller_ref();

   // Create the shared background
   shared_background = game_configuration->create_shared_background();
   shared_foreground = game_configuration->create_shared_foreground();

   // Create the primary_gameplay_screen
   primary_gameplay_screen = game_configuration->create_primary_gameplay_screen(this);

   // Setup our router
   setup_router();

   // Set the framework to use our router
   framework->set_router(&router);

   // Fill our dialog bank
   framework->set_dialog_system_dialog_node_bank(game_configuration->build_dialog_bank_by_identifier());

   // Setup achievements
   achievements.set_achievements(game_configuration->build_achievements());

   // Setup intro logos screen (if empty, will simply be skipped)
   intro_logos_screen.set_event_emitter(event_emitter);
   intro_logos_screen.set_font_bin(font_bin);
   intro_logos_screen.set_auto_advance(true);
   intro_logos_screen.set_background(shared_background);
   intro_logos_screen.set_foreground(shared_foreground);
   intro_logos_screen.initialize();
   intro_logos_screen.get_storyboard_element_ref().set_pages(
      game_configuration->create_intro_logos_storyboard_pages()
   );

   // Setup intro storyboard screen (if empty, will simply be skipped)
   intro_storyboard_screen.set_event_emitter(event_emitter);
   intro_storyboard_screen.set_font_bin(font_bin);
   intro_storyboard_screen.set_auto_advance(true);
   intro_storyboard_screen.set_background(shared_background);
   intro_storyboard_screen.set_foreground(shared_foreground);
   intro_storyboard_screen.initialize();
   intro_storyboard_screen.get_storyboard_element_ref().set_pages(
      game_configuration->create_intro_storyboard_pages()
   );

   // Setup title screen
   title_screen.set_event_emitter(event_emitter);
   title_screen.set_menu_options(game_configuration->build_title_screen_menu_options());
   title_screen.set_font_bin(font_bin);
   title_screen.set_copyright_text(game_configuration->build_copyright_text(&release_info));
   title_screen.set_background(shared_background);
   title_screen.set_foreground(shared_foreground);
   //title_screen.initialize(); // NOTE: Initialization is not necessary for this screen

   // Setup achievements screen
   achievements_screen.set_achievements(&achievements);
   achievements_screen.set_event_emitter(event_emitter);
   achievements_screen.set_font_bin(font_bin);
   achievements_screen.set_background(shared_background);
   achievements_screen.set_foreground(shared_foreground);
   achievements_screen.initialize();

   // Setup version screen
   version_screen.set_bitmap_bin(bitmap_bin);
   version_screen.set_font_bin(font_bin);
   version_screen.set_model_bin(model_bin);
   version_screen.set_event_emitter(event_emitter);
   version_screen.set_background(shared_background);
   version_screen.initialize();

   // Setup new game intro storyboard screen
   new_game_intro_storyboard_screen.set_event_emitter(event_emitter);
   new_game_intro_storyboard_screen.set_font_bin(font_bin);
   new_game_intro_storyboard_screen.set_background(shared_background);
   new_game_intro_storyboard_screen.set_foreground(shared_foreground);
   new_game_intro_storyboard_screen.initialize();
   new_game_intro_storyboard_screen.get_storyboard_element_ref().set_pages(
      game_configuration->create_new_game_intro_storyboard_pages()
   );

   // Setup load a saved game screen
   load_a_saved_game_screen.set_event_emitter(event_emitter);
   load_a_saved_game_screen.set_bitmap_bin(bitmap_bin);
   load_a_saved_game_screen.set_font_bin(font_bin);
   load_a_saved_game_screen.set_model_bin(model_bin); // Currently not used, but required
   load_a_saved_game_screen.initialize();
   load_a_saved_game_screen.set_background(shared_background);
   load_a_saved_game_screen.set_foreground(shared_foreground);
   load_a_saved_game_screen.set_save_slots(game_configuration->build_save_slots_for_load_a_saved_game_screen());

   // TODO: Setup level select screen
   level_select_screen.set_event_emitter(event_emitter);
   level_select_screen.set_bitmap_bin(bitmap_bin);
   level_select_screen.set_font_bin(font_bin);
   level_select_screen.set_levels_list(
      // NOTE: if this list is empty, then the screen will automatically submit on activate
      game_configuration->build_level_list_for_level_select_screen_by_identifier("discarded-for-now")
   );
   level_select_screen.set_background(shared_background);
   level_select_screen.set_foreground(shared_foreground);
   level_select_screen.initialize();

   // TODO: Setup game over screen
   game_over_screen.set_event_emitter(event_emitter);
   game_over_screen.set_font_bin(font_bin);
   game_over_screen.set_background(shared_background);
   game_over_screen.set_foreground(shared_foreground);
   game_over_screen.initialize();

   // Setup game won screen
   game_won_screen.set_font_bin(font_bin);
   game_won_screen.set_background(shared_background);
   game_won_screen.set_foreground(shared_foreground);
   //game_won_screen.initialize(); // NOTE: Initialization is not necessary for this screen

   // Setup game won outro storyboard screen
   game_won_outro_storyboard_screen.set_event_emitter(event_emitter);
   game_won_outro_storyboard_screen.set_background(shared_background);
   game_won_outro_storyboard_screen.set_foreground(shared_foreground);
   game_won_outro_storyboard_screen.initialize();

   // Setup the settings screen
   settings_screen.set_event_emitter(event_emitter); // TODO: See if this is necessary
   settings_screen.set_bitmap_bin(bitmap_bin); // Currently not used, but required
   settings_screen.set_font_bin(font_bin);
   settings_screen.set_model_bin(model_bin); // Currently not used, but required
   settings_screen.set_background(shared_background);
   settings_screen.set_foreground(shared_foreground);
   settings_screen.initialize();

   // Setup rolling credits screen
   rolling_credits_screen.set_event_emitter(event_emitter); // TODO: See if this is necessary
   rolling_credits_screen.set_font_bin(font_bin);
   rolling_credits_screen.set_background(shared_background);
   rolling_credits_screen.set_foreground(shared_foreground);
   rolling_credits_screen.set_sections(game_configuration->build_rolling_credits_sections());
   rolling_credits_screen.initialize();

   // TODO: Setup our main gameplay screen
   //primary_gameplay_screen-
   /* TODO: Setup a gameplay screen
   primary_gameplay_screen.set_event_emitter(event_emitter);
   primary_gameplay_screen.set_bitmap_bin(bitmap_bin);
   primary_gameplay_screen.set_font_bin(font_bin);
   primary_gameplay_screen.set_model_bin(model_bin);
   primary_gameplay_screen.set_game_configuration(game_configuration); // TODO: Consider how to remove this dependency
   primary_gameplay_screen.initialize();
   */

   // TODO: Load up our sound effects and music tracks
   game_configuration->load_audio_controller();

   //primary_gameplay_screen = game_configuration->create_primary_gameplay_screen();

   return;
}

bool Complete::on_route_event_unhandled_func(uint32_t unhandled_event, AllegroFlare::Routers::Standard* router, void* user_data)
{
   if (!(router))
   {
      std::stringstream error_message;
      error_message << "[Complete::on_route_event_unhandled_func]: error: guard \"router\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Complete::on_route_event_unhandled_func: error: guard \"router\" not met");
   }
   if (!(user_data))
   {
      std::stringstream error_message;
      error_message << "[Complete::on_route_event_unhandled_func]: error: guard \"user_data\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Complete::on_route_event_unhandled_func: error: guard \"user_data\" not met");
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

void Complete::setup_router()
{
   if (!(primary_gameplay_screen))
   {
      std::stringstream error_message;
      error_message << "[Complete::setup_router]: error: guard \"primary_gameplay_screen\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Complete::setup_router: error: guard \"primary_gameplay_screen\" not met");
   }
   router.set_screen_manager(&framework->get_screen_manager_ref());
   router.set_event_emitter(event_emitter);
   router.set_pause_managed_gameplay_screen(primary_gameplay_screen); // TODO: Test this

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

      // TODO: Modify this design to emit a level loading event, instead of loading here explicitly.
      if (!primary_gameplay_screen)
      {
         AllegroFlare::Logger::throw_error(
            "AllegroFlare::Runners::Complete::setup_router",
            "primary_gameplay_screen is nullptr"
         );
      }

      primary_gameplay_screen->load_level_by_identifier(level_identifier_to_load);

      /* // TODO: Consider uncommenting this
      primary_gameplay_screen.load_level_by_identifier(level_identifier_to_load);
      */

      // TODO: Improve design and address a "return false" if the level did not load or does not exist
      // TODO: Address concern that return type of lambda may not be the same signature of the load_level_handler
      return true;
   });

   // Set the callbacks related related to GameSession
   router.set_on_create_new_session_func(
      [this](AllegroFlare::Routers::Standard* screen, void* user_data) {
         // TODO: Test this method
         AllegroFlare::GameSession &game_session = screen->get_game_session_ref();
         this->game_configuration->setup_new_game_progress_and_state_info(&game_session); // NOTE: user_data is not necessary
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
         AllegroFlare::Logger::info_from(
           "Router::setup_router",
           "in on_menu_choice_callback_func, Currently there is no action implemented on this callback"
        );
      }
   );
   load_a_saved_game_screen.set_on_erase_focused_save_slot_func(
      [this](AllegroFlare::LoadASavedGame::Screen* screen, void* data) {
         // TODO: Handle here
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
   ///* // TODO: Consider uncommented this
   primary_gameplay_screen->set_on_finished_callback_func(
      [this](AllegroFlare::Screens::Gameplay* screen, void* data) {
      //[this]([[COMPONENT_NAME_FIRST_FRAGMENT]]::Gameplay::Screen* screen, void* data) {
         this->router.emit_route_event(
            AllegroFlare::Routers::Standard::EVENT_PRIMARY_GAMEPLAY_SCREEN_FINISHED,
            nullptr,
            al_get_time()
         );
      }
   );
   //*/
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
      [this](AllegroFlare::Screens::TitleScreen* screen, void* data) {
         this->router.emit_route_event(
            AllegroFlare::Routers::Standard::EVENT_TITLE_SCREEN_FINISHED,
            nullptr,
            al_get_time()
         );
      }
   );
   title_screen.set_on_menu_choice_callback_func(
      [this](AllegroFlare::Screens::TitleScreen* screen, void* data) {
         std::string menu_choice = screen->infer_current_menu_option_value();

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
            this->game_configuration->continue_from_last_save();
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
            AllegroFlare::Logger::throw_error("Foobar", "baz");
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
      error_message << "[Complete::run]: error: guard \"game_configuration\" not met.";
      std::cerr << "\033[1;31m" << error_message.str() << " An exception will be thrown to halt the program.\033[0m" << std::endl;
      throw std::runtime_error("Complete::run: error: guard \"game_configuration\" not met");
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
      &framework->get_model_bin_ref(),
      game_configuration
   );
   runner.initialize();
   framework->register_screen("runner", &runner);

   framework->run_loop();

   delete framework;
   return;
}


} // namespace Runners
} // namespace AllegroFlare


