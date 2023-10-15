#pragma once


#include <string>


namespace AllegroFlare
{
   namespace GameProgressAndStateInfos
   {
      class Base
      {
      public:
         static constexpr char* TYPE = (char*)"AllegroFlare/GameProgressAndStateInfos/Base";

      private:
         std::string type;

      protected:


      public:
         Base(std::string type=AllegroFlare::GameProgressAndStateInfos::Base::TYPE);
         virtual ~Base();

         std::string get_type() const;
         virtual std::string export_to_string();
         virtual void import_from_string(std::string data_string="[unset-data_string]");
         bool is_type(std::string possible_type="");
      };
   }
}



