#pragma once


#include <vector>
#include <allegro5/allegro_primitives.h>
#include <AllegroFlare/Vec2D.hpp>
#include <AllegroFlare/Vec3D.hpp>




namespace AllegroFlare
{
   typedef struct
   {
      float x, y, z;
      float u, v;
      ALLEGRO_COLOR color;
      float nx, ny, nz;
   } ALLEGRO_VERTEX_WITH_NORMAL;




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

   public:
      ALLEGRO_VERTEX_DECL *vertex_declaration;
      std::vector<ALLEGRO_VERTEX_WITH_NORMAL> vertexes;
      ALLEGRO_BITMAP *texture;
      std::vector<named_object> named_objects;

      Model3D();
      ~Model3D();

      bool load_obj_file(const char *filename, float scale=1.0);
      void inspect();
      void clear();
      int get_num_vertexes();
      int get_num_named_objects();
      vec3d get_min_vertex_coordinate();
      vec3d get_max_vertex_coordinate();

      void draw();
      bool draw_object(int index);
      bool draw_object(std::string name);

      void set_texture(ALLEGRO_BITMAP *tx);
      bool set_named_object_texture(int index, ALLEGRO_BITMAP *tx);
      bool set_named_object_texture(std::string object_name, ALLEGRO_BITMAP *tx);
      bool set_named_object_color(int index, ALLEGRO_COLOR col);
      bool set_named_object_color(std::string object_name, ALLEGRO_COLOR col);
      void scale(float scale);
   };
}


