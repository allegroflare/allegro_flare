
#include <gtest/gtest.h>

#include <AllegroFlare/PhysicalInputDeviceToVirtualControllerMapping.hpp>

#include <AllegroFlare/PhysicalInputDevices/Keyboard.hpp>


class Keyboard_TestClass : public AllegroFlare::PhysicalInputDevices::Base
{
public:
   Keyboard_TestClass() : AllegroFlare::PhysicalInputDevices::Base("KeyboardTestClass") {}
   virtual bool is_keyboard() override { return true; }
};

class NotAKeyboard_TestClass : public AllegroFlare::PhysicalInputDevices::Base
{
public:
   NotAKeyboard_TestClass() : AllegroFlare::PhysicalInputDevices::Base("NotAKeyboard_TestClass") {}
   virtual bool is_keyboard() override { return false; }
};


TEST(AllegroFlare_PhysicalInputDeviceToVirtualControllerMappingTest, can_be_created_without_blowing_up)
{
   AllegroFlare::PhysicalInputDeviceToVirtualControllerMapping physical_input_device_to_virtual_controller_mapping;
}


TEST(AllegroFlare_PhysicalInputDeviceToVirtualControllerMappingTest,
   physical_input_device_is_keyboard__when_the_input_device_is_a_keyboard__returns_true)
{
   AllegroFlare::PhysicalInputDeviceToVirtualControllerMapping physical_input_device_to_virtual_controller_mapping;
   Keyboard_TestClass *keyboard_input_device = new Keyboard_TestClass;
   physical_input_device_to_virtual_controller_mapping.set_physical_input_device(keyboard_input_device);

   EXPECT_EQ(true, physical_input_device_to_virtual_controller_mapping.physical_input_device_is_keyboard());

   physical_input_device_to_virtual_controller_mapping.set_physical_input_device(nullptr);
   delete keyboard_input_device;
}


TEST(AllegroFlare_PhysicalInputDeviceToVirtualControllerMappingTest,
   physical_input_device_is_keyboard__when_the_input_device_is_not_a_keyboard__returns_true)
{
   AllegroFlare::PhysicalInputDeviceToVirtualControllerMapping physical_input_device_to_virtual_controller_mapping;
   NotAKeyboard_TestClass *not_a_keyboard_input_device = new NotAKeyboard_TestClass;
   physical_input_device_to_virtual_controller_mapping.set_physical_input_device(not_a_keyboard_input_device);

   EXPECT_EQ(false, physical_input_device_to_virtual_controller_mapping.physical_input_device_is_keyboard());

   physical_input_device_to_virtual_controller_mapping.set_physical_input_device(nullptr);
   delete not_a_keyboard_input_device;
}


