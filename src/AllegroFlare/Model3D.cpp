


#include <AllegroFlare/Model3D.hpp>

#include <allegro5/allegro_color.h>
#include <allegro5/allegro_primitives.h>
#include <AllegroFlare/Model3DObjLoader.hpp>
#include <AllegroFlare/Vec3D.hpp>
#include <cstdio>
#include <iostream>
#include <sstream>




namespace AllegroFlare
{
   Model3D::Model3D()
      : vertex_declaration(nullptr)
      , vertexes()
      , vertex_buffer(nullptr)
      , texture(nullptr)
      , named_objects()
      , initialized(false)
   {
      //build_vertex_declaration();
   }




   Model3D::~Model3D()
   {
      if (vertex_declaration) al_destroy_vertex_decl(vertex_declaration);
   }


   void Model3D::initialize()
   {
      if (initialized) throw std::runtime_error("[AllegroFlare::Model3D::initialize]: error: cannot initialize "
                                                "more than once.");
      if (!al_is_system_installed() || !al_is_primitives_addon_initialized() || !al_get_current_display())
      {
         // TODO: be sure if al_get_current_display() is even required here
         throw std::runtime_error("[AllegroFlare::Model3D::initialize]: error: al_is_system_installed() or "
                                  "al_is_primitives_addon_initialized() or al_get_current_display() not met.");
      }
      build_vertex_declaration();

      initialized = true;
   }


   void Model3D::build_vertex_declaration()
   {
      if (vertex_declaration) return;

      ALLEGRO_VERTEX_ELEMENT elems[] = {
         {ALLEGRO_PRIM_POSITION, ALLEGRO_PRIM_FLOAT_3, offsetof(ALLEGRO_VERTEX_WITH_NORMAL, x)},
         {ALLEGRO_PRIM_TEX_COORD, ALLEGRO_PRIM_FLOAT_2, offsetof(ALLEGRO_VERTEX_WITH_NORMAL, u)},
         {ALLEGRO_PRIM_COLOR_ATTR, 0, offsetof(ALLEGRO_VERTEX_WITH_NORMAL, color)},
         {ALLEGRO_PRIM_USER_ATTR, ALLEGRO_PRIM_FLOAT_3, offsetof(ALLEGRO_VERTEX_WITH_NORMAL, nx)},
         {0, 0, 0}
      };

      vertex_declaration = al_create_vertex_decl(elems, sizeof(ALLEGRO_VERTEX_WITH_NORMAL));
   }




   bool Model3D::load_obj_file(const char *filename, float scale)
   {
      validate_initialized_or_output_to_cerr("load_obj_file");
      Model3DObjLoader loader(this, filename, scale);
      return loader.load();
   }




   void Model3D::inspect_vertices()
   {
      for (unsigned i=0; i<vertexes.size(); i++)
         printf("[%d] %f %f %f : %f %f : %f %f %f\n", i, vertexes[i].x, vertexes[i].y, vertexes[i].z, vertexes[i].u, vertexes[i].v, vertexes[i].nx, vertexes[i].ny, vertexes[i].nz);
   }




   void Model3D::validate_initialized_or_output_to_cerr(std::string calling_function)
   {
      if (!initialized)
      {
         std::cerr << "[AllegroFlare::Model3D::" << calling_function << "]: error: initialized not met." << std::endl;
      }
   }




   void Model3D::clear()
   {
      validate_initialized_or_output_to_cerr("clear");
      vertexes.clear();
      named_objects.clear();
   }



   void Model3D::append(AllegroFlare::Model3D &other)
   {
      if (vertex_buffer)
      {
         al_destroy_vertex_buffer(vertex_buffer);
         vertex_buffer = nullptr;
      }

      // if the model contains named objects, append is not supported
      if ((named_objects.size() > 0) || (other.named_objects.size() > 0))
      {
         std::stringstream error_message;
         error_message << "[AllegroFlare::Model3D::append] error: "
                       << "Models cannot be merged because one or the other contains named objects. Merging models "
                       << "with named objects is not supported.";
         throw std::runtime_error(error_message.str());
      }
   }



   int Model3D::get_num_vertexes()
   {
      return vertexes.size();
   }




   int Model3D::get_num_named_objects()
   {
      return named_objects.size();
   }




