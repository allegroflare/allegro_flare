#pragma once


#include <AllegroFlare/Elements/DialogBoxes/Base.hpp>
#include <AllegroFlare/GameEventDatas/Base.hpp>


namespace AllegroFlare
{
   namespace Prototypes
   {
      namespace FixedRoom2D
      {
         namespace DialogEventDatas
         {
            class CloseDialog : public AllegroFlare::GameEventDatas::Base
            {
            private:
               AllegroFlare::Elements::DialogBoxes::Base* dialog;

            protected:


            public:
               CloseDialog(AllegroFlare::Elements::DialogBoxes::Base* dialog=nullptr);
               ~CloseDialog();

               void set_dialog(AllegroFlare::Elements::DialogBoxes::Base* dialog);
               AllegroFlare::Elements::DialogBoxes::Base* get_dialog() const;
            };
         }
      }
   }
}



