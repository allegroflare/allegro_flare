#pragma once

#define ALLEGRO_FLARE_EVENT_PROGRAM_START               ALLEGRO_GET_EVENT_TYPE('F','P','g','S')
#define ALLEGRO_FLARE_EVENT_SHUTDOWN_PROGRAM            ALLEGRO_GET_EVENT_TYPE('F','S','d','n')
#define ALLEGRO_FLARE_EVENT_EXIT_GAME                   ALLEGRO_GET_EVENT_TYPE('F','E','x','t')
#define ALLEGRO_FLARE_EVENT_START_NEW_GAME              ALLEGRO_GET_EVENT_TYPE('F','S','t','r')
#define ALLEGRO_FLARE_EVENT_SELECT_LEVEL                ALLEGRO_GET_EVENT_TYPE('F','S','l','l')
#define ALLEGRO_FLARE_EVENT_START_TITLE_SCREEN          ALLEGRO_GET_EVENT_TYPE('F','T','t','l')
#define ALLEGRO_FLARE_EVENT_GAME_WON                    ALLEGRO_GET_EVENT_TYPE('F','G','m','w')
#define ALLEGRO_FLARE_EVENT_CONTINUE_GAME               ALLEGRO_GET_EVENT_TYPE('F','C','t','n')
#define ALLEGRO_FLARE_EVENT_PAUSE_GAME                  ALLEGRO_GET_EVENT_TYPE('F','P','w','s')
#define ALLEGRO_FLARE_EVENT_UNPAUSE_GAME                ALLEGRO_GET_EVENT_TYPE('F','U','n','p')
#define ALLEGRO_FLARE_EVENT_PLAY_MUSIC_TRACK            ALLEGRO_GET_EVENT_TYPE('F','S','t','m')
#define ALLEGRO_FLARE_EVENT_PLAY_SOUND_EFFECT           ALLEGRO_GET_EVENT_TYPE('F','P','s','f')
#define ALLEGRO_FLARE_EVENT_VIRTUAL_CONTROL_BUTTON_DOWN ALLEGRO_GET_EVENT_TYPE('F','V','b','d')
#define ALLEGRO_FLARE_EVENT_VIRTUAL_CONTROL_BUTTON_UP   ALLEGRO_GET_EVENT_TYPE('F','V','b','u')
#define ALLEGRO_FLARE_EVENT_VIRTUAL_CONTROL_AXIS_CHANGE ALLEGRO_GET_EVENT_TYPE('F','V','a','c')
#define ALLEGRO_FLARE_EVENT_UNLOCK_ACHIEVEMENT          ALLEGRO_GET_EVENT_TYPE('F','U','l','A')
#define ALLEGRO_FLARE_EVENT_ACHIEVEMENT_UNLOCKED        ALLEGRO_GET_EVENT_TYPE('F','A','c','U')
#define ALLEGRO_FLARE_EVENT_SWITCH_SCREEN               ALLEGRO_GET_EVENT_TYPE('F','s','m','s')

#define ALLEGRO_FLARE_EVENT_SHOW_INPUT_HINTS_BAR        ALLEGRO_GET_EVENT_TYPE('F','S','I','h')
#define ALLEGRO_FLARE_EVENT_HIDE_INPUT_HINTS_BAR        ALLEGRO_GET_EVENT_TYPE('F','H','I','h')
#define ALLEGRO_FLARE_EVENT_SET_INPUT_HINTS_BAR         ALLEGRO_GET_EVENT_TYPE('F','S','I','h')

// User's Events in their game
#define ALLEGRO_FLARE_EVENT_GAME_EVENT                  ALLEGRO_GET_EVENT_TYPE('F','E','G','E')

// Consider:
// { 
//    std::string event_identifier
//    intptr_t allegro_event
// }

// Also Consider:
// ALLEGRO_FLARE_EVENT_INCREMENT_PLAYER_STAT


