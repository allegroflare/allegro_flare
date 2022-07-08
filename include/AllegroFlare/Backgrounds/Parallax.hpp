#pragma once


#include <AllegroFlare/Backgrounds/Base.hpp>


namespace AllegroFlare
{
   namespace Backgrounds
   {
      class Parallax : public AllegroFlare::Backgrounds::Base
      {
      private:

      public:
         Parallax();
         virtual ~Parallax();

         virtual void update();
         virtual void draw();
      };
   }
}



