#pragma once


#include <string>


namespace AllegroFlare
{
   class InitializedAndDestroyed
   {
   private:
      std::string calling_class_name;
      bool initialized;
      bool destroyed;

   protected:


   public:
      InitializedAndDestroyed(std::string calling_class_name="[unset-calling_class]");
      virtual ~InitializedAndDestroyed();

      bool get_initialized() const;
      bool get_destroyed() const;
      bool is_initialized_and_not_destroyed();
      void initialize();
      void destroy();
      virtual void on_initialize();
      virtual void on_destroy();
   };
}



