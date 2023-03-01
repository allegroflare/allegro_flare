

#include <AllegroFlare/VirtualController.hpp>




namespace AllegroFlare
{


VirtualController::VirtualController()
   : right_button_pressed(false)
   , left_button_pressed(false)
   , up_button_pressed(false)
   , down_button_pressed(false)
   , a_button_pressed(false)
   , b_button_pressed(false)
   , x_button_pressed(false)
   , y_button_pressed(false)
   , left_bumper_pressed(false)
   , right_bumper_pressed(false)
   , start_button_pressed(false)
   , primary_stick_position()
   , secondary_stick_position()
{
}


VirtualController::~VirtualController()
{
}


void VirtualController::set_right_button_pressed(bool right_button_pressed)
{
   this->right_button_pressed = right_button_pressed;
}


void VirtualController::set_left_button_pressed(bool left_button_pressed)
{
   this->left_button_pressed = left_button_pressed;
}


void VirtualController::set_up_button_pressed(bool up_button_pressed)
{
   this->up_button_pressed = up_button_pressed;
}


void VirtualController::set_down_button_pressed(bool down_button_pressed)
{
   this->down_button_pressed = down_button_pressed;
}


void VirtualController::set_a_button_pressed(bool a_button_pressed)
{
   this->a_button_pressed = a_button_pressed;
}


void VirtualController::set_b_button_pressed(bool b_button_pressed)
{
   this->b_button_pressed = b_button_pressed;
}


void VirtualController::set_x_button_pressed(bool x_button_pressed)
{
   this->x_button_pressed = x_button_pressed;
}


void VirtualController::set_y_button_pressed(bool y_button_pressed)
{
   this->y_button_pressed = y_button_pressed;
}


void VirtualController::set_left_bumper_pressed(bool left_bumper_pressed)
{
   this->left_bumper_pressed = left_bumper_pressed;
}


void VirtualController::set_right_bumper_pressed(bool right_bumper_pressed)
{
   this->right_bumper_pressed = right_bumper_pressed;
}


void VirtualController::set_start_button_pressed(bool start_button_pressed)
{
   this->start_button_pressed = start_button_pressed;
}


void VirtualController::set_primary_stick_position(AllegroFlare::vec2d primary_stick_position)
{
   this->primary_stick_position = primary_stick_position;
}


void VirtualController::set_secondary_stick_position(AllegroFlare::vec2d secondary_stick_position)
{
   this->secondary_stick_position = secondary_stick_position;
}


bool VirtualController::get_right_button_pressed() const
{
   return right_button_pressed;
}


bool VirtualController::get_left_button_pressed() const
{
   return left_button_pressed;
}


bool VirtualController::get_up_button_pressed() const
{
   return up_button_pressed;
}


bool VirtualController::get_down_button_pressed() const
{
   return down_button_pressed;
}


bool VirtualController::get_a_button_pressed() const
{
   return a_button_pressed;
}


bool VirtualController::get_b_button_pressed() const
{
   return b_button_pressed;
}


bool VirtualController::get_x_button_pressed() const
{
   return x_button_pressed;
}


bool VirtualController::get_y_button_pressed() const
{
   return y_button_pressed;
}


bool VirtualController::get_left_bumper_pressed() const
{
   return left_bumper_pressed;
}


bool VirtualController::get_right_bumper_pressed() const
{
   return right_bumper_pressed;
}


bool VirtualController::get_start_button_pressed() const
{
   return start_button_pressed;
}


AllegroFlare::vec2d VirtualController::get_primary_stick_position() const
{
   return primary_stick_position;
}


AllegroFlare::vec2d VirtualController::get_secondary_stick_position() const
{
   return secondary_stick_position;
}


void VirtualController::clear()
{
   right_button_pressed = false;
   left_button_pressed = false;
   up_button_pressed = false;
   down_button_pressed = false;
   a_button_pressed = false;
   b_button_pressed = false;
   start_button_pressed = false;
   return;
}


} // namespace AllegroFlare


