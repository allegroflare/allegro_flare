#pragma once




namespace AllegroFlare
{
   namespace GraphicsPipelines
   {
      namespace DynamicEntityPipeline
      {
         class EntityRenderFlags
         {
         public:
            static constexpr char* RENDER_WITH_SKYBOX = (char*)"render_with_skybox";
            static constexpr char* DO_NOT_RENDER = (char*)"do_not_render";
            static constexpr char* DOES_NOT_CAST_SHADOWS = (char*)"does_not_cast_shadows";

         private:

         protected:


         public:
            EntityRenderFlags();
            ~EntityRenderFlags();

         };
      }
   }
}



