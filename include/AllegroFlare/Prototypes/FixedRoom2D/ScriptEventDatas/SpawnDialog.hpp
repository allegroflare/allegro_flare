#pragma once


#include <AllegroFlare/GameEventDatas/Base.hpp>
#include <string>
#include <vector>


namespace AllegroFlare
{
   namespace Prototypes
   {
      namespace FixedRoom2D
      {
         namespace ScriptEventDatas
         {
            class SpawnDialog : public AllegroFlare::GameEventDatas::Base
            {
            private:
               std::vector<std::string> dialog_pages;

            public:
               SpawnDialog(std::vector<std::string> dialog_pages={"[unset-dialog_pages]"});
               ~SpawnDialog();

               void set_dialog_pages(std::vector<std::string> dialog_pages);
               std::vector<std::string> get_dialog_pages();
            };
         }
      }
   }
}



