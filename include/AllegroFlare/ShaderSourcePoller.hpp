#pragma once


#include <allegro5/allegro.h>
#include <filesystem>
#include <string>


namespace AllegroFlare
{
   class ShaderSourcePoller
   {
   private:
      ALLEGRO_EVENT_QUEUE* event_queue;
      std::string vertex_source_filename;
      std::string fragment_source_filename;
      std::string path;
      std::filesystem::file_time_type last_recorded_vertex_source_file_changed_at;
      std::filesystem::file_time_type last_recorded_fragment_source_file_changed_at;
      ALLEGRO_TIMER* polling_timer;
      bool polling_active;
      bool initialized;

   protected:


   public:
      ShaderSourcePoller(ALLEGRO_EVENT_QUEUE* event_queue=nullptr, std::string vertex_source_filename="[unset-vertex_source_filename]", std::string fragment_source_filename="[unset-vertex_source_filename]", std::string path="[unset-path]");
      ~ShaderSourcePoller();

      void set_vertex_source_filename(std::string vertex_source_filename);
      void set_fragment_source_filename(std::string fragment_source_filename);
      void set_path(std::string path);
      ALLEGRO_EVENT_QUEUE* get_event_queue() const;
      std::string get_vertex_source_filename() const;
      std::string get_fragment_source_filename() const;
      std::string get_path() const;
      std::filesystem::file_time_type get_last_recorded_vertex_source_file_changed_at() const;
      std::filesystem::file_time_type get_last_recorded_fragment_source_file_changed_at() const;
      ALLEGRO_TIMER* get_polling_timer() const;
      void set_event_queue(ALLEGRO_EVENT_QUEUE* event_queue=nullptr);
      void initialize();
      void start_polling();
      void stop_polling();
      bool poll();
   };
}



