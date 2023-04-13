#pragma once


#include <string>


namespace AllegroFlare
{
   namespace GameplayMechanics
   {
      namespace Triggers
      {
         class Base
         {
         public:
            static constexpr char* TYPE = (char*)"AllegroFlare/GameplayMechanics/Triggers/Base";

         private:
            std::string type;
            bool triggered;
            virtual void on_trigger();

         protected:


         public:
            Base(std::string type=AllegroFlare::GameplayMechanics::Triggers::Base::TYPE);
            virtual ~Base();

            std::string get_type() const;
            bool get_triggered() const;
            void trigger();
            bool is_type(std::string possible_type="");
         };
      }
   }
}



