


#include <AllegroFlare/MultitextureModel3D.hpp>

#include <allegro5/allegro_color.h>
#include <allegro5/allegro_primitives.h>
#include <AllegroFlare/MultitextureModel3DObjLoader.hpp>
#include <AllegroFlare/Vec3D.hpp>
#include <cstdio>
#include <iostream>
#include <sstream>




namespace AllegroFlare
{
   MultitextureModel3D::MultitextureModel3D()
      : initialized(false)
      , vertex_declaration(nullptr)
      , vertexes()
      , vertex_buffer(nullptr)
      , texture(nullptr)
      , named_objects()
   {
      //build_vertex_declaration();
   }




   MultitextureModel3D::~MultitextureModel3D()
   {
      if (vertex_declaration) al_destroy_vertex_decl(vertex_declaration);
   }


   void MultitextureModel3D::initialize()
   {
      if (initialized) throw std::runtime_error("[AllegroFlare::MultitextureModel3D::initialize]: error: cannot initialize "
                                                "more than once.");
      if (!al_is_system_installed() || !al_is_primitives_addon_initialized() || !al_get_current_display())
      {
         // TODO: al_get_current_display() is needed in this case because al_create_vertex_decl has a condition
         // requiring a display, here: https://github.com/liballeg/allegro5/blob/d2b6b61cb28e1ece3c78907f18c3e34725e3623e/addons/primitives/primitives.c#L211-L215
     
         throw std::runtime_error("[AllegroFlare::MultitextureModel3D::initialize]: error: al_is_system_installed() or "
                                  "al_is_primitives_addon_initialized() or al_get_current_display() not met.");
      }
      build_vertex_declaration();

      initialized = true;
   }


   void MultitextureModel3D::build_vertex_declaration()
   {
      if (vertex_declaration) return;
      vertex_declaration = create_ALLEGRO_VERTEX_WITH_TWO_UVS_AND_NORMAL_vertex_declaration();
   }




   bool MultitextureModel3D::load_obj_file(const char *filename, float scale)
   {
      validate_initialized_or_output_to_cerr("load_obj_file");
      MultitextureModel3DObjLoader loader(this, filename, scale);
      return loader.load();
   }




   void MultitextureModel3D::inspect_status()
   {
      std::stringstream output;
      output << "-             model:" << std::endl;
      output << "       num_vertices: " << vertexes.size() << std::endl;
      output << "  has_vertex_buffer: " << (vertex_buffer ? "true" : "false") << std::endl;
      output << "  num_named_objects: " << named_objects.size() << std::endl;

      // output info for named objects
      if (named_objects.size() > 0) output << "      named_objects:" << std::endl;
      for (int i=0; i<named_objects.size(); i++)
      {
         output << "                     - named_object:" << std::endl;
         output << "                         identifier: \"" << named_objects[i].identifier << "\"" << std::endl;
         output << "                        num_indexes: " << named_objects[i].index_list.size() << std::endl;
      }

      std::cout << output.str();
   }




   void MultitextureModel3D::validate_initialized_or_output_to_cerr(std::string calling_function)
   {
      if (!initialized)
      {
         std::cerr << "[AllegroFlare::MultitextureModel3D::" << calling_function << "]: error: initialized not met." << std::endl;
      }
   }



   void MultitextureModel3D::validate_not_vertex_buffer(std::string calling_function)
   {
      if (vertex_buffer)
      {
         std::stringstream error_message;
         error_message << "[AllegroFlare::MultitextureModel3D::" << calling_function << "]: error: This function is not supported "
                       << "in this current model state. The model is being rendered as a vertex_buffer.";
         throw std::runtime_error(error_message.str());
      }
   }


   void MultitextureModel3D::destroy_and_clear_vertex_buffer()
   {
      if (vertex_buffer)
      {
         al_destroy_vertex_buffer(vertex_buffer);
         vertex_buffer = nullptr;
         return;
      }
   }


   void MultitextureModel3D::clear()
   {
      validate_initialized_or_output_to_cerr("clear");

      vertexes.clear();
      named_objects.clear();
      destroy_and_clear_vertex_buffer();
   }



   void MultitextureModel3D::append(AllegroFlare::MultitextureModel3D &other)
   {
      // Either model contains named objects, append is not supported
      if ((named_objects.size() > 0) || (other.named_objects.size() > 0))
      {
         std::stringstream error_message;
         error_message << "[AllegroFlare::MultitextureModel3D::append] error: "
                       << "Models cannot be merged because one or the other contains named objects. If you wish to "
                       << "merge, you will need to flatten (flatten_single_named_object()) the model. Merging models "
                       << "with named objects is not supported for the time being.";
         throw std::runtime_error(error_message.str());
      }

      // Output warning if the textures do not match
      if (other.texture && (other.texture != texture))
      {
         std::cout << "[AllegroFlare::MultitextureModel3D::append]: warning: The object being appended contains a texture that is "
                   << "different from this source model's texture. The source model's texture will be used."
                   << std::endl;
      }

      // Destroy our existing vertex buffer if it exists
      if (vertex_buffer)
      {
         std::cout << "[AllegroFlare::MultitextureModel3D::append]: warning: The source model contains a vertex buffer. It will "
                   << "be destroyed and will need to be recreated if you wish to use one with the newly merged data."
                   << std::endl;

         destroy_and_clear_vertex_buffer();
      }

      vertexes.insert(vertexes.end(), other.vertexes.begin(), other.vertexes.end());
   }



