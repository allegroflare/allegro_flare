

#include <AllegroFlare/RenderStateInfo.hpp>

#include <allegro5/allegro.h>


namespace AllegroFlare
{


RenderStateInfo::RenderStateInfo()
{
}


RenderStateInfo::~RenderStateInfo()
{
}


std::string RenderStateInfo::decode_write_mask(int write_mask)
{
   std::string result;

   if (write_mask & ALLEGRO_MASK_RED)
   {
      result += "ALLEGRO_MASK_RED ";
   }
   if (write_mask & ALLEGRO_MASK_GREEN)
   {
      result += "ALLEGRO_MASK_GREEN ";
   }
   if (write_mask & ALLEGRO_MASK_BLUE)
   {
      result += "ALLEGRO_MASK_BLUE ";
   }
   if (write_mask & ALLEGRO_MASK_ALPHA)
   {
      result += "ALLEGRO_MASK_ALPHA ";
   }
   if (write_mask & ALLEGRO_MASK_DEPTH)
   {
      result += "ALLEGRO_MASK_DEPTH ";
   }

   // Trim the trailing space, if any
   if (!result.empty() && result.back() == ' ')
   {
      result.pop_back();
   }

   return result;
}


} // namespace AllegroFlare


