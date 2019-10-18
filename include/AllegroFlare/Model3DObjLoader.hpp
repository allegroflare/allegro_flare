#pragma once


namespace AllegroFlare
{
   class Model3D;


   class Model3DObjLoader
   {
   private:
      Model3D *model;
      const char *filename;
      float scale;

   public:
      Model3DObjLoader(Model3D *model, const char *filename, float scale=1.0);
      bool load();
   };
}


