#pragma once


#include <AllegroFlare/Placement2D.hpp>


namespace Wicked
{
   namespace CameraControlStrategies
   {
      class Base
      {
      private:
         AllegroFlare::Placement2D* camera;
         bool initialized;

      protected:


      public:
         Base(AllegroFlare::Placement2D* camera=nullptr);
         virtual ~Base();

         void set_camera(AllegroFlare::Placement2D* camera);
         AllegroFlare::Placement2D* get_camera() const;
         bool get_initialized() const;
         AllegroFlare::Placement2D* &get_camera_ref();
         virtual void initialize();
         virtual void update();
      };
   }
}



