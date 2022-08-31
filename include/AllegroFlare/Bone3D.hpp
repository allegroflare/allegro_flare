#pragma once


#include <AllegroFlare/Bone3D.hpp>
#include <AllegroFlare/Placement3D.hpp>
#include <vector>


namespace AllegroFlare
{
   class Bone3D : public AllegroFlare::Placement3D
   {
   private:
      std::vector<AllegroFlare::Bone3D*> children;

   protected:


   public:
      Bone3D(std::vector<AllegroFlare::Bone3D*> children={});
      ~Bone3D();

      void set_children(std::vector<AllegroFlare::Bone3D*> children);
      std::vector<AllegroFlare::Bone3D*> get_children() const;
      std::vector<AllegroFlare::Bone3D*> &get_children_ref();
      void add_child(AllegroFlare::Bone3D* bone={});
   };
}



