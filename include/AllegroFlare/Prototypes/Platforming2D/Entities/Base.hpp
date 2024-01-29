#pragma once


#include <AllegroFlare/ElementID.hpp>
#include <string>


namespace AllegroFlare
{
   namespace Prototypes
   {
      namespace Platforming2D
      {
         namespace Entities
         {
            class Base : public AllegroFlare::ElementID
            {
            public:
               static constexpr char* TYPE = (char*)"Entities/Base";

            private:
               std::string type;
               AllegroFlare::ElementID* parent;

            protected:


            public:
               Base(std::string type=AllegroFlare::Prototypes::Platforming2D::Entities::Base::TYPE, AllegroFlare::ElementID* parent=nullptr);
               virtual ~Base();

               std::string get_type() const;
               AllegroFlare::ElementID* get_parent() const;
               virtual void update();
               virtual void draw();
               virtual void on_attribute_added(std::string attribute="[unset-attribute]");
               virtual void on_attribute_removed(std::string attribute="[unset-attribute]");
               bool is_type(std::string possible_type="");
            };
         }
      }
   }
}



