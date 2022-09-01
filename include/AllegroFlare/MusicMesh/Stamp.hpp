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
         uint32_t multimesh_id;

      protected:


      public:
         Stamp(uint32_t id=0, uint32_t multimesh_id=0);
         ~Stamp();

         void set_id(uint32_t id);
         void set_multimesh_id(uint32_t multimesh_id);
         uint32_t get_id() const;
         uint32_t get_multimesh_id() const;
         void reassign_multimesh_id(uint32_t new_multimesh_id=0);
      };
   }
}



