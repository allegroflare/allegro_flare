#pragma once




namespace AllegroFlare
{
   class MultiMeshUV
   {
   private:
      float u1;
      float v1;
      float u2;
      float v2;

   protected:


   public:
      MultiMeshUV(float u1=0, float v1=0, float u2=0, float v2=0);
      ~MultiMeshUV();

      void set_u1(float u1);
      void set_v1(float v1);
      void set_u2(float u2);
      void set_v2(float v2);
      float get_u1() const;
      float get_v1() const;
      float get_u2() const;
      float get_v2() const;
      float infer_width();
      float infer_height();
   };
}



