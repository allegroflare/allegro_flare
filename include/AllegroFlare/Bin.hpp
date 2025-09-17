#pragma once


#include <sstream>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <filesystem>
#include <allegro5/allegro5.h> // for ALLEGRO_PATH
#include <AllegroFlare/ConsoleColor.hpp>
#include <AllegroFlare/Logger.hpp>


namespace AllegroFlare
{
   template<class T2, class T>
   class Bin
   {
   public:
      class Record
      {
      public:
         T2 identifier;
         ALLEGRO_PATH *file_path;
         T data;
         bool preloaded;

         Record(T2 identifier, ALLEGRO_PATH *file_path, T data);
         ~Record();
      };

      // TODO: Rename this to "output_on_destruction_events" or something similar
      void set_cout_record_names_on_clear(bool cout_record_names_on_clear=false);

      Bin(std::string type="Bin");
      void set_path(std::string directory); // <- hmm
      void set_full_path(std::string directory); // <- hmm
      bool is_initialized();
      std::string get_path(bool use_native_path_sep=false);
      virtual ~Bin(); // < should this be a pure virtual funcion that requires clear()?
      Record *get_record(T2 identifier);
      T get(T2 identifier);
      T auto_get(T2 identifier);
      bool preload(T2 identifier_and_filename);
      bool preload(T2 identifier, std::string filename);
      bool load(T2 identifier, std::string filename, std::string called_through="load");
      bool include(T2 identifier, T data);
      bool rename(T2 identifier, T2 new_identifer);
      bool exists(T2 identifier);
      bool destroy(T2 identifier);
      void clear(); //< doesn't work as a base class function in the destructor
      int size();
      virtual T load_data(T2 identifier) = 0;
      virtual void destroy_data(T) = 0;
      virtual bool validate() = 0;
      std::string get_str();
      T operator[](const T2 &identifier); // this is equivelent to auto_get()

      // TODO: virtual T clone(T2 existing_identifier, T2 new_clone_identifier);

   private:
      std::string type;
      bool initialized;
      void ensure_initialization_or_output_error_message(std::string calling_function_name);
      ALLEGRO_PATH *directory;
      std::vector<Record *> record;
      std::vector<std::string> explode(const std::string &delimiter, const std::string &str);
      bool cout_record_names_on_clear;
   };


   template<class T2, class T>
   static bool bin_record_comp(const typename Bin<T2, T>::Record *b1, const typename Bin<T2, T>::Record *b2)
   {
      return b1->identifier.compare(b2->identifier) < 0;
   }


   template<class T2, class T>
   Bin<T2, T>::Bin(std::string type)
      : type(type)
      , initialized(false)
      , directory(nullptr)
      , record()
      , cout_record_names_on_clear(false)
   {}


   template<class T2, class T>
   Bin<T2, T>::~Bin()
   {}


   template<class T2, class T>
   Bin<T2, T>::Record::Record(T2 identifier, ALLEGRO_PATH *file_path, T data)
      : identifier(identifier)
      , file_path(file_path)
      , data(data)
      , preloaded(false)
   {
      //std::cout << "Bin::Record created -> " << identifier << std::endl;
   }


   template<class T2, class T>
   Bin<T2, T>::Record::~Record()
   {
      // NOTE: This here could be a reason why allegro blows up if the bins are not cleared
      // TODO: Investigate the above comment
      if (file_path) al_destroy_path(file_path);
      // destroy T?
   }


   template<class T2, class T>
   std::string Bin<T2, T>::get_path(bool use_native_path_sep)
   {
      if (!directory) return ""; // TODO: consider throwing error
      return al_path_cstr(directory, use_native_path_sep ? ALLEGRO_NATIVE_PATH_SEP : '/');
   }


   template<class T2, class T>
   void Bin<T2, T>::set_path(std::string path)
   {
      std::vector<std::string> path_parts = explode("/", path);
      if (directory) al_destroy_path(directory);
      char *current_path = al_get_current_directory();
      if (!current_path)
      {
         throw std::runtime_error("[AllegroFlare::Bin::set_path]: critical error: could not get the current path.");
      }
      directory = al_create_path_for_directory(current_path);
      al_free(current_path);

      //directory = al_get_standard_path(ALLEGRO_RESOURCES_PATH);
      for (std::vector<std::string>::iterator it=path_parts.begin(); it!=path_parts.end(); it++)
      {
         al_append_path_component(directory, it->c_str());
      }
      initialized = true;
   }


   template<class T2, class T>
   void Bin<T2, T>::set_full_path(std::string path)
   {
      if (directory) al_destroy_path(directory);
      directory = al_create_path_for_directory(path.c_str());
      initialized = true;
   }


   template<class T2, class T>
   bool Bin<T2, T>::is_initialized()
   {
      return initialized;
   }


