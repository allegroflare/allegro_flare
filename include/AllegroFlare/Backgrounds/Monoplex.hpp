#pragma once


#include <AllegroFlare/Backgrounds/Base.hpp>
#include <AllegroFlare/BitmapBin.hpp>


namespace AllegroFlare
{
   namespace Backgrounds
   {
      class Monoplex : public AllegroFlare::Backgrounds::Base
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



