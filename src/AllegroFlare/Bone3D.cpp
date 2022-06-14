

#include <AllegroFlare/Bone3D.hpp>



namespace AllegroFlare
{


Bone3D::Bone3D(std::vector<AllegroFlare::Bone3D*> children)
   : AllegroFlare::Placement3D()
   , children(children)
{
}


Bone3D::~Bone3D()
{
}


void Bone3D::set_children(std::vector<AllegroFlare::Bone3D*> children)
{
   this->children = children;
}


std::vector<AllegroFlare::Bone3D*> Bone3D::get_children()
{
   return children;
}


std::vector<AllegroFlare::Bone3D*> &Bone3D::get_children_ref()
{
   return children;
}


void Bone3D::add_child(AllegroFlare::Bone3D* bone)
{
   children.push_back(bone);
   return;
}
} // namespace AllegroFlare