   // returns true if flattened or if is already flattened
   bool MultitextureModel3D::flatten_single_named_object()
   {
      validate_initialized_or_output_to_cerr("flatten_single_named_object");
      validate_not_vertex_buffer("flatten_single_named_object");

      // if there are more than one named object, throw an error
      if (get_num_named_objects() > 1)
      {
         std::stringstream error_message;
         error_message << "[AllegroFlare::MultitextureModel3D::flatten_single_named_object] error: "
                       << "Cannot flatten model because it contains more than one named object "
                       << "(" << get_num_named_objects() << " named object(s)).";
         throw std::runtime_error(error_message.str());
      }

      if (named_objects[0].texture)
      {
         std::cout << "[AllegroFlare::MultitextureModel3D::flatten_single_named_object]: warning: The named object (identifier: \""
                   << named_objects[0].identifier << "\") contains a bitmap.  It may be left dangling as it is "
                   << "flattened."
                   << std::endl;
      }

      named_objects.clear();
      return true;
   }



   int MultitextureModel3D::get_num_vertexes()
   {
      return vertexes.size();
   }




   int MultitextureModel3D::get_num_named_objects()
   {
      return named_objects.size();
   }



   void MultitextureModel3D::promote_to_vertex_buffer()
   {
      validate_initialized_or_output_to_cerr("promote_to_vertex_buffer");
      if (vertex_buffer) return;

      if (get_num_named_objects() >= 1)
      {
         std::stringstream error_message;
         error_message << "[AllegroFlare::MultitextureModel3D::promote_to_vertex_buffer] error: "
                       << "Cannot promote because it contains more than one named object "
                       << "(" << get_num_named_objects() << " named object(s)).";
         throw std::runtime_error(error_message.str());
      }

      vertex_buffer = al_create_vertex_buffer(
         vertex_declaration,
         &vertexes[0],
         vertexes.size(),
         ALLEGRO_PRIM_BUFFER_STATIC
      );
   }



   void MultitextureModel3D::draw()
   {
      validate_initialized_or_output_to_cerr("draw");

      if (vertex_buffer)
      {
         al_draw_vertex_buffer(vertex_buffer, texture, 0, vertexes.size(), ALLEGRO_PRIM_TRIANGLE_LIST);
         return;
      }

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




   bool MultitextureModel3D::draw_object(int index)
   {
      validate_initialized_or_output_to_cerr("draw_object");
      validate_not_vertex_buffer("draw_object");

      if (index < 0 || index > (int)named_objects.size()) return false;

      named_object &object = named_objects[index];

      al_draw_indexed_prim(&vertexes[0], vertex_declaration,
            (object.texture) ? object.texture : texture,
            &object.index_list[0], object.index_list.size(), ALLEGRO_PRIM_TRIANGLE_LIST);

      return true;
   }




   bool MultitextureModel3D::draw_object(std::string name)
   {
      validate_initialized_or_output_to_cerr("draw_object");
      validate_not_vertex_buffer("draw_object");

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




   void MultitextureModel3D::set_texture(ALLEGRO_BITMAP *tx)
   {
      validate_initialized_or_output_to_cerr("set_texture");
      texture = tx;
   }




   bool MultitextureModel3D::set_named_object_texture(int index, ALLEGRO_BITMAP *tx)
   {
      validate_initialized_or_output_to_cerr("set_named_object_texture");
      validate_not_vertex_buffer("set_named_object_texture");

      if (index < 0 || index > (int)named_objects.size()) return false;
      named_objects[index].texture = tx;
      return true;
   }




   bool MultitextureModel3D::set_named_object_texture(std::string object_name, ALLEGRO_BITMAP *tx)
   {
      validate_initialized_or_output_to_cerr("set_named_object_texture");
      validate_not_vertex_buffer("set_named_object_texture");

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




   void MultitextureModel3D::scale(float scale)
   {
      validate_initialized_or_output_to_cerr("scale");
      validate_not_vertex_buffer("scale");

      for (unsigned i=0; i<vertexes.size(); i++)
      {
         vertexes[i].x *= scale;
         vertexes[i].y *= scale;
         vertexes[i].z *= scale;
      }
   }



   void MultitextureModel3D::displace(AllegroFlare::Vec3D displacement)
   {
      validate_initialized_or_output_to_cerr("displace");
      validate_not_vertex_buffer("displace");

      for (unsigned i=0; i<vertexes.size(); i++)
      {
         vertexes[i].x += displacement.x;
         vertexes[i].y += displacement.y;
         vertexes[i].z += displacement.z;
      }
   }




   vec3d MultitextureModel3D::get_min_vertex_coordinate()
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




   vec3d MultitextureModel3D::get_max_vertex_coordinate()
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



   AllegroFlare::Physics::AABB3D MultitextureModel3D::build_bounding_box()
   {
      return AllegroFlare::Physics::AABB3D(get_min_vertex_coordinate(), get_max_vertex_coordinate());
   }


   std::vector<AllegroFlare::ALLEGRO_VERTEX_WITH_TWO_UVS_AND_NORMAL> MultitextureModel3D::extract_named_object_vertices(std::string object_name)
   {
      // TODO: Consider that there could be multiple named objects with the same name; Throw in this case.
      named_object *found_named_object = nullptr;

      bool object_exists = false;
      for (unsigned i=0; i<named_objects.size(); i++)
      {
         if (named_objects[i].identifier == object_name)
         {
            found_named_object = &named_objects[i];
            break;
         }
      }

      if (!found_named_object)
      {
         std::stringstream error_message;
         error_message << "[AllegroFlare::MultitextureModel3D::extract_named_object_vertices] error: "
                       << "Looking for named_object named \"" << object_name << "\" but it does not exist.";
         throw std::runtime_error(error_message.str());
      }

      std::vector<AllegroFlare::ALLEGRO_VERTEX_WITH_TWO_UVS_AND_NORMAL> result;

      for (auto &vertex_index_num : found_named_object->index_list)
      {
         result.push_back(vertexes[vertex_index_num]);
      }

      return result;
   }
}



