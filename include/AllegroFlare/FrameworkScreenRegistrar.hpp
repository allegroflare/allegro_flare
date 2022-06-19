#pragma once


#include <AllegroFlare/Screen.hpp>
#include <AllegroFlare/ScreenManager.hpp>


namespace AllegroFlare
{
   class FrameworkScreenRegistrar
   {
   private:
      AllegroFlare::ScreenManager* screens;
      AllegroFlare::Screen* screen;

   public:
      FrameworkScreenRegistrar(AllegroFlare::ScreenManager* screens=nullptr, AllegroFlare::Screen* screen=nullptr);
      ~FrameworkScreenRegistrar();

      bool append();
      bool remove();
   };
}



