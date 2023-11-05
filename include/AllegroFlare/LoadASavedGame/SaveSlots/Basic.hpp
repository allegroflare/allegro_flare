#pragma once


#include <AllegroFlare/LoadASavedGame/SaveSlots/Base.hpp>
#include <string>


namespace AllegroFlare
{
   namespace LoadASavedGame
   {
      namespace SaveSlots
      {
         class Basic : public AllegroFlare::LoadASavedGame::SaveSlots::Base
         {
         public:
            static constexpr char* TYPE = (char*)"AllegroFlare/LoadASavedGame/SaveSlots/Basic";

         private:
            std::string save_name;

         protected:


         public:
            Basic(std::string save_name="[unset-save_name]");
            ~Basic();

            void set_save_name(std::string save_name);
            std::string get_save_name() const;
         };
      }
   }
}



