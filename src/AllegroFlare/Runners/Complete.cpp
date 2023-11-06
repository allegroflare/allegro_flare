

#include <AllegroFlare/Runners/Complete.hpp>

#include <AllegroFlare/Color.hpp>
#include <AllegroFlare/Elements/RollingCredits/SectionFactory.hpp>
#include <AllegroFlare/EventNames.hpp>
#include <AllegroFlare/Frameworks/Full.hpp>
#include <AllegroFlare/GameEventDatas/ScreenActivated.hpp>
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


Complete::Complete(AllegroFlare::Frameworks::Full* framework, AllegroFlare::EventEmitter* event_emitter, AllegroFlare::BitmapBin* bitmap_bin, AllegroFlare::FontBin* font_bin, AllegroFlare::ModelBin* model_bin)
   : AllegroFlare::Screens::Base(AllegroFlare::Runners::Complete::TYPE)
   , framework(framework)
   , event_emitter(event_emitter)
   , bitmap_bin(bitmap_bin)
   , font_bin(font_bin)
   , model_bin(model_bin)
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
   , primary_gameplay_screen()
   , game_configuration(nullptr)
   , solid_black_background(ALLEGRO_COLOR{0, 0, 0, 1})
   , release_info({})
   , initialized(false)
{
}


Complete::~Complete()
{
}


AllegroFlare::GameConfigurations::Complete* Complete::create_game_configuration()
{
   return new AllegroFlare::GameConfigurations::Complete(); // TODO: Replace this with a real configuration
}

