#pragma once


#include <AllegroFlare/Screen.hpp>
#include <AllegroFlare/Screens.hpp>


namespace AllegroFlare
{
   class FrameworkScreenRegistrar
   {
   private:
      AllegroFlare::Screens* screens;
      AllegroFlare::Screen* screen;

   public:
      FrameworkScreenRegistrar(AllegroFlare::Screens* screens=nullptr, AllegroFlare::Screen* screen=nullptr);
      ~FrameworkScreenRegistrar();


   bool append();
   bool remove();
   };
}



