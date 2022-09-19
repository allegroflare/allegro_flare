

#include <Tileo/TileIndexInfo.hpp>



namespace Tileo
{


TileIndexInfo::TileIndexInfo(int index_num, ALLEGRO_BITMAP* bitmap_source, ALLEGRO_BITMAP* sub_bitmap, float u1, float v1, float u2, float v2)
   : index_num(index_num)
   , bitmap_source(bitmap_source)
   , sub_bitmap(sub_bitmap)
   , u1(u1)
   , v1(v1)
   , u2(u2)
   , v2(v2)
{
}


TileIndexInfo::~TileIndexInfo()
{
}


void TileIndexInfo::set_index_num(int index_num)
{
   this->index_num = index_num;
}


void TileIndexInfo::set_bitmap_source(ALLEGRO_BITMAP* bitmap_source)
{
   this->bitmap_source = bitmap_source;
}


void TileIndexInfo::set_sub_bitmap(ALLEGRO_BITMAP* sub_bitmap)
{
   this->sub_bitmap = sub_bitmap;
}


void TileIndexInfo::set_u1(float u1)
{
   this->u1 = u1;
}


void TileIndexInfo::set_v1(float v1)
{
   this->v1 = v1;
}


void TileIndexInfo::set_u2(float u2)
{
   this->u2 = u2;
}


void TileIndexInfo::set_v2(float v2)
{
   this->v2 = v2;
}


int TileIndexInfo::get_index_num()
{
   return index_num;
}


ALLEGRO_BITMAP* TileIndexInfo::get_bitmap_source()
{
   return bitmap_source;
}


ALLEGRO_BITMAP* TileIndexInfo::get_sub_bitmap()
{
   return sub_bitmap;
}


float TileIndexInfo::get_u1()
{
   return u1;
}


float TileIndexInfo::get_v1()
{
   return v1;
}


float TileIndexInfo::get_u2()
{
   return u2;
}


float TileIndexInfo::get_v2()
{
   return v2;
}


} // namespace Tileo


