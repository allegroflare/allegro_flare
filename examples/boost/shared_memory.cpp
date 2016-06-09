



#include <allegro_flare/shared_memory.h>




SharedMemory::SharedMemory(std::string identifier, int size, bool clear_on_launch)
   : identifier(identifier)
   , size(size)
   , shared_memory_object(new boost::interprocess::shared_memory_object(boost::interprocess::open_or_create, identifier.c_str(), boost::interprocess::read_write))
   , mapped_region(NULL)
   , empty_char(' ')
{
   // size it
   shared_memory_object->truncate(size);

   // map it
   mapped_region = new boost::interprocess::mapped_region(*shared_memory_object, boost::interprocess::read_write, 0, size);

   // clear it if needed
   if (clear_on_launch) clear();
}




SharedMemory::~SharedMemory()
{
   // clean up
   shared_memory_object->remove(identifier.c_str());
}




void SharedMemory::write(std::string message)
{
   if ((int)message.length() > size)
   {
      std::cout << "message exceeds shared memory size; truncating." << size << std::endl;
      message.resize(size);
   }

   // clear it (using '\0') as the null char
   std::memset(mapped_region->get_address(), empty_char, mapped_region->get_size());

   // set the memory of the string
   char *mem = static_cast<char*>(mapped_region->get_address());
   for(std::size_t i = 0; i < message.size(); ++i)
   {
      *mem = message[i];
      mem++;
   }
}




void SharedMemory::clear()
{
   char *address = (char *)mapped_region->get_address();
   size_t size = mapped_region->get_size();

   for (size_t i=0; i<size; i++) address[i] = empty_char;
}




bool SharedMemory::is_empty()
{
   char *mem = static_cast<char*>(mapped_region->get_address());
   for(std::size_t i=0; i<mapped_region->get_size(); ++i)
   {
      if (*mem != empty_char) return false;
      mem++;
   }
   return true;
}




bool SharedMemory::write_if_empty(std::string message)
{
   if (!is_empty()) return false;
   write(message);
   return true;
}




std::string SharedMemory::read()
{
   std::string current_content(size, empty_char);
   char *mem = static_cast<char*>(mapped_region->get_address());
   for(std::size_t i = 0; i < mapped_region->get_size(); ++i) current_content[i] = *mem++;
   return current_content;
}




char SharedMemory::get_empty_char()
{
   return empty_char;
}




/*
int main(int argv, char *argc[])
{
   SharedMemoryObject shared_memory_object("shared_message_memory", 256);
}
*/




