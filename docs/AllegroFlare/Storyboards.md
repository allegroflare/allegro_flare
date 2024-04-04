## Arbitrary Storyboards

in our game:


your configuration:


handle:

```
      this_runner->game_configuration->handle_arbitrary_storyboard_screen_finished();
      return true;
```

handle:

```
  - name: on_arbitrary_storyboard_screen_activated_func
    type: bool
    static: true
    parameters:
      - name: router
        type: AllegroFlare::Routers::Standard*
        default_argument: nullptr
      - name: user_data
        type: void*
        default_argument: nullptr
    guards: [ router, user_data ]
    body: |
      AllegroFlare::Runners::Complete* this_runner = static_cast<AllegroFlare::Runners::Complete*>(user_data);
      //this_runner->game_configuration->handle_arbitrary_storyboard_screen_activated(); // TODO: Is this necessary?

      // TODO: Consider how to pass along a storyboard identifier that should be loaded
      std::string storyboard_identifier = "[unset-storyboard_identifier]";
      // Set the pages of the storyboard to this storyboard
      // TODO: Consider if the arbitrary_storyboard_screen should be a pointer and created new here
      this_runner->arbitrary_storyboard_screen.get_storyboard_element_ref().set_pages(
         this_runner->game_configuration->create_arbitrary_storyboard_pages_by_identifier(storyboard_identifier)
```

emit an event when it's time to go to the storyboard:


 - in the primary_gameplay_screen_finished, we're gonna:


```
            this->router.emit_route_event(
               AllegroFlare::Routers::Standard::EVENT_ACTIVATE_ARBITRARY_STORYBOARD_SCREEN,
               nullptr,
               al_get_time()
            );
```


## TODOS:

- Add tests in AllegroFlare/Routers/Standard for `on_arbitrary_storyboard_screen_activated_func`.
- Clean up this guide.
- Add these funcs to blast template for configuration.
