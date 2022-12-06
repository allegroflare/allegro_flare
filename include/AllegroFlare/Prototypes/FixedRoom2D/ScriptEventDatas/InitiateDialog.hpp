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
            class InitiateDialog : public AllegroFlare::GameEventDatas::Base
            {
            public:
               static constexpr char* TYPE = (char*)"ScriptEventDatas/InitiateDialog";

            private:
               std::vector<std::string> dialog_pages;

            protected:


            public:
               InitiateDialog(std::vector<std::string> dialog_pages={"[unset-dialog_pages]"});
               ~InitiateDialog();

               void set_dialog_pages(std::vector<std::string> dialog_pages);
               std::vector<std::string> get_dialog_pages() const;
            };
         }
      }
   }
}



