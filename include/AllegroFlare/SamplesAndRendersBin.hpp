#pragma once


#include <AllegroFlare/Bin.hpp>
#include <allegro5/allegro.h>
#include <allegro5/allegro_audio.h>
#include <map>
#include <string>
#include <utility>


namespace AllegroFlare
{
   class SamplesAndRendersBin : public AllegroFlare::Bin<std::string, std::pair<ALLEGRO_SAMPLE*, ALLEGRO_BITMAP*>>
   {
   private:
      std::map<ALLEGRO_SAMPLE*, ALLEGRO_BITMAP*> samples_to_bitmaps_map;

   protected:


   public:
      SamplesAndRendersBin();
      virtual ~SamplesAndRendersBin();

      virtual bool validate() override;
      ALLEGRO_BITMAP* find_render_by_sample(ALLEGRO_SAMPLE* sample=nullptr);
      virtual std::pair<ALLEGRO_SAMPLE*, ALLEGRO_BITMAP*> load_data(std::string identifier="[unset-identifier]") override;
      virtual void destroy_data(std::pair<ALLEGRO_SAMPLE*, ALLEGRO_BITMAP*> sample_and_render={ nullptr, nullptr }) override;
   };
}



