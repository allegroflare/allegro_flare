#pragma once


#include <AllegroFlare/GameEventDatas/Base.hpp>
#include <string>


namespace AllegroFlare
{
   namespace Prototypes
   {
      namespace FixedRoom2D
      {
         namespace ScriptEventDatas
         {
            class CollectItem : public AllegroFlare::GameEventDatas::Base
            {
            private:
               std::string item_dictionary_name_to_collect;

            protected:


            public:
               CollectItem(std::string item_dictionary_name_to_collect="[unset-item_dictionary_name_to_collect]");
               ~CollectItem();

               void set_item_dictionary_name_to_collect(std::string item_dictionary_name_to_collect);
               std::string get_item_dictionary_name_to_collect() const;
            };
         }
      }
   }
}