   template<class T2, class T>
   typename Bin<T2, T>::Record *Bin<T2, T>::get_record(T2 identifier)
   {
      ensure_initialization_or_output_error_message(__FUNCTION__);

      int first, last, mid, comp;

      if (record.empty()) return NULL;

      first = 0;
      last = record.size()-1;

      while (first <= last)
      {
         mid = (first + last) / 2;  // compute mid point.
         comp = record[mid]->identifier.compare(identifier);

         if (comp < 0) first = mid + 1;  // repeat search in top half.
         else if (comp > 0) last = mid - 1; // repeat search in bottom half.
         else return record.at(mid);     // found it. return position
      }

      return NULL;
   }


   template<class T2, class T>
   T Bin<T2, T>::get(T2 identifier)
   {
      Bin<T2, T>::Record *r = get_record(identifier);
      if (r) return r->data;
      std::string class_name = type; //typeid(*this).name();
      std::cout << CONSOLE_COLOR_RED
                << "["
                << class_name
                << "::"
                << __FUNCTION__
                << "] could not load \""
                << identifier
                << "\""
                << CONSOLE_COLOR_DEFAULT
                << std::endl;
      return NULL;
   }


   template<class T2, class T>
   T Bin<T2, T>::auto_get(T2 identifier)
   {
      Bin<T2, T>::Record *r = get_record(identifier);
      if (r) return r->data;

      if (load(identifier, identifier, "auto_get"))
      {
         std::string class_name = type; //typeid(*this).name();
         std::cout << CONSOLE_COLOR_YELLOW << "[" << class_name << "::" << __FUNCTION__  << "] Record \"" << identifier << "\" auto-created" << CONSOLE_COLOR_DEFAULT << std::endl;
         return get(identifier);
      }

      std::string class_name = type; //typeid(*this).name();
      std::cout << CONSOLE_COLOR_RED << "[" << class_name << "::" << __FUNCTION__  << "] could not load \"" << identifier << "\"" << CONSOLE_COLOR_DEFAULT << std::endl;
      return NULL;
   }


   template<class T2, class T>
   bool Bin<T2, T>::preload(T2 identifier_and_filename)
   {
      return preload(identifier_and_filename, identifier_and_filename);
   }


   template<class T2, class T>
   bool Bin<T2, T>::preload(T2 identifier, std::string filename)
   {
      bool result = load(identifier, filename, __FUNCTION__);
      Record *r = get_record(identifier);
      if (r) r->preloaded = true;
      return result;
   }


   template<class T2, class T>
   bool Bin<T2, T>::load(T2 identifier, std::string filename, std::string called_through)
   {
      if (called_through == "load")
      {
         std::cout << CONSOLE_COLOR_CYAN // TODO change this to light blue
                   << "[" << type << "::load] Deprecation Warning: Calling \"load\" directly is deprecated on call "
                   << "load(\"" << identifier << "\",\"" << filename << "\"). "
                   << "Please use "
                   << "\"preload\" instead with the same arguments." << CONSOLE_COLOR_DEFAULT
                   << std::endl;
      }

      ALLEGRO_PATH *path = NULL;
      Bin<T2, T>::Record *r = get_record(identifier);
      if (r) return false;

      if (directory)
      {
         path = al_clone_path(directory);
         al_set_path_filename(path, filename.c_str()); //<- should probably be append_path_thing
      }

      r = new Bin<T2, T>::Record(identifier, path, load_data(al_path_cstr(path, ALLEGRO_NATIVE_PATH_SEP)));
      //r->identifier = identifier;
      //r->file_path = path;
      //std::cout << "4";
      //r->data = load_data(al_path_cstr(r->file_path, ALLEGRO_NATIVE_PATH_SEP));

      //std::cout << "4";

      if (!r->data)
      {
         std::string class_name = type; //typeid(*this).name();
         std::cout << CONSOLE_COLOR_RED
                   << "[" << class_name << "::" << called_through << "] "
                   << "could not load \"" << identifier << "\" "
                   << "while looking in path \"" << al_path_cstr(path, ALLEGRO_NATIVE_PATH_SEP) << "\" while working "
                   << "in path \"" << std::filesystem::current_path().string() << "\". "
                   << "Will continue with process but most likely a crash will occur going forward."
                   << CONSOLE_COLOR_DEFAULT << std::endl;
         //return NULL;
      }

      record.push_back(r);
      std::sort(record.begin(), record.end(), bin_record_comp<T2, T>);

      if (!r->data) return false;
      return true;
   }


   template<class T2, class T>
   bool Bin<T2, T>::exists(T2 identifier)
   {
      return get_record(identifier) != nullptr;
   }


   template<class T2, class T>
   void Bin<T2, T>::set_cout_record_names_on_clear(bool cout_record_names_on_clear)
   {
      this->cout_record_names_on_clear = cout_record_names_on_clear;
   }


   template<class T2, class T>
   bool Bin<T2, T>::include(T2 identifier, T data)
   {
      // check if the record already exists
      Bin<T2, T>::Record *r = get_record(identifier);
      if (r) return false;

      // create a new record
      r = new Bin<T2, T>::Record(identifier, NULL, data);
      record.push_back(r);

      // sort
      std::sort(record.begin(), record.end(), bin_record_comp<T2, T>);

      // return success or failure
      if (!r->data) return false;
      return true;
   }


