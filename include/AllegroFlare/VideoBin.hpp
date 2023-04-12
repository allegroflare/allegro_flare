#pragma once


#include <AllegroFlare/Bin.hpp>
#include <allegro5/allegro_video.h>
#include <string>


namespace AllegroFlare
{
   class VideoBin : public AllegroFlare::Bin<std::string, ALLEGRO_VIDEO*>
   {
   private:

   protected:


   public:
      VideoBin();
      virtual ~VideoBin();

      virtual bool validate() override;
      virtual ALLEGRO_VIDEO* load_data(std::string identifier="[unset-identifier]") override;
      virtual void destroy_data(ALLEGRO_VIDEO* video=nullptr) override;
   };
}



