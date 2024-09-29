#pragma once


#include <AllegroFlare/BitmapBin.hpp>
#include <AllegroFlare/EventEmitter.hpp>
#include <AllegroFlare/FontBin.hpp>
#include <AllegroFlare/GameEvent.hpp>
#include <AllegroFlare/GameEventDatas/Base.hpp>
#include <AllegroFlare/Inventory.hpp>
#include <AllegroFlare/InventoryIndex.hpp>
#include <AllegroFlare/Prototypes/FixedRoom2D/Configuration.hpp>
#include <AllegroFlare/Prototypes/FixedRoom2D/Cursor.hpp>
#include <AllegroFlare/Prototypes/FixedRoom2D/DialogSystem.hpp>
#include <AllegroFlare/Prototypes/FixedRoom2D/Entities/Base.hpp>
#include <AllegroFlare/Prototypes/FixedRoom2D/EntityCollectionHelper.hpp>
#include <AllegroFlare/Prototypes/FixedRoom2D/Room.hpp>
#include <AllegroFlare/Prototypes/FixedRoom2D/Script.hpp>
#include <AllegroFlare/Prototypes/FixedRoom2D/ScriptRunner.hpp>
#include <AllegroFlare/Shaders/Base.hpp>
#include <allegro5/allegro_font.h>
#include <map>
#include <set>
#include <string>
#include <vector>


namespace AllegroFlare
{
   namespace Prototypes
   {
      namespace FixedRoom2D
      {
         class FixedRoom2D
         {
         public:
            static constexpr char* DEFAULT_STANDARD_DIALOG_BOX_FONT_NAME = (char*)"Inter-Regular.ttf";
            static constexpr int DEFAULT_STANDARD_DIALOG_BOX_FONT_SIZE = -36;

         private:
            AllegroFlare::BitmapBin* bitmap_bin;
            AllegroFlare::FontBin* font_bin;
            AllegroFlare::EventEmitter* event_emitter;
            AllegroFlare::InventoryIndex inventory_index;
            AllegroFlare::Inventory af_inventory;
            AllegroFlare::Inventory flags;
            std::map<std::string, AllegroFlare::Prototypes::FixedRoom2D::Entities::Base*> entity_dictionary;
            std::map<std::string, AllegroFlare::Prototypes::FixedRoom2D::Room*> room_dictionary;
            std::map<std::string, std::string> entity_room_associations;
            std::map<std::string, AllegroFlare::Prototypes::FixedRoom2D::Script> script_dictionary;
            AllegroFlare::Prototypes::FixedRoom2D::ScriptRunner script_runner;
            AllegroFlare::Prototypes::FixedRoom2D::EntityCollectionHelper entity_collection_helper;
            AllegroFlare::Prototypes::FixedRoom2D::Cursor cursor;
            std::string starting_room_identifier;
            AllegroFlare::Prototypes::FixedRoom2D::Room* current_room;
            AllegroFlare::Shaders::Base* room_shader;
            bool initialized;
            AllegroFlare::Prototypes::FixedRoom2D::DialogSystem dialog_system;
            bool paused;
            std::set<std::string> subscribed_to_game_event_names;
            std::string standard_dialog_box_font_name;
            int standard_dialog_box_font_size;
            void process_interaction_event(AllegroFlare::GameEventDatas::Base* game_event_data=nullptr);
            void process_script_event(AllegroFlare::GameEventDatas::Base* game_event_data=nullptr);
            void emit_interaction_event(std::string item_dictionary_name="[unset-item_dictionary_name]", float cursor_x=0.0, float cursor_y=0.0);
            void move_cursor_within_room(float distance_x=0.0, float distance_y=0.0, std::vector<AllegroFlare::Prototypes::FixedRoom2D::Entities::Base*> entities_in_this_room={});
            ALLEGRO_FONT* obtain_empty_room_font();

         protected:


         public:
            FixedRoom2D(AllegroFlare::BitmapBin* bitmap_bin=nullptr, AllegroFlare::FontBin* font_bin=nullptr, AllegroFlare::EventEmitter* event_emitter=nullptr, std::string standard_dialog_box_font_name=DEFAULT_STANDARD_DIALOG_BOX_FONT_NAME, int standard_dialog_box_font_size=DEFAULT_STANDARD_DIALOG_BOX_FONT_SIZE);
            ~FixedRoom2D();

            void set_bitmap_bin(AllegroFlare::BitmapBin* bitmap_bin);
            void set_event_emitter(AllegroFlare::EventEmitter* event_emitter);
            void set_room_shader(AllegroFlare::Shaders::Base* room_shader);
            void set_standard_dialog_box_font_name(std::string standard_dialog_box_font_name);
            void set_standard_dialog_box_font_size(int standard_dialog_box_font_size);
            AllegroFlare::Shaders::Base* get_room_shader() const;
            std::string get_standard_dialog_box_font_name() const;
            int get_standard_dialog_box_font_size() const;
            AllegroFlare::Prototypes::FixedRoom2D::ScriptRunner &get_script_runner_ref();
            AllegroFlare::Prototypes::FixedRoom2D::EntityCollectionHelper &get_entity_collection_helper_ref();
            void set_font_bin(AllegroFlare::FontBin* font_bin=nullptr);
            std::set<std::string> get_subscribed_to_game_event_names();
            bool is_subscribed_to_game_event_name(std::string game_event_name="[unset-game_event_name]");
            void initialize();
            bool load_configuration(AllegroFlare::Prototypes::FixedRoom2D::Configuration configuration={});
            bool enter_start_room();
            bool load_gametest_configuration();
            void update();
            bool enter_room(std::string room_name="[unset-room_name]");
            void unhover_any_and_all_entities();
            std::string get_current_room_dictionary_name(AllegroFlare::Prototypes::FixedRoom2D::Room* room=nullptr);
            void render();
            void render_void_room();
            void process_subscribed_to_game_event(AllegroFlare::GameEvent* game_event=nullptr);
            void render_entities_in_current_room();
            std::vector<AllegroFlare::Prototypes::FixedRoom2D::Entities::Base*> get_entities_in_current_room();
            std::string get_dictionary_name_of_current_room();
            void suspend_all_rooms();
            void resume_all_rooms();
            void pause_game();
            void unpause_game();
            void dialog_cursor_up();
            void dialog_cursor_down();
            bool dialog_is_finished();
            void activate_primary_action();
            void interact_with_item_under_cursor();
            void emit_close_current_active_dialog_event();
            void move_cursor_up();
            void move_cursor_down();
            void move_cursor_left();
            void move_cursor_right();
            void move_cursor(float distance_x=0.0, float distance_y=0.0);
            void reset_cursor_to_default();
         };
      }
   }
}



