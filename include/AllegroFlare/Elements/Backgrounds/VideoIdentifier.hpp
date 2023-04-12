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
            static constexpr char* TYPE = (char*)"AllegroFlare/Elements/Backgrounds/VideoIdentifier";

         private:
            AllegroFlare::VideoBin* video_bin;
            std::string video_identifier;
            ALLEGRO_VIDEO* obtain_video();

         protected:


         public:
            VideoIdentifier(AllegroFlare::VideoBin* video_bin=nullptr, std::string video_identifier="[unset-video_identifier]");
            ~VideoIdentifier();

            void activate() override;
            void deactivate() override;
            void render() override;
         };
      }
   }
}



