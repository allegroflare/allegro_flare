

#include <AllegroFlare/PhysicalInputDeviceToVirtualControllerMappingFactory.hpp>

#include <AllegroFlare/PhysicalInputDevices/Keyboard.hpp>
#include <AllegroFlare/VirtualControllers/GenericController.hpp>
#include <allegro5/allegro.h>


namespace AllegroFlare
{


PhysicalInputDeviceToVirtualControllerMappingFactory::PhysicalInputDeviceToVirtualControllerMappingFactory()
{
}


PhysicalInputDeviceToVirtualControllerMappingFactory::~PhysicalInputDeviceToVirtualControllerMappingFactory()
{
}


AllegroFlare::PhysicalInputDeviceToVirtualControllerMapping PhysicalInputDeviceToVirtualControllerMappingFactory::create_single_player_keyboard_mapping_from_scratch()
{
   AllegroFlare::PhysicalInputDeviceToVirtualControllerMapping mapping;

   AllegroFlare::Player *player = new AllegroFlare::Player("Player 1");

   mapping.set_player(player);
   mapping.set_physical_input_device(new AllegroFlare::PhysicalInputDevices::Keyboard);
   mapping.set_virtual_controller(new AllegroFlare::VirtualControllers::GenericController);

   mapping.set_multiple_mappings({
      { ALLEGRO_KEY_ENTER, AllegroFlare::VirtualControllers::GenericController::BUTTON_MENU },
      { ALLEGRO_KEY_SPACE, AllegroFlare::VirtualControllers::GenericController::BUTTON_A },
      { ALLEGRO_KEY_A,     AllegroFlare::VirtualControllers::GenericController::BUTTON_A },
      { ALLEGRO_KEY_B,     AllegroFlare::VirtualControllers::GenericController::BUTTON_B },
      { ALLEGRO_KEY_X,     AllegroFlare::VirtualControllers::GenericController::BUTTON_X },
      { ALLEGRO_KEY_Y,     AllegroFlare::VirtualControllers::GenericController::BUTTON_Y },
      { ALLEGRO_KEY_UP,    AllegroFlare::VirtualControllers::GenericController::BUTTON_UP },
      { ALLEGRO_KEY_DOWN,  AllegroFlare::VirtualControllers::GenericController::BUTTON_DOWN },
      { ALLEGRO_KEY_LEFT,  AllegroFlare::VirtualControllers::GenericController::BUTTON_LEFT },
      { ALLEGRO_KEY_RIGHT, AllegroFlare::VirtualControllers::GenericController::BUTTON_RIGHT },
      { ALLEGRO_KEY_R,     AllegroFlare::VirtualControllers::GenericController::BUTTON_RIGHT_BUMPER },
      { ALLEGRO_KEY_E,     AllegroFlare::VirtualControllers::GenericController::BUTTON_LEFT_BUMPER },
   });

   return mapping;
}


} // namespace AllegroFlare


