# How to add a pause:

0) event_emitter->emit_router_event(AllegroFlare::Routers::Standard::EVENT_PAUSE_GAMEPLAY);
  1) (primary gameplay screen is suspended)
  2) the router calls on_gameplay_paused_func()
     - you provide the behavior for this, for example, activate subscreen, activate pause screen?
3) pause screen initiates the unpause event
  4) event_emitter->emit_router_event(AllegroFlare::Routers::Standard::EVENT_UNPAUSE_GAMEPLAY);
  5) the router calls on_gameplay_unpaused_func()
     - you provide the behavior for this, for example, activate gameplay screen?
  1) (primary gameplay screen is unsuspended)


TODO: Where in the configuration is the callback provided and defined?
