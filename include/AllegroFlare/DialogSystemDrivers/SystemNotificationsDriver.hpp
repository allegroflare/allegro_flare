#pragma once


#include <AllegroFlare/DialogSystemDrivers/Base.hpp>
#include <AllegroFlare/DialogTree/NodeBank.hpp>
#include <string>


namespace AllegroFlare
{
   namespace DialogSystemDrivers
   {
      class SystemNotificationsDriver : public AllegroFlare::DialogSystemDrivers::Base
      {
      public:
         static constexpr char* TYPE = (char*)"AllegroFlare/DialogSystemDrivers/SystemNotificationsDriver";

      private:

      protected:


      public:
         SystemNotificationsDriver();
         ~SystemNotificationsDriver();

         bool load_node_bank_func(std::string filename="[unset-filename]", AllegroFlare::DialogTree::NodeBank* node_bank=nullptr, void* user_data=nullptr);
      };
   }
}



