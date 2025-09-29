



#include <AllegroFlare/Placement3D.hpp>

#include <AllegroFlare/Useful.hpp> // just for #define TAU
#include <AllegroFlare/Logger.hpp>
#include <math.h> // just cos, sin




namespace AllegroFlare
{



Placement3D::Placement3D()
   : position(0, 0, 0)
   , size(0, 0, 0)
   , align(0.5, 0.5, 0.5)
   , scale(1.0, 1.0, 1.0)
   , anchor(0, 0, 0)
   , rotation(0, 0, 0)
   , rotation_order(RotationOrder::YXZ)
{}




Placement3D::Placement3D(float x, float y, float z)
   : position(x, y, z)
   , size(0, 0, 0)
   , align(0.5, 0.5, 0.5)
   , scale(1.0, 1.0, 1.0)
   , anchor(0, 0, 0)
   , rotation(0, 0, 0)
{}




Placement3D::Placement3D(AllegroFlare::Vec3D position)
   : position(position.x, position.y, position.z)
   , size(0, 0, 0)
   , align(0.5, 0.5, 0.5)
   , scale(1.0, 1.0, 1.0)
   , anchor(0, 0, 0)
   , rotation(0, 0, 0)
{}




void Placement3D::start_transform()
{
   ALLEGRO_TRANSFORM transform;

   if (!al_get_current_transform()) return;
   al_copy_transform(&previous_transform, al_get_current_transform());

   this->build_transform(&transform);

   al_compose_transform(&transform, &previous_transform);
   al_use_transform(&transform);
}




void Placement3D::start_transform_with_zyx_ordered_rotation()
{
   ALLEGRO_TRANSFORM transform;

   if (!al_get_current_transform()) return;
   al_copy_transform(&previous_transform, al_get_current_transform());

   this->build_transform_with_zyx_ordered_rotation(&transform);

   al_compose_transform(&transform, &previous_transform);
   al_use_transform(&transform);
}




void Placement3D::start_reverse_transform()
{
   ALLEGRO_TRANSFORM transform;

   if (!al_get_current_transform()) return;
   al_copy_transform(&previous_transform, al_get_current_transform());

   this->build_reverse_transform(&transform);

   al_compose_transform(&transform, &previous_transform);
   al_use_transform(&transform);
}




void Placement3D::restore_transform()
{
   if (!al_get_current_transform()) return;
   al_use_transform(&previous_transform);
}




void Placement3D::build_transform(ALLEGRO_TRANSFORM *transform)
{
   al_identity_transform(transform);

   // offset for alignment and anchors
   al_translate_transform_3d(transform, -align.x*size.x, -align.y*size.y, -align.z*size.z);
   al_scale_transform_3d(transform, scale.x, scale.y, scale.z);
   al_translate_transform_3d(transform, anchor.x, anchor.y, anchor.z);

   // rotate
   const float &rx = rotation.x * AllegroFlare::TAU;
   const float &ry = rotation.y * AllegroFlare::TAU;
   const float &rz = rotation.z * AllegroFlare::TAU;

   switch (rotation_order)
   {
      case RotationOrder::XYZ:
         al_rotate_transform_3d(transform, 1, 0, 0, rx);
         al_rotate_transform_3d(transform, 0, 1, 0, ry);
         al_rotate_transform_3d(transform, 0, 0, 1, rz);
         break;
      case RotationOrder::XZY:
         al_rotate_transform_3d(transform, 1, 0, 0, rx);
         al_rotate_transform_3d(transform, 0, 0, 1, rz);
         al_rotate_transform_3d(transform, 0, 1, 0, ry);
         break;
      case RotationOrder::YXZ:
         al_rotate_transform_3d(transform, 0, 1, 0, ry);
         al_rotate_transform_3d(transform, 1, 0, 0, rx);
         al_rotate_transform_3d(transform, 0, 0, 1, rz);
         break;
      case RotationOrder::YZX:
         al_rotate_transform_3d(transform, 0, 1, 0, ry);
         al_rotate_transform_3d(transform, 0, 0, 1, rz);
         al_rotate_transform_3d(transform, 1, 0, 0, rx);
         break;
      case RotationOrder::ZXY:
         al_rotate_transform_3d(transform, 0, 0, 1, rz);
         al_rotate_transform_3d(transform, 1, 0, 0, rx);
         al_rotate_transform_3d(transform, 0, 1, 0, ry);
         break;
      case RotationOrder::ZYX:
         al_rotate_transform_3d(transform, 0, 0, 1, rz);
         al_rotate_transform_3d(transform, 0, 1, 0, ry);
         al_rotate_transform_3d(transform, 1, 0, 0, rx);
         break;
      default: // Includes UNDEF
         AllegroFlare::Logger::throw_error(
            THIS_CLASS_AND_METHOD_NAME,
            "Unhandled rotation_order."
         );
         break;
   }

   // translate
   al_translate_transform_3d(transform, position.x, position.y, position.z);
}



void Placement3D::build_reverse_transform(ALLEGRO_TRANSFORM *transform)
{
   al_identity_transform(transform);

   // translate
   al_translate_transform_3d(transform, -position.x, -position.y, -position.z);

   // rotate
   const float &rx = rotation.x * AllegroFlare::TAU;
   const float &ry = rotation.y * AllegroFlare::TAU;
   const float &rz = rotation.z * AllegroFlare::TAU;

   switch (rotation_order)
   {
      case RotationOrder::XYZ:
         al_rotate_transform_3d(transform, 0, 0, -1, rz);
         al_rotate_transform_3d(transform, 0, -1, 0, ry);
         al_rotate_transform_3d(transform, -1, 0, 0, rx);
         break;
      case RotationOrder::XZY:
         al_rotate_transform_3d(transform, 0, -1, 0, ry);
         al_rotate_transform_3d(transform, 0, 0, -1, rz);
         al_rotate_transform_3d(transform, -1, 0, 0, rx);
         break;
      case RotationOrder::YXZ:
         al_rotate_transform_3d(transform, 0, 0, -1, rz);
         al_rotate_transform_3d(transform, -1, 0, 0, rx);
         al_rotate_transform_3d(transform, 0, -1, 0, ry);
         break;
      case RotationOrder::YZX:
         al_rotate_transform_3d(transform, -1, 0, 0, rx);
         al_rotate_transform_3d(transform, 0, 0, -1, rz);
         al_rotate_transform_3d(transform, 0, -1, 0, ry);
         break;
      case RotationOrder::ZXY:
         al_rotate_transform_3d(transform, 0, -1, 0, ry);
         al_rotate_transform_3d(transform, -1, 0, 0, rx);
         al_rotate_transform_3d(transform, 0, 0, -1, rz);
         break;
      case RotationOrder::ZYX:
         al_rotate_transform_3d(transform, -1, 0, 0, rx);
         al_rotate_transform_3d(transform, 0, -1, 0, ry);
         al_rotate_transform_3d(transform, 0, 0, -1, rz);
         break;
      default: // Includes UNDEF
         AllegroFlare::Logger::throw_error(
            THIS_CLASS_AND_METHOD_NAME,
            "Unhandled rotation_order."
         );
         break;
   }

   // offset for alignment and anchors
   al_translate_transform_3d(transform, -anchor.x, -anchor.y, -anchor.z);
   al_scale_transform_3d(transform, 1.0/scale.x, 1.0/scale.y, 1.0/scale.z);
   al_translate_transform_3d(transform, align.x*size.x, align.y*size.y, align.z*size.z);
}



void Placement3D::build_transform_with_zyx_ordered_rotation(ALLEGRO_TRANSFORM *transform)
{
   al_identity_transform(transform);

   // offset for alignment and anchors
   al_translate_transform_3d(transform, -align.x*size.x, -align.y*size.y, -align.z*size.z);
   al_scale_transform_3d(transform, scale.x, scale.y, scale.z);
   al_translate_transform_3d(transform, anchor.x, anchor.y, anchor.z);

   // rotate
   al_rotate_transform_3d(transform, 0, 0, 1, rotation.z * AllegroFlare::TAU);
   al_rotate_transform_3d(transform, 0, 1, 0, rotation.y * AllegroFlare::TAU);
   al_rotate_transform_3d(transform, 1, 0, 0, rotation.x * AllegroFlare::TAU);
   //al_rotate_transform_3d(transform, 0, 1, 0, rotation.y * AllegroFlare::TAU);
   //al_rotate_transform_3d(transform, 0, 0, 1, rotation.z * AllegroFlare::TAU);

   // translate
   al_translate_transform_3d(transform, position.x, position.y, position.z);
}



void Placement3D::build_view_projection_transform(
      ALLEGRO_TRANSFORM *transform,
      float near_plane,
      float far_plane,
      float zoom,
      float surface_width,
      float surface_height
   )
{
   // TODO: Consider validating transform
   // TODO: Consider validating arguments are realistic
   // TODO: Add tests for this function

   build_reverse_transform(transform);

   float mul = near_plane / zoom;
   float aspect_ratio = surface_height / surface_width;

   al_perspective_transform(
      transform,
      -1 * mul,
      aspect_ratio * mul,
      near_plane, 1 * mul,
      -aspect_ratio * mul,
      far_plane
   );
};



AllegroFlare::Vec3D Placement3D::build_strafe_vector_xz()
{
   // TODO: Test this method

   AllegroFlare::Vec2D move_vec(
      cos(rotation.y * AllegroFlare::TAU),
      sin(rotation.y * AllegroFlare::TAU)
   );
   move_vec.normalized();
   return AllegroFlare::Vec3D(move_vec.x, 0, move_vec.y);
}



AllegroFlare::Vec3D Placement3D::get_real_position()
{
   AllegroFlare::Vec3D real_position(0, 0, 0);
   ALLEGRO_TRANSFORM t;
   build_transform(&t);

   al_transform_coordinates_3d(&t, &real_position.x, &real_position.y, &real_position.z);

   return real_position;
}




Placement3D& Placement3D::operator+=(const Placement3D& other)
{
   position += other.position;
   size += other.size;
   align += other.align;
   scale += other.scale;
   anchor += other.anchor;
   rotation += other.rotation;
   return *this;
}




bool Placement3D::operator==(const Placement3D& other) const
{
   return (
      position == other.position
      && size == other.size
      && align == other.align
      && scale == other.scale
      && anchor == other.anchor
      && rotation == other.rotation
      );
}



std::string Placement3D::rotation_order_to_string(RotationOrder order)
{
   switch (order)
   {
      case RotationOrder::XYZ: return "XYZ";
      case RotationOrder::XZY: return "XZY";
      case RotationOrder::YXZ: return "YXZ";
      case RotationOrder::YZX: return "YZX";
      case RotationOrder::ZXY: return "ZXY";
      case RotationOrder::ZYX: return "ZYX";
      default: return "Unknown";
   }
}



void Placement3D::next_rotation_order(bool loop)
{
   if (rotation_order == RotationOrder::UNDEF)
   {
      AllegroFlare::Logger::throw_error(
         THIS_CLASS_AND_METHOD_NAME,
         "Unhandled rotation_order."
      );
   }

   int first = static_cast<int>(RotationOrder::XYZ);
   int last  = static_cast<int>(RotationOrder::ZYX);
   int value = static_cast<int>(rotation_order);

   if (value == last)
   {
      rotation_order = loop ? RotationOrder::XYZ : RotationOrder::ZYX;
      return;
   }

   rotation_order = static_cast<RotationOrder>(value + 1);
}



void Placement3D::previous_rotation_order(bool loop)
{
   if (rotation_order == RotationOrder::UNDEF)
   {
      AllegroFlare::Logger::throw_error(
         THIS_CLASS_AND_METHOD_NAME,
         "Unhandled rotation_order."
      );
   }

   int first = static_cast<int>(RotationOrder::XYZ);
   int last  = static_cast<int>(RotationOrder::ZYX);
   int value = static_cast<int>(rotation_order);

   if (value == first)
   {
      rotation_order = loop ? RotationOrder::ZYX : RotationOrder::XYZ;
      return;
   }

   rotation_order = static_cast<RotationOrder>(value - 1);
}



} // namespace AllegroFlare




