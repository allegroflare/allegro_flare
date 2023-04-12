

#include <AllegroFlare/Video.hpp>




namespace AllegroFlare
{


Video::Video(ALLEGRO_VIDEO* al_video)
   : al_video(al_video)
{
}


Video::~Video()
{
}


void Video::set_al_video(ALLEGRO_VIDEO* al_video)
{
   this->al_video = al_video;
}


ALLEGRO_VIDEO* Video::get_al_video() const
{
   return al_video;
}




} // namespace AllegroFlare


