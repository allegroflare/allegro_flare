#pragma once


class PlayerControl
{
public:
   PlayerControl()
      : forward_backward_velocity(0.0)
      , strafe_left_right_velocity(0.0)
      , rotation_left_right_velocity(0.0)
   {}

   float forward_backward_velocity;
   float strafe_left_right_velocity;
   float rotation_left_right_velocity;

   void set_forward_backward_velocity(float v)
   {
      forward_backward_velocity = v;
   }

   void set_strafe_left_right_velocity(float v)
   {
      strafe_left_right_velocity = v;
   }

   void set_rotation_left_right_velocity(float v)
   {
      rotation_left_right_velocity = v;
   }
};


