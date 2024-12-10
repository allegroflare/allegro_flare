#pragma once


#include <vector>
#include <allegro5/allegro_primitives.h>
#include <AllegroFlare/Vec2D.hpp>
#include <AllegroFlare/Vec3D.hpp>
#include <AllegroFlare/Physics/AABB3D.hpp>
#include <AllegroFlare/ALLEGRO_VERTEX_WITH_NORMAL.hpp>



namespace AllegroFlare
{
   class Model3D
   {
   public:
      struct named_object
      {
      public:
         std::string identifier;
         std::vector<int> index_list;
         ALLEGRO_BITMAP *texture;
      };

   private:
      friend class Model3DObjLoader;

      struct vt_coord
      {
      public:
         float u;
         float v;
      };

      bool initialized;
      void validate_initialized_or_output_to_cerr(std::string calling_function);
      void validate_not_vertex_buffer(std::string calling_function);

   public:
      ALLEGRO_VERTEX_DECL *vertex_declaration;
      std::vector<ALLEGRO_VERTEX_WITH_NORMAL> vertices;
      ALLEGRO_VERTEX_BUFFER *vertex_buffer;
      ALLEGRO_BITMAP *texture;
      std::vector<named_object> named_objects;

      Model3D();
      ~Model3D();

      void initialize();
      void build_vertex_declaration();
      bool load_obj_file(const char *filename, float scale=1.0);
      void inspect_vertices();
      void inspect_status();
      void destroy_and_clear_vertex_buffer();
      void clear();

      void append(AllegroFlare::Model3D &other);
      bool flatten_single_named_object();
      int get_num_vertices();
      int get_num_named_objects(); // this should be renamed to "count_..."
      int count_num_named_objects_with_name(std::string object_name);
      void promote_to_vertex_buffer();

      vec3d get_min_vertex_coordinate(); // should be renamed "calc_min_vertex..."
      vec3d get_max_vertex_coordinate(); // should be renamed "calc_min_vertex..."
      AllegroFlare::Physics::AABB3D build_bounding_box();

      std::vector<ALLEGRO_VERTEX_WITH_NORMAL> extract_named_object_vertices(std::string object_name);
      std::vector<std::vector<ALLEGRO_VERTEX_WITH_NORMAL>> extract_named_objects_vertices(std::string object_name);

      void draw();
      bool draw_object(int index);
      bool draw_object(std::string name);

      void set_texture(ALLEGRO_BITMAP *tx);
      bool set_named_object_texture(int index, ALLEGRO_BITMAP *tx);
      bool set_named_object_texture(std::string object_name, ALLEGRO_BITMAP *tx);
      bool set_named_object_color(int index, ALLEGRO_COLOR col);
      bool set_named_object_color(std::string object_name, ALLEGRO_COLOR col);
      void remove_named_object(std::string object_name); // TODO: Handle the edge cases of this implementation
      void remove_named_objects(std::string object_name);
      void scale(float scale);
      void displace(AllegroFlare::Vec3D displacement);
      //void transform(ALLEGRO_TRANSFORM *transform); // NOTE: There are issues with this, specifically with rotation
                                                      // on the normal. It needs to be tested in coordination with the
                                                      // CollisionMesh to ensure it will work as expected

      std::vector<ALLEGRO_VERTEX_WITH_NORMAL> &vertexes = vertices; // TODO: Remove this at some point
   };
}