void Complete::handle_game_event(AllegroFlare::GameEvent* game_event)
{
   // TODO: Handle top-level game events here
   if (game_event->is_type(AllegroFlare::GameEventDatas::ScreenActivated::NAME))
   {
      AllegroFlare::GameEventDatas::ScreenActivated* as =
        static_cast<AllegroFlare::GameEventDatas::ScreenActivated*>(game_event->get_data());

      // TODO: Handle game-specific logic for a after a screen switch
   }
   return;
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
   handle_game_event(game_event);
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
   // Create the resources
   AllegroFlare::Achievements &achievements = framework->get_achievements_ref();
   AllegroFlare::AudioController &audio_controller = framework->get_audio_controller_ref();

   // Create a storyboard factory and page factory
   AllegroFlare::StoryboardFactory storyboard_factory;
   storyboard_factory.set_font_bin(font_bin);
   storyboard_factory.set_event_emitter(event_emitter);
   AllegroFlare::StoryboardPageFactory page_factory;
   page_factory.set_font_bin(font_bin);
   page_factory.set_bitmap_bin(bitmap_bin);
   page_factory.set_model_bin(model_bin);

   // Setup our router
   setup_router();

   // Set the framework to use our router
   framework->set_router(&router);

   // TODO: Create the game configuration for our game
   // Setup the configuration
   game_configuration = create_game_configuration();

   // Fill our dialog bank
   framework->set_dialog_system_dialog_node_bank(game_configuration->build_dialog_bank_by_identifier());

   // TODO: Setup achievements
   achievements.set_achievements(game_configuration->build_achievements());

   // TODO: Setup intro logos screen
   intro_logos_screen.set_event_emitter(event_emitter);
   intro_logos_screen.set_font_bin(font_bin);
   intro_logos_screen.set_auto_advance(true);
   intro_logos_screen.set_background(&solid_black_background);
   intro_logos_screen.initialize();
   intro_logos_screen.get_storyboard_element_ref().set_pages(
      game_configuration->create_intro_logos_storyboard_pages()
   );

   // TODO: Setup intro storyboard screen
   intro_storyboard_screen.set_event_emitter(event_emitter);
   intro_storyboard_screen.set_font_bin(font_bin);
   intro_storyboard_screen.set_auto_advance(true);
   intro_storyboard_screen.set_background(&solid_black_background);
   intro_storyboard_screen.initialize();
   intro_storyboard_screen.get_storyboard_element_ref().set_pages(
      game_configuration->create_intro_storyboard_pages()
   );

   // TODO: Setup title screen
   title_screen.set_event_emitter(event_emitter);
   title_screen.set_menu_options(game_configuration->build_title_screen_menu_options());
   title_screen.set_font_bin(font_bin);
   // TODO: Update this text to include the copyright symbol
   std::string copyright_text = "(c) 2023 CLUBCATT Games         clubcatt.com         version " + release_info.get_version();
   title_screen.set_copyright_text(copyright_text);
   title_screen.set_background(&solid_black_background);
   //title_screen.initialize(); // NOTE: Initialization is not necessary for this screen

   // TODO: Setup achievements screen
   achievements_screen.set_achievements(&achievements);
   achievements_screen.set_event_emitter(event_emitter);
   achievements_screen.set_font_bin(font_bin);
   achievements_screen.set_background(&solid_black_background);
   achievements_screen.initialize();

   // TODO: Setup version screen
   version_screen.set_bitmap_bin(bitmap_bin);
   version_screen.set_font_bin(font_bin);
   version_screen.set_model_bin(model_bin);
   version_screen.set_event_emitter(event_emitter);
   version_screen.set_background(&solid_black_background);
   version_screen.initialize();

   // TODO: Setup new game intro storyboard screen
   new_game_intro_storyboard_screen.set_event_emitter(event_emitter);
   new_game_intro_storyboard_screen.set_font_bin(font_bin);
   new_game_intro_storyboard_screen.set_background(&solid_black_background);
   new_game_intro_storyboard_screen.initialize();
   new_game_intro_storyboard_screen.get_storyboard_element_ref().set_pages(
      game_configuration->create_new_game_intro_storyboard_pages()
   );

   // TODO: Setup load a saved game screen
   load_a_saved_game_screen.set_event_emitter(event_emitter);
   load_a_saved_game_screen.set_bitmap_bin(bitmap_bin);
   load_a_saved_game_screen.set_font_bin(font_bin);
   load_a_saved_game_screen.set_model_bin(model_bin); // Currently not used, but required
   load_a_saved_game_screen.initialize();

   load_a_saved_game_screen.set_background(&solid_black_background);
   load_a_saved_game_screen.set_save_slots({
      new AllegroFlare::LoadASavedGame::SaveSlots::Empty(), // TODO: Fill this list with items from save file
      new AllegroFlare::LoadASavedGame::SaveSlots::Empty(),
      new AllegroFlare::LoadASavedGame::SaveSlots::Empty(),
   });


   // TODO: Setup level select screen
   level_select_screen.set_event_emitter(event_emitter);
   level_select_screen.set_bitmap_bin(bitmap_bin);
   level_select_screen.set_font_bin(font_bin);
   //level_select_screen.set_levels_list({
      //{ "Candy Kingdom", "candy_kingdom" },
      //{ "Cherry Blossom Grove", "cherry_blossom_grove" },
      //{ "Bubble Pop Bay", "bubble_pop_bay" },
      //{ "Neon City Nights", "neon_city_nights" },
      //{ "Wonderland Woods", "wonderland_woods" },
   //});
   level_select_screen.set_levels_list(
      game_configuration->build_level_list_for_level_select_screen_by_identifier("discarded-for-now")
   );
   level_select_screen.set_background(&solid_black_background);
   level_select_screen.initialize();

   // TODO: Setup game over screen
   game_over_screen.set_event_emitter(event_emitter);
   game_over_screen.set_font_bin(font_bin);
   game_over_screen.set_background(&solid_black_background);
   game_over_screen.initialize();

   // TODO: Setup game won screen
   game_won_screen.set_font_bin(font_bin);
   game_won_screen.set_background(&solid_black_background);
   //game_won_screen.initialize(); // NOTE: Initialization is not necessary for this screen

   // TODO: Setup game won outro storyboard screen
   game_won_outro_storyboard_screen.set_event_emitter(event_emitter);
   game_won_outro_storyboard_screen.set_background(&solid_black_background);
   game_won_outro_storyboard_screen.initialize();

   // TODO: Setup the settings screen
   settings_screen.set_event_emitter(event_emitter); // TODO: See if this is necessary
   settings_screen.set_bitmap_bin(bitmap_bin); // Currently not used, but required
   settings_screen.set_font_bin(font_bin);
   settings_screen.set_model_bin(model_bin); // Currently not used, but required
   settings_screen.set_background(&solid_black_background);
   settings_screen.initialize();

   // TODO: Setup rolling credits screen
   AllegroFlare::Elements::RollingCredits::SectionFactory section_factory;
   rolling_credits_screen.set_event_emitter(event_emitter); // TODO: See if this is necessary
   rolling_credits_screen.set_font_bin(font_bin);
   rolling_credits_screen.set_background(&solid_black_background);
   rolling_credits_screen.set_sections(
      game_configuration->build_rolling_credits_sections()
   );
   /*
   {
      section_factory.create_spacer(),

      section_factory.create_text(
         "A game by Mark Oates"
      ),

      section_factory.create_spacer(),

      section_factory.create_text(
         "KrampusHack 2023\nhttps://tins.amarillion.org/krampu23"
      ),

      section_factory.create_section_spacer(),

      section_factory.create_header("Programming"),
      section_factory.create_column_with_labels({
         { "Made with", "Allegro (5.2.9)" },
         {          "", "https://liballeg.org/" },
         //{          "", "by Allegro Developers" },
         { "Framework", "AllegroFlare (0.8.11-wip)" },
         {          "", "https://github.com/allegroflare/allegro_flare" },
         {          "", "by Mark Oates" },
      }),

      section_factory.create_section_spacer(),
   });
   */
   rolling_credits_screen.append_sections(section_factory.create_standard_disclaimers_text());
   rolling_credits_screen.initialize();

   // Setup our main gameplay screen
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
   router.set_screen_manager(&framework->get_screen_manager_ref());
   router.set_event_emitter(event_emitter);

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
      &primary_gameplay_screen
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
   /* // TODO: Consider uncommented this
   primary_gameplay_screen.set_on_finished_callback_func(
      [this]([[COMPONENT_NAME_FIRST_FRAGMENT]]::Gameplay::Screen* screen, void* data) {
         this->router.emit_route_event(
            AllegroFlare::Routers::Standard::EVENT_PRIMARY_GAMEPLAY_SCREEN_FINISHED,
            nullptr,
            al_get_time()
         );
      }
   );
   */
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

void Complete::run(std::string deployment_environment_mode)
{
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
      &framework->get_model_bin_ref()
   );
   runner.initialize();
   framework->register_screen("runner", &runner);

   framework->run_loop();

   delete framework;
   return;
}


} // namespace Runners
} // namespace AllegroFlare


