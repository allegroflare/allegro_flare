#pragma once


#include <string>


namespace AllegroFlare
{
   namespace Elements
   {
      namespace Backgrounds
      {
         class Base
         {
         public:
            static constexpr char* TYPE = (char*)"AllegroFlare/Elements/Backgrounds/Base";

         private:
            std::string type;

         protected:


         public:
            Base(std::string type=AllegroFlare::Elements::Backgrounds::Base::TYPE);
            virtual ~Base();

            std::string get_type() const;
            virtual void activate();
            virtual void deactivate();
            virtual void update();
            virtual void render();
            virtual void show();
            virtual void hide();
            bool is_type(std::string possible_type="");
         };
      }
   }
}



