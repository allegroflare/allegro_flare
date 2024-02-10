#pragma once


#include <AllegroFlare/Camera2D.hpp>
#include <string>


namespace AllegroFlare
{
   namespace CameraControlStrategies2D
   {
      class Base
      {
      public:
         static constexpr char* TYPE = (char*)"AllegroFlare/CameraControlStrategies2D/Base";

      private:
         std::string type;
         AllegroFlare::Camera2D* camera;
         bool initialized;

      protected:


      public:
         Base(std::string type=AllegroFlare::CameraControlStrategies2D::Base::TYPE, AllegroFlare::Camera2D* camera=nullptr);
         virtual ~Base();

         void set_camera(AllegroFlare::Camera2D* camera);
         std::string get_type() const;
         AllegroFlare::Camera2D* get_camera() const;
         bool get_initialized() const;
         AllegroFlare::Camera2D* &get_camera_ref();
         bool is_type(std::string possible_type="");
         virtual void initialize();
         virtual void update();
      };
   }
}



