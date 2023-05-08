#pragma once


#include <AllegroFlare/Elements/StoryboardPages/Base.hpp>
#include <AllegroFlare/Placement2D.hpp>
#include <allegro5/allegro.h>
#include <string>


namespace AllegroFlare
{
   namespace Elements
   {
      namespace StoryboardPages
      {
         class Image : public AllegroFlare::Elements::StoryboardPages::Base
         {
         private:
            ALLEGRO_BITMAP* bitmap;
            std::string reveal_style;
            float duration_to_advance_sec;
            float started_at;

         protected:


         public:
            Image(ALLEGRO_BITMAP* bitmap=nullptr, std::string reveal_style="reveal", float duration_to_advance_sec=2.0f);
            virtual ~Image();

            void set_bitmap(ALLEGRO_BITMAP* bitmap);
            void set_reveal_style(std::string reveal_style);
            void set_duration_to_advance_sec(float duration_to_advance_sec);
            ALLEGRO_BITMAP* get_bitmap() const;
            std::string get_reveal_style() const;
            float get_duration_to_advance_sec() const;
            float get_started_at() const;
            virtual void start() override;
            virtual void update() override;
            virtual void render() override;
            virtual void advance() override;
            float infer_age();
            void modify_params_for_hide(AllegroFlare::Placement2D* place=nullptr, ALLEGRO_COLOR* color=nullptr);
            void modify_params_for_reveal(AllegroFlare::Placement2D* place=nullptr, ALLEGRO_COLOR* color=nullptr);
         };
      }
   }
}



