

#include <AllegroFlare/VirtualControls.hpp>



namespace AllegroFlare
{


int VirtualControls::BUTTON_UP = 1;


int VirtualControls::BUTTON_DOWN = 2;


int VirtualControls::BUTTON_LEFT = 3;


int VirtualControls::BUTTON_RIGHT = 4;


int VirtualControls::BUTTON_A = 5;


int VirtualControls::BUTTON_B = 6;


int VirtualControls::BUTTON_X = 7;


int VirtualControls::BUTTON_Y = 8;


int VirtualControls::BUTTON_START = 9;


int VirtualControls::BUTTON_RIGHT_BUMPER = 10;


int VirtualControls::BUTTON_LEFT_BUMPER = 11;


int VirtualControls::PRIMARY_STICK = 0;


int VirtualControls::SECONDARY_STICK = 1;


VirtualControls::VirtualControls()
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


VirtualControls::~VirtualControls()
{
}


void VirtualControls::set_right_button_pressed(bool right_button_pressed)
{
   this->right_button_pressed = right_button_pressed;
}


void VirtualControls::set_left_button_pressed(bool left_button_pressed)
{
   this->left_button_pressed = left_button_pressed;
}


void VirtualControls::set_up_button_pressed(bool up_button_pressed)
{
   this->up_button_pressed = up_button_pressed;
}


void VirtualControls::set_down_button_pressed(bool down_button_pressed)
{
   this->down_button_pressed = down_button_pressed;
}


void VirtualControls::set_a_button_pressed(bool a_button_pressed)
{
   this->a_button_pressed = a_button_pressed;
}


void VirtualControls::set_b_button_pressed(bool b_button_pressed)
{
   this->b_button_pressed = b_button_pressed;
}


void VirtualControls::set_x_button_pressed(bool x_button_pressed)
{
   this->x_button_pressed = x_button_pressed;
}


void VirtualControls::set_y_button_pressed(bool y_button_pressed)
{
   this->y_button_pressed = y_button_pressed;
}


void VirtualControls::set_left_bumper_pressed(bool left_bumper_pressed)
{
   this->left_bumper_pressed = left_bumper_pressed;
}


void VirtualControls::set_right_bumper_pressed(bool right_bumper_pressed)
{
   this->right_bumper_pressed = right_bumper_pressed;
}


void VirtualControls::set_start_button_pressed(bool start_button_pressed)
{
   this->start_button_pressed = start_button_pressed;
}


void VirtualControls::set_primary_stick_position(AllegroFlare::vec2d primary_stick_position)
{
   this->primary_stick_position = primary_stick_position;
}


void VirtualControls::set_secondary_stick_position(AllegroFlare::vec2d secondary_stick_position)
{
   this->secondary_stick_position = secondary_stick_position;
}


int VirtualControls::get_BUTTON_UP()
{
   return BUTTON_UP;
}


int VirtualControls::get_BUTTON_DOWN()
{
   return BUTTON_DOWN;
}


int VirtualControls::get_BUTTON_LEFT()
{
   return BUTTON_LEFT;
}


int VirtualControls::get_BUTTON_RIGHT()
{
   return BUTTON_RIGHT;
}


int VirtualControls::get_BUTTON_A()
{
   return BUTTON_A;
}


int VirtualControls::get_BUTTON_B()
{
   return BUTTON_B;
}


int VirtualControls::get_BUTTON_X()
{
   return BUTTON_X;
}


int VirtualControls::get_BUTTON_Y()
{
   return BUTTON_Y;
}


int VirtualControls::get_BUTTON_START()
{
   return BUTTON_START;
}


int VirtualControls::get_BUTTON_RIGHT_BUMPER()
{
   return BUTTON_RIGHT_BUMPER;
}


int VirtualControls::get_BUTTON_LEFT_BUMPER()
{
   return BUTTON_LEFT_BUMPER;
}


int VirtualControls::get_PRIMARY_STICK()
{
   return PRIMARY_STICK;
}


int VirtualControls::get_SECONDARY_STICK()
{
   return SECONDARY_STICK;
}


bool VirtualControls::get_right_button_pressed() const
{
   return right_button_pressed;
}


bool VirtualControls::get_left_button_pressed() const
{
   return left_button_pressed;
}


bool VirtualControls::get_up_button_pressed() const
{
   return up_button_pressed;
}


bool VirtualControls::get_down_button_pressed() const
{
   return down_button_pressed;
}


bool VirtualControls::get_a_button_pressed() const
{
   return a_button_pressed;
}


bool VirtualControls::get_b_button_pressed() const
{
   return b_button_pressed;
}


bool VirtualControls::get_x_button_pressed() const
{
   return x_button_pressed;
}


bool VirtualControls::get_y_button_pressed() const
{
   return y_button_pressed;
}


bool VirtualControls::get_left_bumper_pressed() const
{
   return left_bumper_pressed;
}


bool VirtualControls::get_right_bumper_pressed() const
{
   return right_bumper_pressed;
}


bool VirtualControls::get_start_button_pressed() const
{
   return start_button_pressed;
}


AllegroFlare::vec2d VirtualControls::get_primary_stick_position() const
{
   return primary_stick_position;
}


AllegroFlare::vec2d VirtualControls::get_secondary_stick_position() const
{
   return secondary_stick_position;
}


void VirtualControls::clear()
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


