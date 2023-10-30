#pragma once


#include <AllegroFlare/DialogTree/NodeBank.hpp>
#include <AllegroFlare/Levels/Base.hpp>
#include <string>
#include <utility>
#include <vector>


namespace AllegroFlare
{
   namespace GameConfigurations
   {
      class Base
      {
      public:
         static constexpr char* TYPE = (char*)"AllegroFlare/GameConfigurations/Base";

      private:
         std::string type;

      protected:


      public:
         Base(std::string type=AllegroFlare::GameConfigurations::Base::TYPE);
         virtual ~Base();

         std::string get_type() const;
         virtual AllegroFlare::Levels::Base* load_level_by_identifier(std::string level_identifier="[unset-level_identifier]");
         virtual std::vector<std::pair<std::string, std::string>> build_level_list_for_level_select_screen_by_identifier(std::string identifier="[unset-identifier]");
         virtual AllegroFlare::DialogTree::NodeBank build_dialog_bank_by_identifier(std::string identifier="[unset-identifier]");
         bool is_type(std::string possible_type="");
      };
   }
}



