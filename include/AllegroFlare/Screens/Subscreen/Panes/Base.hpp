#pragma once


#include <AllegroFlare/FontBin.hpp>
#include <string>


namespace AllegroFlare
{
   namespace Screens
   {
      namespace Subscreen
      {
         namespace Panes
         {
            class Base
            {
            public:
               static constexpr char* TYPE = (char*)"AllegroFlare/Screens/Subscreen/Panes/Base";

            private:
               std::string type;
               std::string name;

            protected:


            public:
               Base(std::string type=AllegroFlare::Screens::Subscreen::Panes::Base::TYPE, std::string name="[unset-name]");
               virtual ~Base();

               void set_name(std::string name);
               std::string get_type() const;
               std::string get_name() const;
               virtual void on_switch_in();
               virtual void on_switch_out();
               virtual void update();
               virtual void render();
               void draw_empty_state(AllegroFlare::FontBin* font_bin=nullptr, std::string placeholder_text="Empty");
               bool is_type(std::string possible_type="");
            };
         }
      }
   }
}