   void Model3D::draw()
   {
      validate_initialized_or_output_to_cerr("draw");
      if (vertexes.empty()) return;

      if (named_objects.empty())
      {
         al_draw_prim(&vertexes[0], vertex_declaration, texture, 0, vertexes.size(), ALLEGRO_PRIM_TRIANGLE_LIST);
      }
      else
      {
         // draw each of the named objects individually
         // TODO: this is not optimized, revisit this in the future
         for (unsigned i=0; i<named_objects.size(); i++)
         {
            draw_object(i);
         }
      }
   }




   bool Model3D::draw_object(int index)
   {
      validate_initialized_or_output_to_cerr("draw_object");
      if (index < 0 || index > (int)named_objects.size()) return false;

      named_object &object = named_objects[index];

      al_draw_indexed_prim(&vertexes[0], vertex_declaration,
            (object.texture) ? object.texture : texture,
            &object.index_list[0], object.index_list.size(), ALLEGRO_PRIM_TRIANGLE_LIST);

      return true;
   }




   bool Model3D::draw_object(std::string name)
   {
      validate_initialized_or_output_to_cerr("draw_object");
      bool object_exists = false;
      for (unsigned i=0; i<named_objects.size(); i++)
      {
         if (named_objects[i].identifier == name)
         {
            draw_object(i);
            object_exists = true;
         }
      }
      return object_exists;
   }




   void Model3D::set_texture(ALLEGRO_BITMAP *tx)
   {
      validate_initialized_or_output_to_cerr("set_texture");
      texture = tx;
   }




   bool Model3D::set_named_object_texture(int index, ALLEGRO_BITMAP *tx)
   {
      validate_initialized_or_output_to_cerr("set_named_object_texture");
      if (index < 0 || index > (int)named_objects.size()) return false;
      named_objects[index].texture = tx;
      return true;
   }




   bool Model3D::set_named_object_texture(std::string object_name, ALLEGRO_BITMAP *tx)
   {
      validate_initialized_or_output_to_cerr("set_named_object_texture");
      bool object_exists = false;
      for (unsigned i=0; i<named_objects.size(); i++)
      {
         if (named_objects[i].identifier == object_name)
         {
            named_objects[i].texture = tx;
            object_exists = true;
         }
      }
      return object_exists;
   }




   void Model3D::scale(float scale)
   {
      validate_initialized_or_output_to_cerr("scale");
      for (unsigned i=0; i<vertexes.size(); i++)
      {
         vertexes[i].x *= scale;
         vertexes[i].y *= scale;
         vertexes[i].z *= scale;
      }
   }



   void Model3D::displace(AllegroFlare::Vec3D displacement)
   {
      validate_initialized_or_output_to_cerr("displace");
      for (unsigned i=0; i<vertexes.size(); i++)
      {
         vertexes[i].x += displacement.x;
         vertexes[i].y += displacement.y;
         vertexes[i].z += displacement.z;
      }
   }




   vec3d Model3D::get_min_vertex_coordinate()
   {
      validate_initialized_or_output_to_cerr("get_min_vertex_coordinate");
      if (vertexes.empty()) return vec3d(0, 0, 0);

      vec3d min_coord = vec3d(vertexes[0].x, vertexes[0].y, vertexes[0].z);
      for (unsigned i=1; i<vertexes.size(); i++)
      {
         if (vertexes[i].x < min_coord.x) min_coord.x = vertexes[i].x;
         if (vertexes[i].y < min_coord.y) min_coord.y = vertexes[i].y;
         if (vertexes[i].z < min_coord.z) min_coord.z = vertexes[i].z;
      }
      return min_coord;
   }




   vec3d Model3D::get_max_vertex_coordinate()
   {
      validate_initialized_or_output_to_cerr("get_max_vertex_coordinate");
      if (vertexes.empty()) return vec3d(0, 0, 0);

      vec3d max_coord = vec3d(vertexes[0].x, vertexes[0].y, vertexes[0].z);
      for (unsigned i=0; i<vertexes.size(); i++)
      {
         if (vertexes[i].x > max_coord.x) max_coord.x = vertexes[i].x;
         if (vertexes[i].y > max_coord.y) max_coord.y = vertexes[i].y;
         if (vertexes[i].z > max_coord.z) max_coord.z = vertexes[i].z;
      }
      return max_coord;
   }
}