   template<class T2, class T>
   bool Bin<T2, T>::rename(T2 identifier, T2 new_identifer)
   // be sure to test this
   {
      Bin<T2, T>::Record *r = get_record(identifier);
      if (!r) return false;

      r->identifier = new_identifer;

      std::sort(record.begin(), record.end(), bin_record_comp<T2, T>);

      return true;
   }


   template<class T2, class T>
   bool Bin<T2, T>::destroy(T2 identifier)
   // be sure to test this
   {
      // Get the record
      Bin<T2, T>::Record *r = get_record(identifier);
      if (!r) return false;

      // Find the element in the vector
      typename std::vector<Bin<T2, T>::Record *>::iterator it = std::find(record.begin(), record.end(), r);
      if (it == record.end())
      {
         // Record was not found
         // TODO: output error here
         return false;
      }

      // TODO: Fix this error message
      //std::cout << "[Bin:] Erasing data for identifier \"" << identifier << "\"." << std::flush;

      std::string class_name = type; //typeid(*this).name();
      std::string info_message = AllegroFlare::Logger::build_info_message(
         class_name + "::" + __FUNCTION__,
         "Erasing data for identifier \"" + identifier + "\"."
      );

      std::cout << info_message << std::endl;

      // Destroy the data in the record, and destroy the record itself
      destroy_data(r->data);
      delete r;

      // Remove the element from the vector
      record.erase(it);

      std::sort(record.begin(), record.end(), bin_record_comp<T2, T>); // This may not be necessary

      return true;
   }


   template<class T2, class T>
   void Bin<T2, T>::clear()
   {
      // hmm... this function doesn't work if you place it in this base class's destructor
      // the derived class is destructed before this base class.  destroy_data is a pure virtual function
      // from the derived class.
      int num_records = record.size();
      //int current_record_num = 1;

      if (cout_record_names_on_clear)
      {
         std::cout << "[" << type << "::" << __FUNCTION__  << "] Info: Destroying " << num_records << " records (";
      }
      for (typename std::vector<Bin<T2, T>::Record *>::iterator it=record.begin(); it!=record.end(); it++)
      {
         if (cout_record_names_on_clear) std::cout << "\"" << (*it)->identifier << "\", " << std::flush;
         destroy_data((*it)->data);
         delete (*it);
         //current_record_num++;
      }
      if (cout_record_names_on_clear)
      {
         std::cout << ")" << std::endl << std::flush;
      }

      record.clear();
      record.shrink_to_fit(); // This call to "shrink_to_fit" is used so that all memory that is allocated by the bin
                              // is deallocated as well (specifically including the space allocated in this vector).
                              // However, the C++ standard does not *guarantee* that the capacity will actually be
                              // reduced here with this call to "shrink_to_fit", which is the purpose of this function.
                              // For our purposes here however, it's specifically for testing, and works on the
                              // development platforms.
   }


   template<class T2, class T>
   int Bin<T2, T>::size()
   {
      return record.size();
   }


   template<class T2, class T>
   std::string Bin<T2, T>::get_str()
   {
      std::stringstream result;
      result << "Bin dump" << std::endl;
      for (unsigned i=0; i<record.size(); i++)
         result << i << ": " << record[i]->identifier;
      return result.str();
   }


   template<class T2, class T>
   T Bin<T2, T>::operator[](const T2 &identifier)
   {
      return auto_get(identifier);
   }


   template<class T2, class T>
   void Bin<T2, T>::ensure_initialization_or_output_error_message(std::string calling_function_name)
   {
      if (!initialized)
      {
         std::string classname = type; //typeid(*this).name();
         std::cout
            << CONSOLE_COLOR_RED
            << "["
            << classname
            << ":"
            << calling_function_name
            << "] "
            << "This function is being called prior to the initialization of the bin.  " \
               "This will likely result in a crash.  To remedy this, be sure to set the path " \
               "with \"set_path\" or \"set_full_path\" before use."
            << CONSOLE_COLOR_DEFAULT
            << std::endl;
      }
   }


   template<class T2, class T>
   std::vector<std::string> Bin<T2, T>::explode(const std::string &delimiter, const std::string &str)
   {
      // note: this function skips multiple delimiters, e.g. it will not return return empty tokens
      std::vector<std::string> arr;

      int strleng = str.length();
      int delleng = delimiter.length();
      if (delleng==0)
         return arr;//no change

      int i=0;
      int k=0;
      while(i<strleng)
      {
         int j=0;
         while (i+j<strleng && j<delleng && str[i+j]==delimiter[j])
            j++;
         if (j==delleng)//found delimiter
         {
            arr.push_back(str.substr(k, i-k));
            i+=delleng;
            k=i;
         }
         else
         {
            i++;
         }
      }
      arr.push_back(str.substr(k, i-k));
      return arr;
   }
}


