#pragma once


#include <AllegroFlare/Placement2D.hpp>
#include <string>


namespace AllegroFlare
{
   namespace CameraControlStrategies2D
   {
      class Base
      {
      public:
         static constexpr char* TYPE = "AllegroFlare/CameraControlStrategies2D/Base";

      private:
         std::string type;
         AllegroFlare::Placement2D* camera;
         bool initialized;

      protected:


      public:
         Base(std::string type=AllegroFlare::CameraControlStrategies2D::Base::TYPE, AllegroFlare::Placement2D* camera=nullptr);
         virtual ~Base();

         void set_camera(AllegroFlare::Placement2D* camera);
         std::string get_type() const;
         AllegroFlare::Placement2D* get_camera() const;
         bool get_initialized() const;
         AllegroFlare::Placement2D* &get_camera_ref();
         bool is_type(std::string possible_type="");
         virtual void initialize();
         virtual void update();
      };
   }
}



