#pragma once


#include <AllegroFlare/Vec2D.hpp>
#include <AllegroFlare/VirtualControllers/Base.hpp>
#include <cstdint>


namespace AllegroFlare
{
   namespace VirtualControllers
   {
      class GenericController : public AllegroFlare::VirtualControllers::Base
      {
      public:
         static constexpr uint32_t PRIMARY_STICK = 0;
         static constexpr uint32_t SECONDARY_STICK = 1;
         static constexpr char* TYPE = (char*)"AllegroFlare/VirtualControllers/GenericController";
         static constexpr char* DEFAULT_NAME = (char*)"Generic AllegroFlare Controller";

public:

         enum : uint32_t
         {
            BUTTON_UNDEF = 0,
            BUTTON_UP,
            BUTTON_DOWN,
            BUTTON_LEFT,
            BUTTON_RIGHT,
            BUTTON_A,
            BUTTON_B,
            BUTTON_X,
            BUTTON_Y,
            BUTTON_MENU,
            BUTTON_RIGHT_BUMPER,
            BUTTON_LEFT_BUMPER,
         };
      private:
         AllegroFlare::Vec2D primary_stick_position;
         AllegroFlare::Vec2D secondary_stick_position;

      protected:


      public:
         GenericController();
         ~GenericController();

         void set_primary_stick_position(AllegroFlare::Vec2D primary_stick_position);
         void set_secondary_stick_position(AllegroFlare::Vec2D secondary_stick_position);
         AllegroFlare::Vec2D get_primary_stick_position() const;
         AllegroFlare::Vec2D get_secondary_stick_position() const;
      };
   }
}



