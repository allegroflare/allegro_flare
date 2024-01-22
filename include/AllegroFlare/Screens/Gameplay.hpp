#pragma once


#include <AllegroFlare/Screens/Base.hpp>
#include <AllegroFlare/Screens/Gameplay.hpp>
#include <functional>
#include <string>


namespace AllegroFlare
{
   namespace Screens
   {
      class Gameplay : public AllegroFlare::Screens::Base
      {
      public:
         static constexpr char* TYPE = (char*)"AllegroFlare/Screens/Gameplay";

      private:
         std::string property;

      protected:


      public:
         Gameplay(std::string property="[unset-property]");
         virtual ~Gameplay();

         std::string get_property() const;
         virtual void set_on_finished_callback_func(std::function<void(AllegroFlare::Screens::Gameplay*, void*)> on_finished_callback_func={});
         virtual void set_on_finished_callback_func_user_data(void* on_finished_callback_func_user_data=nullptr);
         virtual void load_level_by_identifier(std::string possible_type="");
         bool property_is(std::string possible_type="");
      };
   }
}



