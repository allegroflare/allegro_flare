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
            class CollectEvidence : public AllegroFlare::GameEventDatas::Base
            {
            public:
               static constexpr char* TYPE = "ScriptEventDatas/CollectEvidence";

            private:
               std::string item_dictionary_name_to_collect;

            protected:


            public:
               CollectEvidence(std::string item_dictionary_name_to_collect="[unset-item_dictionary_name_to_collect]");
               ~CollectEvidence();

               void set_item_dictionary_name_to_collect(std::string item_dictionary_name_to_collect);
               std::string get_item_dictionary_name_to_collect() const;
            };
         }
      }
   }
}



