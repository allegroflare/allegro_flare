#pragma once


#include <AllegroFlare/DialogSystemDrivers/Base.hpp>
#include <AllegroFlare/DialogTree/NodeBank.hpp>


namespace AllegroFlare
{
   namespace DialogSystemDrivers
   {
      class SystemNotificationsDriver : public AllegroFlare::DialogSystemDrivers::Base
      {
      public:
         static constexpr char* CONFIRM_EXIT_PROGRAM = (char*)"confirm_exit_program";
         static constexpr char* TYPE = (char*)"AllegroFlare/DialogSystemDrivers/SystemNotificationsDriver";

      private:

      protected:


      public:
         SystemNotificationsDriver();
         ~SystemNotificationsDriver();

         static AllegroFlare::DialogTree::NodeBank build_node_bank();
      };
   }
}



