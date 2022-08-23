#pragma once


#include <AllegroFlare/MotionComposer/Messages/Base.hpp>
#include <string>


namespace AllegroFlare
{
   namespace MotionComposer
   {
      namespace Messages
      {
         class AddActor2D : public AllegroFlare::MotionComposer::Messages::Base
         {
         private:
            std::string identifier;

         public:
            AddActor2D(std::string identifier="[unset-identifier]");
            ~AddActor2D();

            void set_identifier(std::string identifier);
            std::string &get_identifier_ref();
            std::string get_identifier() const;
         };
      }
   }
}



