

#include <AllegroFlare/InitializedAndDestroyed.hpp>

#include <AllegroFlare/Logger.hpp>


namespace AllegroFlare
{


InitializedAndDestroyed::InitializedAndDestroyed(std::string calling_class_name)
   : calling_class_name(calling_class_name)
   , initialized(false)
   , destroyed(false)
{
}


InitializedAndDestroyed::~InitializedAndDestroyed()
{
   // TODO: Test if this is still called as a base class from a derived class
   if (is_initialized_and_not_destroyed())
   {
      AllegroFlare::Logger::warn_from(
         THIS_CLASS_AND_METHOD_NAME,
         "The destructor for this class was called before destroy() and after initialize(); Be sure to call "
            "destroy first; Called from \"" + calling_class_name + "\"."
      );
   }
   return;
}


bool InitializedAndDestroyed::get_initialized() const
{
   return initialized;
}


bool InitializedAndDestroyed::get_destroyed() const
{
   return destroyed;
}


bool InitializedAndDestroyed::is_initialized_and_not_destroyed()
{
   return initialized && !destroyed;
}

void InitializedAndDestroyed::initialize()
{
   if (initialized)
   {
      AllegroFlare::Logger::throw_error(
         THIS_CLASS_AND_METHOD_NAME,
         "guard \"(initialized)\" not met; Called from \"" + calling_class_name + "\"."
      );
   }
   if (destroyed)
   {
      AllegroFlare::Logger::throw_error(
         THIS_CLASS_AND_METHOD_NAME,
         "guard \"(destroyed)\" not met; Called from \"" + calling_class_name + "\"."
      );
   }
   on_initialize();
   initialized = true;
}

void InitializedAndDestroyed::destroy()
{
   if (!initialized)
   {
      AllegroFlare::Logger::throw_error(
         THIS_CLASS_AND_METHOD_NAME,
         "guard \"(!initialized)\" not met; Called from \"" + calling_class_name + "\"."
      );
   }
   if (destroyed)
   {
      AllegroFlare::Logger::throw_error(
         THIS_CLASS_AND_METHOD_NAME,
         "guard \"(destroyed)\" not met; Called from \"" + calling_class_name + "\"."
      );
   }
   on_destroy();
   return;
}

void InitializedAndDestroyed::on_initialize()
{
   AllegroFlare::Logger::throw_error(
      THIS_CLASS_AND_METHOD_NAME,
      "Needs to be overridden in the derived class \"" + calling_class_name + "\""
   );
   return;
}

void InitializedAndDestroyed::on_destroy()
{
   AllegroFlare::Logger::throw_error(
      THIS_CLASS_AND_METHOD_NAME,
      "Needs to be overridden in the derived class \"" + calling_class_name + "\""
   );
   return;
}


} // namespace AllegroFlare


