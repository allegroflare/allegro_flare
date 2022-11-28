#pragma once


#include <AllegroFlare/BitmapBin.hpp>
#include <AllegroFlare/EventEmitter.hpp>
#include <AllegroFlare/FontBin.hpp>
#include <AllegroFlare/Frameworks/Full.hpp>
#include <AllegroFlare/GameEvent.hpp>
#include <AllegroFlare/ModelBin.hpp>
#include <AllegroFlare/Prototypes/CubeShooter/Screen.hpp>
#include <AllegroFlare/SampleBin.hpp>
#include <AllegroFlare/Screens/Base.hpp>
#include <functional>
#include <map>
#include <string>


namespace AllegroFlare
{
   namespace Prototypes
   {
      namespace CubeShooter
      {
         class Runner : public AllegroFlare::Screens::Base
         {
         public:
            static constexpr char* EVENT_ACTIVATE_CUBE_SHOOTER_SCREEN = "activate_cube_shooter_screen";
            static constexpr char* MODE_TEST = "test";
            static constexpr char* MODE_PRODUCTION = "production";
            static constexpr char* MODE_DEVELOPMENT = "development";

         private:
            std::string mode;
            AllegroFlare::Frameworks::Full* framework;
            AllegroFlare::EventEmitter* event_emitter;
            AllegroFlare::BitmapBin* bitmap_bin;
            AllegroFlare::FontBin* font_bin;
            AllegroFlare::SampleBin* sample_bin;
            AllegroFlare::ModelBin* model_bin;
            AllegroFlare::Prototypes::CubeShooter::Screen cube_shooter_screen;
            bool initialized;

         protected:


         public:
            Runner(std::string mode=MODE_PRODUCTION, AllegroFlare::Frameworks::Full* framework=nullptr, AllegroFlare::EventEmitter* event_emitter=nullptr, AllegroFlare::BitmapBin* bitmap_bin=nullptr, AllegroFlare::FontBin* font_bin=nullptr, AllegroFlare::SampleBin* sample_bin=nullptr, AllegroFlare::ModelBin* model_bin=nullptr);
            virtual ~Runner();

            void initialize();
            std::map<std::string, std::function<void()>> event_map();
            virtual void game_event_func(AllegroFlare::GameEvent* ev=nullptr) override;
            static void RUN(std::string mode="production", bool disable_escape_key_will_shutdown=false);
            static bool is_test_mode(std::string mode="[unset-mode]");
            static bool is_development_mode(std::string mode="[unset-mode]");
            static bool is_production_mode(std::string mode="[unset-mode]");
            bool in_development_mode();
            bool in_production_mode();
            bool in_test_mode();
            static bool is_valid_mode(std::string mode="[unset-mode]");
         };
      }
   }
}



