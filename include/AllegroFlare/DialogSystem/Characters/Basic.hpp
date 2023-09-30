#pragma once


#include <AllegroFlare/DialogSystem/Characters/Base.hpp>
#include <string>


namespace AllegroFlare
{
   namespace DialogSystem
   {
      namespace Characters
      {
         class Basic : public AllegroFlare::DialogSystem::Characters::Base
         {
         public:
            static constexpr char* TYPE = (char*)"AllegroFlare/DialogSystem/Characters/Basic";

         private:
            std::string display_name;
            std::string avatar_thumbnail_identifier;
            std::string avatar_portrait_identifier;

         protected:


         public:
            Basic(std::string display_name="[unset-display_name]");
            ~Basic();

            void set_display_name(std::string display_name);
            void set_avatar_thumbnail_identifier(std::string avatar_thumbnail_identifier);
            void set_avatar_portrait_identifier(std::string avatar_portrait_identifier);
            std::string get_display_name() const;
            std::string get_avatar_thumbnail_identifier() const;
            std::string get_avatar_portrait_identifier() const;
         };
      }
   }
}



