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
            float duration_to_advance_sec;
            std::string reveal_style;
            float started_at;

         protected:


         public:
            Image(ALLEGRO_BITMAP* bitmap=nullptr);
            virtual ~Image();

            void set_bitmap(ALLEGRO_BITMAP* bitmap);
            void set_duration_to_advance_sec(float duration_to_advance_sec);
            void set_reveal_style(std::string reveal_style);
            ALLEGRO_BITMAP* get_bitmap() const;
            float get_duration_to_advance_sec() const;
            std::string get_reveal_style() const;
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



