

#include <AllegroFlare/TileMaps/PrimMeshAtlasIndexRecord.hpp>




namespace AllegroFlare
{
namespace TileMaps
{


PrimMeshAtlasIndexRecord::PrimMeshAtlasIndexRecord(int index_num, ALLEGRO_BITMAP* bitmap_source, ALLEGRO_BITMAP* sub_bitmap, float u1, float v1, float u2, float v2)
   : index_num(index_num)
   , bitmap_source(bitmap_source)
   , sub_bitmap(sub_bitmap)
   , u1(u1)
   , v1(v1)
   , u2(u2)
   , v2(v2)
{
}


PrimMeshAtlasIndexRecord::~PrimMeshAtlasIndexRecord()
{
}


void PrimMeshAtlasIndexRecord::set_index_num(int index_num)
{
   this->index_num = index_num;
}


void PrimMeshAtlasIndexRecord::set_bitmap_source(ALLEGRO_BITMAP* bitmap_source)
{
   this->bitmap_source = bitmap_source;
}


void PrimMeshAtlasIndexRecord::set_sub_bitmap(ALLEGRO_BITMAP* sub_bitmap)
{
   this->sub_bitmap = sub_bitmap;
}


void PrimMeshAtlasIndexRecord::set_u1(float u1)
{
   this->u1 = u1;
}


void PrimMeshAtlasIndexRecord::set_v1(float v1)
{
   this->v1 = v1;
}


void PrimMeshAtlasIndexRecord::set_u2(float u2)
{
   this->u2 = u2;
}


void PrimMeshAtlasIndexRecord::set_v2(float v2)
{
   this->v2 = v2;
}


int PrimMeshAtlasIndexRecord::get_index_num() const
{
   return index_num;
}


ALLEGRO_BITMAP* PrimMeshAtlasIndexRecord::get_bitmap_source() const
{
   return bitmap_source;
}


ALLEGRO_BITMAP* PrimMeshAtlasIndexRecord::get_sub_bitmap() const
{
   return sub_bitmap;
}


float PrimMeshAtlasIndexRecord::get_u1() const
{
   return u1;
}


float PrimMeshAtlasIndexRecord::get_v1() const
{
   return v1;
}


float PrimMeshAtlasIndexRecord::get_u2() const
{
   return u2;
}


float PrimMeshAtlasIndexRecord::get_v2() const
{
   return v2;
}




} // namespace TileMaps
} // namespace AllegroFlare


