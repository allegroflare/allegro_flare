#pragma once


#include <AllegroFlare/Prototypes/Platforming2D/TMJObjectLoaderObjectCustomProperties.hpp>
#include <functional>
#include <string>


namespace AllegroFlare
{
   namespace Prototypes
   {
      namespace Platforming2D
      {
         class TMJObjectLoader
         {
         private:
            std::string filename;
            std::function<void(std::string, float, float, float, float, int, AllegroFlare::Prototypes::Platforming2D::TMJObjectLoaderObjectCustomProperties, void*)> object_parsed_callback;
            void* object_parsed_callback_user_data;
            bool loaded;
            static bool file_exists(std::string filename="[unset-filename]");

         protected:


         public:
            TMJObjectLoader(std::string filename="[unset-filename]");
            ~TMJObjectLoader();

            void set_object_parsed_callback(std::function<void(std::string, float, float, float, float, int, AllegroFlare::Prototypes::Platforming2D::TMJObjectLoaderObjectCustomProperties, void*)> object_parsed_callback);
            void set_object_parsed_callback_user_data(void* object_parsed_callback_user_data);
            std::function<void(std::string, float, float, float, float, int, AllegroFlare::Prototypes::Platforming2D::TMJObjectLoaderObjectCustomProperties, void*)> get_object_parsed_callback() const;
            void* get_object_parsed_callback_user_data() const;
            void load();
         };
      }
   }
}



