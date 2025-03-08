#pragma once


#include <string>


namespace AllegroFlare
{
   namespace LoadASavedGame
   {
      namespace SaveSlots
      {
         class Base
         {
         public:
            static constexpr char* TYPE = (char*)"AllegroFlare/LoadASavedGame/SaveSlots/Base";

         private:
            std::string type;
            std::string filename;

         protected:


         public:
            Base(std::string type=AllegroFlare::LoadASavedGame::SaveSlots::Base::TYPE);
            ~Base();

            void set_filename(std::string filename);
            std::string get_type() const;
            std::string get_filename() const;
            bool is_type(std::string possible_type="");
         };
      }
   }
}



