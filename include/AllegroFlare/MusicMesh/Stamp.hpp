#pragma once


#include <cstdint>


namespace AllegroFlare
{
   namespace MusicMesh
   {
      class Stamp
      {
      private:
         uint32_t id;
         float x;
         float y;
         uint32_t multi_mesh_id;

      protected:


      public:
         Stamp(uint32_t id=0, float x=0.0f, float y=0.0f, uint32_t multi_mesh_id=0);
         ~Stamp();

         void set_id(uint32_t id);
         void set_x(float x);
         void set_y(float y);
         void set_multi_mesh_id(uint32_t multi_mesh_id);
         uint32_t get_id() const;
         float get_x() const;
         float get_y() const;
         uint32_t get_multi_mesh_id() const;
         void reassign_multi_mesh_id(uint32_t new_multi_mesh_id=0);
      };
   }
}



