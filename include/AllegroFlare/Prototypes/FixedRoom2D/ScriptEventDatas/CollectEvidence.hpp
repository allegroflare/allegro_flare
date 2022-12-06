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
               static constexpr char* TYPE = (char*)"ScriptEventDatas/CollectEvidence";

            private:
               std::string evidence_dictionary_name_to_collect;

            protected:


            public:
               CollectEvidence(std::string evidence_dictionary_name_to_collect="[unset-evidence_dictionary_name_to_collect]");
               ~CollectEvidence();

               void set_evidence_dictionary_name_to_collect(std::string evidence_dictionary_name_to_collect);
               std::string get_evidence_dictionary_name_to_collect() const;
            };
         }
      }
   }
}



