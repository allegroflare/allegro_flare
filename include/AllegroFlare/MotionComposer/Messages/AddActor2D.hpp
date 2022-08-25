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
            std::string bitmap_identifier;
            std::string script;

         public:
            AddActor2D(std::string identifier="[unset-identifier]", std::string bitmap_identifier="[unset-bitmap_identifier]", std::string script="[unset-script]");
            ~AddActor2D();

            void set_identifier(std::string identifier);
            void set_bitmap_identifier(std::string bitmap_identifier);
            void set_script(std::string script);
            std::string &get_identifier_ref();
            std::string &get_bitmap_identifier_ref();
            std::string &get_script_ref();
            std::string get_identifier() const;
            std::string get_bitmap_identifier() const;
            std::string get_script() const;
         };
      }
   }
}



