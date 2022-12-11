#pragma once


#include <AllegroFlare/MotionComposer/Messages/Base.hpp>
#include <string>


namespace AllegroFlare
{
   namespace MotionComposer
   {
      namespace Messages
      {
         class RunBuildProcess : public AllegroFlare::MotionComposer::Messages::Base
         {
         public:
            static constexpr char* TYPE = (char*)"Messages/RunBuildProcess";

         private:
            std::string platform;
            std::string source_release_zip_url;

         protected:


         public:
            RunBuildProcess(std::string platform="[unset-platform]", std::string source_release_zip_url="[unset-source_release_zip_url]");
            ~RunBuildProcess();

            void set_platform(std::string platform);
            void set_source_release_zip_url(std::string source_release_zip_url);
            std::string get_platform() const;
            std::string get_source_release_zip_url() const;
            std::string &get_platform_ref();
            std::string &get_source_release_zip_url_ref();
         };
      }
   }
}



