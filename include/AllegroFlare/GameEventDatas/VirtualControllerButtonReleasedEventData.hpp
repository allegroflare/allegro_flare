#pragma once


#include <AllegroFlare/GameEventDatas/Base.hpp>
#include <AllegroFlare/Player.hpp>
#include <AllegroFlare/VirtualControllers/Base.hpp>


namespace AllegroFlare
{
   namespace GameEventDatas
   {
      class VirtualControllerButtonReleasedEventData : public AllegroFlare::GameEventDatas::Base
      {
      public:
         static constexpr char* TYPE = (char*)"AllegroFlare/GameEventDatas/VirtualControllerButtonReleasedEventData";

      private:
         AllegroFlare::Player* player;
         AllegroFlare::VirtualControllers::Base* virtual_controller;
         int virtual_controller_button_num;

      protected:


      public:
         VirtualControllerButtonReleasedEventData(AllegroFlare::Player* player=nullptr, AllegroFlare::VirtualControllers::Base* virtual_controller=nullptr, int virtual_controller_button_num=0);
         ~VirtualControllerButtonReleasedEventData();

         void set_player(AllegroFlare::Player* player);
         void set_virtual_controller(AllegroFlare::VirtualControllers::Base* virtual_controller);
         void set_virtual_controller_button_num(int virtual_controller_button_num);
         AllegroFlare::Player* get_player() const;
         AllegroFlare::VirtualControllers::Base* get_virtual_controller() const;
         int get_virtual_controller_button_num() const;
      };
   }
}



