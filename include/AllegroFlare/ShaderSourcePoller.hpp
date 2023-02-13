#pragma once


#include <filesystem>
#include <string>


namespace AllegroFlare
{
   class ShaderSourcePoller
   {
   private:
      std::string vertex_source_filename;
      std::string fragment_source_filename;
      std::string path;
      std::filesystem::file_time_type last_recorded_vertex_source_file_changed_at;
      std::filesystem::file_time_type last_recorded_fragment_source_file_changed_at;

   protected:


   public:
      ShaderSourcePoller(std::string vertex_source_filename="[unset-vertex_source_filename]", std::string fragment_source_filename="[unset-vertex_source_filename]", std::string path="[unset-path]");
      ~ShaderSourcePoller();

      void set_vertex_source_filename(std::string vertex_source_filename);
      void set_fragment_source_filename(std::string fragment_source_filename);
      void set_path(std::string path);
      std::string get_vertex_source_filename() const;
      std::string get_fragment_source_filename() const;
      std::string get_path() const;
      bool poll();
   };
}



