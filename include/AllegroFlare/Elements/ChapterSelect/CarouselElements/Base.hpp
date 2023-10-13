#pragma once


#include <string>


namespace AllegroFlare
{
   namespace Elements
   {
      namespace ChapterSelect
      {
         namespace CarouselElements
         {
            class Base
            {
            public:
               static constexpr char* TYPE = (char*)"AllegroFlare/Elements/ChapterSelect/CarouselElements/Base";

            private:
               std::string type;

            protected:


            public:
               Base(std::string type=AllegroFlare::Elements::ChapterSelect::CarouselElements::Base::TYPE);
               virtual ~Base();

               std::string get_type() const;
               virtual float calculate_width();
               virtual float calculate_height();
               virtual void update();
               virtual void render();
               bool is_type(std::string possible_type="");
            };
         }
      }
   }
}



