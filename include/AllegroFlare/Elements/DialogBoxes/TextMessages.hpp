#pragma once


#include <AllegroFlare/Elements/DialogBoxes/Base.hpp>
#include <string>
#include <tuple>
#include <vector>


namespace AllegroFlare
{
   namespace Elements
   {
      namespace DialogBoxes
      {
         class TextMessages : public AllegroFlare::Elements::DialogBoxes::Base
         {
         public:
            static constexpr char* SELF = (char*)"SELF";
            static constexpr char* TYPE = (char*)"AllegroFlare/Elements/DialogBoxes/TextMessages";

         private:
            std::vector<std::tuple<std::string, std::string, float>> messages;

         protected:


         public:
            TextMessages(std::vector<std::tuple<std::string, std::string, float>> messages={});
            ~TextMessages();

            void set_messages(std::vector<std::tuple<std::string, std::string, float>> messages);
            std::vector<std::tuple<std::string, std::string, float>> get_messages() const;
         };
      }
   }
}



