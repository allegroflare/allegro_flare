#pragma once


#include <AllegroFlare/BitmapBin.hpp>
#include <AllegroFlare/Elements/Backgrounds/Base.hpp>


namespace AllegroFlare
{
   namespace Elements
   {
      namespace Backgrounds
      {
         class Monoplex : public AllegroFlare::Elements::Backgrounds::Base
         {
         private:
            AllegroFlare::BitmapBin* bitmap_bin;
            float monoplex_1_counter;
            float monoplex_2_counter;
            float monoplex_3_counter;

         public:
            Monoplex(AllegroFlare::BitmapBin* bitmap_bin=nullptr);
            virtual ~Monoplex();

            virtual void update() override;
            virtual void render() override;
         };
      }
   }
}



