#pragma once


#include <string>
#include <vector>


namespace AllegroFlare
{
   class ReleaseInfo
   {
   private:
      std::string project_git_hash;
      std::string project_git_timestamp;
      int version_number_major;
      int version_number_minor;
      int version_number_patch;
      std::vector<std::string> version_number_labels;
      std::vector<std::string> version_number_metadata;
      int build_number;
      std::string time_of_build;
      std::string building_platform_os_name;
      std::string building_platform_os_version;
      std::string building_platform_chipset;
      std::string compiler_name;
      std::string compiler_version;
      std::string allegro_version_num;
      std::string allegro_version_git_hash;
      std::string allegro_version_git_timestamp;
      std::string allegro_flare_version_num;
      std::string allegro_flare_version_git_hash;
      std::string allegro_flare_version_git_timestamp;

   protected:


   public:
      ReleaseInfo();
      ~ReleaseInfo();

      void set_project_git_hash(std::string project_git_hash);
      void set_project_git_timestamp(std::string project_git_timestamp);
      void set_version_number_major(int version_number_major);
      void set_version_number_minor(int version_number_minor);
      void set_version_number_patch(int version_number_patch);
      void set_version_number_labels(std::vector<std::string> version_number_labels);
      void set_version_number_metadata(std::vector<std::string> version_number_metadata);
      void set_build_number(int build_number);
      void set_time_of_build(std::string time_of_build);
      void set_building_platform_os_name(std::string building_platform_os_name);
      void set_building_platform_os_version(std::string building_platform_os_version);
      void set_building_platform_chipset(std::string building_platform_chipset);
      void set_compiler_name(std::string compiler_name);
      void set_compiler_version(std::string compiler_version);
      void set_allegro_version_num(std::string allegro_version_num);
      void set_allegro_version_git_hash(std::string allegro_version_git_hash);
      void set_allegro_version_git_timestamp(std::string allegro_version_git_timestamp);
      void set_allegro_flare_version_num(std::string allegro_flare_version_num);
      void set_allegro_flare_version_git_hash(std::string allegro_flare_version_git_hash);
      void set_allegro_flare_version_git_timestamp(std::string allegro_flare_version_git_timestamp);
      std::string get_project_git_hash() const;
      std::string get_project_git_timestamp() const;
      int get_version_number_major() const;
      int get_version_number_minor() const;
      int get_version_number_patch() const;
      std::vector<std::string> get_version_number_labels() const;
      std::vector<std::string> get_version_number_metadata() const;
      int get_build_number() const;
      std::string get_time_of_build() const;
      std::string get_building_platform_os_name() const;
      std::string get_building_platform_os_version() const;
      std::string get_building_platform_chipset() const;
      std::string get_compiler_name() const;
      std::string get_compiler_version() const;
      std::string get_allegro_version_num() const;
      std::string get_allegro_version_git_hash() const;
      std::string get_allegro_version_git_timestamp() const;
      std::string get_allegro_flare_version_num() const;
      std::string get_allegro_flare_version_git_hash() const;
      std::string get_allegro_flare_version_git_timestamp() const;
   };
}



