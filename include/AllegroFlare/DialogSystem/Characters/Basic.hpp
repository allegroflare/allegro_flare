#pragma once


#include <AllegroFlare/DialogSystem/Characters/Base.hpp>
#include <map>
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
            std::string feature_description;
            std::string avatar_thumbnail_identifier;
            std::string avatar_portrait_identifier;
            std::map<std::string, std::string> expressions;

         protected:


         public:
            Basic(std::string display_name="[unset-display_name]");
            virtual ~Basic();

            void set_display_name(std::string display_name);
            void set_feature_description(std::string feature_description);
            void set_avatar_thumbnail_identifier(std::string avatar_thumbnail_identifier);
            void set_avatar_portrait_identifier(std::string avatar_portrait_identifier);
            void set_expressions(std::map<std::string, std::string> expressions);
            std::string get_feature_description() const;
            std::string get_avatar_thumbnail_identifier() const;
            std::string get_avatar_portrait_identifier() const;
            std::map<std::string, std::string> get_expressions() const;
            virtual std::string get_display_name() override;
            void add_expression(std::string expression_name="[unset-expression_name]", std::string image_identifier="[unset-image_identifier]");
            void remove_expression(std::string expression_name="[unset-expression_name]");
            void clear_expressions();
            bool expression_exists(std::string expression_name="[unset-expression_name]");
            std::string find_expression(std::string expression_name="[unset-expression_name]");
         };
      }
   }
}



