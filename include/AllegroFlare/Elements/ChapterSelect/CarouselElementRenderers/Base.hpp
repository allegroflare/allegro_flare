#pragma once


#include <string>


namespace AllegroFlare
{
   namespace Elements
   {
      namespace ChapterSelect
      {
         namespace CarouselElementRenderers
         {
            class Base
            {
            public:
               static constexpr char* TYPE = (char*)"AllegroFlare/Elements/ChapterSelect/CarouselElementRenderers/Base";

            private:
               std::string type;

            protected:


            public:
               Base(std::string type=AllegroFlare::Elements::ChapterSelect::CarouselElementRenderers::Base::TYPE);
               ~Base();

               std::string get_type() const;
               bool is_type(std::string possible_type="");
            };
         }
      }
   }
}



