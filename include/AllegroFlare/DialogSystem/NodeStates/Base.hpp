#pragma once


#include <AllegroFlare/Time.hpp>
#include <string>


namespace AllegroFlare
{
   namespace DialogSystem
   {
      namespace NodeStates
      {
         class Base
         {
         public:
            static constexpr char* TYPE = (char*)"AllegroFlare/DialogSystem/NodeStates/Base";

         private:
            std::string type;

         protected:


         public:
            Base(std::string type=AllegroFlare::DialogSystem::NodeStates::Base::TYPE);
            virtual ~Base();

            std::string get_type() const;
            virtual void update(float time_now=AllegroFlare::Time::absolute_now());
            bool is_type(std::string possible_type="");
         };
      }
   }
}



