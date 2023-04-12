#pragma once


#include <AllegroFlare/Elements/Backgrounds/Base.hpp>
#include <AllegroFlare/VideoBin.hpp>
#include <allegro5/allegro.h>
#include <string>


namespace AllegroFlare
{
   namespace Elements
   {
      namespace Backgrounds
      {
         class VideoIdentifier : public AllegroFlare::Elements::Backgrounds::Base
         {
         public:
            static constexpr char* VIDEO_FIT_STRATEGY_STRETCH_TO_FIT = (char*)"stretch_to_fit";
            static constexpr char* TYPE = (char*)"AllegroFlare/Elements/Backgrounds/VideoIdentifier";

         private:
            AllegroFlare::VideoBin* video_bin;
            std::string video_identifier;
            int surface_width;
            int surface_height;
            bool video_is_playing;
            ALLEGRO_VIDEO* obtain_video();

         protected:


         public:
            VideoIdentifier(AllegroFlare::VideoBin* video_bin=nullptr, std::string video_identifier="[unset-video_identifier]");
            ~VideoIdentifier();

            void set_surface_width(int surface_width);
            void set_surface_height(int surface_height);
            int get_surface_width() const;
            int get_surface_height() const;
            void activate() override;
            void deactivate() override;
            void render() override;
         };
      }
   }
}



