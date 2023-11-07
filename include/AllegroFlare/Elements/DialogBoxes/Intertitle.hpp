#pragma once


#include <AllegroFlare/Elements/DialogBoxes/Base.hpp>
#include <string>


namespace AllegroFlare
{
   namespace Elements
   {
      namespace DialogBoxes
      {
         class Intertitle : public AllegroFlare::Elements::DialogBoxes::Base
         {
         public:
            static constexpr char* TYPE = (char*)"AllegroFlare/Elements/DialogBoxes/Intertitle";

         private:
            std::string text;
            int revealed_characters_count;
            float all_characters_revealed_at;
            float wait_duration_after_all_characters_are_revealed;

         protected:


         public:
            Intertitle(std::string text="[text-not-set]");
            virtual ~Intertitle();

            void set_text(std::string text);
            std::string get_text() const;
            int get_revealed_characters_count() const;
            float get_all_characters_revealed_at() const;
            float get_wait_duration_after_all_characters_are_revealed() const;
            virtual void start() override;
            virtual void update() override;
            virtual void advance() override;
            std::string generate_revealed_text();
            void reveal_all_characters();
            bool all_characters_are_revealed();
         };
      }
   }
}



