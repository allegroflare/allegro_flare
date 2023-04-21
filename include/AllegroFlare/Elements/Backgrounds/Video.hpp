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
         class Video : public AllegroFlare::Elements::Backgrounds::Base
         {
         public:
            static constexpr char* VIDEO_FIT_STRATEGY_STRETCH_TO_FIT = (char*)"stretch_to_fit";
            static constexpr char* TYPE = (char*)"AllegroFlare/Elements/Backgrounds/Video";

         private:
            AllegroFlare::VideoBin* video_bin;
            std::string video_identifier;
            int surface_width;
            int surface_height;
            bool video_is_playing;
            bool initialized;
            ALLEGRO_VIDEO* obtain_video();

         protected:


         public:
            Video(AllegroFlare::VideoBin* video_bin=nullptr, std::string video_identifier="[unset-video_identifier]");
            ~Video();

            void set_surface_width(int surface_width);
            void set_surface_height(int surface_height);
            AllegroFlare::VideoBin* get_video_bin() const;
            std::string get_video_identifier() const;
            int get_surface_width() const;
            int get_surface_height() const;
            void set_video_bin(AllegroFlare::VideoBin* video_bin=nullptr);
            void set_video_identifier(std::string video_identifier="[unset-video_identifier]");
            void initialize();
            void activate() override;
            void deactivate() override;
            void render() override;
         };
      }
   }
}



