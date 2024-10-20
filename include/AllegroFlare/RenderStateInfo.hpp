#pragma once


#include <string>


namespace AllegroFlare
{
   class RenderStateInfo
   {
   private:

   protected:


   public:
      RenderStateInfo();
      ~RenderStateInfo();

      std::string decode_write_mask(int write_mask=0);
   };
}



