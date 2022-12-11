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

         protected:


         public:
            RunBuildProcess(std::string platform="[unset-platform]");
            ~RunBuildProcess();

            void set_platform(std::string platform);
            std::string get_platform() const;
            std::string &get_platform_ref();
         };
      }
   }
}



