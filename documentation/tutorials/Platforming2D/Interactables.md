
making an object "interactable"


Simplest:

-> tag the object with INTERACTABLE_BY_PLAYER
-> when the player presses the button to interact, EntityCollecitonHelper::select_all_interactable_by_player_currently_colliding_with_player, and select the appropriate
interactable object (if any).


To add interaction input hints:

-> assume your object has a tmj_object_name
-> tag the object with INTERACTABLE_BY_PLAYER
-> in your Gameplay/Screen, consider having an override for:
   -> on_enter_player_controlled_entity_collision_with_interactable(player_controlled_entity, entity);
   -> on_exit_player_controlled_entity_collision_with_interactable(player_controlled_entity, entity);
   -> ... if you want to display input hints or something


When creating your player:

         player_character->set_on_interact_func(SomePlatformer::Gameplay::Screen::on_player_interacts);
         player_character->set_on_interact_func_user_data(this);


In your screen class, create `SomePlatformer::Gameplay::Screen`s callbacks `SomePlatformer::Gameplay::Screen::on_player_interacts`.  Might look something like this:


```
  - name: on_player_interacts
    static: true
    parameters:
      - name: player_character_ptr
        type: SomePlatformer::Entities::PlayerCharacter*
        default_argument: nullptr
      - name: user_data
        type: void*
        default_argument: nullptr
    guards: [ player_character_ptr, user_data ]
    body: |
      using namespace AllegroFlare::Prototypes::Platforming2D::EntityFlagNames;
      auto &player_character = *static_cast<SomePlatformer::Entities::PlayerCharacter*>(player_character_ptr);
      auto &screen = *static_cast<SomePlatformer::Gameplay::Screen*>(user_data);

      AllegroFlare::Prototypes::Platforming2D::EntityCollectionHelper collection_helper(&screen.get_entity_pool_ref());
      auto interactables = collection_helper.select_all_interactable_by_player_currently_colliding_with_player();
      if (interactables.empty())
      {
         // Do nothing
      }
      else
      {
         AllegroFlare::Prototypes::Platforming2D::Entities::Basic2D* interactable = interactables[0];
         std::string tmj_object_type = interactable->get(TMJ_OBJECT_TYPE);
         if (true==false) {}
         else if (tmj_object_type == JourneyOfTheCat::Entities::Signpost::TMJ_OBJECT_TYPE)
         {
            auto as = static_cast<JourneyOfTheCat::Entities::Signpost*>(interactable);
            std::string signpost_dialog_node_identifier_to_spawn = as->get_dialog_node_identifier();
            screen.get_event_emitter()->emit_activate_dialog_node_by_name_event(
                  signpost_dialog_node_identifier_to_spawn
               );
         }
      }

      return;
```



```
  - name: emit_show_input_hints_bar_event

  - name: emit_hide_input_hints_bar_event

  - name: emit_set_input_hints_bar_event
    parameters:
      - name: tokens
        type: std::vector<std::string>
        default_argument: '{}'
    body: |
      intptr_t data_to_pass = (intptr_t)(void *)(new std::vector<std::string>(tokens));
      emit_event(ALLEGRO_FLARE_EVENT_SET_INPUT_HINTS_BAR, data_to_pass);
    body_dependency_symbols:
      - ALLEGRO_FLARE_EVENT_SET_INPUT_HINTS_BAR




   std::vector<std::string> keyboard_key_combo_tokens = {
      "I", "%SPACER", "LABEL>>", "Toggle inventory", 
      "%SEPARATOR",
      "X", "%SPACER", "LABEL>>", "Exit", 
      "%SEPARATOR",
      "P", "%SPACER", "LABEL>>", "Pause", 
      "%SEPARATOR",
      "SHIFT", "%SPACE", "%PLUS", "%SPACE", "ESC", "%SPACER", "LABEL>>", "Exit program", 
   };
```
