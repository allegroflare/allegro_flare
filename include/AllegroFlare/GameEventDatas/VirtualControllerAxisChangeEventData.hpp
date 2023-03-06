#pragma once


#include <AllegroFlare/GameEventDatas/Base.hpp>
#include <AllegroFlare/Player.hpp>
#include <AllegroFlare/VirtualControllers/Base.hpp>


namespace AllegroFlare
{
   namespace GameEventDatas
   {
      class VirtualControllerAxisChangeEventData : public AllegroFlare::GameEventDatas::Base
      {
      public:
         static constexpr char* TYPE = (char*)"AllegroFlare/GameEventDatas/VirtualControllerAxisChangeEventData";

      private:
         AllegroFlare::Player* player;
         AllegroFlare::VirtualControllers::Base* virtual_controller;
         int virtual_controller_stick;
         int virtual_controller_axis;
         float virtual_controller_position;

      protected:


      public:
         VirtualControllerAxisChangeEventData(AllegroFlare::Player* player=nullptr, AllegroFlare::VirtualControllers::Base* virtual_controller=nullptr, int virtual_controller_stick=0, int virtual_controller_axis=0, float virtual_controller_position=0.0f);
         ~VirtualControllerAxisChangeEventData();

         void set_player(AllegroFlare::Player* player);
         void set_virtual_controller(AllegroFlare::VirtualControllers::Base* virtual_controller);
         void set_virtual_controller_stick(int virtual_controller_stick);
         void set_virtual_controller_axis(int virtual_controller_axis);
         void set_virtual_controller_position(float virtual_controller_position);
         AllegroFlare::Player* get_player() const;
         AllegroFlare::VirtualControllers::Base* get_virtual_controller() const;
         int get_virtual_controller_stick() const;
         int get_virtual_controller_axis() const;
         float get_virtual_controller_position() const;
      };
   }
}



